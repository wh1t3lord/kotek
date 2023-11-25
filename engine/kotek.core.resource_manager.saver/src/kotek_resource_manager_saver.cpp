#include "../include/kotek_resource_manager_saver.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceSaverManager::ktkResourceSaverManager(void) :
	ktkIResourceSaverManager()
{
}

ktkResourceSaverManager::~ktkResourceSaverManager(void) {}

void ktkResourceSaverManager::Initialize(
	ktkIFileSystem* p_filesystem, ktkMainManager* p_main_manager)
{
	this->m_p_manager_filesystem = p_filesystem;

	this->Set_Saver(eResourceLoadingType::kText,
		new ktkResourceSaverFile_Text(p_main_manager));

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	for (unsigned int i = 0; i < KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL;
		 ++i)
	{
		this->m_writers[i].second = true;
	}
#endif
}

void ktkResourceSaverManager::Shutdown(void)
{
	for (auto& [type, saver] : this->m_savers)
	{
		auto* p_saver = saver;

		delete p_saver;
	}

	this->m_savers.clear();

#ifdef KOTEK_DEBUG
	for (auto& [id, pair] : this->m_writers)
	{
		auto is_free = pair.second.load();

		KOTEK_ASSERT(is_free,
			"file is not free, but we do shutdown that means that file is "
			"opened and awaits for writing or currently writes something rn!");
	}
#endif

	this->m_writers.clear();
}

void ktkResourceSaverManager::Set_Saver(
	eResourceLoadingType resource_type, ktkIResourceSaver* p_saver)
{
	KOTEK_ASSERT(p_saver, "you can't pass an invalid pointer here");

	KOTEK_ASSERT(p_saver->Get_Type() != eResourceLoadingType::kUnknown,
		"you must override Get_Type method because it uses default return "
		"type. It is not acceptable because developer must strictly specify "
		"what its instance contains and for what it was created");

	if (this->m_savers.find(resource_type) != this->m_savers.end())
	{
		KOTEK_MESSAGE_WARNING(
			"you try to replace resource loader for type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));

		delete this->m_savers[resource_type];
		this->m_savers[resource_type] = nullptr;
	}

	this->m_savers[resource_type] = p_saver;
}

ktkIResourceSaver* ktkResourceSaverManager::Get_Saver(
	eResourceLoadingType resource_type) const noexcept
{
	KOTEK_ASSERT(resource_type != eResourceLoadingType::kUnknown,
		"you must pass a valid enum");

	ktkIResourceSaver* p_result{};

	if (this->m_savers.find(resource_type) != this->m_savers.end())
	{
		p_result = this->m_savers.at(resource_type);

		KOTEK_ASSERT(p_result->Get_Type() == resource_type,
			"you must specify correct type of what you saving: [{}], because "
			"your saver has [{}]",
			helper::Translate_ResourceLoadingType(resource_type),
			helper::Translate_ResourceLoadingType(p_result->Get_Type()));

		if (p_result->Get_Type() != resource_type)
			p_result = nullptr;
	}

	if (p_result == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"couldn't obtain loader for resource saving type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));
	}

	return p_result;
}

bool ktkResourceSaverManager::Save(
	const ktk::filesystem::path& path, ktk::any data) noexcept
{
	KOTEK_ASSERT(path.has_extension(),
		"you must provide an extension for your file: [{}]", path);

	bool result{};

	auto resource_type = this->DetectResourceTypeByFileFormat(path);

	auto* p_saver = this->Get_Saver(resource_type);

	KOTEK_ASSERT(p_saver, "failed to find saver for format file: [{}]",
		path.extension());

	if (p_saver)
		result = p_saver->Save(path, data);

	return result;
}

bool ktkResourceSaverManager::Open(const ktk::filesystem::path& path,
	eResourceWritingType resource_type, eResourceWritingPolicy policy,
	eResourceWritingMode mode, ktk::uint32_t id) noexcept
{
	KOTEK_ASSERT(path.empty() == false, "you must pass a not empty path!");
	KOTEK_ASSERT(
		resource_type != eResourceWritingType::kUnknown, "must be defined!");
	KOTEK_ASSERT(
		policy != eResourceWritingPolicy::kEndOfEnum, "must be defined!");
	KOTEK_ASSERT(mode != eResourceWritingMode::kEndOfEnum, "must be defined!");
	KOTEK_ASSERT(id != ktk::uint32_t(-1), "must be valid!");
	KOTEK_ASSERT(this->m_p_manager_filesystem,
		"you must initialize file system before calling this method!");
	KOTEK_ASSERT(this->m_writers.find(id) != this->m_writers.end(),
		"failed to find file by its id: [{}]", id);

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	bool result{};

	switch (resource_type)
	{
	case eResourceWritingType::kText:
	{
		KOTEK_ASSERT(path.has_extension() == true, "must have extension");
		KOTEK_ASSERT(
			path.extension().string().find("json") != std::string::npos,
			"must have a such name");

		auto* file = &this->m_writers.at(id).first;

		auto is_already_opened = this->m_writers.at(id).second.load();

		std::ios_base::openmode om = -1;

		switch (mode)
		{
		case eResourceWritingMode::kNew:
		{
			om = std::ios::in | std::ios::out | std::ios::trunc;
			break;
		}
		case eResourceWritingMode::kAppend:
		{
			om = std::ios::app;
			break;
		}
		default:
		{
			KOTEK_ASSERT(false, "unknown openmode");
			break;
		}
		}

		file->open(path, om);
		result = file->good();
		KOTEK_ASSERT(result, "failed to open file: [{}]; error: {}", path, strerror(errno));

		this->m_writers.at(id).second = false;

		break;
	}
	}

	return result;
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, const char* p_string) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file << p_string;
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, const char* p_string, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file.write(p_string, size);
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, const unsigned char* p_raw_memory) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file << p_raw_memory;
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const unsigned char* p_raw_memory, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such file!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file.write((char*)&p_raw_memory[0], size);
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::int32_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file << value;
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::float_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file << value;
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::double_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file << value;
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::int32_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::uint32_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::float_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::double_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::int8_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};
	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::int16_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::uint16_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	ktk::cfstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id).first;
	}

	if (p_file)
	{
		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	Core::eFileWritingControlCharacterType type) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such file: {}", resource_id);

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		switch (type)
		{
		case Core::eFileWritingControlCharacterType::kSpace:
		{
			file << " ";
			break;
		}
		case Core::eFileWritingControlCharacterType::kNewLine:
		{
			file << std::endl;
			break;
		}
		case Core::eFileWritingControlCharacterType::kFlush:
		{
			file << std::flush;
			break;
		}
		default:
		{
			KOTEK_ASSERT(false,
				"engine doesn't implement default character, pass something "
				"exact");
			break;
		}
		}
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::size_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		file << value;
	}
}

void ktkResourceSaverManager::Seekg(
	ktk::uint32_t resource_id, ktk::size_t bytes, eFileSeekDirectionType type)
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such file: {}", resource_id);
	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		KOTEK_ASSERT(this->m_writers.at(resource_id).second == false,
			"file must be in state for writing!");

		std::ios_base::seekdir direction;

		switch (type)
		{
		case Core::eFileSeekDirectionType::kSeekdDirectionCurrent:
		{
			direction = std::ios::cur;
			break;
		}
		case Core::eFileSeekDirectionType::kSeekDirectionBegin:
		{
			direction = std::ios::beg;
			break;
		}
		case Core::eFileSeekDirectionType::kSeekDirectionEnd:
		{
			direction = std::ios::end;
			break;
		}
		}

		file.seekg(bytes, direction);
	}
}

ktk::size_t ktkResourceSaverManager::Tellp(ktk::uint32_t resource_id)
{
	ktk::size_t result{};

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such file: {}", resource_id);

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		result = file.tellp();
	}

	return result;
}

ktk::size_t ktkResourceSaverManager::Tellg(ktk::uint32_t resource_id)
{
	ktk::size_t result{};

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such file: {}", resource_id);

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;

		result = file.tellg();
	}

	return result;
}

void ktkResourceSaverManager::Read(
	ktk::uint32_t resource_id, char* p_buffer, ktk::size_t size)
{
	KOTEK_ASSERT(resource_id != ktk::uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(p_buffer, "must be valid!");

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id).first;
		file.read(p_buffer, size);
	}
}

bool ktkResourceSaverManager::Close(ktk::uint32_t id) noexcept
{
	KOTEK_ASSERT(id != ktk::uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(this->m_writers.empty() == false, "early calling!");

	ktk::mt::lock_guard<ktk::mt::mutex> lock_guard{this->m_mutex};

	bool result{};

	if (this->m_writers.empty() == false)
	{
		if (this->m_writers.find(id) != this->m_writers.end())
		{
			KOTEK_ASSERT(this->m_writers.at(id).second == false,
				"you try to close the file that was closed or not even "
				"opened!");

			this->m_writers.at(id).first.close();
			// we set this file that it is 'freed' for writing
			this->m_writers.at(id).second = true;
			KOTEK_MESSAGE("closed file: {}", id);
			result = true;
		}
	}

	return result;
}

ktk::uint32_t ktkResourceSaverManager::GenerateFileID(void) noexcept
{
	KOTEK_ASSERT(this->m_writers.empty() == false,
		"you must initialize your file pool!");

	// this means that if result equals to
	// KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL it means value is invalid
	// because we initialize from [0,
	// KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL - 1]
	ktk::uint32_t result{KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL};

#ifdef KOTEK_DEBUG
	bool is_any_avaiable = false;
#endif

	for (const auto& [id, pair] : this->m_writers)
	{
		bool is_available = pair.second;

		if (is_available)
		{
			result = id;

#ifdef KOTEK_DEBUG
			is_any_avaiable = true;
#endif
			break;
		}
	}

	this->m_writers.at(result).second = false;

#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(is_any_avaiable,
		"failed to obtain any avaiable file for writing. It means that engine "
		"doesn't have any freed file, allocate more! Current file pool size "
		"is: [{}]",
		KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL);
#endif

	return result;
}

eResourceLoadingType ktkResourceSaverManager::DetectResourceTypeByFileFormat(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(this->m_savers.empty() == false,
		"you must provide some loaders. Otherwise loaders are empty thus "
		"loader manager is invalid!");

	eResourceLoadingType result{eResourceLoadingType::kUnknown};

	for (const auto& [resource_type, p_saver] : this->m_savers)
	{
		bool status = p_saver->DetectTypeByFullPath(path);

		if (status == false)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("Determing format type of file and it is not: {}",
				helper::Translate_ResourceLoadingType(p_saver->Get_Type()));
#endif
		}
		else
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE(
				"Obtained type by loader: {}", p_saver->Get_UserDescription());
#endif

			result = p_saver->Get_Type();
			break;
		}
	}

	KOTEK_ASSERT(result != eResourceLoadingType::kUnknown,
		"you didn't provide any detector for a format file: {}",
		reinterpret_cast<const char*>(path.extension().u8string().c_str()));

	return result;
}

/*
bool ktkResourceSaverManager::Save_Text(
    const ktk::filesystem::path& path, ktk::any data) noexcept
{
    KOTEK_ASSERT(this->m_p_manager_filesystem,
        "you must initialize your file system here");

    if (this->m_p_manager_filesystem->IsValidPath(path) == false)
    {
        KOTEK_ASSERT(false, "path is not valid: {}", path.c_str());
        return false;
    }

    ktkFileText* p_casted_file = std::any_cast<ktkFileText*>(data);

    KOTEK_ASSERT(
        p_casted_file, "you must have a valid instance of ktkFileText");

    KOTEK_ASSERT(p_casted_file->Get_FileName().empty() == false,
        "you can't have an empty filename in your ktkFileText instance");

    auto path_compiled = path;

    path_compiled /= p_casted_file->Get_FileName().get_as_is();

    ktk::ofstream output_file(path_compiled);

    output_file << p_casted_file->Get_FileAsSerializedString().get_as_is();

    output_file.close();

#ifdef KOTEK_DEBUG
    KOTEK_MESSAGE("file was successfully created: {}", path_compiled.c_str());
#endif

    return true;
}

bool ktkResourceSaverManager::Save_Text_Formatted(
    const ktk::filesystem::path& path, ktk::any data) noexcept
{

}

void ktkResourceSaverManager::FormatTextFile_Json(ktk::ofstream& file,
    const ktk::json::value& json, std::string* indent) noexcept
{

}
*/

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK