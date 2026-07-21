cmake_minimum_required(VERSION 3.21)

project(kotek.render VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

kotek_add_library(${PROJECT_NAME}
	"include/kotek_render.h"
	"src/main_render_dll.cpp"
)

if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared)

if (WIN32)
	# DEPRECATED: until you write the whole vulkan renderer
#target_link_libraries(${PROJECT_NAME} kotek.render.dx12)
endif()


target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl)

# TODO: Vulkan you implement in the last stage of development. First gl and gl without shaderc!
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.vk) 

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.bgfx)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.software)

# angle modules are only added when KOTEK_CONFIGURATION_TYPE is
# not "minimal" (see kotek/CMakeLists.txt)
if (TARGET kotek.render.angle.gles23)
	target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.angle.gles23)
	target_compile_definitions(${PROJECT_NAME} PRIVATE KOTEK_USE_RENDER_ANGLE_GLES23)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render")