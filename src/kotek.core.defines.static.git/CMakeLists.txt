cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.git VERSION 1 LANGUAGES CXX)




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

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

	#ifdef KOTEK_GIT_WAS_FOUND
		#define KOTEK_USE_GIT_CURRENT_COMMIT ${KOTEK_GIT_CURRENT_COMMIT}
		#define KOTEK_USE_GIT_CURRENT_BRANCH_NAME ${KOTEK_GIT_CURRENT_BRANCH_NAME}
		#define KOTEK_USE_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH ${KOTEK_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH}
		#define KOTEK_USE_WHEN_YOU_GENERATED_SOLUTION ${KOTEK_WHEN_YOU_GENERATED_SOLUTION}
	#endif
	")
else()
	message(WARNING "[${PROJECT_NAME}]: can't find Git for generating preprocessors!")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_Git SHUTDOWN ShutdownModule_Core_Defines_Static_Git
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_static_git.h"
	"src/main_core_defines_static_git_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)