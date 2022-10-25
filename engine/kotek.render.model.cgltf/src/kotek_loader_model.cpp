#include "../include/kotek_loader_model.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkLoaderModel_CGLTF::ktkLoaderModel_CGLTF(Core::ktkIFileSystem* p_filesystem) :
	m_p_filesystem{p_filesystem}
{
}

ktkLoaderModel_CGLTF::ktkLoaderModel_CGLTF(void) : m_p_filesystem{} {}

ktkLoaderModel_CGLTF::~ktkLoaderModel_CGLTF(void) {}

ktk::any ktkLoaderModel_CGLTF::Load(const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(this->m_p_filesystem,
		"you must initialize file system for this loader");

	return ktk::any();
}

bool ktkLoaderModel_CGLTF::Load(
	const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
{
	KOTEK_ASSERT(this->m_p_filesystem,
		"you must initialize file system for this loader");

	return true;
}

const ktk::string& ktkLoaderModel_CGLTF::Get_UserDescription(
	void) const noexcept
{
	return KOTEK_TEXT("this is loader based on cgltf library for "
					  "loading glTF 2.0 models");
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

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
