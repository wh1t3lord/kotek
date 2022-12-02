cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.vld VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_memory.h"
	"include/kotek_core_memory_vld.h" 
	"src/main_core_memory_vld_dll.cpp"
)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if(WIN32)
	if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			message("[${PROJECT_NAME}]: vcpkg doesn't support VLD package yet")
		else()
			list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_VLD_FOUND)
			target_include_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/vld/include/")
			target_link_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/vld/lib/Win64/")
		endif()
	endif()
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)