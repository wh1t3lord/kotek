message(STATUS "applying ${CMAKE_CURRENT_LIST_FILE}")

# this file is included both by the engine root and by kotek itself; apply once.
# IMPORTANT: the applied flag is set at the END of the file — setting it up
# front poisons the MSVC-dependent parts when an includer pulls this file in
# before its project() call (MSVC is not defined yet, the block is skipped,
# and a later post-project include then returns early forever)
get_property(_kotek_compiler_globals_applied GLOBAL PROPERTY KOTEK_COMPILER_GLOBALS_APPLIED)
if (_kotek_compiler_globals_applied)
	return()
endif()

if(MSVC)
    # we force that option because it is important to embed runtime libraries otherwise it will be hard to maintain windows xp and current windows development (or probably other compilers that users might want to use or override manually)
    # and we make shipping the user output .exe or applicaction easily without any troubles
    # NOTE: static CRT requires vcpkg deps built with the matching triplet
    # (KOTEK_VCPKG_TRIPLET=x64-windows-static, see kotek/CMakeLists.txt); mixing
    # /MT with dynamic-CRT deps fails with LNK2038.
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # /MP spawns several CL.EXE per project and they share one compiler PDB;
    # /FS serializes those writes through mspdbsrv (fixes sporadic C1041)
    add_compile_options(/FS)
endif()

# for all possible compilers
add_compile_definitions(
    NOMINMAX
)

# C++ standard switching model:
# - default is C++20 for all modern targets
# - Windows XP targets must use C++17, because the last XP-capable toolset
#   (v141_xp, usable from modern Visual Studio installations) tops out at C++17.
#   Set -DKOTEK_WINDOWS_XP=ON to force the standard to 17 (and use the v141_xp
#   toolset: -T v141_xp), or override only the standard with -DKOTEK_CPP_STANDARD=17.
if ("${KOTEK_WINDOWS_XP}" STREQUAL "")
	set(KOTEK_WINDOWS_XP "OFF" CACHE INTERNAL "target Windows XP (forces C++17, needs v141_xp toolset)")
endif()

if ("${KOTEK_CPP_STANDARD}" STREQUAL "")
	if ("${KOTEK_WINDOWS_XP}" STREQUAL "ON")
		set(KOTEK_CPP_STANDARD "17" CACHE INTERNAL "C++ standard used for the whole codebase (17 for Windows XP)")
	else()
		set(KOTEK_CPP_STANDARD "20" CACHE INTERNAL "C++ standard used for the whole codebase (17 for Windows XP)")
	endif()
endif()

message(STATUS "[kotek]: C++ standard is C++${KOTEK_CPP_STANDARD} (KOTEK_WINDOWS_XP=${KOTEK_WINDOWS_XP})")

# By default (aka no legacy systems like Windows XP) we use C++20 standard
# Otherwise we will fit to 17 because latest official compiler support of Windows XP can provide full C++17 standard support
set(CMAKE_CXX_STANDARD ${KOTEK_CPP_STANDARD})

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# exposed so code can guard C++20-only features when building for Windows XP
add_compile_definitions(KOTEK_USE_CPP_STANDARD=${KOTEK_CPP_STANDARD})

# mark applied only after everything ran — never before the MSVC block (see
# the comment at the top)
set_property(GLOBAL PROPERTY KOTEK_COMPILER_GLOBALS_APPLIED ON)

message(STATUS "${CMAKE_CURRENT_LIST_FILE} is applied!")
