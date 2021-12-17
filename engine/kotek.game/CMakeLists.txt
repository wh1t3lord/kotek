cmake_minimum_required(VERSION 3.19.3)

project(kotek.game VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
include_directories("../../deps/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

 
find_package(glfw3 3.3 REQUIRED PATHS "../../deps/")
find_package(TBB REQUIRED PATHS "../../deps/") 

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	find_package(glm REQUIRED PATHS "../../deps/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")

if(glfw3_FOUND)
	message("+ GLFW is found")
else()
	message("- GLFW is not found")
endif()

add_library(${PROJECT_NAME} STATIC
	"kotek_engine.h"
	"kotek_game.h"
	"kotek_update.cpp"
	"kotek_callbacks.h"
	"main_game_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} kotek.render)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} TBB::tbb)