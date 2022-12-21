#pragma once

#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.io/include/kotek_core_containers_io.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkFileSystem;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

constexpr const char* kFormatFile_Text = ".json";

// TODO: think about save and load operations, because it manages
// resource manager and its loader and saver managers
class ktkFileText
{
public:
	ktkFileText(void);
	ktkFileText(const ktkFileText& instance);
	ktkFileText(const ktk::string& file_name);
	ktkFileText& operator=(const ktkFileText& instance);
	~ktkFileText(void);

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

	const ktk::json::object& Get_Json(void) const noexcept;

	bool IsKeyExist(const ktk::string& field_name) const noexcept;

	/**
	 * Template for specifying types for writting in field in json.
	 *
	 * \param field_name the field name in json.
	 * \param data your specified DataType.
	 * \return void
	 */
	template <typename DataType>
	void Write(const ktk::string& field_name, DataType data) noexcept
	{
		this->m_json.Write<DataType>(field_name, data);
	}

	/**
	 * Getter of m_file_name field.
	 *
	 * \return m_file_name field of class. Possible output as
	 * "something.kFormatFile_Text" (see kFormatFile_Text constant in
	 * header kotek_file_text.h)
	 */
	const ktk::string& Get_FileName(void) const noexcept;

	/**
	 * Set file name to m_file_name field in class.
	 * When string is passed to this method the m_file_name adds with
	 * kFormatFile_Text. So if you wanted to specify the format you
	 * don't need to write the string like "mytextfile.someformat". You
	 * just write and pass only the string of file name WITHOUT format.
	 * Otherwise you will get a such result when you pass the following
	 * string "example.txt" -> "example.txt.kFormatFile_Text" (see
	 * kFormatFile_Text constant in header kotek_file_text.h), it is not
	 * right and keep that in mind.
	 *
	 * \param file_name your string that specifies the name of file
	 * \param is_apply_format means that after your file_name will be applied by
	 * format what this class accepts. For example if file_name="kek" then the
	 * final name will be kek.json if is_apply_format=true \return void
	 */
	void Set_FileName(
		const ktk::string& file_name, bool is_apply_format = true) noexcept;

	/**
	 * Setter for m_json field in class.
	 *
	 * \param data your ktkJson instance that will be assigned to m_json
	 * field. \return void
	 */
	void Set_Json(const ktkJson& data) noexcept;

	/**
	 * You will get a string that contains all information about the
file. It means you will get the file as string like
	 * {
	        "employee": {
	        "name": "sonoo",
	        "salary": 56000,
	        "married": true.
	        }
	   }
	 * So all that thing will be as ktk::string. It needs for
serializing when you save your file through Saver of Resource Manager.
	 * \return
	 */
	ktk::string Get_FileAsSerializedString(void) const noexcept;

private:
	ktkJson m_json;
	ktk::string m_file_name;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
