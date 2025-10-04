#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkFileSystem_VFM;

class ktkFileSystem_Zlib
{
public:
	ktkFileSystem_Zlib();
	~ktkFileSystem_Zlib();


	void Initialize(ktkFileSystem_VFM* p_vfm);
	void Shutdown(void);

private:
	ktkFileSystem_VFM* m_p_vfm;
	ktk_vector<ktkFileHandleType, KOTEK_DEF_FILESYSTEM_ZLIB_MAX_FILES> m_files;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK