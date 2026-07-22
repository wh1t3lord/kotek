cmake_minimum_required(VERSION 3.21)

project(kotek.core.engine_config VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Engine_Config SHUTDOWN ShutdownModule_Core_Engine_Config
	"include/kotek_std_config.h"
	"src/kotek_std_config.cpp"
	"include/kotek_core_engine_config.h"
	"src/main_core_engine_config_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.dll)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_set)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.string)
