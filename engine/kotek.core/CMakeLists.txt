cmake_minimum_required(VERSION 3.19.3)

project(kotek.core VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(Boost COMPONENTS json container unit_test_framework REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(fmt REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(mimalloc 1.7 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/mimalloc/${CMAKE_BUILD_TYPE}/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

if(TBB_FOUND)
	message("[Package][+]: TBB")
else()
	message("[Package][-]: TBB")
endif()

if(Boost_FOUND)
	message("[Package][+]: BOOST")
else()
	message("[Package][-]: BOOST")
endif()

if(fmt_FOUND)
	message("[Package][+]: FMT")
else()
	message("[Package][-]: FMT")
endif()


if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "ON")
	message("[Engine]: adding tests for runtime in project ${PROJECT_NAME}")
	set(to_include_tests 
		"tests/kotek_core_test_filesystem.cpp"
		"tests/kotek_core_test_string.cpp")
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



message("[Engine]: files to attach (KOTEK_TESTS): ${to_include_tests}")
message("[Engine]: files to attach (KOTEK_CPU_PROFILER): ${to_include_cpu_profiler}")
message("[Engine]: files to attach (KOTEK_GPU_PROFILER): ${to_include_gpu_profiler}")

add_library(${PROJECT_NAME} STATIC 
	"main_core_dll.cpp"
	"kotek_core.h"
	"kotek_std.h"
    "kotek_std_alias_numerics.h"
    "kotek_std_utility.h"
    "kotek_std_alias_math.h"
    "kotek_std_alias_ui.h"
    "kotek_std_alias_containers.h"
    "kotek_std_alias_casting.h"
    "kotek_std_alias_char_model.h"
    "kotek_std_preprocessors.h"
    "kotek_std_alias_io.h"
    "kotek_std_constants.h"
    "kotek_std_memory.h"
    "kotek_std_alias_format.h"
    "kotek_std_os.h"
    "kotek_std_dependent_preprocessors.h"
    "kotek_std_alias_string.h"
	"kotek_std_memory.cpp"
	"kotek_std_alias_casting.cpp"
	"kotek_std_string.cpp"
	"kotek_filesystem.h"
	"kotek_filesystem.cpp"
	"kotek_main_manager.cpp"
	"kotek_main_manager.h"
    "kotek_component_allocator.h"
	"kotek_file.h"
	"kotek_file.cpp"
	"kotek_json.h"
	"kotek_json.cpp"
	"kotek_console.h"
	"kotek_console.cpp"
	"kotek_input.h"
	"kotek_input.cpp"
	"kotek_profiler.h"
	"kotek_profiler.cpp"
	"kotek_dynamic_library.h"
	"kotek_dynamic_library.cpp"
	"kotek_std_string.h"
	${to_include_tests}
	${to_include_cpu_profiler}
	${to_include_gpu_profiler}
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} kotek.core.api)
target_link_libraries(${PROJECT_NAME} kotek.core.memory)
target_link_libraries(${PROJECT_NAME} kotek.engine.window)
target_link_libraries(${PROJECT_NAME} TBB::tbb)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} mimalloc-static)