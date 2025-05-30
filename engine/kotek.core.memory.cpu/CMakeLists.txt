cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.cpu VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			find_package(mimalloc REQUIRED)
		endif()
	elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			file(GLOB nuget_mimalloc_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Mimalloc.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_mimalloc_folder}" MATCHES "Kotek.Packages.Mimalloc.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package mimalloc exists!")
			else()
				message(FATAL_ERROR "failed to find mimalloc package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()
		endif()
	else()
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			find_package(mimalloc REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/mimalloc/${CMAKE_BUILD_TYPE}/")
		endif()
	endif()
endif()

message("[${PROJECT_NAME}]: memory allocator for CPU = ${KOTEK_MEMORY_ALLOCATOR_CPU}")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_memory.h"
	"include/kotek_core_memory_cpu.h" 
	"include/offsetAllocator.hpp"
	"src/main_core_memory_cpu_dll.cpp"
	"src/kotek_std_memory.cpp"
	"src/offsetAllocator.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/memory")
if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: mimalloc package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/mimalloc-debug.lib")
			message("[${PROJECT_NAME}][Debug]: adding mimalloc-debug.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/mimalloc-debug.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/mimalloc.lib")
			message("[${PROJECT_NAME}][None-Debug]: adding mimalloc.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/mimalloc.lib)
		endif()

		set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_mimalloc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

		set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/mimalloc-debug.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/mimalloc-redirect.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_3 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/mimalloc-debug.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)

		set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/mimalloc.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/mimalloc-redirect.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_3 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/mimalloc.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)

		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_3}>"

			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_3}>"

			COMMAND_EXPAND_LISTS

			COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
		)
	endif()
else()
	if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC")
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc-static)
		endif()
	else()
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc)
		endif()
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)