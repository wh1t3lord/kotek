cmake_minimum_required(VERSION 3.21)

project(kotek.game VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
	if ("${KOTEK_USER_GAME_PROJECT_NAME}" STREQUAL "")
		message(FATAL_ERROR "specify KOTEK_USER_GAME_PROJECT_NAME of folder where your root source directory is located. e.g. see zircon example")
	endif()

	include_directories(../../../${KOTEK_USER_GAME_PROJECT_NAME})
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Game SHUTDOWN ShutdownModule_Game
	"include/kotek_engine.h"
	"include/kotek_game.h"
	"src/kotek_update.cpp"
	"include/kotek_callbacks.h"
	# the splash overlay is created by the engine bootstrapper BEFORE any
	# module/plugin is initialized, so it cannot live in a plugin module
	# (moved from kotek.core.window)
	"include/kotek_window_splash.h"
	"src/kotek_window_splash.cpp"
	"src/main_game_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/user dll loading")
kotek_target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui)

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
	if ("${KOTEK_USER_GAME_MODULE_FOR_LINK_NAME}" STREQUAL "")
		message(FATAL_ERROR "you must specify KOTEK_USER_GAME_MODULE_FOR_LINK_NAME for linking to kotek.game project. See zircon example ")
	endif()

	kotek_target_link_libraries(${PROJECT_NAME} PUBLIC ${KOTEK_USER_GAME_MODULE_FOR_LINK_NAME})
endif()