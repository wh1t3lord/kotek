#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#define KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL 10

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

	bool Save(
		const ktk::filesystem::path& path, ktk::any data) noexcept override;

	bool Open(const ktk::filesystem::path& path,
		eResourceWritingType resource_type, eResourceWritingPolicy policy,
		eResourceWritingMode mode, ktk::uint32_t id) noexcept override;
	void Write(
		ktk::uint32_t resource_id, const char* p_string) noexcept override;
	void Write(ktk::uint32_t resource_id, const char* p_string,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id,
		const unsigned char* p_raw_memory) noexcept override;
	void Write(ktk::uint32_t resource_id, const unsigned char* p_raw_memory,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, ktk::int32_t value) noexcept override;
	void Write(ktk::uint32_t resource_id, ktk::float_t value) noexcept override;
	void Write(
		ktk::uint32_t resource_id, ktk::double_t value) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::int32_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::uint32_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::float_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::double_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::int8_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::int16_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id, const ktk::uint16_t* p_arr,
		ktk::size_t size) noexcept override;
	void Write(ktk::uint32_t resource_id,
		Core::eFileWritingControlCharacterType type) noexcept override;
	bool Close(ktk::uint32_t id) noexcept override;

	ktk::uint32_t GenerateFileID(void) noexcept override;

protected:
	eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk::filesystem::path& path) noexcept override;

private:
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	ktk::static_unordered_map<ktk::uint32_t, std::pair<ktk::cofstream, Kotek::ktk::mt::atomic<bool>>,
		KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL>
		m_writers;
#else
	ktk::unordered_map<ktk::uint32_t, std::pair<ktk::cofstream, bool>>
		m_writers;
#endif

	// TODO: think how to replace for placement new and make it more useful
	ktk::unordered_map<eResourceLoadingType, ktkIResourceSaver*> m_savers;
	ktk::mt::mutex m_mutex;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK