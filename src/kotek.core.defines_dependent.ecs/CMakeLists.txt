cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines_dependent.ecs VERSION 1 LANGUAGES CXX)




if ("${KOTEK_ECS_BACKEND}" STREQUAL "ENTT")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_ECS_BACKEND_ENTT)
	message(STATUS "[${PROJECT_NAME}] selected ecs backend: ENTT")
elseif("${KOTEK_ECS_BACKEND}" STREQUAL "PICO")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_ECS_BACKEND_PICO)
	message(STATUS "[${PROJECT_NAME}] selected ecs backend: PICO")
elseif("${KOTEK_ECS_BACKEND}" STREQUAL "")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_ECS_BACKEND_PICO)
	set(KOTEK_ECS_BACKEND "PICO" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: you didn't specify any ecs backend so will be selected PICO")
else()
	message(FATAL_ERROR "unsupported backend if you want to see in kotek framework report to developers: https://github.com/wh1t3lord/kotek/issues")
endif()

file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once
		#ifdef KOTEK_ECS_BACKEND_ENTT
			#define KOTEK_USE_ECS_BACKEND_ENTT
		#endif

		#ifdef KOTEK_ECS_BACKEND_PICO
			#define KOTEK_USE_ECS_BACKEND_PICO
		#endif
")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_dependent_preprocessors.h"
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_dependent_ecs.h"
	"src/main_core_defines_dependent_ecs_dll.cpp"
)
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/dependent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
