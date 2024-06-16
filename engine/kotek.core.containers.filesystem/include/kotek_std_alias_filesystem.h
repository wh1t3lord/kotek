#pragma once

#include <kotek.core.containers.filesystem.path/include/kotek_core_containers_filesystem_path.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

	#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
		defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
// todo: rename to filesystem when you finish static_path and all replacement to
// ktk_filesystem_path
namespace filesystem
{
	ktk_filesystem_path current_path();
	bool exists(const ktk_filesystem_path& path);
	bool create_directory(const ktk_filesystem_path& path);
	bool remove(const ktk_filesystem_path& path);
} // namespace filesystem
	#else
namespace filesystem = std::filesystem;
	#endif

#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK