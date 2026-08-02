cmake_minimum_required(VERSION 3.21)

project(kotek.render.nri VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

# NVIDIA NRI backend (task K11, phase 1): D3D12 device + swapchain + a clear
# color present; phase 2 (zircon Z5 P4): the swapchain's frame splits into
# Begin_Frame/End_Frame with the pass hook between them, recorded through
# the narrow ktkRenderFramePassContext surface. The NRI target itself is
# provided by the pinned clone in kotek/external/nri (see
# kotek/cmake/windows/nri.cmake)
set(to_include_core_files
	"include/kotek_render_device.h"
	"src/kotek_render_device.cpp"
	"include/kotek_render_swapchain.h"
	"src/kotek_render_swapchain.cpp"
	"include/kotek_render_frame_pass_context.h"
	"src/kotek_render_frame_pass_context.cpp"
	"include/kotek_render_resource_manager.h"
	"src/kotek_render_resource_manager.cpp")

set(to_include_module_files
	"include/kotek_render_nri.h"
	"src/main_render_nri_dll.cpp")

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Render_NRI SHUTDOWN ShutdownModule_Render_NRI
	${to_include_core_files}
	${to_include_module_files}
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/nri")
if (UNIX)
	set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

source_group("Core" FILES ${to_include_core_files})
source_group("Module" FILES ${to_include_module_files})

# the pch brings kotek's own headers; NRI headers come only from this
# module's own includes (module-boundary rule: no NRI types escape into
# interfaces or other modules)
kotek_target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)

# NRI's public include dir (Include/) propagates from the target; it is a
# static library (NRI_STATIC_LIBRARY=ON) so no runtime dll is involved
kotek_target_link_libraries(${PROJECT_NAME} PRIVATE NRI)
