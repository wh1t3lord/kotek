cmake_minimum_required(VERSION 3.21)

if (WIN32)
	include("cmake/windows/compiler_globals.cmake")
else()
	message(FATAL_ERROR "todo: impl")
endif()

project(kotek.engine)

# K6: `cmake -DKOTEK_HELP=ON` prints every kotek option with its meaning and
# stops before dependencies/modules are processed (fast, no vcpkg fetch)
include("cmake/options_help.cmake")
if ("${KOTEK_HELP}" STREQUAL "ON")
	kotek_print_options_help()
	return()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
message("[${PROJECT_NAME}]: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("[${PROJECT_NAME}]: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")

#### DEPENDENCY TRIPLET / CRT CONSISTENCY ####
# The vcpkg triplet must match the CRT from cmake/windows/compiler_globals.cmake:
# static CRT (/MT, the default) -> x64-windows-static, dynamic CRT (/MD) -> x64-windows.
if ("${KOTEK_VCPKG_TRIPLET}" STREQUAL "")
	set(KOTEK_VCPKG_TRIPLET "x64-windows-static" CACHE INTERNAL "vcpkg triplet for installing and finding dependencies")
endif()

# consumed by the vcpkg.cmake toolchain include below
set(VCPKG_TARGET_TRIPLET "${KOTEK_VCPKG_TRIPLET}")

message("[${PROJECT_NAME}]: vcpkg triplet is '${KOTEK_VCPKG_TRIPLET}'")

#### LIBRARY LINKAGE MODEL (global + per-module overrides) ####
include("cmake/library.cmake")

# the generated kotek_entry_config.h / kotek_plugin_manifest.h /
# kotek_plugin_registry.h must be includable from every module
# (KOTEK_INVOKE_MODULE_* macros in PLUGIN mode; the module registry feeds the
# plugin override system in EVERY linkage mode, task K21)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/generated")
include_directories("${CMAKE_BINARY_DIR}/generated")

# it is our requirement for generating the library e.g. don't just write 'cmake ..' - OUTDATED
# By new standard you can pass a empty string, but we need to generate solution for debug build. It is required for including/generating stuff for better debug experience
# Memory leak manager, etc
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
	#message(FATAL_ERROR "[${PROJECT_NAME}]: you must specify CMAKE_BUILD_TYPE flag with the following types: Debug, Release, MinSizeRel, RelWithDebInfo. It supposed to be like -DCMAKE_BUILD_TYPE=Debug")
	set(CMAKE_BUILD_TYPE Debug)
	message("[${PROJECT_NAME}]: Setting build type to: ${CMAKE_BUILD_TYPE}")
endif()

#### OVERRIDING PROJECT NAMES ####

if ("${KOTEK_PROJECT_NAME_OVERRIDE_KOTEK}" STREQUAL "")
	set(KOTEK_PROJECT_NAME_OVERRIDE_KOTEK "kotek" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: Setting default name for kotek.exe folder: ${KOTEK_PROJECT_NAME_OVERRIDE_KOTEK}")
else()
	message("[${PROJECT_NAME}]: Your overriden kotek.exe [${KOTEK_PROJECT_NAME_OVERRIDE_KOTEK}]")
endif()

#### OVERRIDING PROJECT NAMES ####

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "")
	set(KOTEK_DEPS_FOLDER_ENABLE "ON" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: KOTEK_DEPS_FOLDER is enabled! Now you should specified your dependency folder name (but not its path)")
endif()

message("[${PROJECT_NAME}]: build type is '${CMAKE_BUILD_TYPE}'")

if ("${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}" STREQUAL "")
	# per-build-tree, NOT the source include dir: the generated content is
	# configuration-specific (dev type, library type, capacities), so two
	# build dirs with different configs must never clobber each other
	set(KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS ${CMAKE_BINARY_DIR}/generated/kotek_std_preprocessors.h)
endif()

if ("${KOTEK_LIBRARY_TYPE}" STREQUAL "")
	set(KOTEK_LIBRARY_TYPE "EMB" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: library development - ${KOTEK_LIBRARY_TYPE} (EMB is embedded and DYN is dynamic and HYB is hybrid, check documentation about these definitions)")
endif()

# Assert presentation: by DEFAULT a failed CRT assert opens the stock modal
# dialog (Abort/Retry/Ignore) — that is what end users and manual debugging
# expect. Automation (agents, CI/CD) must not hang on an invisible dialog,
# so they configure -DKOTEK_ASSERT_STDERR_ROUTING=ON which routes CRT
# asserts/errors to stderr and fails fast. This covers CRT-level reports
# (debug_heap, invalid parameter, _CrtDbgReport); KOTEK_ASSERT itself logs
# through the engine logger in every configuration.
if ("${KOTEK_ASSERT_STDERR_ROUTING}" STREQUAL "")
	set(KOTEK_ASSERT_STDERR_ROUTING "OFF" CACHE INTERNAL "route CRT asserts to stderr instead of the modal dialog (use ON for CI/agents)")
endif()

if ("${KOTEK_ASSERT_STDERR_ROUTING}" STREQUAL "ON")
	add_compile_definitions(KOTEK_USE_ASSERT_STDERR_ROUTING)
	message("[${PROJECT_NAME}]: CRT asserts route to stderr (no modal dialog)")
endif()

message("[${PROJECT_NAME}]: filename for generating preprocessors: '${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}'")

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "")
	message("[${PROJECT_NAME}]: using nuget packages")

	if ("${KOTEK_CONFIGURATION_TYPE}" STREQUAL "")
		set(KOTEK_CONFIGURATION_TYPE "minimal" CACHE INTERNAL "")
	endif()

	message("KOTEK_CONFIGURATION_TYPE=${KOTEK_CONFIGURATION_TYPE}")

	if (NOT "${KOTEK_CONFIGURATION_TYPE}" STREQUAL "")
		set(KOTEK_VCPKG_FILENAME "vcpkg_nuget_${KOTEK_CONFIGURATION_TYPE}.cmake")
		message("KOTEK_VCPKG_FILENAME=${KOTEK_VCPKG_FILENAME} using this for installing packages from vcpkg")
	endif()

	if (WIN32)
		include("cmake/windows/${KOTEK_VCPKG_FILENAME}")
		include("cmake/windows/nuget.cmake")
	endif()

	include("${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# the vcpkg toolchain must be active on EVERY configure, not only the first
# one (cached *_DIR vars only cover packages that were already found once;
# any new find_package would fail without the toolchain paths)
if (WIN32 AND "${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
	include("${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

if ("${KOTEK_CPP_ASAN}" STREQUAL "")
	if ("$<CONFIG:Debug>" STREQUAL "1")
		message("[${PROJECT_NAME}]: enabling address sanitizer (ASAN)")
		set(KOTEK_CPP_ASAN "ON" CACHE INTERNAL "")
	endif()
endif()

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "")
		message("Using nuget packages because you didn't provide a folder that has a package manager\n So we don't need to build solution and using precompiled packages")	
		
		if ("${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
			set(KOTEK_DEPS_FOLDER "vcpkg" CACHE INTERNAL "")
		else()
			set(KOTEK_DEPS_FOLDER "nuget" CACHE INTERNAL "")
		endif()	
	else()
		if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${KOTEK_DEPS_FOLDER}" AND NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			message("[${PROJECT_NAME}]: your dependency folder is '${KOTEK_DEPS_FOLDER}'")
		elseif (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${KOTEK_DEPS_FOLDER}" AND "${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			message("[${PROJECT_NAME}]: you use precompiled packages with nuget")
		else()
			message(FATAL_ERROR "you can't use nuget and ${KOTEK_DEPS_FOLDER} at same time! You need to pass an empty string to KOTEK_DEPS_FOLDER otherwise delete nuget folder and pass a valid folder name to KOTEK_DEPS_FOLDER")
		endif()
	endif()
endif()

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "")
	set(KOTEK_STD_LIBRARY_STATIC_CONTAINERS "ON" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: static containers are enabled by default!")
endif()

if ("${KOTEK_STD_LIBRARY_HYBRID_CONTAINERS}" STREQUAL "")
	set(KOTEK_STD_LIBRARY_HYBRID_CONTAINERS "ON" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: hybrid containers are enabled by default!")
endif()

if ("${KOTEK_STD_LIBRARY_DYNAMIC_CONTAINERS}" STREQUAL "")
	set(KOTEK_STD_LIBRARY_DYNAMIC_CONTAINERS "ON" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: dynamic containers are enabled by default!")
endif()

if ("${KOTEK_STARTUP_RENDERER}" STREQUAL "")
	set(KOTEK_STARTUP_RENDERER "OpenGLES_SpecifiedByUser" CACHE INTERNAL "")
	set(KOTEK_STARTUP_RENDERER_VERSION "OpenGLES_3_1" CACHE INTERNAL "")
	set(KOTEK_STARTUP_RENDERER_VENDOR "BGFX" CACHE INTERNAL "")
	message("[${PROJECT_NAME}]: using OpenGL ES ver 3.1 as default renderer (${KOTEK_STARTUP_RENDERER_VENDOR})")
endif()

include_directories("src")

# Imported targets created by find_package are directory-scoped by default,
# which breaks usage propagation across module directories (most visibly in
# KOTEK_LINKAGE=PLUGIN where erased plugin edges are re-applied to consumers
# by kotek_finalize_plugin_links). Re-find the shared packages with GLOBAL
# before any module is processed; the per-module find_package calls then
# no-op on the already-existing targets.
if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	find_package(zstd CONFIG REQUIRED GLOBAL)
	find_package(etl CONFIG REQUIRED GLOBAL)
	find_package(GTest CONFIG REQUIRED GLOBAL)
	find_package(Boost COMPONENTS json CONFIG REQUIRED GLOBAL)
	find_package(Boost COMPONENTS container CONFIG REQUIRED GLOBAL)
	find_package(Ktx CONFIG REQUIRED GLOBAL)
	find_package(ZLIB REQUIRED GLOBAL)
	find_package(Vulkan REQUIRED GLOBAL)
	find_package(glfw3 CONFIG REQUIRED GLOBAL)
	find_package(bgfx CONFIG REQUIRED GLOBAL)
	find_package(utf8cpp CONFIG REQUIRED GLOBAL)
	find_package(spdlog CONFIG REQUIRED GLOBAL)
	find_package(glm CONFIG REQUIRED GLOBAL)
	find_package(fmt CONFIG REQUIRED GLOBAL)
	find_package(Tracy REQUIRED GLOBAL)
	find_package(TBB REQUIRED GLOBAL)
	find_package(RmlUi CONFIG REQUIRED GLOBAL)
	find_package(PkgConfig REQUIRED GLOBAL)
	find_package(PNG REQUIRED GLOBAL)
	find_package(BZip2 REQUIRED GLOBAL)
	find_package(Freetype CONFIG REQUIRED GLOBAL)
endif()

# per-module, per-config build-tree location for the generated preprocessors
# header: the file's content is configuration-specific (dev type, library
# type, capacities) and EVERY defines module generates its own copy, so the
# old shared relative path made (a) parallel build dirs of different configs
# clobber each other and (b) an absolute shared path made modules reset one
# another. Set the var per module right before its add_subdirectory and
# expose the build-tree dir on the module's public include path (the
# umbrella includes the header by quoted name; stale source-tree copies
# must not exist).
function(kotek_add_defines_subdirectory dir)
	set(KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS
		"${CMAKE_CURRENT_BINARY_DIR}/${dir}/include/kotek_std_preprocessors.h")
	add_subdirectory("${dir}")

	# legacy codegen in many defines modules appends "#pragma once" once per
	# section instead of writing it once at the top (harmless while each
	# module's file was unused or overwritten per configure; fatal now that
	# the file is always included) — normalize to a single leading pragma
	if (EXISTS "${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}")
		file(READ "${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
			_kotek_gen_content)
		string(REGEX REPLACE "#pragma once" "" _kotek_gen_body
			"${_kotek_gen_content}")
		file(WRITE "${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
			"#pragma once\n${_kotek_gen_body}")
	endif()

	get_filename_component(_kotek_mod_name "${dir}" NAME)
	target_include_directories(${_kotek_mod_name} PUBLIC
		"${CMAKE_CURRENT_BINARY_DIR}/src")
endfunction()

kotek_add_defines_subdirectory("src/kotek.core.defines.static.tests")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.cpp")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.git")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.render")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.render.dx")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.render.gl")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.render.vk")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.render.bgfx")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.math")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.os")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.os.win32")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.os.linux")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.profilers")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.sdk")
kotek_add_defines_subdirectory("src/kotek.core.defines.static.string")
kotek_add_defines_subdirectory("src/kotek.core.defines.static")


kotek_add_defines_subdirectory("src/kotek.core.defines_dependent.text")
kotek_add_defines_subdirectory("src/kotek.core.defines_dependent.message")
kotek_add_defines_subdirectory("src/kotek.core.defines_dependent.assert")
kotek_add_defines_subdirectory("src/kotek.core.defines_dependent.ecs")
kotek_add_defines_subdirectory("src/kotek.core.defines_dependent")

kotek_add_defines_subdirectory("src/kotek.core.defines")

add_subdirectory("src/kotek.core")
add_subdirectory("src/kotek.core.api")
add_subdirectory("src/kotek.core.types")
add_subdirectory("src/kotek.core.types.char")
add_subdirectory("src/kotek.core.types.numerics")
add_subdirectory("src/kotek.core.types.string")
add_subdirectory("src/kotek.core.casting")
add_subdirectory("src/kotek.core.casting.lexical")
add_subdirectory("src/kotek.core.casting.string")
add_subdirectory("src/kotek.core.constants")
add_subdirectory("src/kotek.core.constants.math")
add_subdirectory("src/kotek.core.constants.ecs")
add_subdirectory("src/kotek.core.constants.string")
add_subdirectory("src/kotek.core.constants.window")
add_subdirectory("src/kotek.core.constants.render")
add_subdirectory("src/kotek.core.containers")
add_subdirectory("src/kotek.core.containers.any")
add_subdirectory("src/kotek.core.containers.array")
add_subdirectory("src/kotek.core.containers.string")
add_subdirectory("src/kotek.core.containers.hash")
add_subdirectory("src/kotek.core.containers.deque")
add_subdirectory("src/kotek.core.containers.dll")
add_subdirectory("src/kotek.core.containers.filesystem")
add_subdirectory("src/kotek.core.containers.filesystem.path")
add_subdirectory("src/kotek.core.containers.function")
add_subdirectory("src/kotek.core.containers.io")
add_subdirectory("src/kotek.core.containers.json")
add_subdirectory("src/kotek.core.containers.map")
add_subdirectory("src/kotek.core.containers.microsoft")
add_subdirectory("src/kotek.core.containers.microsoft.wrl.comptr")
add_subdirectory("src/kotek.core.containers.multithreading")
add_subdirectory("src/kotek.core.containers.multithreading.tbb")
add_subdirectory("src/kotek.core.containers.multithreading.atomic")
add_subdirectory("src/kotek.core.containers.multithreading.mutex")
add_subdirectory("src/kotek.core.containers.multithreading.shared_mutex")
add_subdirectory("src/kotek.core.containers.multithreading.thread")
add_subdirectory("src/kotek.core.containers.multithreading.semaphore")
add_subdirectory("src/kotek.core.containers.multithreading.queue")
add_subdirectory("src/kotek.core.containers.multithreading.condition_variable")
add_subdirectory("src/kotek.core.containers.pair")
add_subdirectory("src/kotek.core.containers.queue")
add_subdirectory("src/kotek.core.containers.shared_ptr")
add_subdirectory("src/kotek.core.containers.unique_ptr")
add_subdirectory("src/kotek.core.containers.unordered_map")
add_subdirectory("src/kotek.core.containers.unordered_set")
add_subdirectory("src/kotek.core.containers.variant")
add_subdirectory("src/kotek.core.containers.vector")
add_subdirectory("src/kotek.core.containers.list")
add_subdirectory("src/kotek.core.filesystem")
add_subdirectory("src/kotek.core.filesystem.file_text")
add_subdirectory("src/kotek.core.format")
add_subdirectory("src/kotek.core.memory")
add_subdirectory("src/kotek.core.memory.cpu")
add_subdirectory("src/kotek.core.memory.gpu")
add_subdirectory("src/kotek.core.memory.gpu.vulkan")

add_subdirectory("src/kotek.core.math")
add_subdirectory("src/kotek.core.profilers")
add_subdirectory("src/kotek.core.profilers.cpu")
add_subdirectory("src/kotek.core.profilers.gpu")
add_subdirectory("src/kotek.core.os")
add_subdirectory("src/kotek.core.os.win32")
add_subdirectory("src/kotek.core.os.linux")
add_subdirectory("src/kotek.core.window")
add_subdirectory("src/kotek.core.window.glfw")
add_subdirectory("src/kotek.core.window_manager")
add_subdirectory("src/kotek.core.log")
add_subdirectory("src/kotek.core.console")
add_subdirectory("src/kotek.core.engine_config")
add_subdirectory("src/kotek.core.main_manager")
add_subdirectory("src/kotek.core.ecs")
add_subdirectory("src/kotek.core.enum")
add_subdirectory("src/kotek.core.enum.core")
add_subdirectory("src/kotek.core.enum.render")
add_subdirectory("src/kotek.core.enum.render.dx")
add_subdirectory("src/kotek.core.enum.render.gl")
add_subdirectory("src/kotek.core.enum.render.vk")
add_subdirectory("src/kotek.core.enum.render.bgfx")
add_subdirectory("src/kotek.core.input")
add_subdirectory("src/kotek.core.utility")

add_subdirectory("src/kotek.game")

add_subdirectory("src/kotek.ui")
add_subdirectory("src/kotek.ui.imgui")

if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
	add_subdirectory("src/kotek.ui.cef")
elseif("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "RMLUI")
	add_subdirectory("src/kotek.ui.rmlui")
endif()

add_subdirectory("src/kotek.ui.videoplayer")
add_subdirectory("src/kotek.ui.videoplayer.avif")

if (WIN32)
	# DEPRECATED: undo comments when you finish vulkan renderer!
#add_subdirectory("src/kotek.render.dx12")
endif()

add_subdirectory("src/kotek.render")

# render backends: bgfx (raster) is the only built-in one; NRI (dx12/vk + ray
# tracing) is planned. gl/vk/software/angle/glad and their shared modules were
# removed (2026-07-22, owner decision); the per-backend defines/enum config
# modules stay for enum stability and future NRI reuse.
add_subdirectory("src/kotek.render.shared")
add_subdirectory("src/kotek.render.shared.bgfx")
add_subdirectory("src/kotek.render.bgfx")

add_subdirectory("src/kotek.exe")

# PLUGIN mode: re-apply erased-edge usage (see library.cmake)
if ("${KOTEK_LINKAGE}" STREQUAL "PLUGIN")
	kotek_finalize_plugin_links()
endif()

# in EVERY linkage mode: emit the explicit-loading manifest (PLUGIN loader),
# the per-entry linkage flags (KOTEK_INVOKE_MODULE_* selection) and the
# module-name<->symbol registry (plugin override system, task K21 — an
# override dll must also work for static/shared builds), then make them
# visible to kotek.core.main_manager (static leaf linked into every plugin
# and into the exe — it implements the ktkPluginInvoke* loader and the
# ktkPluginTryOverride override lookup, see kotek_plugin_invoke.cpp /
# kotek_plugin_override.cpp)
set(KOTEK_PLUGIN_MANIFEST_FILE "${CMAKE_BINARY_DIR}/generated/kotek_plugin_manifest.h")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/generated")
kotek_generate_plugin_manifest("${KOTEK_PLUGIN_MANIFEST_FILE}" "${CMAKE_BINARY_DIR}/generated/kotek_entry_config.h" "${CMAKE_BINARY_DIR}/generated/kotek_plugin_registry.h")
target_include_directories(kotek.core.main_manager PUBLIC "${CMAKE_BINARY_DIR}/generated")

# TODO: when CMake will fix that we can restore but for now we can't use this due to breaking USE_FOLDERS feature...
# TODO2: Rename cmake default filter folder CMakePredefinedTargets as just plain 'targets' word
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT kotek)