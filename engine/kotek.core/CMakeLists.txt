cmake_minimum_required(VERSION 3.19.3)

project(kotek.core VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(Boost COMPONENTS json unit_test_framework filesystem REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(assimp REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/assimp/${CMAKE_BUILD_TYPE}")
find_package(Vulkan REQUIRED)

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

message("[Engine]: files to attach (KOTEK_TESTS): ${to_include_tests}")

add_library(${PROJECT_NAME} STATIC 
	"src/main_core_dll.cpp"
	"include/kotek_core.h"
	"include/kotek_std.h"
    "include/kotek_std_utility.h"
	"src/kotek_std_utility.cpp"
    "include/kotek_std_alias_ui.h"
    "include/kotek_std_alias_containers.h"
	"include/kotek_std_alias_multithreading.h"
    "include/kotek_std_os.h"
	"src/kotek_main_manager.cpp"
	"include/kotek_main_manager.h"
    "include/kotek_component_allocator.h"
	"include/kotek_input.h"
	"src/kotek_input.cpp"
	"include/kotek_resource_manager.h"
	"src/kotek_resource_manager.cpp"
	"include/kotek_interface_resource_loader_manager.h"
	${to_include_tests}
)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.console)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.format)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.char)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers Boost::json Boost::unit_test_framework Boost::filesystem)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp)