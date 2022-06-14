cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.imgui VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(to_include 	
    "include/imgui_impl_dx12.h"
	"include/imgui_impl_dx9.h"
	"include/imgui_impl_win32.h"
	"include/imgui_impl_vulkan.h"
    "src/imgui_impl_dx12.cpp"
	"src/imgui_impl_dx9.cpp"
	"src/imgui_impl_win32.cpp"
    "src/imgui_impl_vulkan.cpp"
	)
elseif(UNIX)
    set(to_include
    "include/imgui_impl_vulkan.h"
    "src/imgui_impl_vulkan.cpp")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_imgui.h"
	"include/imconfig.h"
	"include/imgui.h"
	"include/imgui_internal.h"
	"include/imstb_rectpack.h"
	"include/imstb_textedit.h"
	"include/imstb_truetype.h"
	"include/imgui_impl_glfw.h"
	"include/imgui_impl_opengl3.h"
	"include/imgui_impl_opengl3_loader.h"
	"src/imgui.cpp"
	"src/imgui_demo.cpp"
	"src/imgui_draw.cpp"
	"src/imgui_tables.cpp"
	"src/imgui_widgets.cpp"
	"src/imgui_impl_glfw.cpp"
	"src/imgui_impl_opengl3.cpp"
	${to_include}
	"src/main_ui_imgui_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)