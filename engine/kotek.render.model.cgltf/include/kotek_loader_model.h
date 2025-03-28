#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
class ktkLoaderModel_CGLTF : public Core::ktkIResourceLoader
{
public:
	ktkLoaderModel_CGLTF(Core::ktkIFileSystem* p_filesystem);
	ktkLoaderModel_CGLTF(void);
	~ktkLoaderModel_CGLTF(void);

	bool Load(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle object_from_construct) noexcept override;

	ktk::cstring Get_UserDescription(void) const noexcept override;

	Core::eResourceLoadingType Get_Type(void) const noexcept override;

	bool DetectTypeByFullPath(
		const ktk_filesystem_path& path) noexcept override;

	ktkIResourceLoader* Get_Loader(
		const ktk_filesystem_path& extension_of_file) noexcept override;

	ktk::cstring Get_AllSupportedFormats(void) const noexcept override;

private:
	Core::ktkIFileSystem* m_p_filesystem;
	ktk::unordered_map<std::string_view, Core::ktkIResourceLoader*> m_loaders;
};
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
