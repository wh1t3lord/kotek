cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.microsoft.wrl.comptr VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_microsoft_wrl_comptr.h"
	"include/kotek_core_containers_microsoft_wrl_comptr.h"
	"src/main_core_containers_microsoft_wrl_comptr_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/vendor/microsoft")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)