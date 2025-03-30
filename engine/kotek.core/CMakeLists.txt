cmake_minimum_required(VERSION 3.19.3)

project(kotek.core VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(Boost COMPONENTS json filesystem REQUIRED)

			if ("${KOTEK_TESTS}" STREQUAL "ON")
				find_package(GTest CONFIG REQUIRED)
			endif()
		elseif("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			file(GLOB nuget_boost_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Boost.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_boost_folder}" MATCHES "Kotek.Packages.Boost.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package boost exists!")
			else()
				message(FATAL_ERROR "failed to find boost package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()

			if ("${KOTEK_TESTS}" STREQUAL "ON")
				find_package(GTest CONFIG REQUIRED)
			endif()
		else()
			if ("${KOTEK_TESTS}" STREQUAL "ON")
				find_package(GTest REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
			endif()

			find_package(Boost COMPONENTS json filesystem REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "ON")
	message("[${PROJECT_NAME}]: adding tests for runtime in project ${PROJECT_NAME}")
	set(to_include_tests 
		"tests/kotek_core_test_filesystem.cpp"
		"tests/kotek_core_test_json.cpp"
		"tests/kotek_core_test_string.cpp"
	)
elseif("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "OFF")
	# TODO: add support for own projects for unit testing
	message("[${PROJECT_NAME}]: creating test projects for project ${PROJECT_NAME}")
	set(to_include_tests "")
else()
	message("[${PROJECT_NAME}]: tests are disabled for project ${PROJECT_NAME}")
	set(to_include_tests "")
endif()

message("[${PROJECT_NAME}]: files to attach (KOTEK_TESTS): ${to_include_tests}")

add_library(${PROJECT_NAME} STATIC 
	"src/main_core_dll.cpp"
	"include/kotek_core.h"
	"include/kotek_json_casting_math_matrix.h"
	"include/kotek_json_casting_math_vector.h"
	"include/kotek_json_casting_std_vector.h"
	"include/kotek_json_casting_std_map.h"
	"include/kotek_json_casting_string.h"
	"include/kotek_json_casting_other.h"
	${to_include_tests}
)


if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if (WIN32)
			if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		
				if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/boost_filesystem-vc140-mt-gd.lib")
					message("[${PROJECT_NAME}][Debug]: adding boost_filesystem-vc140-mt-gd.lib to Debug configuration")
					target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/boost_filesystem-vc140-mt-gd.lib)
				endif()

				if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/boost_filesystem-vc140-mt.lib")
					message("[${PROJECT_NAME}][None-Debug]: adding boost_filesystem-vc140-mt.lib to not Debug configurations")
					target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/boost_filesystem-vc140-mt.lib)
				endif()

				set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

				set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/boost_filesystem-vc143-mt-gd-x64-1_84.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
				set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/boost_filesystem-vc143-mt-gd-x64-1_84.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
				set(copy_local_command_debug_3 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/boost_json-vc143-mt-gd-x64-1_84.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
				set(copy_local_command_debug_4 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/boost_json-vc143-mt-gd-x64-1_84.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		


				set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/boost_filesystem-vc143-mt-x64-1_84.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
				set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/boost_filesystem-vc143-mt-x64-1_84.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
				set(copy_local_command_release_3 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/boost_json-vc143-mt-x64-1_84.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
				set(copy_local_command_release_4 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/boost_json-vc143-mt-x64-1_84.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		
				add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
					COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"
					COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_3}>"
					COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_4}>"
					COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
					COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"	
					COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_3}>"
					COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_4}>"			
					COMMAND_EXPAND_LISTS
					COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
				)
			endif()

		else()
			message(FATAL_ERROR "provide implementation for other platforms")
		endif()

		if ("${KOTEK_TESTS}" STREQUAL "ON")
			target_link_libraries(${PROJECT_NAME} PUBLIC 
				GTest::gtest 
				GTest::gmock
			)
		endif()
	else()
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			Boost::headers 
			Boost::json 
			Boost::filesystem
		)

		if ("${KOTEK_TESTS}" STREQUAL "ON")
			target_link_libraries(${PROJECT_NAME} PUBLIC 
				GTest::gtest 
				GTest::gmock
			)
		endif()
	endif()
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.console)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.format)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.log)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.resource_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.ecs)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.input)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.utility)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.engine_config)