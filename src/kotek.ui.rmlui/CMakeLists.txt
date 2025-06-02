cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.rmlui VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Freetype CONFIG REQUIRED)
find_package(RmlUi 6.0 CONFIG REQUIRED)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_game_ui_manager.h"
	"src/kotek_ui_game_ui_manager.cpp"

	"include/kotek_ui_rmlui.h"
	"src/main_ui_rmlui_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui/vendor")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
	target_compile_definitions(${PROJECT_NAME} PUBLIC -DRMLUI_STATIC_LIB)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Freetype::Freetype)
target_link_libraries(${PROJECT_NAME} PUBLIC RmlUi::RmlUi)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window)
