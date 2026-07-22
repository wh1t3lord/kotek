cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.queue VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_Queue SHUTDOWN ShutdownModule_Core_Containers_Queue
	"include/kotek_std_alias_queue.h"
	"include/kotek_std_alias_hybrid_queue.h"
	"include/kotek_std_alias_static_queue.h"
	"include/kotek_core_containers_queue.h"
	"src/main_core_containers_queue_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.deque)