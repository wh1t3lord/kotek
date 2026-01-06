cmake_minimum_required(VERSION 3.21)

project(kotek.game VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
	if ("${KOTEK_USER_GAME_PROJECT_NAME}" STREQUAL "")
		message(FATAL_ERROR "specify KOTEK_USER_GAME_PROJECT_NAME of folder where your root source directory is located. e.g. see zircon example")
	endif()

	include_directories(../../../${KOTEK_USER_GAME_PROJECT_NAME})
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_engine.h"
	"include/kotek_game.h"
	"src/kotek_update.cpp"
	"include/kotek_callbacks.h"
	"src/main_game_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/user dll loading")
target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui)

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
	if ("${KOTEK_USER_GAME_MODULE_FOR_LINK_NAME}" STREQUAL "")
		message(FATAL_ERROR "you must specify KOTEK_USER_GAME_MODULE_FOR_LINK_NAME for linking to kotek.game project. See zircon example ")
	endif()

	target_link_libraries(${PROJECT_NAME} PUBLIC ${KOTEK_USER_GAME_MODULE_FOR_LINK_NAME})
endif()