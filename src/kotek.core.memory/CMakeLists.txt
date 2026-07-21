cmake_minimum_required(VERSION 3.21)

project(kotek.core.memory VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




kotek_add_library(${PROJECT_NAME}
	"include/kotek_core_memory.h" 
	"src/main_core_memory_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/memory")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.gpu)