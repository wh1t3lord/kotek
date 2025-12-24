cmake_minimum_required(VERSION 3.21)

project(kotek.core.os.win32 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	# TODO: add SDL
	if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glfw3 REQUIRED)

			if (NOT "${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
				find_package(unofficial-angle CONFIG REQUIRED)
			endif()

			if ("${KOTEK_BGFX}" STREQUAL "ON")
				find_package(bgfx REQUIRED)
			endif()

			if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
				find_package(zstd CONFIG REQUIRED)
				find_package(Threads REQUIRED)
			elseif("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "SHARED")
				find_package(ZLIB REQUIRED)
			endif()
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")

			if (NOT "${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
				find_package(unofficial-angle CONFIG REQUIRED)
			endif()

			if ("${KOTEK_BGFX}" STREQUAL "ON")
				find_package(bgfx CONFIG REQUIRED)
			endif()

			file(GLOB nuget_glfw3_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Glfw3.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_glfw3_folder}" MATCHES "Kotek.Packages.Glfw3.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package glfw3 exists!")
			else()
				message(FATAL_ERROR "failed to find glfw3 package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()						

			if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
				find_package(zstd CONFIG REQUIRED)
				find_package(Threads REQUIRED)
			elseif("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "SHARED")
				find_package(ZLIB REQUIRED)
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
	"include/kotek_core_os_win32.h"
	"src/main_core_os_win32_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/os/vendor")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.win32)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)

# TODO: flag for using gles detection like for vulkan KOTEK_VULKAN but KOTEK_GLES and specify what version of gles and shipping
if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: glfw3 package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/glfw3dll.lib")
			message("[${PROJECT_NAME}][Debug]: adding glfw3dll.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/glfw3dll.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/glfw3dll.lib")
			message("[${PROJECT_NAME}][None-Debug]: glfw3dll.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/glfw3dll.lib)
		endif()

		set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glfw3_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

		set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/glfw3.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/glfw3.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)

		set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/glfw3.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/glfw3.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)

		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"			
			COMMAND_EXPAND_LISTS
			COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
	   )
	endif()

	if (NOT "${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			unofficial::angle::libEGL
			unofficial::angle::libANGLE
			unofficial::angle::libGLESv2
		)
	endif()

	if ("${KOTEK_BGFX}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			bgfx::bx 
			bgfx::bgfx 
			bgfx::bimg 
			bgfx::bimg_decode
		)
	endif()
elseif("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
		find_package(zstd CONFIG REQUIRED)
		find_package(Threads REQUIRED)
	elseif("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "SHARED")
		find_package(ZLIB REQUIRED)
	endif()

	if (NOT "${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			unofficial::angle::libEGL
			unofficial::angle::libANGLE
			unofficial::angle::libGLESv2
		)
	endif()

	if ("${KOTEK_BGFX}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			bgfx::bx 
			bgfx::bgfx 
			bgfx::bimg 
			bgfx::bimg_decode
		)
	endif()
else()
	message(FATAL_ERROR "provide implementation for custom folder and compiled by user")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
endif()

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	# nothing here
else()
	if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
		target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
	endif()
endif()
