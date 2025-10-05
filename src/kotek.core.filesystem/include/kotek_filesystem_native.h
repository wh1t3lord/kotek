#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE

	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
class ktkFileSystem_VFM;
	#endif

class ktkFileSystem_Native
{
	struct file_handle_no_vfm_t
	{
		FILE* p_file = nullptr;
	};

	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	struct file_handle_vfm_t
	{
		kun_ktk uint32_t vfm_file_id = decltype(vfm_file_id)(-1);
	};
	#endif

	struct file_handle_t
	{
		std::variant<file_handle_no_vfm_t
	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
			,
			file_handle_vfm_t
	#endif
			>
			desc;
	};

public:
	ktkFileSystem_Native();
	~ktkFileSystem_Native();

	void Initialize(ktkFileSystem_VFM* p_vfm);
	void Shutdown();

	bool Write(ktkFileHandleType file, unsigned char* p_data,
		kun_ktk size_t size_in_bytes);

	bool Read_File(const ktk_filesystem_path& path_to_file,
		kun_ktk ustring& result) noexcept;

	template <kun_ktk size_t Bytes>
	bool Read_File(const ktk_filesystem_path& path_to_file,
		ktk_vector<kun_ktk uint8_t, Bytes>& result);

	bool Read_File(kun_ktk uint8_t*& p_buffer, size_t& size,
		const ktk_filesystem_path& path_to_file) noexcept;

private:
	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	ktkFileSystem_VFM* m_p_vfm;
	#endif

	ktk_vector<file_handle_t, KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT>
		m_files;
};
#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK