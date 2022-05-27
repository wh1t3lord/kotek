cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines_dependent.message VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS log REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_dependent_preprocessors.h"
	"include/kotek_core_defines_dependent_message.h"
	"src/main_core_defines_dependent_message_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.text)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers Boost::log)