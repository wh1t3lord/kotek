#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
class ktkLoaderModel_CGLTF : public Core::ktkIResourceLoader
{
public:
	ktkLoaderModel_CGLTF(Core::ktkIFileSystem* p_filesystem);
	ktkLoaderModel_CGLTF(void);
	~ktkLoaderModel_CGLTF(void);

	ktk::any Load(const ktk::filesystem::path& path) noexcept override;

	bool Load(const ktk::filesystem::path& path,
		ktk::any object_from_construct) noexcept override;

	const ktk::string& Get_UserDescription(void) const noexcept override;

	Core::eResourceLoadingType Get_Type(void) const noexcept override;

	bool DetectTypeByFullPath(
		const ktk::filesystem::path& path) noexcept override;

	Core::ktkIResourceFormatAnalyzer*
	Get_FormatAnalyzer() const noexcept override;

	void Set_FormatAnalyzer(
		Core::ktkIResourceFormatAnalyzer* p_format_analyzer) noexcept override;

private:
	Core::ktkIFileSystem* m_p_filesystem;
	Core::ktkIResourceFormatAnalyzer* m_p_format_analyzer;
};
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK