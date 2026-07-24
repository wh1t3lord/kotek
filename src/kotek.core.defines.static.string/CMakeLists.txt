cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.string VERSION 1 LANGUAGES CXX)




if ("${KOTEK_UNICODE}" STREQUAL "")
	set(KOTEK_UNICODE "ON" CACHE INTERNAL "")
endif()

message("[${PROJECT_NAME}]: UNICODE is '${KOTEK_UNICODE}'")

if("${KOTEK_UNICODE}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DUNICODE -D_UNICODE -DKOTEK_UNICODE)
endif()

if ("${KOTEK_UNICODE}" STREQUAL "ON")
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

	#ifdef KOTEK_UNICODE
		#define KOTEK_USE_UNICODE
	#endif
	")
else()
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_String SHUTDOWN ShutdownModule_Core_Defines_Static_String
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_static_string.h"
	"src/main_core_defines_static_string_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)