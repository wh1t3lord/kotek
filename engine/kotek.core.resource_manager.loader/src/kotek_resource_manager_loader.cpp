#include "../include/kotek_resource_manager_loader.h"

namespace Kotek
{
	namespace Core
	{
		ktkResourceLoaderManager::ktkResourceLoaderManager(void) {}

		ktkResourceLoaderManager::~ktkResourceLoaderManager(void) {}

		void ktkResourceLoaderManager::Initialize(
			ktkIFileSystem* p_manager_filesystem)
		{
			this->m_p_manager_filesystem = p_manager_filesystem;
		}

		void ktkResourceLoaderManager::Shutdown(void) {}

		eResourceLoadingType
		ktkResourceLoaderManager::DetectResourceTypeByFileFormat(
			const ktk::filesystem::path& path) noexcept
		{
			return eResourceLoadingType();
		}

		ktk::any ktkResourceLoaderManager::Load_Text(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Texture(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Model(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Sound(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Video(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_CPlusPlusLibrary(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		bool ktkResourceLoaderManager::Load_Text(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			if (this->m_p_manager_filesystem->IsValidPath(path) == false)
			{
				KOTEK_ASSERT(false, "path is not valid: {}", path.c_str());
				return false;
			}

			ktkFile* p_casted_file =
				std::any_cast<ktkFile*>(object_from_construct);

			KOTEK_ASSERT(p_casted_file,
				"you must have a valid instance of object_from_construct");

			ktkJson json;

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("reading file: {}", path.c_str());
#endif

			ktk::ifstream file(path);

			if (file.good()) 
			{
				ktk::istreambuf_iterator being(file);
				ktk::istreambuf_iterator end;

				ktk::string_legacy content(being, end);

				ktk::json::parser parser;

				ktk::json::error_code code;

				parser.reset();

				parser.write(content, code);

				if (code) 
				{
					KOTEK_MESSAGE(
						"can't parse file status: [{}]", code.message());
				}
				else
				{
					ktk::json::value data = parser.release();

					KOTEK_ASSERT(data.is_object(),
						"your file must be object not a some code of json");

					json = data.as_object();
				}
			}
			else
			{
				KOTEK_MESSAGE("can't read file: {}", path.c_str());
				return false;
			}

			file.close();


			p_casted_file->Set_Json(json);
			p_casted_file->SetFileName(path.filename().string());

			return true;
		}

		bool ktkResourceLoaderManager::Load_Texture(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return true;
		}

		bool ktkResourceLoaderManager::Load_Model(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return true;
		}

		bool ktkResourceLoaderManager::Load_Sound(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return true;
		}

		bool ktkResourceLoaderManager::Load_Video(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return true;
		}
	} // namespace Core
} // namespace Kotek