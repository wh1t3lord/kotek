cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Enum SHUTDOWN ShutdownModule_Core_Enum
	"include/kotek_core_enum.h" 
	"src/main_core_enum_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.core)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render)