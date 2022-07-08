#include "../include/kotek_resource_manager_saver.h"

namespace Kotek
{
	namespace Core
	{
		ktkResourceSaverManager::ktkResourceSaverManager(void) :
			ktkIResourceSaver()
		{}

		ktkResourceSaverManager::~ktkResourceSaverManager(void) {}

		void ktkResourceSaverManager::Initialize(ktkIFileSystem* p_filesystem)
		{
			this->m_p_manager_filesystem = p_filesystem;
		}

		void ktkResourceSaverManager::Shutdown(void) {}

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

			ktkFile* p_casted_file = std::any_cast<ktkFile*>(data);

			KOTEK_ASSERT(
				p_casted_file, "you must have a valid instance of ktkFile");

			KOTEK_ASSERT(p_casted_file->Get_FileName().empty() == false,
				"you can't have an empty filename in your ktkFile instance");

			auto path_compiled = path;

			path_compiled /= p_casted_file->Get_FileName().get_as_is();

			ktk::ofstream output_file(path_compiled);

			output_file
				<< p_casted_file->Get_FileAsSerializedString().get_as_is();

			output_file.close();

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE(
				"file was successfully created: {}", path_compiled.c_str());
#endif

			return true;
		}

		bool ktkResourceSaverManager::Save_Text_Formatted(
			const ktk::filesystem::path& path, ktk::any data) noexcept
		{
			KOTEK_ASSERT(this->m_p_manager_filesystem,
				"you must initialize your filesystem here");

			if (this->m_p_manager_filesystem->IsValidPath(path) == false)
			{
				KOTEK_ASSERT(false, "path is not valid: {}", path.c_str());
				return false;
			}

			ktkFile* p_casted_file = std::any_cast<ktkFile*>(data);

			KOTEK_ASSERT(
				p_casted_file, "you must have a valid instance of ktkFile");

			KOTEK_ASSERT(p_casted_file->Get_FileName().empty() == false,
				"you can't have an empty filename in your ktkFile instance");

			auto path_compiled = path;

			path_compiled /= p_casted_file->Get_FileName().get_as_is();

			ktk::ofstream output_file(path_compiled);

			this->FormatTextFile_Json(output_file, p_casted_file->Get_Json());

			output_file.close();

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("file was successfully created with formatting: {}", path_compiled.c_str());
#endif

			return true;
		}

		void ktkResourceSaverManager::FormatTextFile_Json(ktk::ofstream& file,
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
							 << ktk::json::serialize(it->key()).c_str()
							 << " : ";
						this->FormatTextFile_Json(file, it->value(), indent);
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
						this->FormatTextFile_Json(file, *it, indent);
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
	} // namespace Core
} // namespace Kotek