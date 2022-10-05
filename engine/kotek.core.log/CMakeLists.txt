cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.log VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		find_package(Boost COMPONENTS log REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
	endif()
else()
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		find_package(Boost COMPONENTS log REQUIRED)
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_log.h"
	"include/kotek_core_log.h"
	"src/main_core_log_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	target_link_libraries(${PROJECT_NAME} PUBLIC 
		Boost::headers 
		Boost::log
	)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)