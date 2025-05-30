cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.log VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(spdlog CONFIG REQUIRED)
	elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		file(GLOB nuget_spdlog_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Spdlog.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
		if ("${nuget_spdlog_folder}" MATCHES "Kotek.Packages.Spdlog.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
			message("[${PROJECT_NAME}][nuget]: package spdlog exists!")
		else()
			message(FATAL_ERROR "failed to find spdlog package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
		endif()	
	else()
		find_package(spdlog REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/") 
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_log.h"
	"include/kotek_core_log.h"
	"src/main_core_log_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_spdlog_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
		message("[${PROJECT_NAME}]: spdlog package included directory")
		target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_spdlog_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/spdlogd.lib")
		message("[${PROJECT_NAME}][Debug]: adding spdlogd.lib to Debug configuration")
		target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/spdlogd.lib)
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_spdlog_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/spdlog.lib")
		message("[${PROJECT_NAME}][None-Debug]: adding spdlog.lib to not Debug configurations")
		target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_spdlog_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/spdlog.lib)
	endif()

	set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_spdlog_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

	set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/spdlogd.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
	set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/spdlogd.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
	
	set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/spdlog.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
	set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/spdlog.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
	

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

		COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
		COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"

		COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
		COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"

		COMMAND_EXPAND_LISTS

		COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
   )

   target_compile_definitions(${PROJECT_NAME} PUBLIC SPDLOG_USE_STD_FORMAT)
else()
	target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog_header_only)
endif()