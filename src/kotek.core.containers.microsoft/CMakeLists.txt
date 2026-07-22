cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.microsoft VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_Microsoft SHUTDOWN ShutdownModule_Core_Containers_Microsoft
	"include/kotek_core_containers_microsoft.h"
	"src/main_core_containers_microsoft_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/vendor/microsoft")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.microsoft.wrl.comptr)