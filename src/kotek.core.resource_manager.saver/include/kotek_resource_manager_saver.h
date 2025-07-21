#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

// todo: re-write using task manager
class ktkResourceSaverManager : public ktkIResourceSaverManager
{
public:
	ktkResourceSaverManager(void);
	~ktkResourceSaverManager(void);

	void Initialize(
		ktkIFileSystem* p_filesystem, ktkMainManager* p_main_manager) override;
	void Shutdown(void) override;

	// warning never use a variable on stack to add/replace saver only created
	// saver with new and without handling by your own delete, this class
	// manages delete thing!
	void Set_Saver(eResourceLoadingType resource_type,
		ktkIResourceSaver* p_saver) override;

	ktkIResourceSaver* Get_Saver(
		eResourceLoadingType resource_type) const noexcept override;

	bool Save(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle data) noexcept override;

protected:
	eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk_filesystem_path& path) noexcept override;

private:
	//	ktk_unordered_map<kun_ktk uint32_t,
	//		std::pair<kun_ktk cfstream, kun_ktk kun_mt atomic<bool>>,
	//		KOTEK_DEF_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL>
	//		m_writers;

	// writers can be allocated only from filesystem e.g. fstreams

	// TODO: think how to replace for placement new and make it more useful
	ktk_unordered_map<eResourceLoadingType, ktkIResourceSaver*,
		KOTEK_DEF_RESOURCE_SAVERS_TYPE_MAX_COUNT>
		m_savers;
	kun_ktk kun_mt mutex m_mutex;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK