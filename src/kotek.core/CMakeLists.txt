cmake_minimum_required(VERSION 3.21)

project(kotek.core VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")

			if ("${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
				find_package(Boost COMPONENTS json CONFIG REQUIRED)
			else()

				find_package(Boost COMPONENTS json CONFIG REQUIRED)
				
				if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
					find_package(Boost COMPONENTS filesystem CONFIG REQUIRED)
				endif()
				
			endif()

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

			if ("${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
				find_package(Boost COMPONENTS json CONFIG REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
			else()
				find_package(Boost COMPONENTS json CONFIG REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

				if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
					find_package(Boost COMPONENTS filesystem CONFIG REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
				endif()
			endif()
		endif()
endif()

if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "ON" AND NOT "${KOTEK_LINKAGE}" STREQUAL "PLUGIN")
	# tests are a static-linkage feature: they instantiate concrete classes
	# from feature modules (ktkFileSystem, ktkFileSystem_VFM,
	# ktkFrameworkConfig, ...), which is forbidden in PLUGIN mode (no link
	# edges between plugin dlls)
	add_subdirectory("tests/kotek.core.tests.plugin")
	message("[${PROJECT_NAME}]: adding tests for runtime in project ${PROJECT_NAME}")
	set(to_include_tests 
		"tests/kotek_core_test_filesystem.cpp"
		"tests/kotek_core_test_json.cpp"
		"tests/kotek_core_test_string.cpp"
		"tests/kotek_core_test_container_deque.cpp"
		"tests/kotek_core_test_container_vector.cpp"
		"tests/kotek_core_test_container_unordered_set.cpp"
		"tests/kotek_core_test_container_unordered_map.cpp"
		"tests/kotek_core_test_container_set.cpp"
		"tests/kotek_core_test_container_queue.cpp"
		"tests/kotek_core_test_container_map.cpp"
		"tests/kotek_core_test_container_list.cpp"
		"tests/kotek_core_test_plugin_override.cpp"
		"tests/kotek_core_test_math_backends.cpp"
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

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core SHUTDOWN ShutdownModule_Core 
	"src/main_core_dll.cpp"
	"include/kotek_core.h"
	"include/kotek_json_casting_math_matrix.h"
	"include/kotek_json_casting_math_vector.h"
	"include/kotek_json_casting_std_vector.h"
	"include/kotek_json_casting_std_map.h"
	"include/kotek_json_casting_string.h"
	"include/kotek_json_casting_other.h"
	"include/kotek_hash_aliases.h"
	${to_include_tests}
)

if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_TESTS_RUNTIME}" STREQUAL "ON" AND NOT "${KOTEK_LINKAGE}" STREQUAL "PLUGIN")
	# plugin override tests (task K21): absolute path of the test-double
	# dll (generator expression) — the tests copy it into their isolated
	# plugins/ folders; the target is defined by the add_subdirectory above
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		KOTEK_TEST_PLUGIN_OVERRIDE_DLL_PATH="$<TARGET_FILE:kotek.core.tests.plugin>")
	add_dependencies(${PROJECT_NAME} kotek.core.tests.plugin)
endif()

# math backend parity tests (kotek_core_test_math_backends.cpp) compute
# reference values with raw GLM calls; under the DXM backend glm does not
# propagate from kotek.core.math, so pull it here explicitly
if ("${KOTEK_TESTS}" STREQUAL "ON" AND "${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		file(GLOB nuget_glm_folder_tests RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Glm.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
		if ("${nuget_glm_folder_tests}" MATCHES "Kotek.Packages.Glm.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
			target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glm_folder_tests}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		else()
			message(FATAL_ERROR "[${PROJECT_NAME}]: glm nuget package is required for the math backend tests")
		endif()
	else()
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glm CONFIG REQUIRED)
		else()
			find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
		kotek_target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
	endif()
endif()


if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if (WIN32)
			if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		
				if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/boost_filesystem-vc140-mt-gd.lib")
					message("[${PROJECT_NAME}][Debug]: adding boost_filesystem-vc140-mt-gd.lib to Debug configuration")
					kotek_target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/boost_filesystem-vc140-mt-gd.lib)
				endif()

				if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/boost_filesystem-vc140-mt.lib")
					message("[${PROJECT_NAME}][None-Debug]: adding boost_filesystem-vc140-mt.lib to not Debug configurations")
					kotek_target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/boost_filesystem-vc140-mt.lib)
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
			kotek_target_link_libraries(${PROJECT_NAME} PUBLIC 
				GTest::gtest 
				GTest::gmock
			)
		endif()
	else()

		kotek_target_link_libraries(${PROJECT_NAME} PUBLIC
			Boost::json
		)

		if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
			kotek_target_link_libraries(${PROJECT_NAME} PUBLIC 
				Boost::headers 
				Boost::filesystem
			)
		endif()

		if ("${KOTEK_TESTS}" STREQUAL "ON")
			kotek_target_link_libraries(${PROJECT_NAME} PUBLIC 
				GTest::gtest 
				GTest::gmock
			)
		endif()
	endif()
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.console)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.math)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.format)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.log)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window_manager)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.ecs)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.input)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.utility)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.engine_config)