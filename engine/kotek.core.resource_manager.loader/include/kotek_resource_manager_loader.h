#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

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

	bool Load(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle object_from_construct) noexcept override;

	bool Open(const ktk_filesystem_path& path,
		eResourceReadingType resource_type, eResourceReadingPolicy policy,
		kun_ktk uint32_t id) noexcept override;
	void Seekg(kun_ktk uint32_t resource_id, kun_ktk size_t bytes,
		eFileSeekDirectionType type) override;
	kun_ktk size_t Tellg(kun_ktk uint32_t resource_id) override;
	void Read(kun_ktk uint32_t resource_id, char* p_buffer,
		kun_ktk size_t size) override;
	bool Is_Open(kun_ktk uint32_t resource_id) noexcept override;
	bool Close(kun_ktk uint32_t id) noexcept override;
	kun_ktk uint32_t GenerateFileID(void) noexcept override;

protected:
	eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk_filesystem_path& path) noexcept override;

	ktk_unordered_map < kun_ktk uint32_t,
		std::pair<kun_ktk ifstream, kun_ktk kun_mt atomic<bool>>,
			KOTEK_DEF_RESOURCE_LOADER_MANAGER_SIZE_FILE_POOL>
			m_readers;

	ktk_unordered_map<eResourceLoadingType, ktkIResourceLoader*,
		KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT>
		m_loaders;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK