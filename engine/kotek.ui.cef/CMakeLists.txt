cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.cef VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
	message("[Engine]: searching package for CEF!")
endif()

if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
set(IMPLEMENTATION_FILES_CEF 
	"include/kotek_ui_game_ui_manager.h"
	"src/kotek_ui_game_ui_manager.cpp"
	"include/kotek_ui_cef_application.h"
	"src/kotek_ui_cef_application.cpp")
else()
set(IMPLEMENTATION_FILES_CEF "")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_cef.h"
	${IMPLEMENTATION_FILES_CEF}
	"src/main_ui_cef_dll.cpp")

if (WIN32)
	# There's no package so we need to use our pre-compiled solution
	if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
		message("[Engine]: CEF is found!")
		target_include_directories(${PROJECT_NAME} PUBLIC ${PATH_TO_CEF})
		target_link_directories(${PROJECT_NAME} PUBLIC ${PATH_TO_CEF_LIB})
	else()
		message(FATAL_ERROR "can't find dependency folder of pre-compiled CEF (Chromium Embeddeed Framework). Disable this project in order to compile the solution.")
	endif()
endif()


target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)