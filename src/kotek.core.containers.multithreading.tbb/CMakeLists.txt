cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.multithreading.tbb VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(TBB REQUIRED)
	elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		file(GLOB nuget_onetbb_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Onetbb.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
		if ("${nuget_onetbb_folder}" MATCHES "Kotek.Packages.Onetbb.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
			message("[${PROJECT_NAME}][nuget]: package onetbb exists!")
		else()
			message(FATAL_ERROR "failed to find onetbb package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
		endif()
	else()
		find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_tbb.h"
	"include/kotek_core_containers_multithreading_tbb.h"
	"src/main_core_containers_multithreading_tbb_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/multithreading")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
		message("[${PROJECT_NAME}]: onetbb package included directory")
		target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
	endif()

	if (WIN32)
		# Debug
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbb12_debug.lib")
			message("[${PROJECT_NAME}][Debug]: adding tbb12_debug.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbb12_debug.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbbbind_2_5_debug.lib")
			message("[${PROJECT_NAME}][Debug]: adding tbbbind_2_5_debug.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbbbind_2_5_debug.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbbmalloc_debug.lib")
			message("[${PROJECT_NAME}][Debug]: adding tbbmalloc_debug.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbbmalloc_debug.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbbmalloc_proxy_debug.lib")
			message("[${PROJECT_NAME}][Debug]: adding tbbmalloc_proxy_debug.lib to Debug configuration")
			target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbbmalloc_proxy_debug.lib)
		endif()

		# Release
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbb12.lib")
			message("[${PROJECT_NAME}][None-Debug]: adding tbb12.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbb12.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbbbind_2_5.lib")
			message("[${PROJECT_NAME}][None-Debug]: adding tbbbind_2_5.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbbbind_2_5.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbbmalloc_proxy.lib")
			message("[${PROJECT_NAME}][None-Debug]: adding tbbmalloc_proxy.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbbmalloc_proxy.lib)
		endif()

		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbbmalloc.lib")
			message("[${PROJECT_NAME}][None-Debug]: adding tbbmalloc.lib to not Debug configurations")
			target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbbmalloc.lib)
		endif()

		# Post comand = copy bins

		set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_onetbb_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

		set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbb12_debug.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbbbind_2_5_debug.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_3 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbbmalloc_debug.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_4 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbbmalloc_proxy_debug.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_5 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbb12_debug.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_6 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbbbind_2_5_debug.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_7 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbbmalloc_debug.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
		set(copy_local_command_debug_8 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/tbbmalloc_proxy_debug.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)

		set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbb12.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbbbind_2_5.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_3 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbbmalloc.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_4 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbbmalloc_proxy.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_5 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbb12.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_6 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbbbind_2_5.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_7 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbbmalloc.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
		set(copy_local_command_release_8 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/tbbmalloc_proxy.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)


		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_3}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_4}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_5}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_6}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_7}>"
			COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_8}>"

			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_3}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_4}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_5}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_6}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_7}>"
			COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_8}>"

			COMMAND_EXPAND_LISTS

			COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
   		)

	endif()
else()
	target_link_libraries(${PROJECT_NAME} PUBLIC TBB::tbb)
endif()