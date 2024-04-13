#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceLoaderManager : public ktkIResourceLoaderManager
{
public:
	ktkResourceLoaderManager(void);
	~ktkResourceLoaderManager(void);

	void Initialize(ktkIFileSystem* p_manager_filesystem,
		ktkMainManager* p_main_manager) override;
	void Shutdown(void) override;

	void Set_Loader(eResourceLoadingType resource_type,
		ktkIResourceLoader* p_loader) override;

	ktkIResourceLoader* Get_Loader(
		eResourceLoadingType resource_type) const noexcept override;

	ktk::any Load(const ktk_filesystem_path& path) noexcept override;
	bool Load(const ktk_filesystem_path& path,
		ktk::any object_from_construct) noexcept override;

protected:
	eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk_filesystem_path& path) noexcept override;

	ktk_unordered_map<eResourceLoadingType, ktkIResourceLoader*,
		KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT>
		m_loaders;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK