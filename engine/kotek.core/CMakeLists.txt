cmake_minimum_required(VERSION 3.19.3)

project(kotek.core VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		find_package(Boost COMPONENTS json unit_test_framework filesystem REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
	endif()
else()
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		find_package(Boost COMPONENTS json unit_test_framework filesystem REQUIRED)
	endif()
endif()

if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "ON")
	message("[${PROJECT_NAME}]: adding tests for runtime in project ${PROJECT_NAME}")
	set(to_include_tests 
		"tests/kotek_core_test_filesystem.cpp")
elseif("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "OFF")
	# TODO: add support for own projects for unit testing
	message("[${PROJECT_NAME}]: creating test projects for project ${PROJECT_NAME}")
	set(to_include_tests "")
else()
	message("[${PROJECT_NAME}]: tests are disabled for project ${PROJECT_NAME}")
	set(to_include_tests "")
endif()

message("[${PROJECT_NAME}]: files to attach (KOTEK_TESTS): ${to_include_tests}")

add_library(${PROJECT_NAME} STATIC 
	"src/main_core_dll.cpp"
	"include/kotek_core.h"
	${to_include_tests}
)


if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	target_link_libraries(${PROJECT_NAME} PUBLIC 
		Boost::headers 
		Boost::json 
		Boost::unit_test_framework 
		Boost::filesystem
	)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.console)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.format)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.log)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.resource_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.ecs)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.input)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.utility)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.engine_config)