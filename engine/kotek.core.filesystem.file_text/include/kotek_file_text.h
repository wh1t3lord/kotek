#pragma once

#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.io/include/kotek_core_containers_io.h>

namespace Kotek
{
	namespace Core
	{
		class ktkFileSystem;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		constexpr const char* kFormatFile = ".json";

		// TODO: think about save and load operations, because it manages
		// resource manager and its loader and saver managers
		class ktkFile
		{
		public:
			ktkFile(void);
			ktkFile(const ktkFile& instance);
			ktkFile(const ktk::string& file_name);
			ktkFile& operator=(const ktkFile& instance);
			~ktkFile(void);

			/* TODO: implement separated loader and saver classes 
			bool Load(
				Core::ktkMainManager& main_manager, const ktk::string& path);

			/// <summary>
			/// creates file from ktk::ofstream class
			/// </summary>
			/// <param name="path">your full path where file to create in your
			/// OS</param> <param name="serialized_json_into_string">this is
			/// your valid json which serialize by boost library and serialize
			/// function of that library</param> <returns></returns>
			bool Save(Core::ktkMainManager& main_manager,
				const ktk::string& full_path_to_folder,
				const ktk::string& full_path_to_file, bool is_format = true);

			// file_name without format!!
			bool Save(
				Core::ktkMainManager& main_manager, const ktk::string& path);

			bool Save(Core::ktkFileSystem* p_file_system,
				const ktk::string& full_path_to_folder,
				const ktk::string& full_path_to_file, bool is_format = true);

			bool Save(
				Core::ktkFileSystem* p_file_system, const ktk::string& path);
			*/

			template <typename ReturnType = ktkJson>
			ReturnType Get(const ktk::string& key_name) const noexcept
			{
				return this->m_json.Get<ReturnType>(key_name);
			}

			ktk::string GetString(const ktk::string& key_name) const noexcept;

			const ktk::json::object& GetJson(void) const noexcept;

			bool IsKeyExist(const ktk::string& field_name) const noexcept;

			template <typename DataType>
			void Write(const ktk::string& field_name, DataType data) noexcept
			{
				this->m_json.Write<DataType>(field_name, data);
			}

			template <>
			void Write<const ktk::string&>(
				const ktk::string& field_name, const ktk::string& data) noexcept
			{
				this->m_json.Write<ktk::json::array>(
					field_name, {data.get_as_is()});
			}

#ifdef KOTEK_USE_UNICODE
			template <>
			void Write<const char8_t*>(
				const ktk::string& field_name, const char8_t* p_string) noexcept
			{
				ktk::string str;
				str = p_string;

				this->m_json.Write<ktk::json::array>(
					field_name, {str.get_as_is()});
			}

			template <>
			void Write<const char16_t*>(const ktk::string& field_name,
				const char16_t* p_string) noexcept
			{
				ktk::string str;
				str = p_string;

				this->m_json.Write<ktk::json::array>(
					field_name, {str.get_as_is()});
			}

			template <>
			void Write<const char32_t*>(const ktk::string& field_name,
				const char32_t* p_string) noexcept
			{
				ktk::string str;
				str = p_string;

				this->m_json.Write<ktk::json::array>(
					field_name, {str.get_as_is()});
			}

	#ifdef KOTEK_PLATFORM_WINDOWS
			template <>
			void Write<const wchar_t*>(
				const ktk::string& field_name, const wchar_t* p_string) noexcept
			{
				ktk::string str;
				str = p_string;

				this->m_json.Write<ktk::json::array>(
					field_name, {str.get_as_is()});
			}
	#endif
#endif

			const ktk::string& GetFileName(void) const noexcept;
			void SetFileName(const ktk::string& file_name) noexcept;

		private:
			void PrettyWrite(ktk::ofstream& file, const ktk::json::value& json,
				std::string* indent = nullptr) noexcept;

		private:
			ktkJson m_json;
			ktk::string m_file_name;
		};
	} // namespace Core
} // namespace Kotek
