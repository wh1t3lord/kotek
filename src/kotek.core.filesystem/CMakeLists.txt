cmake_minimum_required(VERSION 3.21)

project(kotek.core.filesystem VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_FileSystem SHUTDOWN ShutdownModule_Core_FileSystem
	"include/kotek_filesystem.h"
	"include/kotek_filesystem_native.h"
	"include/kotek_filesystem_zlib.h"
	"include/kotek_virtualfilemapper.h"
	"include/kotek_core_filesystem.h"
	"src/kotek_filesystem.cpp"
	"src/kotek_filesystem_native.cpp"
	"src/kotek_filesystem_zlib.cpp"
	"src/kotek_virtualfilemapper.cpp"
	"src/main_core_filesystem_dll.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/filesystem")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem.file_text)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
# provides ktk::filesystem::create_directory/exists/current_path used by
# kotek_filesystem.cpp; in PLUGIN mode undeclared static-leaf deps are
# unresolved (in STATIC mode the exe resolved them implicitly)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem)