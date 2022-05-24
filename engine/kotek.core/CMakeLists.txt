cmake_minimum_required(VERSION 3.19.3)

project(kotek.core VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(Boost COMPONENTS json unit_test_framework filesystem REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(assimp REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/assimp/${CMAKE_BUILD_TYPE}")
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

if(Boost_FOUND)
	message("[Package][+]: BOOST")
else()
	message("[Package][-]: BOOST")
endif()

if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "ON")
	message("[Engine]: adding tests for runtime in project ${PROJECT_NAME}")
	set(to_include_tests 
		"tests/kotek_core_test_filesystem.cpp")
elseif("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "OFF")
	# TODO: add support for own projects for unit testing
	message("[Engine]: creating test projects for project ${PROJECT_NAME}")
	set(to_include_tests "")
else()
	message("[Engine]: tests are disabled for project ${PROJECT_NAME}")
	set(to_include_tests "")
endif()

if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	message("[Engine]: adding files of CPU profiler in project ${PROJECT_NAME}")
	set(to_include_cpu_profiler
		"tracy/Tracy.hpp"
		"tracy/TracyClient.cpp")

	if ("${KOTEK_GPU_PROFILER}" STREQUAL "ON")
		message("[Engine]: adding files of GPU profiler in project ${PROJECT_NAME}")
		set(to_include_gpu_profiler 
			"tracy/TracyD3D11.hpp"
			"tracy/TracyD3D12.hpp"
			"tracy/TracyOpenGL.hpp"
			"tracy/TracyVulkan.hpp")
	endif()

else()
	set(to_include_cpu_profiler "")
	set(to_include_gpu_profiler "")
endif()

# TODO: think about including the last version of OpenGL and respect to gdal4 folder
set(to_include_glad "glad3/glad.h"
					"glad3/glad.c")



message("[Engine]: files to attach (KOTEK_TESTS): ${to_include_tests}")
message("[Engine]: files to attach (KOTEK_CPU_PROFILER): ${to_include_cpu_profiler}")
message("[Engine]: files to attach (KOTEK_GPU_PROFILER): ${to_include_gpu_profiler}")

add_library(${PROJECT_NAME} STATIC 
	"src/main_core_dll.cpp"
	"include/kotek_core.h"
	"include/kotek_std.h"
    "include/kotek_std_utility.h"
	"src/kotek_std_utility.cpp"
    "include/kotek_std_alias_ui.h"
    "include/kotek_std_alias_containers.h"
	"include/kotek_std_alias_multithreading.h"
    "include/kotek_std_alias_io.h"
    "include/kotek_std_os.h"
	"include/kotek_filesystem.h"
	"src/kotek_filesystem.cpp"
	"src/kotek_main_manager.cpp"
	"include/kotek_main_manager.h"
    "include/kotek_component_allocator.h"
	"include/kotek_file.h"
	"src/kotek_file.cpp"
	"include/kotek_json.h"
	"src/kotek_json.cpp"
	"include/kotek_console.h"
	"src/kotek_console.cpp"
	"include/kotek_input.h"
	"src/kotek_input.cpp"
	"include/kotek_profiler.h"
	"src/kotek_profiler.cpp"
	"include/kotek_dynamic_library.h"
	"include/kotek_resource_manager.h"
	"src/kotek_resource_manager.cpp"
	"include/kotek_interface_resource_loader_manager.h"
	${to_include_tests}
	${to_include_cpu_profiler}
	${to_include_gpu_profiler}
	${to_include_glad}
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${ASSIMP_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} kotek.core.api)
target_link_libraries(${PROJECT_NAME} kotek.core.casting)
target_link_libraries(${PROJECT_NAME} kotek.core.casting.string)
target_link_libraries(${PROJECT_NAME} kotek.core.containers)
target_link_libraries(${PROJECT_NAME} kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} kotek.core.containers.hash)
target_link_libraries(${PROJECT_NAME} kotek.core.memory)
target_link_libraries(${PROJECT_NAME} kotek.core.math)
target_link_libraries(${PROJECT_NAME} kotek.core.defines)
target_link_libraries(${PROJECT_NAME} kotek.core.defines.dependent)
target_link_libraries(${PROJECT_NAME} kotek.core.types.char)
target_link_libraries(${PROJECT_NAME} kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} kotek.core.types.string)
target_link_libraries(${PROJECT_NAME} kotek.core.format)
target_link_libraries(${PROJECT_NAME} kotek.engine.window)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})