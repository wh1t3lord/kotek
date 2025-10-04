#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>



KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkFileSystem_VFM;

class ktkFileSystem_Native
{
public:
	ktkFileSystem_Native();
	~ktkFileSystem_Native();

	void Initialize(ktkFileSystem_VFM* p_vfm);
	void Shutdown();

	bool Write(
		ktkFileHandleType file, 
		unsigned char* p_data, 
		kun_ktk size_t size_in_bytes
	);

	bool Read_File(
		const ktk_filesystem_path& path_to_file,
		kun_ktk ustring& result
	) noexcept;

	template<kun_ktk size_t Bytes>
	bool Read_File(
		const ktk_filesystem_path& path_to_file,
		ktk_vector<kun_ktk uint8_t, Bytes>& result
	);

	bool Read_File(
		kun_ktk uint8_t*& p_buffer,
		size_t& size,
		const ktk_filesystem_path& path_to_file
	) noexcept;



private:
	ktkFileSystem_VFM* m_p_vfm;
	ktk_vector<ktkFileHandleType, KOTEK_DEF_FILESYSTEM_NATIVE_MAX_FILES>
		m_files;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK