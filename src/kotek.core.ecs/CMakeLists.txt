cmake_minimum_required(VERSION 3.21)

project(kotek.core.ecs VERSION 1 LANGUAGES CXX)

message("[${PROJECT_NAME}]: KOTEK_ECS_BACKEND=${KOTEK_ECS_BACKEND}")
if ("${KOTEK_ECS_BACKEND}" STREQUAL "ENTT")

	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		file(GLOB nuget_entt_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Entt.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
		if ("${nuget_entt_folder}" MATCHES "Kotek.Packages.Entt.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
			message("[${PROJECT_NAME}][nuget]: package entt exists!")
		else()
			message(FATAL_ERROR "failed to find entt package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
		endif()	
	else()
		find_package(EnTT REQUIRED)
	endif()

endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_ecs.h"
	"src/main_core_ecs_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.ecs)

if ("${KOTEK_ECS_BACKEND}" STREQUAL "ENTT")

	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_entt_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: EnTT package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_entt_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()
	else()
		target_link_libraries(${PROJECT_NAME} PUBLIC EnTT::EnTT)
	endif()

endif()