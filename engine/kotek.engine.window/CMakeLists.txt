cmake_minimum_required(VERSION 3.19.3)

project(kotek.engine.window VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(Boost COMPONENTS unit_test_framework REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    find_package(directxmath REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")

if (WIN32)
    set(to_include 	
    "src/imgui_impl_dx12.cpp"
	"include/imgui_impl_dx12.h"
	"include/imgui_impl_dx9.h"
	"src/imgui_impl_dx9.cpp"
	"include/imgui_impl_win32.h"
	"src/imgui_impl_win32.cpp"
    "src/imgui_impl_vulkan.cpp"
	"include/imgui_impl_vulkan.h")
elseif(UNIX)
    set(to_include
    "src/imgui_impl_vulkan.cpp"
	"include/imgui_impl_vulkan.h") 
endif()

message("[Engine]: files to attach: ${to_include}")

add_library(${PROJECT_NAME} STATIC
	    "include/kotek_engine_window.h"
		"include/kotek_engine_keycodes.h"
		"include/vk_mem_alloc.h"
		"src/vk_mem_alloc.cpp"
		"include/imconfig.h"
		"src/imgui.cpp"
		"include/imgui.h"
		"src/imgui_demo.cpp"
		"src/imgui_draw.cpp"
		"include/imgui_internal.h"
		"src/imgui_tables.cpp"
		"src/imgui_widgets.cpp"
		"include/imstb_rectpack.h"
		"include/imstb_textedit.h"
		"include/imstb_truetype.h"
		"include/imgui_impl_glfw.h"
		"src/imgui_impl_glfw.cpp"
		"include/imgui_impl_opengl3.h"
		"src/imgui_impl_opengl3.cpp"
		"include/imgui_impl_opengl3_loader.h"
		${to_include}
	    "include/kotek_engine_window_impl.h"
	    "src/kotek_engine_window_impl.cpp"
	    "src/main_engine_window_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_link_libraries(${PROJECT_NAME} glm::glm)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    target_link_libraries(${PROJECT_NAME} Microsoft::DirectXMath)
endif()

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} TBB::tbb)

