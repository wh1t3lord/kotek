#include "../include/kotek_loader_model.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkLoaderModel_CGLTF::ktkLoaderModel_CGLTF(Core::ktkIFileSystem* p_filesystem) :
	m_p_filesystem{p_filesystem}
{
	// probably it is expected that your engine could support many formats so in
	// that case you just register your final classes that contains Load method
	// as implementation of your loading algorithm for specified file format
	// In such scenario where you just have only one place for loading (e.g.
	// library that handles that) you just register 'yourself' in order to load
	// the library

	// TODO: create ktkLoaderModel class that will register this class, the code
	// below is not corrected because we need to register it to final instance
	// of all loader's of specified type like models and etc
	this->m_loaders[".gltf"] = this;
	this->m_loaders[".glb"] = this;
}

ktkLoaderModel_CGLTF::ktkLoaderModel_CGLTF(void) : m_p_filesystem{} {}

ktkLoaderModel_CGLTF::~ktkLoaderModel_CGLTF(void) {}

ktk::any ktkLoaderModel_CGLTF::Load(const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(this->m_p_filesystem,
		"you must initialize file system for this loader");

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

	ktk::any result;

	return result;
}

bool ktkLoaderModel_CGLTF::Load(
	const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
{
	KOTEK_ASSERT(this->m_p_filesystem,
		"you must initialize file system for this loader");

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

	bool result{};

	return result;
}

const ktk::string& ktkLoaderModel_CGLTF::Get_UserDescription(
	void) const noexcept
{
	return KOTEK_TEXT("this is loader based on cgltf library for "
					  "loading glTF 2.0 models (.glb, .gltf)");
}

Core::eResourceLoadingType ktkLoaderModel_CGLTF::Get_Type(void) const noexcept
{
	return Core::eResourceLoadingType::kModel;
}

bool ktkLoaderModel_CGLTF::DetectTypeByFullPath(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(
		path.empty() == false, "you must pass a not empty path to file!");

	KOTEK_ASSERT(path.has_extension(),
		"you must have extension for your file, supported extensions "
		"for analyze: [{}]",
		this->Get_AllSupportedFormats());

	return this->m_loaders.find(path.extension().c_str()) !=
		this->m_loaders.end();
}

Core::ktkIResourceLoader* ktkLoaderModel_CGLTF::Get_Loader(
	const ktk::filesystem::path& extension_of_file) noexcept
{
	KOTEK_ASSERT(extension_of_file.empty() == false,
		"your extension is an empty string");

	Core::ktkIResourceLoader* p_result{};
	if (this->m_loaders.find(extension_of_file.c_str()) ==
		this->m_loaders.end())
		return p_result;

	p_result = this->m_loaders.at(extension_of_file.c_str());

	KOTEK_ASSERT(p_result,
		"your m_loaders field contains invalid pointer of loader instance");

	return p_result;
}

ktk::string ktkLoaderModel_CGLTF::Get_AllSupportedFormats(void) const noexcept
{
	ktk::string result;
	for (const auto& [format_name, p_loader] : this->m_loaders)
	{
		result += format_name;
		result += " ; ";
	}

	result.get_as_is().pop_back();
	result.get_as_is().pop_back();
	result.get_as_is().pop_back();

	return result;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
