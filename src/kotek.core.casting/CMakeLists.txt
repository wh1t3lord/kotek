cmake_minimum_required(VERSION 3.21)

project(kotek.core.casting VERSION 1 LANGUAGES CXX)




if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(Boost REQUIRED)
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			# Nothing here probably
		else()
			kotek_find_package(Boost REQUIRED)
		endif()
	endif()
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Casting SHUTDOWN ShutdownModule_Core_Casting
	"include/kotek_core_casting.h"
	"src/main_core_casting_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	if (NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		kotek_target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
	endif()
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/casting")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.lexical)