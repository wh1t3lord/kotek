#pragma once

#include <kotek.core.containers.filesystem.path/include/kotek_core_containers_filesystem_path.h>

#include <kotek.core.enum.core/include/kotek_core_enum_core.h>

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

	#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
		defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
// todo: rename to filesystem when you finish static_path and all replacement to
// ktk_filesystem_path
KOTEK_BEGIN_NAMESPACE_FILESYSTEM
	ktk_filesystem_path current_path();
	bool exists(const ktk_filesystem_path& path);
	bool create_directory(const ktk_filesystem_path& path);
	bool remove(const ktk_filesystem_path& path);
KOTEK_END_NAMESPACE_FILESYSTEM
	#else
namespace filesystem = std::filesystem;
	#endif

KOTEK_BEGIN_NAMESPACE_FILESYSTEM
constexpr const char* get_frameworks_folder_name_by_enum(
	kun_core eFolderIndex id)
{
	constexpr const char* _kFrameworkFolderNames[] = {"", "data_game",
		"configs", "scripts", "textures", "shaders", "glsl", "hlsl", "webgpu",
		"spv", "models", "sounds", "levels", "ai", "tests", "shader_cache",
		"sdk", "settings", "scenes", "data_user"};

	constexpr int _kFrameworkFolderNamesSize =
		sizeof(_kFrameworkFolderNames) / sizeof(_kFrameworkFolderNames[0]);

	static_assert(
		static_cast<int>(static_cast<int>(kun_core eFolderIndex::kEndOfEnum)) ==
			(_kFrameworkFolderNamesSize),
		"you forget to update array of names (_kFrameworkFolderNames) or "
		"something else");

	return _kFrameworkFolderNames[static_cast<int>(id)];
}
KOTEK_END_NAMESPACE_FILESYSTEM

#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK