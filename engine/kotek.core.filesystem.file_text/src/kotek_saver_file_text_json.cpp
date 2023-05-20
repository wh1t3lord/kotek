#include "../include/kotek_saver_file_text_json.h"
#include <kotek.core.filesystem/include/kotek_core_filesystem.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkSaverFile_JSON::ktkSaverFile_JSON(ktkMainManager* p_main_manager) :
	m_p_main_manager{p_main_manager}
{
}

ktkSaverFile_JSON::~ktkSaverFile_JSON() {}

bool ktkSaverFile_JSON::Save(
	const ktk::filesystem::path& path, ktk::any object_for_saving) noexcept
{
	KOTEK_ASSERT(path.has_extension(),
		"you must save with full path aka filename + extension");
	KOTEK_ASSERT(path.has_parent_path(),
		"you must path a FULL path, in this case you just passed a file with "
		"extension without any real path, we can't understand where you want "
		"to save your file on device");

	auto* p_filesystem = this->m_p_main_manager->GetFileSystem();
	KOTEK_ASSERT(p_filesystem, "you must initialize your filesystem here");

	auto folder_where_we_want_to_save = path.parent_path();

	if (p_filesystem->IsValidPath(folder_where_we_want_to_save) == false)
	{
		// if we are here it means that your passed path is really invalid and
		// it is not existed on OS's file system
		KOTEK_MESSAGE_WARNING("path is not valid for saving: [{}]", path);

		return false;
	}

	ktkFileText* p_casted_file = std::any_cast<ktkFileText*>(object_for_saving);

	KOTEK_ASSERT(
		p_casted_file, "you must have a valid instance of ktkFileText");

	KOTEK_ASSERT(p_casted_file->Get_FileName().empty() == false,
		"you can't have an empty filename in your ktkFileText instance");

    ktk::cofstream output_file(path);

	this->FormatTextFile_JSON(output_file, p_casted_file->Get_Json());

	output_file.close();

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("file was successfully created with formatting: {}", path);
#endif

	return true;
}

bool ktkSaverFile_JSON::DetectTypeByFullPath(
	const ktk::filesystem::path& path) noexcept
{
	return false;
}

ktk::cstring ktkSaverFile_JSON::Get_UserDescription() const noexcept
{
	return KOTEK_TEXTU("JSON saver (not GeoJSON)");
}

eResourceLoadingType ktkSaverFile_JSON::Get_Type() const noexcept
{
	return eResourceLoadingType::kText;
}

ktkIResourceSaver* ktkSaverFile_JSON::Get_Saver(
	const ktk::filesystem::path& extension_of_file) noexcept
{
	return nullptr;
}

ktk::cstring ktkSaverFile_JSON::Get_AllSupportedFormats(void) const noexcept
{
	return kFormatFile_Text;
}

void ktkSaverFile_JSON::FormatTextFile_JSON(ktk::cofstream& file,
	const ktk::json::value& json, std::string* indent) noexcept
{
#ifdef KOTEK_USE_BOOST_LIBRARY
	std::string indent_;

	if (!indent)
		indent = &indent_;

	switch (json.kind())
	{
	case ktk::json::kind::object:
	{
		file << "{\n";
		indent->append(4, ' ');
		auto const& obj = json.get_object();
		if (!obj.empty())
		{
			auto it = obj.begin();
			for (;;)
			{
				file << indent->c_str()
					 << ktk::json::serialize(it->key()).c_str() << " : ";
				this->FormatTextFile_JSON(file, it->value(), indent);
				if (++it == obj.end())
					break;
				file << ",\n";
			}
		}
		file << "\n";
		indent->resize(indent->size() - 4);
		file << indent->c_str() << "}";
		break;
	}

	case ktk::json::kind::array:
	{
		file << "[\n";
		indent->append(4, ' ');
		auto const& arr = json.get_array();
		if (!arr.empty())
		{
			auto it = arr.begin();
			for (;;)
			{
				file << indent->c_str();
				this->FormatTextFile_JSON(file, *it, indent);
				if (++it == arr.end())
					break;
				file << ",\n";
			}
		}
		file << "\n";
		indent->resize(indent->size() - 4);
		file << indent->c_str() << "]";
		break;
	}

	case ktk::json::kind::string:
	{
		file << ktk::json::serialize(json.get_string()).c_str();
		break;
	}

	case ktk::json::kind::uint64:
		file << json.get_uint64();
		break;

	case ktk::json::kind::int64:
		file << json.get_int64();
		break;

	case ktk::json::kind::double_:
		file << json.get_double();
		break;

	case ktk::json::kind::bool_:
		if (json.get_bool())
			file << "true";
		else
			file << "false";
		break;

	case ktk::json::kind::null:
		file << "null";
		break;
	}

	if (indent->empty())
		file << "\n";
#else
	KOTEK_ASSERT(false, "not implemented! (nlohmann)");
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
