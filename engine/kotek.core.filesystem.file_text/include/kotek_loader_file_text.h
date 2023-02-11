#pragma once

#include "kotek_loader_file_text_json.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceLoaderFile_Text : public ktkIResourceLoader
{
public:
	ktkResourceLoaderFile_Text(ktkMainManager* p_main_manager);
	~ktkResourceLoaderFile_Text();

	ktk::any Load(const ktk::filesystem::path& path) noexcept override;

	bool Load(const ktk::filesystem::path& path,
		ktk::any object_from_construct) noexcept override;

    ktk::cstring Get_UserDescription(void) const noexcept override;

	Core::eResourceLoadingType Get_Type(void) const noexcept override;

	bool DetectTypeByFullPath(
		const ktk::filesystem::path& path) noexcept override;

	ktkIResourceLoader* Get_Loader(
		const ktk::filesystem::path& extension_of_file) noexcept override;

    ktk::cstring Get_AllSupportedFormats(void) const noexcept override;

private:
	void Register_Loaders(void) noexcept;
	void Delete_Loaders(void) noexcept;

private:
	ktkMainManager* m_p_main_manager;
    ktk::unordered_map<ktk::cstring, ktkIResourceLoader*> m_loaders;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
