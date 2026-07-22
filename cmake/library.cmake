message(STATUS "applying ${CMAKE_CURRENT_LIST_FILE}")

# KOTEK LINKAGE MODEL — three scenarios
# =====================================
#
# 1. KOTEK_LINKAGE=STATIC (default)
#    Everything is a .lib, linked into kotek.exe. Cycles between modules are
#    tolerated (static libs resolve at the final exe link).
#
# 2. KOTEK_LINKAGE=SHARED ("dll implicit", load-time dynamic linking)
#    Modules are .dll + import .lib; consumers link the import libs and call
#    exported functions directly. WINDOWS_EXPORT_ALL_SYMBOLS is applied (no
#    __declspec annotations needed for functions; data globals still need
#    export macros). REQUIRES the module dependency graph to be acyclic —
#    Windows DLLs cannot have circular link edges.
#
# 3. KOTEK_LINKAGE=PLUGIN ("dll explicit", run-time dynamic linking)
#    Feature modules are .dll loaded by kotek.exe at RUNTIME with
#    LoadLibrary + GetProcAddress (via ktk::dll::shared_library). Each plugin
#    module exports its existing entry points
#       bool InitializeModule_<X>(ktkMainManager*)
#       bool ShutdownModule_<X>(ktkMainManager*)
#    which are registered with kotek_add_library(INIT ... SHUTDOWN ...) and
#    compiled into a generated manifest (kotek_plugin_manifest.h). The loader
#    in kotek.game walks the manifest in dependency order at startup and in
#    reverse at shutdown. There are NO link edges between plugin modules:
#    kotek_target_link_libraries() converts links to plugin modules into
#    usage-requirement propagation (include dirs / compile definitions via
#    genexes), so the cyclic-graph problem does not exist in this mode.
#    Consequence: plugin module code may call other modules ONLY through
#    ktkMainManager interfaces; direct cross-module calls are unresolved at
#    link time — that is the enforcement mechanism of interface purity.
#    Leaf/utility modules (defines, types, constants, containers, enum, api,
#    main_manager, casting, math, format, utility, pch) stay STATIC and are
#    linked into whichever binary needs them (state is shared by pointer via
#    ktkMainManager, so per-DLL code duplication is harmless).
#
# Per-module overrides (all modes):
#   KOTEK_LINKAGE_FORCE_STATIC  = "a;b"  -> always .lib
#   KOTEK_LINKAGE_FORCE_SHARED  = "c;d"  -> always .dll (+ import lib in
#                                           SHARED mode; in PLUGIN mode these
#                                           become implicitly-linked DLLs)
#
# The user game library (game.ktk) is NOT governed here; it is controlled by
# KOTEK_DEVELOPMENT_TYPE (SHARED/STATIC) as before — it is itself the oldest
# example of the explicit-loading mechanism.

set(KOTEK_LINKAGE_VALID_VALUES STATIC SHARED PLUGIN)

if ("${KOTEK_LINKAGE}" STREQUAL "")
	set(KOTEK_LINKAGE "STATIC" CACHE INTERNAL "module linkage scenario: STATIC, SHARED (dll implicit) or PLUGIN (dll explicit)")
endif()

list(FIND KOTEK_LINKAGE_VALID_VALUES "${KOTEK_LINKAGE}" _kotek_linkage_index)
if (_kotek_linkage_index EQUAL -1)
	message(FATAL_ERROR "[kotek]: KOTEK_LINKAGE must be one of '${KOTEK_LINKAGE_VALID_VALUES}', got '${KOTEK_LINKAGE}'")
endif()

if ("${KOTEK_LINKAGE_FORCE_STATIC}" STREQUAL "")
	set(KOTEK_LINKAGE_FORCE_STATIC "" CACHE INTERNAL "modules always built as .lib")
endif()

if ("${KOTEK_LINKAGE_FORCE_SHARED}" STREQUAL "")
	set(KOTEK_LINKAGE_FORCE_SHARED "" CACHE INTERNAL "modules always built as implicitly-linked .dll")
endif()

# leaf/utility modules that stay static in PLUGIN mode (linked into consumers)
set(KOTEK_PLUGIN_STATIC_MODULES
	"kotek.pch"
	"kotek.game"
	"kotek.core.api"
	"kotek.core.main_manager"
	"kotek.core.utility"
	"kotek.core.math"
	"kotek.core.format"
	# header-only ECS backends (pico/entt) bake their implementation into one
	# TU; a runtime plugin is meaningless for them — backend choice is a
	# build-time switch (KOTEK_ECS_BACKEND), not a runtime one
	"kotek.core.ecs"
	CACHE INTERNAL "modules that remain .lib when KOTEK_LINKAGE=PLUGIN")

# modules that are implicitly-linked DLLs even in PLUGIN mode (import lib is
# linked normally; they are not part of the explicit-loading manifest).
# Membership rationale: global-state infrastructure whose symbols everyone
# resolves directly (logging macros expand to Get_LoggerMain()), as opposed
# to gameplay-level replacement points which belong to explicit loading.
set(KOTEK_PLUGIN_IMPLICIT_MODULES
	"kotek.render.gl.glad"
	"kotek.core.log"
	CACHE INTERNAL "implicitly-linked shared modules when KOTEK_LINKAGE=PLUGIN")

# wildcard groups of static leaves in PLUGIN mode (prefix match)
set(KOTEK_PLUGIN_STATIC_GROUPS
	"kotek.core.defines"
	"kotek.core.types"
	"kotek.core.constants"
	"kotek.core.containers"
	"kotek.core.enum"
	"kotek.core.casting"
	CACHE INTERNAL "module-name prefixes that remain .lib when KOTEK_LINKAGE=PLUGIN")

if (NOT "${KOTEK_LINKAGE}" STREQUAL "STATIC" OR NOT "${KOTEK_LINKAGE_FORCE_SHARED}" STREQUAL "")
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

message(STATUS "[kotek]: linkage scenario is '${KOTEK_LINKAGE}' (force static: '${KOTEK_LINKAGE_FORCE_STATIC}', force shared: '${KOTEK_LINKAGE_FORCE_SHARED}')")

# so code can guard for the active scenario (e.g. the loader in kotek.game)
add_compile_definitions(KOTEK_USE_LINKAGE_${KOTEK_LINKAGE})

function(_kotek_is_plugin_static_module target_name out_var)
	set(_result FALSE)
	if ("${target_name}" IN_LIST KOTEK_PLUGIN_STATIC_MODULES)
		set(_result TRUE)
	else()
		foreach (_prefix IN LISTS KOTEK_PLUGIN_STATIC_GROUPS)
			string(FIND "${target_name}" "${_prefix}." _pos)
			if (_pos EQUAL 0)
				set(_result TRUE)
				break()
			endif()
		endforeach()
	endif()
	set(${out_var} ${_result} PARENT_SCOPE)
endfunction()

# TRUE when target_name is destined to become an explicitly-loaded plugin in
# PLUGIN mode. Name-based on purpose: decided identically at any point of the
# configure run (cyclic links point 'backward', a registration-order check
# would be order-dependent and let cycles slip through as real link edges).
function(_kotek_is_plugin_destined target_name out_var)
	set(_result FALSE)
	# only real modules can be plugins; third-party/plain library names
	# (opengl32, GTest::gtest, Boost::json, ...) must never match
	string(REGEX MATCH "^(kotek\\.|zircon\\.)" _is_module_name "${target_name}")
	if ("${KOTEK_LINKAGE}" STREQUAL "PLUGIN"
		AND NOT "${_is_module_name}" STREQUAL ""
		AND NOT "${target_name}" IN_LIST KOTEK_PLUGIN_STATIC_MODULES
		AND NOT "${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_STATIC
		AND NOT "${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_SHARED
		AND NOT "${target_name}" IN_LIST KOTEK_PLUGIN_IMPLICIT_MODULES)
		set(_result TRUE)
		foreach (_prefix IN LISTS KOTEK_PLUGIN_STATIC_GROUPS)
			string(FIND "${target_name}" "${_prefix}" _pos)
			if (_pos EQUAL 0)
				set(_result FALSE)
				break()
			endif()
		endforeach()
	endif()
	set(${out_var} ${_result} PARENT_SCOPE)
endfunction()

function(kotek_resolve_linkage out_var target_name)
	if ("${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_STATIC)
		set(_type STATIC)
	elseif ("${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_SHARED)
		set(_type SHARED)
	elseif ("${KOTEK_LINKAGE}" STREQUAL "SHARED")
		set(_type SHARED)
	elseif ("${KOTEK_LINKAGE}" STREQUAL "PLUGIN")
		_kotek_is_plugin_destined("${target_name}" _is_plugin)
		if (_is_plugin)
			set(_type SHARED)
		else()
			set(_type STATIC)
		endif()
	else()
		set(_type STATIC)
	endif()
	set(${out_var} ${_type} PARENT_SCOPE)
endfunction()

# drop-in replacement for add_library(<target> STATIC ...). Extra optional
# metadata: INIT <InitializeModule_X symbol> SHUTDOWN <ShutdownModule_X symbol>
# (needed for the PLUGIN manifest; harmless in other modes).
function(kotek_add_library target_name)
	set(_options)
	set(_one_value INIT SHUTDOWN)
	cmake_parse_arguments(KOTEK_LIB "${_options}" "${_one_value}" "" ${ARGN})

	kotek_resolve_linkage(_kotek_linkage "${target_name}")
	add_library(${target_name} ${_kotek_linkage} ${KOTEK_LIB_UNPARSED_ARGUMENTS})

	if ("${_kotek_linkage}" STREQUAL "SHARED")
		set_target_properties(${target_name} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
		string(TOUPPER "${target_name}" _kotek_upper)
		string(REPLACE "." "_" _kotek_upper "${_kotek_upper}")
		target_compile_definitions(${target_name} PUBLIC KOTEK_USE_SHARED_${_kotek_upper})
	endif()

	# PLUGIN bookkeeping: record entry symbols of every module that has them
	if (NOT "${KOTEK_LIB_INIT}" STREQUAL "")
		set_property(GLOBAL PROPERTY KOTEK_MODULE_INIT_${target_name} "${KOTEK_LIB_INIT}")
		set_property(GLOBAL PROPERTY KOTEK_MODULE_SHUTDOWN_${target_name} "${KOTEK_LIB_SHUTDOWN}")
	endif()

	# PLUGIN membership: only modules with registered entry symbols become
	# explicitly-loaded plugins; other SHARED modules stay implicitly linked
	# (order of registration = dependency order, because kotek/CMakeLists.txt
	# adds modules in dependency order)
	if ("${KOTEK_LINKAGE}" STREQUAL "PLUGIN" AND "${_kotek_linkage}" STREQUAL "SHARED"
		AND NOT "${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_SHARED
		AND NOT "${KOTEK_LIB_INIT}" STREQUAL "")
		set_property(GLOBAL APPEND PROPERTY KOTEK_PLUGIN_LOAD_ORDER "${target_name}")
	endif()

	message(STATUS "[${target_name}]: linkage is '${_kotek_linkage}'")
endfunction()

# drop-in replacement for target_link_libraries(). In PLUGIN mode, a link to a
# plugin module must NOT become a link edge (that is the whole point of
# explicit loading): propagate its usage requirements instead.
function(kotek_target_link_libraries target_name)
	if (NOT "${KOTEK_LINKAGE}" STREQUAL "PLUGIN")
		target_link_libraries(${target_name} ${ARGN})
		return()
	endif()

	set(_scope PUBLIC)
	foreach (_arg IN LISTS ARGN)
		if (_arg MATCHES "^(PUBLIC|PRIVATE|INTERFACE|debug|optimized|general)$")
			set(_scope ${_arg})
			continue()
		endif()

		_kotek_is_plugin_destined("${_arg}" _is_plugin)
		if (_is_plugin AND NOT "${_arg}" STREQUAL "${target_name}")
			# no link edge to the plugin itself. Its own interface properties
			# flow via lazy genexes; its static/third-party link items are
			# re-applied at the end of the configure run by
			# kotek_finalize_plugin_links() (configure-time evaluation can
			# filter self-references and plugin items, a genex cannot).
			set_property(GLOBAL APPEND PROPERTY KOTEK_PLUGIN_ERASED_EDGES "${target_name}|${_arg}")
			target_include_directories(${target_name} PRIVATE $<TARGET_PROPERTY:${_arg},INTERFACE_INCLUDE_DIRECTORIES>)
			target_compile_definitions(${target_name} PRIVATE $<TARGET_PROPERTY:${_arg},INTERFACE_COMPILE_DEFINITIONS>)
			target_compile_options(${target_name} PRIVATE $<TARGET_PROPERTY:${_arg},INTERFACE_COMPILE_OPTIONS>)
		else()
			target_link_libraries(${target_name} ${_scope} ${_arg})
		endif()
	endforeach()
endfunction()

# PLUGIN mode: re-applies the static/third-party link items of erased plugin
# edges to their consumers. Usage must flow TRANSITIVELY through plugin
# chains (A -> B -> C), so for every recorded erased edge we walk the
# erased-edge graph from the consumer (BFS) and re-apply the safe link items
# of every reachable plugin directly to the consumer. Plugin items and
# self-references are filtered out. Callable again for upper layers.
function(kotek_finalize_plugin_links)
	get_property(_edges GLOBAL PROPERTY KOTEK_PLUGIN_ERASED_EDGES)
	if (NOT _edges)
		return()
	endif()
	list(REMOVE_DUPLICATES _edges)

	foreach (_edge IN LISTS _edges)
		string(REPLACE "|" ";" _parts "${_edge}")
		list(GET _parts 0 _consumer)
		list(GET _parts 1 _dep)

		get_target_property(_consumer_links ${_consumer} LINK_LIBRARIES)
		if (NOT _consumer_links)
			set(_consumer_links "")
		endif()

		# BFS over erased edges starting at _dep
		set(_queue "${_dep}")
		set(_visited "")
		while (_queue)
			list(POP_FRONT _queue _current)
			if ("${_current}" IN_LIST _visited)
				continue()
			endif()
			list(APPEND _visited "${_current}")

			get_target_property(_dep_links ${_current} INTERFACE_LINK_LIBRARIES)
			if (_dep_links)
				set(_pending_keyword "")
				foreach (_item IN LISTS _dep_links)
					if ("${_item}" MATCHES "^(debug|optimized|general)$")
						set(_pending_keyword "${_item}")
						continue()
					endif()
					set(_skip FALSE)
					if ("${_item}" STREQUAL "${_consumer}")
						set(_skip TRUE)
					endif()
					_kotek_is_plugin_destined("${_item}" _is_plugin_item)
					if (_is_plugin_item)
						set(_skip TRUE)
					endif()
					if ("${_item}" MATCHES "::" AND NOT TARGET ${_item})
						get_property(_reported GLOBAL PROPERTY KOTEK_PLUGIN_FIXUP_REPORTED)
						if (NOT "${_consumer}|${_item}" IN_LIST _reported)
							set_property(GLOBAL APPEND PROPERTY KOTEK_PLUGIN_FIXUP_REPORTED "${_consumer}|${_item}")
							message(WARNING "[kotek]: plugin edge fixup: '${_item}' is not visible for '${_consumer}', skipped — make its find_package/pkg_check_modules GLOBAL")
						endif()
						set(_skip TRUE)
					endif()
					if ("${_item}" IN_LIST _consumer_links)
						set(_skip TRUE)
					endif()
					if (NOT _skip)
						# PUBLIC on purpose: erased edges in this codebase are
						# virtually always PUBLIC, and the re-application must
						# restore TRANSITIVE usage flow, not only the
						# consumer's own compile
						if ("${_pending_keyword}" STREQUAL "")
							target_link_libraries(${_consumer} PUBLIC ${_item})
						else()
							target_link_libraries(${_consumer} PUBLIC ${_pending_keyword} ${_item})
						endif()
						list(APPEND _consumer_links "${_item}")
					endif()
					set(_pending_keyword "")
				endforeach()
			endif()

			# continue traversal over _current's own erased edges
			foreach (_inner_edge IN LISTS _edges)
				string(REPLACE "|" ";" _inner_parts "${_inner_edge}")
				list(GET _inner_parts 0 _inner_consumer)
				list(GET _inner_parts 1 _inner_dep)
				if ("${_inner_consumer}" STREQUAL "${_current}")
					list(APPEND _queue "${_inner_dep}")
				endif()
			endforeach()
		endwhile()
	endforeach()

	# processed: later invocations (e.g. from the engine root for upper-layer
	# modules) must only see edges recorded after this point
	set_property(GLOBAL PROPERTY KOTEK_PLUGIN_ERASED_EDGES "")
endfunction()

# writes kotek_plugin_manifest.h: the ordered table of plugin modules with
# their dll file names and init/shutdown symbols. Call once after all modules
# are added (end of kotek/CMakeLists.txt).
function(kotek_generate_plugin_manifest output_file)
	get_property(_modules GLOBAL PROPERTY KOTEK_PLUGIN_LOAD_ORDER)

	set(_entries "")
	set(_count 0)
	foreach (_module IN LISTS _modules)
		get_property(_init GLOBAL PROPERTY KOTEK_MODULE_INIT_${_module})
		get_property(_shutdown GLOBAL PROPERTY KOTEK_MODULE_SHUTDOWN_${_module})
		if ("${_init}" STREQUAL "")
			message(WARNING "[kotek]: plugin module '${_module}' has no INIT/SHUTDOWN symbols registered, skipping in manifest")
			continue()
		endif()
		string(APPEND _entries "\t{\"${_module}.dll\", \"${_init}\", \"${_shutdown}\"},\n")
		math(EXPR _count "${_count}+1")
	endforeach()

	file(WRITE "${output_file}"
		"// generated by cmake/library.cmake kotek_generate_plugin_manifest() — do not edit\n"
		"// KOTEK_LINKAGE=PLUGIN: explicit-loading table, in dependency order\n"
		"#pragma once\n\n"
		"struct ktkPluginModuleDesc\n"
		"{\n"
		"\tconst char* p_dll_name;\n"
		"\tconst char* p_init_symbol;\n"
		"\tconst char* p_shutdown_symbol;\n"
		"};\n\n"
		"static const ktkPluginModuleDesc g_kotek_plugin_modules[] =\n"
		"{\n"
		"${_entries}};\n\n"
		"static const unsigned long g_kotek_plugin_modules_count = ${_count}UL;\n")

	message(STATUS "[kotek]: plugin manifest has ${_count} modules -> ${output_file}")
endfunction()

message(STATUS "${CMAKE_CURRENT_LIST_FILE} is applied!")
