cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.git VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Git)

if (GIT_FOUND)

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_GIT_WAS_FOUND)

	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE kotek_git_status
		OUTPUT_VARIABLE KOTEK_GIT_CURRENT_COMMIT
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	if (kotek_git_status)
		message("[${PROJECT_NAME}]: failed to get current commit, status: '${kotek_git_status}'")
	endif()

	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE kotek_git_status
		OUTPUT_VARIABLE KOTEK_GIT_CURRENT_BRANCH_NAME
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	if (kotek_git_status)
		message("[${PROJECT_NAME}]: failed to get current branch name, status: '${kotek_git_status}'")
	endif()

	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-list --count HEAD
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE kotek_git_status
		OUTPUT_VARIABLE KOTEK_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	if (kotek_git_status)
		message("[${PROJECT_NAME}]: failed to get current commit count, status: '${kotek_git_status}'")
	endif()

	string(TIMESTAMP KOTEK_WHEN_YOU_GENERATED_SOLUTION "%w %A %B %Y %H:%M:%S")

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_GIT_WAS_FOUND
		#define KOTEK_USE_GIT_CURRENT_COMMIT ${KOTEK_GIT_CURRENT_COMMIT}
		#define KOTEK_USE_GIT_CURRENT_BRANCH_NAME ${KOTEK_GIT_CURRENT_BRANCH_NAME}
		#define KOTEK_USE_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH ${KOTEK_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH}
		#define KOTEK_USE_WHEN_YOU_GENERATED_SOLUTION ${KOTEK_WHEN_YOU_GENERATED_SOLUTION}
	#endif
	")
else()
	message(WARNING "[${PROJECT_NAME}]: can't find Git for generating preprocessors!")

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_git.h"
	"src/main_core_defines_static_git_dll.cpp")

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)