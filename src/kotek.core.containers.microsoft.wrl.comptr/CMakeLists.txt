cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.microsoft.wrl.comptr VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_Microsoft_WRL_ComPtr SHUTDOWN ShutdownModule_Core_Containers_Microsoft_WRL_ComPtr
	"include/kotek_std_alias_microsoft_wrl_comptr.h"
	"include/kotek_core_containers_microsoft_wrl_comptr.h"
	"src/main_core_containers_microsoft_wrl_comptr_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/vendor/microsoft")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)