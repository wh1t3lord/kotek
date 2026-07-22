cmake_minimum_required(VERSION 3.21)

project(kotek.render.shared.dx VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Render_Shared_DX SHUTDOWN ShutdownModule_Render_Shared_DX
	"include/kotek_render_shared_dx.h"
	"src/main_render_shared_dx_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/shared")
kotek_target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)