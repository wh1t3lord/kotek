cmake_minimum_required(VERSION 3.21)

project(kotek.core.filesystem.pack VERSION 1 LANGUAGES CXX)




if (NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	# vcpkg AND manual (custom folder) modes resolve through the wrapper
	# (K10); the zstd/ZLIB targets are also found GLOBAL at the root, so
	# these calls no-op on the existing targets
	kotek_find_package(zstd CONFIG REQUIRED)
	kotek_find_package(ZLIB REQUIRED)
else()
	# nuget mode is legacy (K10) — mirror kotek.core.os.win32's calls
	find_package(zstd CONFIG REQUIRED)
	find_package(ZLIB REQUIRED)
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_FileSystem_Pack SHUTDOWN ShutdownModule_Core_FileSystem_Pack
	"include/kotek_kpack_format.h"
	"include/kotek_filesystem_pack.h"
	"include/kotek_core_filesystem_pack.h"
	"src/kotek_filesystem_pack.cpp"
	"src/kotek_kpack_writer.cpp"
	"src/main_core_filesystem_pack_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/filesystem")
if (UNIX)
	set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)

# the .kpack codecs (the reader's per-block decompression and the shared
# writer's compression) — static triplet targets
kotek_target_link_libraries(${PROJECT_NAME} PRIVATE zstd::libzstd_static)
kotek_target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB::ZLIB)
