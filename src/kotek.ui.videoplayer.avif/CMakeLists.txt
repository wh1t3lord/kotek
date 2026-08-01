cmake_minimum_required(VERSION 3.21)

project(kotek.ui.videoplayer.avif VERSION 1 LANGUAGES CXX)

# TODO: try to find the stuff from vcpkg, but you should add guard because it depends dav1d doesn't use cmake at all




if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	file(GLOB nuget_dav1d_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Dav1d.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
	if ("${nuget_dav1d_folder}" MATCHES "Kotek.Packages.Dav1d.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
		message("[${PROJECT_NAME}][nuget]: package dav1d exists!")
	else()
		message(FATAL_ERROR "failed to find dav1d package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
	endif()
else()
	# vcpkg AND manual modes (K10): pkg-config resolves dav1d via
	# PKG_CONFIG_PATH — the vcpkg toolchain sets it; in manual mode the
	# convention folder <folder>/dav1d/lib/pkgconfig and every candidate
	# prefix's lib/pkgconfig are picked up automatically
	if (NOT "${KOTEK_DEPS_FOLDER_PATH}" STREQUAL "" AND EXISTS "${KOTEK_DEPS_FOLDER_PATH}/dav1d/lib/pkgconfig")
		set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH};${KOTEK_DEPS_FOLDER_PATH}/dav1d/lib/pkgconfig")
	endif()

	# manual mode (2026-08-01, deps-manual CI leg): pkgconf is a TOOL, so
	# do not make a Windows user install it — resolve it from the
	# dependency prefixes themselves (vcpkg-built trees ship
	# tools/pkgconf/pkgconf.exe next to lib/pkgconfig/dav1d.pc).
	# Candidates: CMAKE_PREFIX_PATH (the wrapper's fallback tier, set as
	# an env var by CI/users) plus the convention folder.
	if (NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		set(_kotek_dav1d_prefixes ${CMAKE_PREFIX_PATH} $ENV{CMAKE_PREFIX_PATH})
		if (NOT "${KOTEK_DEPS_FOLDER_PATH}" STREQUAL "")
			list(APPEND _kotek_dav1d_prefixes "${KOTEK_DEPS_FOLDER_PATH}/dav1d")
		endif()
		foreach(_kotek_dav1d_prefix IN LISTS _kotek_dav1d_prefixes)
			if (EXISTS "${_kotek_dav1d_prefix}/lib/pkgconfig")
				set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH};${_kotek_dav1d_prefix}/lib/pkgconfig")
			endif()
		endforeach()
		if (NOT PKG_CONFIG_EXECUTABLE)
			find_program(PKG_CONFIG_EXECUTABLE
				NAMES pkgconf.exe pkg-config.exe pkgconf pkg-config
				PATHS ${_kotek_dav1d_prefixes}
				PATH_SUFFIXES tools/pkgconf)
		endif()
	endif()

	find_package(PkgConfig REQUIRED)
	# GLOBAL: the imported target must be visible outside this directory —
	# PLUGIN mode re-applies it to consumers via kotek_finalize_plugin_links
	pkg_check_modules(dav1d REQUIRED IMPORTED_TARGET GLOBAL dav1d)
endif()


kotek_add_library(${PROJECT_NAME} INIT InitializeModule_UI_VideoPlayer_AVIF SHUTDOWN ShutdownModule_UI_VideoPlayer_AVIF
	"include/kotek_ui_videoplayer_avif.h"
	"src/main_ui_videoplayer_avif_dll.cpp"
	"include/kotek_ui_videoplayer.h"
	"src/kotek_ui_videoplayer.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui/vendor")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
		message("[${PROJECT_NAME}]: dav1d package included directory")
		target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/dav1d.lib")
		message("[${PROJECT_NAME}][Debug]: adding dav1d.lib to Debug configuration")
		kotek_target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/dav1d.lib)
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/dav1d.lib")
		message("[${PROJECT_NAME}][None-Debug]: adding dav1d.lib to not Debug configurations")
		kotek_target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/dav1d.lib)
	endif()

	set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

	set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/dav1d.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)

	set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/dav1d.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)


	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
		COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"

		COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
		COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"

		COMMAND_EXPAND_LISTS

		COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
   )

else()
	# vcpkg + manual (K10): the pkg-config imported target in both cases
	kotek_target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::dav1d)
endif()
