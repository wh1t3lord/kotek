message(STATUS "applying ${CMAKE_CURRENT_LIST_FILE}")

# KOTEK LIBRARY LINKAGE MODEL
# ===========================
# Every module library is created through kotek_add_library() so the link type
# is decided in ONE place. Three knobs:
#
#   KOTEK_LINKAGE = STATIC | SHARED
#       Global default for all modules (default STATIC — the classic
#       "everything is .lib linked into kotek.exe" configuration).
#   KOTEK_LINKAGE_FORCE_STATIC = "module.a;module.b"
#       These modules are always built as .lib, even when KOTEK_LINKAGE=SHARED.
#   KOTEK_LINKAGE_FORCE_SHARED = "module.c;module.d"
#       These modules are always built as .dll, even when KOTEK_LINKAGE=STATIC.
#
# Examples (big variants):
#   all .lib:                       cmake ..                                    (default)
#   all .dll:                       cmake .. -DKOTEK_LINKAGE=SHARED
#   all .dll but core stays .lib:   cmake .. -DKOTEK_LINKAGE=SHARED -DKOTEK_LINKAGE_FORCE_STATIC="kotek.core;kotek.core.api"
#   only render as .dll:            cmake .. -DKOTEK_LINKAGE_FORCE_SHARED="kotek.render;kotek.render.bgfx"
#
# Rules and current limitations (read before flipping to SHARED):
# - On Windows a SHARED module gets WINDOWS_EXPORT_ALL_SYMBOLS so it links
#   without __declspec annotations. This exports functions but NOT data
#   (global variables) — modules that share globals across library boundaries
#   still need a proper export macro; that is future work.
# - Static libraries tolerate circular target dependencies, DLLs do not.
# - PIC is enabled globally when SHARED is involved so static-into-shared
#   linking stays valid on ELF platforms.
# - The user game library (game.ktk) is NOT governed here; it is controlled by
#   KOTEK_DEVELOPMENT_TYPE (SHARED/STATIC) as before.

if ("${KOTEK_LINKAGE}" STREQUAL "")
	set(KOTEK_LINKAGE "STATIC" CACHE INTERNAL "global module linkage: STATIC or SHARED")
endif()

if (NOT "${KOTEK_LINKAGE}" STREQUAL "STATIC" AND NOT "${KOTEK_LINKAGE}" STREQUAL "SHARED")
	message(FATAL_ERROR "[kotek]: KOTEK_LINKAGE must be STATIC or SHARED, got '${KOTEK_LINKAGE}'")
endif()

if ("${KOTEK_LINKAGE_FORCE_STATIC}" STREQUAL "")
	set(KOTEK_LINKAGE_FORCE_STATIC "" CACHE INTERNAL "modules always built as .lib")
endif()

if ("${KOTEK_LINKAGE_FORCE_SHARED}" STREQUAL "")
	set(KOTEK_LINKAGE_FORCE_SHARED "" CACHE INTERNAL "modules always built as .dll")
endif()

if ("${KOTEK_LINKAGE}" STREQUAL "SHARED" OR NOT "${KOTEK_LINKAGE_FORCE_SHARED}" STREQUAL "")
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

message(STATUS "[kotek]: module linkage is '${KOTEK_LINKAGE}' (force static: '${KOTEK_LINKAGE_FORCE_STATIC}', force shared: '${KOTEK_LINKAGE_FORCE_SHARED}')")

function(kotek_resolve_linkage out_var target_name)
	if ("${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_STATIC)
		set(${out_var} STATIC PARENT_SCOPE)
	elseif ("${target_name}" IN_LIST KOTEK_LINKAGE_FORCE_SHARED)
		set(${out_var} SHARED PARENT_SCOPE)
	elseif ("${KOTEK_LINKAGE}" STREQUAL "SHARED")
		set(${out_var} SHARED PARENT_SCOPE)
	else()
		set(${out_var} STATIC PARENT_SCOPE)
	endif()
endfunction()

# drop-in replacement for add_library(<target> STATIC ...): the link type is
# resolved from the linkage model, everything else passes through unchanged.
function(kotek_add_library target_name)
	kotek_resolve_linkage(_kotek_linkage "${target_name}")
	add_library(${target_name} ${_kotek_linkage} ${ARGN})
	if ("${_kotek_linkage}" STREQUAL "SHARED")
		set_target_properties(${target_name} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
		string(TOUPPER "${target_name}" _kotek_upper)
		string(REPLACE "." "_" _kotek_upper "${_kotek_upper}")
		target_compile_definitions(${target_name} PUBLIC KOTEK_USE_SHARED_${_kotek_upper})
	endif()
	message(STATUS "[${target_name}]: linkage is '${_kotek_linkage}'")
endfunction()

message(STATUS "${CMAKE_CURRENT_LIST_FILE} is applied!")
