cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.cef VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CEF REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

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
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui/vendor")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)