cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.json VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(Boost COMPONENTS json REQUIRED)
	elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		file(GLOB nuget_boost_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Boost.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
		if ("${nuget_boost_folder}" MATCHES "Kotek.Packages.Boost.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
			message("[${PROJECT_NAME}][nuget]: package boost exists!")
		else()
			message(FATAL_ERROR "failed to find boost package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
		endif()
	else()
		find_package(Boost COMPONENTS json REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_json.h"
	"include/kotek_std_json.h"
	"src/kotek_std_json.cpp"
	"include/kotek_core_containers_json.h"
	"src/main_core_containers_json_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: boost package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/boost_json-vc140-mt-gd.lib")
			message("[${PROJECT_NAME}][Debug]: adding boost_json-vc140-mt-gd.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/boost_json-vc140-mt-gd.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/boost_json-vc140-mt.lib")
			message("[${PROJECT_NAME}][None-Debug]: adding boost_json-vc140-mt.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/boost_json-vc140-mt.lib)
		endif()
	else()
		target_link_libraries(${PROJECT_NAME} PUBLIC  
			Boost::json
		)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)
