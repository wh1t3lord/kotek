cmake_minimum_required(VERSION 3.21)

project(kotek.core.window.win32 VERSION 1 LANGUAGES CXX)

# own no-dependency Win32 window backend (task K17): raw Win32, no
# third-party libraries at all — there is intentionally no find_package here

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Window_WIN32 SHUTDOWN ShutdownModule_Core_Window_WIN32
	"include/kotek_core_window_win32.h"
	"include/kotek_std_window_win32.h"
	"src/kotek_std_window_win32.cpp"
	"src/main_core_window_win32_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/window management/vendor")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
# the phase-2 WndProc->input bridge consumes ktkInputPlatformBackendArgs_WINAPI
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.input)
