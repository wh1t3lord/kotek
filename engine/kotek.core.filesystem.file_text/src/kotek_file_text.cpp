#include "../include/kotek_file_text.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileText::ktkFileText(void) {}

ktkFileText::ktkFileText(const ktkFileText& instance) : m_json(instance.m_json) {}

ktkFileText::ktkFileText(const ktk::string& file_name) : m_file_name(file_name)
{
	this->m_file_name += kFormatFile_Text;
}

ktkFileText& ktkFileText::operator=(const ktkFileText& instance)
{
	this->m_json = instance.m_json;
	return *this;
}

ktkFileText::~ktkFileText(void) {}

/* TODO: implement separated loader and saver classes
bool ktkFileText::Load(
    Core::ktkMainManager& main_manager, const ktk::string& path)
{
    if (path.empty())
    {
        KOTEK_MESSAGE("can't load file - path is empty");
        return false;
    }

    if (main_manager.GetFileSystem()->IsValidPath(path) == false)
    {
        KOTEK_MESSAGE("you path is invalid and doesn't exist");
        return false;
    }

    KOTEK_MESSAGE("reading file: {}", path.get_as_is());

#ifdef KOTEK_PLATFORM_WINDOWS
    ktk::ifstream _file(path.get_as_is().c_str());
#elif defined(KOTEK_PLATFORM_LINUX)
    ktk::ifstream _file(path.get_as_legacy());
#endif

    if (_file.good())
    {
        ktk::istreambuf_iterator begin(_file);
        ktk::istreambuf_iterator end;

        ktk::string_legacy content(begin, end);

        ktk::json::parse_options options;
        options.allow_comments = true;
        options.allow_invalid_utf8 = true;
        options.allow_trailing_commas = false;

        ktk::json::parser parser(ktk::json::storage_ptr(), options);

        ktk::json::error_code code;

        parser.reset();

        parser.write(content, code);

        if (code)
        {
            ktk::string msg(code.message());
            KOTEK_MESSAGE(
                "can't parse file status[{}]", msg.get_as_is());
        }
        else
        {
            ktk::json::value data = parser.release();

            KOTEK_ASSERT(data.is_object(),
                "your file must be object not a some code of json");

            this->m_json = data.as_object();

            ktk::filesystem::path path_object(path);

            this->m_file_name =
                path_object.filename().u32string().c_str();
        }
    }
    else
    {
        KOTEK_MESSAGE("can't read file: {}", path.get_as_is());
        return false;
    }

    _file.close();

    return true;
}

bool ktkFileText::Save(Core::ktkMainManager& main_manager,
    const ktk::string& full_path_to_folder,
    const ktk::string& full_path_to_file, bool is_format)
{
    return this->Save(main_manager.GetFileSystem(), full_path_to_folder,
        full_path_to_file, is_format);
}

bool ktkFileText::Save(
    Core::ktkMainManager& main_manager, const ktk::string& path)
{
    return this->Save(main_manager.GetFileSystem(), path);
}

bool ktkFileText::Save(Core::ktkFileTextSystem* p_file_system,
    const ktk::string& full_path_to_folder,
    const ktk::string& full_path_to_file, bool is_format)
{
    KOTEK_ASSERT(
        p_file_system, "you passed an invalid file system manager");

    if (full_path_to_file.empty())
    {
        KOTEK_ASSERT(false, "invalid path can't write any data");
        return false;
    }

    if (p_file_system->IsValidPath(full_path_to_folder) == false)
    {
        KOTEK_ASSERT(false, "invalid path can't create output file");
        return false;
    }

#ifdef KOTEK_PLATFORM_WINDOWS
    ktk::ofstream output_file(full_path_to_file.get_as_legacy().c_str());
#elif defined(KOTEK_PLATFORM_LINUX)
    KOTEK_ASSERT(false, "not implemented");
    ktk::string_legacy temp_path_output =
        ktk::cast::to_legacy_string(path);
    ktk::ofstream output_file(temp_path_output.c_str());
#endif

    if (is_format == false)
    {
        output_file << this->m_json.Serialize().get_as_is();
    }
    else
    {
        this->PrettyWrite(output_file, this->m_json.GetObject());
    }

    output_file.close();

#ifdef KOTEK_DEBUG
    KOTEK_MESSAGE("file was successfully created: {}",
        full_path_to_file.get_as_is());
#endif

    return true;
}

bool ktkFileText::Save(
    Core::ktkFileSystem* p_file_system, const ktk::string& path)
{
    ktk::string full_path_with_file_and_its_format = path;

    KOTEK_ASSERT(this->m_file_name.empty() == false,
        "can't save file without a name!");

    full_path_with_file_and_its_format.append_path(this->m_file_name);

    return this->Save(p_file_system, path,
        full_path_with_file_and_its_format, true);
}
*/

ktk::string ktkFileText::Get_String(const ktk::string& key_name) const noexcept
{
	return this->m_json.GetString(key_name);
}

const ktk::json::object& ktkFileText::Get_Json(void) const noexcept
{
	return this->m_json.GetObject();
}

bool ktkFileText::IsKeyExist(const ktk::string& field_name) const noexcept
{
	if (field_name.empty())
	{
		KOTEK_MESSAGE("field is empty");
		return false;
	}

	const ktk::json::object& json = this->m_json.GetObject();

	return json.find(field_name.get_as_legacy()) != json.end();
}

const ktk::string& ktkFileText::Get_FileName(void) const noexcept
{
	return this->m_file_name;
}

void ktkFileText::Set_FileName(const ktk::string& file_name) noexcept
{
	this->m_file_name = file_name;
	this->m_file_name += kFormatFile_Text;
}

void ktkFileText::Set_Json(const ktkJson& data) noexcept
{
	this->m_json = data;
}

ktk::string ktkFileText::Get_FileAsSerializedString(void) const noexcept
{
	return this->m_json.Serialize();
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
