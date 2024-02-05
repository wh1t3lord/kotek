#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkLoaderFile_JSON : public ktkIResourceLoader
{
public:
	ktkLoaderFile_JSON(ktkMainManager* p_main_manager);
	~ktkLoaderFile_JSON();

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
	ktkMainManager* m_p_main_manager;
	ktk_unordered_map<ktk::cstring, ktkIResourceLoader*,
		KOTEK_DEF_JSON_RESOURCE_LOADERS_COUNT>
		m_loaders;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
