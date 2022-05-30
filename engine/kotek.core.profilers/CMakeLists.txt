cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.profilers VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	message("[Engine]: adding files of CPU profiler in project ${PROJECT_NAME}")
	set(to_include_cpu_profiler
		"tracy/Tracy.hpp"
		"tracy/TracyClient.cpp")

	if ("${KOTEK_GPU_PROFILER}" STREQUAL "ON")
		message("[Engine]: adding files of GPU profiler in project ${PROJECT_NAME}")
		set(to_include_gpu_profiler 
			"tracy/TracyD3D11.hpp"
			"tracy/TracyD3D12.hpp"
			"tracy/TracyOpenGL.hpp"
			"tracy/TracyVulkan.hpp")
	endif()

else()
	set(to_include_cpu_profiler "")
	set(to_include_gpu_profiler "")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_profilers.h"
	"include/kotek_profiler.h"
	"src/kotek_profiler.cpp"
	${to_include_cpu_profiler}
	${to_include_gpu_profiler}
	"src/main_core_profilers_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers.gpu)