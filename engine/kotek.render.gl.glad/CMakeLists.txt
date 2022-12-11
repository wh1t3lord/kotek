cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.gl.glad VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "SHARED")
	list(APPEND KOTEK_OUTPUT_PRIVATE_FLAGS -DGLAD_GLAPI_EXPORT_BUILD)
	list(APPEND KOTEK_OUTPUT_FLAGS -DGLAD_GLAPI_EXPORT)
endif()

# This is for preventing other projects that doesn't need a glad at all search for <glad/glad.h> header, because it means that we break the connection between libraries and we need to create some sort of visibility where other libraries that doesn't have a target_link_libraries with this library search for glad/glad.h
list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_GLAD_PREPROCESSOR_VISIBILITY)

add_library(${PROJECT_NAME} ${KOTEK_DEVELOPMENT_TYPE}
	"include/glad/glad.h"
	"include/KHR/khrplatform.h"
	"src/glad.cpp"
	"include/kotek_render_gl_glad.h"
	"src/main_render_gl_glad_dll.cpp")

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "SHARED")
	target_compile_definitions(${PROJECT_NAME} PRIVATE ${KOTEK_OUTPUT_PRIVATE_FLAGS})
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)