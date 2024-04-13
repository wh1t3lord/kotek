#include "../include/kotek_loader_file_text_json.h"
#include "../include/kotek_file_text.h"
#include <kotek.core.filesystem/include/kotek_core_filesystem.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkLoaderFile_JSON::ktkLoaderFile_JSON(ktkMainManager* p_main_manager) :
	m_p_main_manager{p_main_manager}
{
}

ktkLoaderFile_JSON::~ktkLoaderFile_JSON() {}

ktk::any ktkLoaderFile_JSON::Load(const ktk_filesystem_path& path) noexcept
{
	if (path.empty())
	{
		KOTEK_MESSAGE("can't load file - path is empty");
		return false;
	}

	if (this->m_p_main_manager->GetFileSystem()->IsValidPath(path) == false)
	{
		KOTEK_MESSAGE("you path is invalid and doesn't exist");
		return false;
	}

	KOTEK_MESSAGE("reading file: {}", path);

	ktkFileText result;

	ktk::ifstream _file(path.c_str());

	if (_file.good())
	{
		ktk::istreambuf_iterator begin(_file);
		ktk::istreambuf_iterator end;

		ktk::ustring content(begin, end);

		ktk::json::parse_options options;
		options.allow_comments = true;
		options.allow_invalid_utf8 = true;
		options.allow_trailing_commas = false;

		ktk::json::parser parser(ktk::json::storage_ptr(), options);

		ktk::json::error_code code;

		parser.reset();

		parser.write(reinterpret_cast<const char*>(content.c_str()), code);

		if (code)
		{
			KOTEK_MESSAGE("can't parse file status[{}]", code.message());
		}
		else
		{
			ktk::json::value data = parser.release();

			KOTEK_ASSERT(data.is_object(),
				"your file must be object not a some code of json");

			result.Set_Json(data.as_object());

			ktk_filesystem_path path_object(path);
#ifdef KOTEK_USE_UNICODE
	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
			result.Set_FileName(reinterpret_cast<const char*>(
				path_object.filename().u8string().c_str()));
	#else
		#if KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 1
			result.Set_FileName(path_object.filename().string().c_str());
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 8
			result.Set_FileName(path_object.filename().u8string().c_str());
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 16
			result.Set_FileName(path_object.filename().u16string().c_str());
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 32
			result.Set_FileName(path_object.filename().u32string().c_str());
		#endif
	#endif
#else
			result.Set_FileName(path_object.filename().string());
#endif
		}
	}
	else
	{
		KOTEK_MESSAGE("can't read file: {}", path);
		return false;
	}

	_file.close();

	return result;
}

bool ktkLoaderFile_JSON::Load(
	const ktk_filesystem_path& path, ktk::any object_from_construct) noexcept
{
	ktkFileText* p_result = std::any_cast<ktkFileText*>(object_from_construct);

	KOTEK_ASSERT(p_result, "ktkFileText* instance must be valid!");

	if (path.empty())
	{
		KOTEK_MESSAGE("can't load file - path is empty");
		return false;
	}

	if (this->m_p_main_manager->GetFileSystem()->IsValidPath(path) == false)
	{
		KOTEK_MESSAGE("you path is invalid and doesn't exist");
		return false;
	}

	KOTEK_MESSAGE("reading file: {}", path);

	ktk::cifstream _file(path.c_str());

	if (_file.good())
	{
		ktk::cistreambuf_iterator begin(_file);
		ktk::cistreambuf_iterator end;

		ktk::cstring content(begin, end);

		ktk::json::parse_options options;
		options.allow_comments = true;
		options.allow_invalid_utf8 = true;
		options.allow_trailing_commas = false;

		ktk::json::parser parser(ktk::json::storage_ptr(), options);

		ktk::json::error_code code;

		parser.reset();

		parser.write(reinterpret_cast<const char*>(content.c_str()), code);

		if (code)
		{
			KOTEK_MESSAGE("can't parse file status[{}]", code.message());
		}
		else
		{
			ktk::json::value data = parser.release();

			KOTEK_ASSERT(data.is_object(),
				"your file must be object not a some code of json");

			p_result->Set_Json(data.as_object());

			ktk_filesystem_path path_object(path);

#ifdef KOTEK_USE_UNICODE
	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
			p_result->Set_FileName(
				reinterpret_cast<const char*>(
					path_object.filename().u8string().c_str()),
				false);
	#else
		#if KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 1
			p_result->Set_FileName(
				path_object.filename().string().c_str(), false);
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 8
			p_result->Set_FileName(
				path_object.filename().u8string().c_str(), false);
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 16
			p_result->Set_FileName(
				path_object.filename().u16string().c_str(), false);
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE == 32
			p_result->Set_FileName(
				path_object.filename().u32string().c_str(), false);
		#endif
	#endif
#else
			p_result->Set_FileName(
				path_object.filename().string().c_str(), false);
#endif
		}
	}
	else
	{
		KOTEK_MESSAGE("can't read file: {}", path);
		return false;
	}

	_file.close();
	return true;
}

ktk::cstring ktkLoaderFile_JSON::Get_UserDescription(void) const noexcept
{
	return KOTEK_TEXTU("loader for JSON files (not GeoJSON)");
}

Core::eResourceLoadingType ktkLoaderFile_JSON::Get_Type(void) const noexcept
{
	return eResourceLoadingType::kText;
}

bool ktkLoaderFile_JSON::DetectTypeByFullPath(
	const ktk_filesystem_path& path) noexcept
{
	return false;
}

ktkIResourceLoader* ktkLoaderFile_JSON::Get_Loader(
	const ktk_filesystem_path& extension_of_file) noexcept
{
	return nullptr;
}

ktk::cstring ktkLoaderFile_JSON::Get_AllSupportedFormats(void) const noexcept
{
	return kFormatFile_Text;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
