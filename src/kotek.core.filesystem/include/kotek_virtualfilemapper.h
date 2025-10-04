#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

#define VFM_FILE_MAX_COUNT \
	KOTEK_DEF_FILESYSTEM_NATIVE_MAX_FILES + KOTEK_DEF_FILESYSTEM_ZLIB_MAX_FILES

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkFileSystem_VFM
{
	struct vfm_handle_t
	{
		unsigned char lookup_id = -1;

#ifdef KOTEK_USE_PLATFORM_WINDOWS
		/// @brief file mapping handle obtained as result of CreateFileMapping
		HANDLE p_fmh = HANDLE(0);
#endif

		ktkFileHandleType file_id = kInvalidFileHandleType;
	};

public:
	ktkFileSystem_VFM(void);
	~ktkFileSystem_VFM(void);

	void Initialize();
	void Shutdown();

	void MapFile(ktkFileHandleType file_id, kun_ktk fstream& file);

	void UnMapFile(ktkFileHandleType file_id, kun_ktk fstream& file);

private:
	ktk_vector<vfm_handle_t, VFM_FILE_MAX_COUNT> m_mappings;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK