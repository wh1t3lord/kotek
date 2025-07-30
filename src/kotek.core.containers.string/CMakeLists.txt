cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.string VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
				find_package(etl CONFIG REQUIRED)
			endif()
			find_package(utf8cpp CONFIG REQUIRED)

			if ("${KOTEK_TESTS}" STREQUAL "ON")
				find_package(GTest CONFIG REQUIRED)
			endif()
		elseif("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
				file(GLOB nuget_etl_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Etl.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
				if ("${nuget_etl_folder}" MATCHES "Kotek.Packages.Etl.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
					message("[${PROJECT_NAME}][nuget]: package etl exists!")
				else()
					message(FATAL_ERROR "failed to find etl package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
				endif()
			endif()

			file(GLOB nuget_utf8cpp_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Utfcpp.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)

			if ("${nuget_utf8cpp_folder}" MATCHES "Kotek.Packages.Utfcpp.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package utfcpp exists!")
			else()
				message(FATAL_ERROR "failed to find utfcpp package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()

			if ("${KOTEK_TESTS}" STREQUAL "ON")
				find_package(GTest CONFIG REQUIRED)
			endif()
		else()
			if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
				find_package(etl REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
			endif()
			find_package(utf8cpp CONFIG REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

			if ("${KOTEK_TESTS}" STREQUAL "ON")
				find_package(GTest REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
			endif()
		endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"tests/kotek_core_test_string.cpp"
	"include/kotek_std_alias_string.h"
	"include/kotek_std_alias_static_string.h"
	"include/kotek_std_alias_hybrid_string.h"
	"include/kotek_core_containers_string.h"
	"src/main_core_containers_string_dll.cpp"
	"src/kotek_std_alias_string.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.lexical)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.hash)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.format)


if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_etl_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: etl package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_etl_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_utf8cpp_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
		message("[${PROJECT_NAME}]: utf8cpp package included directory")
		target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_utf8cpp_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
	endif()

	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
		GTest::gtest 
		GTest::gmock
		)
	endif()
else()
	target_link_libraries(${PROJECT_NAME} PUBLIC utf8::cpp utf8cpp::utf8cpp)

	if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC etl::etl)
	endif()

	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
		GTest::gtest 
		GTest::gmock
		)
	endif()
endif()