cmake_minimum_required(VERSION 3.19.3)

project(kotek.game VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_engine.h"
	"include/kotek_game.h"
	"src/kotek_update.cpp"
	"include/kotek_callbacks.h"
	"src/main_game_dll.cpp"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui)