cmake_minimum_required(VERSION 3.21)

project(kotek.render.shared VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Render_Shared SHUTDOWN ShutdownModule_Render_Shared
	"include/kotek_render_data_types.h"
	"src/kotek_render_data_types.cpp"
	"include/kotek_render_shared.h"
	"src/main_render_shared_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/shared")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

kotek_target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.gl)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.dx)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.vk)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.bgfx)
