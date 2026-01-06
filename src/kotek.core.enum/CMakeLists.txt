cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_enum.h" 
	"src/main_core_enum_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render)