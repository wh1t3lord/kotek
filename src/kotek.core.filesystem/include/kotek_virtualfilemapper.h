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
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		/// @brief file mapping handle obtained as result of CreateFileMapping
		HANDLE p_fmh = HANDLE(0);
		void* p_data = nullptr;
		size_t file_size = 0;
#else
	#error unknown platform
#endif
	};

public:
	ktkFileSystem_VFM(void);
	~ktkFileSystem_VFM(void);

	void Initialize();
	void Shutdown();

	kun_ktk uint32_t MapFile(
		FILE* p_file
	);

	void UnMapFile(kun_ktk uint32_t file_id);

private:
	ktk_vector<vfm_handle_t, 2048> m_mappings;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK