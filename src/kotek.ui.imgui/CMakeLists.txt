cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.imgui VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_imgui.h"
	"include/kotek_ui_imgui_wrapper.h"
	"include/imgui_impl_dx9.h"
	"include/imgui_impl_dx10.h"
	"include/imgui_impl_dx11.h"
	"include/imgui_impl_dx12.h"
	"include/imgui_impl_glfw.h"
	"include/imgui_impl_opengl2.h"
	"include/imgui_impl_opengl3.h"
	"include/imgui_impl_opengl3_loader.h"
	"include/imgui_impl_vulkan.h"
	"include/imgui_impl_win32.h"
	"include/imconfig.h"
	"include/imgui.h"
	"include/imgui_internal.h"
	"include/imstb_rectpack.h"
	"include/imstb_textedit.h"
	"include/imstb_truetype.h"
	"src/imgui_impl_dx9.cpp"
	"src/imgui_impl_dx10.cpp"
	"src/imgui_impl_dx11.cpp"
	"src/imgui_impl_dx12.cpp"
	"src/imgui_impl_glfw.cpp"
	"src/imgui_impl_opengl2.cpp"
	"src/imgui_impl_opengl3.cpp"
	"src/imgui_impl_vulkan.cpp"
	"src/imgui_impl_win32.cpp"
	"src/imgui.cpp"
	"src/imgui_demo.cpp"
	"src/imgui_draw.cpp"
	"src/imgui_tables.cpp"
	"src/imgui_widgets.cpp"
	"src/kotek_ui_imgui_wrapper.cpp"
	"src/main_ui_imgui_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui/vendor")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.math)