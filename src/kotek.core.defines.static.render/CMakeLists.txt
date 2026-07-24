cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.render VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_Render SHUTDOWN ShutdownModule_Core_Defines_Static_Render
	"include/kotek_core_defines_render.h"
	"src/main_core_defines_render_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.dx)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.vk)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.bgfx)