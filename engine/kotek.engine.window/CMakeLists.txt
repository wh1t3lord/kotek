cmake_minimum_required(VERSION 3.19.3)

project(kotek.engine.window VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
include_directories("../../deps/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(Boost COMPONENTS unit_test_framework REQUIRED PATHS "../../deps/")
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED PATHS "../../deps/")
find_package(TBB REQUIRED PATHS "../../deps/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	find_package(glm REQUIRED PATHS "../../deps/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")

if (WIN32)
    set(to_include 	
    "imgui_impl_dx12.cpp"
	"imgui_impl_dx12.h"
	"imgui_impl_dx9.h"
	"imgui_impl_dx9.cpp"
	"imgui_impl_win32.h"
	"imgui_impl_win32.cpp"
    "imgui_impl_vulkan.cpp"
	"imgui_impl_vulkan.h")
elseif(UNIX)
    set(to_include
    "imgui_impl_vulkan.cpp"
	"imgui_impl_vulkan.h") 
endif()

message("[Engine]: files to attach: ${to_include}")

add_library(${PROJECT_NAME} STATIC
	    "kotek_engine_window.h"
		"kotek_engine_keycodes.h"
		"vk_mem_alloc.h"
		"vk_mem_alloc.cpp"
		"imconfig.h"
		"imgui.cpp"
		"imgui.h"
		"imgui_demo.cpp"
		"imgui_draw.cpp"
		"imgui_internal.h"
		"imgui_tables.cpp"
		"imgui_widgets.cpp"
		"imstb_rectpack.h"
		"imstb_textedit.h"
		"imstb_truetype.h"
		"imgui_impl_glfw.h"
		"imgui_impl_glfw.cpp"
		"imgui_impl_opengl3.h"
		"imgui_impl_opengl3.cpp"
		"imgui_impl_opengl3_loader.h"
		${to_include}
	    "kotek_engine_window_impl.h"
	    "kotek_engine_window_impl.cpp"
	    "main_engine_window_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} TBB::tbb)

