cmake_minimum_required(VERSION 3.21)

project(kotek.core.os.linux VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	# TODO: add SDL
	if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glfw3 REQUIRED)
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			file(GLOB nuget_glfw3_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Glfw3.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_glfw3_folder}" MATCHES "Kotek.Packages.Glfw3.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package glfw3 exists!")
			else()
				message(FATAL_ERROR "failed to find glfw3 package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()		
		else()
			find_package(glfw3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	find_package(Vulkan REQUIRED)
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_os.h"
	"include/kotek_core_os_linux.h"
	"src/main_core_os_linux_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/os/vendor")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.linux)

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
endif()

if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: glfw3 package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()

		if (LINUX)
			message(FATAL_ERROR "provide implementation")
		endif()
	else()
		target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)
