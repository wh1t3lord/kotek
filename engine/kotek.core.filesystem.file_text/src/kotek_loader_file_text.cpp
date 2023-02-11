#include "../include/kotek_loader_file_text.h"
#include "../include/kotek_loader_file_text_json.h"
#include "../include/kotek_file_text.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceLoaderFile_Text::ktkResourceLoaderFile_Text(ktkMainManager* p_main_manager) :
	m_p_main_manager{p_main_manager}
{
	this->Register_Loaders();
}

ktkResourceLoaderFile_Text::~ktkResourceLoaderFile_Text()
{
	this->Delete_Loaders();
}

ktk::any ktkResourceLoaderFile_Text::Load(const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(this->m_p_main_manager,
		"you must initialize main manager for this loader");

	KOTEK_ASSERT(path.empty() == false,
		"you can't pass an empty string of your path to file!");

	auto* p_validation = this->Get_Loader(path.extension());

	KOTEK_ASSERT(p_validation,
		"this class doesn't support your file format: [{}]", path.extension());

	ktk::any result = p_validation->Load(path);

	return result;
}

bool ktkResourceLoaderFile_Text::Load(
	const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
{
	KOTEK_ASSERT(this->m_p_main_manager,
		"you must initialize main manager for this loader");

	KOTEK_ASSERT(path.empty() == false,
		"you can't pass an empty string of your path to file!");

	// in scenario if we have only one loader (because it handles all
	// 'different' formats (at least for their formal namings)) you just need to
	// validate your pointer or just be sure that Get_Loader method returned
	// instance, if it returns nullptr it means that your format is not
	// supported by this class

	auto* p_validation = this->Get_Loader(path.extension());

	KOTEK_ASSERT(p_validation,
		"this class doesn't support your file format: [{}]", path.extension());

	bool result = p_validation->Load(path, object_from_construct);

	return result;
}

ktk::cstring ktkResourceLoaderFile_Text::Get_UserDescription(void) const noexcept
{
	return KOTEK_TEXT("this is loader for Text files");
}

Core::eResourceLoadingType ktkResourceLoaderFile_Text::Get_Type(void) const noexcept
{
	return eResourceLoadingType::kText;
}

bool ktkResourceLoaderFile_Text::DetectTypeByFullPath(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(
		path.empty() == false, "you must pass a not empty path to file!");

	KOTEK_ASSERT(path.has_extension(),
		"you must have extension for your file, supported extensions "
		"for analyze: [{}]",
		this->Get_AllSupportedFormats());

    return this->m_loaders.find(reinterpret_cast<const char*>(path.extension().u8string().c_str())) !=
		this->m_loaders.end();
}

ktkIResourceLoader* ktkResourceLoaderFile_Text::Get_Loader(
	const ktk::filesystem::path& extension_of_file) noexcept
{
	KOTEK_ASSERT(extension_of_file.empty() == false,
		"your extension is an empty string");

	Core::ktkIResourceLoader* p_result{};
    if (this->m_loaders.find(reinterpret_cast<const char*>(extension_of_file.u8string().c_str())) ==
		this->m_loaders.end())
		return p_result;

    p_result = this->m_loaders.at(reinterpret_cast<const char*>(extension_of_file.u8string().c_str()));

	KOTEK_ASSERT(p_result,
		"your m_loaders field contains invalid pointer of loader instance");

	return p_result;
}

ktk::cstring ktkResourceLoaderFile_Text::Get_AllSupportedFormats(void) const noexcept
{
    ktk::cstring result;
	for (const auto& [format_name, p_loader] : this->m_loaders)
	{
		result += format_name;
        result += KOTEK_TEXT(" ; ");
	}

    result.pop_back();
    result.pop_back();
    result.pop_back();

	return result;
}

void ktkResourceLoaderFile_Text::Register_Loaders(void) noexcept 
{
    this->m_loaders[KOTEK_TEXT(".json")] = new ktkLoaderFile_JSON(this->m_p_main_manager);
}

void ktkResourceLoaderFile_Text::Delete_Loaders(void) noexcept 
{
	for (const auto& [loader_name, p_loader] : this->m_loaders)
	{
#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("deleting loader: {}", p_loader->Get_UserDescription());
#endif

		delete p_loader;
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
