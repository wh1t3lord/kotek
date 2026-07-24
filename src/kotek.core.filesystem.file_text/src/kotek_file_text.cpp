#include "../include/kotek_file_text.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/* TODO: implement separated loader and saver classes
bool ktkResourceText::Load(
    Core::ktkMainManager& main_manager, const ktk::ustring&
path)
{
    if (path.empty())
    {
        KOTEK_MESSAGE("can't load file - path is empty");
        return false;
    }

    if (main_manager.GetFileSystem()->IsValidPath(path) ==
false)
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

        ktk::json::parser parser(ktk::json::storage_ptr(),
options);

        ktk::json::error_code code;

        parser.reset();

        parser.write(content, code);

        if (code)
        {
            ktk::ustring msg(code.message());
            KOTEK_MESSAGE(
                "can't parse file status[{}]", msg.get_as_is());
        }
        else
        {
            ktk::json::value data = parser.release();

            KOTEK_ASSERT(data.is_object(),
                "your file must be object not a some code of
json");

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

bool ktkResourceText::Save(Core::ktkMainManager& main_manager,
    const ktk::ustring& full_path_to_folder,
    const ktk::ustring& full_path_to_file, bool is_format)
{
    return this->Save(main_manager.GetFileSystem(),
full_path_to_folder, full_path_to_file, is_format);
}

bool ktkResourceText::Save(
    Core::ktkMainManager& main_manager, const ktk::ustring&
path)
{
    return this->Save(main_manager.GetFileSystem(), path);
}

bool ktkResourceText::Save(Core::ktkResourceTextSystem*
p_file_system, const ktk::ustring& full_path_to_folder, const
ktk::ustring& full_path_to_file, bool is_format)
{
    KOTEK_ASSERT(
        p_file_system, "you passed an invalid file system
manager");

    if (full_path_to_file.empty())
    {
        KOTEK_ASSERT(false, "invalid path can't write any
data"); return false;
    }

    if (p_file_system->IsValidPath(full_path_to_folder) ==
false)
    {
        KOTEK_ASSERT(false, "invalid path can't create output
file"); return false;
    }

#ifdef KOTEK_PLATFORM_WINDOWS
    ktk::ofstream
output_file(full_path_to_file.get_as_legacy().c_str()); #elif
defined(KOTEK_PLATFORM_LINUX) KOTEK_ASSERT(false, "not
implemented"); ktk::string_legacy temp_path_output =
        ktk::cast::to_legacy_string(path);
    ktk::ofstream output_file(temp_path_output.c_str());
#endif

    if (is_format == false)
    {
        output_file << this->m_json.Serialize().get_as_is();
    }
    else
    {
        this->PrettyWrite(output_file,
this->m_json.GetObject());
    }

    output_file.close();

#ifdef KOTEK_DEBUG
    KOTEK_MESSAGE("file was successfully created: {}",
        full_path_to_file.get_as_is());
#endif

    return true;
}

bool ktkResourceText::Save(
    Core::ktkFileSystem* p_file_system, const ktk::ustring&
path)
{
    ktk::ustring full_path_with_file_and_its_format = path;

    KOTEK_ASSERT(this->m_file_name.empty() == false,
        "can't save file without a name!");

    full_path_with_file_and_its_format.append_path(this->m_file_name);

    return this->Save(p_file_system, path,
        full_path_with_file_and_its_format, true);
}
*/

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
