cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.queue VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS headers container REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_queue.h"
	"include/kotek_core_containers_queue.h"
	"src/main_core_containers_queue_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers Boost::container)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.deque)