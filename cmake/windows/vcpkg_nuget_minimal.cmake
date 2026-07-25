message(STATUS "Downloading vcpkg for downloading big packages because of nuget limitations...")

# pin vcpkg to the snapshot the dep set is validated against (2026-05-27);
# cloning floating master makes CI builds non-deterministic — a port that
# builds on the owner's machine can be broken upstream two weeks later
set(KOTEK_VCPKG_PINNED_COMMIT "1bf999414d7def6fea4c3c310d613ceed039f929")

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    message(STATUS "You didn't have vcpkg so we clone it")
    execute_process(COMMAND "git" clone https://github.com/microsoft/vcpkg.git WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# a cache-restored vcpkg/ (installed tree + exe, no checkout) is not a vcpkg
# root — git init + fetch the pin in place instead of cloning into a
# non-empty dir (CI cache hit case)
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/.git")
    execute_process(COMMAND "git" init WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    execute_process(COMMAND "git" remote add origin https://github.com/microsoft/vcpkg.git WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
endif()

# reset to the validated snapshot, but only when not already there —
# fetch hits the network and would run on every configure otherwise.
# the portfile restore keeps the pin checkout below conflict-free when the
# tracy patch (applied further down) is already present in the tree
execute_process(COMMAND "git" checkout -- ports/tracy/portfile.cmake WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg" ERROR_QUIET)
execute_process(COMMAND "git" rev-parse HEAD WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg" OUTPUT_VARIABLE _kotek_vcpkg_head OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
if (NOT "${_kotek_vcpkg_head}" STREQUAL "${KOTEK_VCPKG_PINNED_COMMIT}")
    execute_process(COMMAND "git" fetch --depth 1 origin ${KOTEK_VCPKG_PINNED_COMMIT} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    execute_process(COMMAND "git" checkout FETCH_HEAD WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
endif()

# tracy port patch (idempotent, LF-normalized, fail-loud): ktkProfiler drives
# the profiler lifetime explicitly (tracy::StartupProfiler/ShutdownProfiler
# under TRACY_DELAYED_INIT+TRACY_MANUAL_LIFETIME from defines.static.
# profilers), but upstream compiles those entry points into TracyClient only
# when both cmake options are ON and the port does not forward them — the
# stock lib lacks the symbols and every from-scratch Release link dies with
# LNK2019 (local incremental builds masked it). vcpkg does NOT rebuild an
# installed same-version package on a portfile-only change (verified: plain
# install and --recurse both report "already installed"), so the transition
# is driven by remove+install exactly once, tracked by a marker file.
set(_kotek_tracy_portfile "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/ports/tracy/portfile.cmake")
set(_kotek_tracy_marker "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/.kotek_tracy_manual_lifetime")
set(_kotek_tracy_force_rebuild OFF)
if (EXISTS "${_kotek_tracy_portfile}")
    file(READ "${_kotek_tracy_portfile}" _kotek_tracy_port)
    string(REPLACE "\r\n" "\n" _kotek_tracy_port "${_kotek_tracy_port}")
    set(_kotek_tracy_anchor "    INVERTED_FEATURES\n        crash-handler TRACY_NO_CRASH_HANDLER\n)")
    set(_kotek_tracy_patched "    INVERTED_FEATURES\n        crash-handler TRACY_NO_CRASH_HANDLER\n)\n\n# patched by kotek (cmake/windows/vcpkg_nuget_minimal.cmake): the engine\n# drives the profiler lifetime explicitly (ktkProfiler calls\n# tracy::StartupProfiler/ShutdownProfiler) — upstream compiles those entry\n# points into TracyClient only when both options are on and the port does\n# not forward them\nlist(APPEND FEATURE_OPTIONS \"-DTRACY_DELAYED_INIT=ON\" \"-DTRACY_MANUAL_LIFETIME=ON\")")
    if (_kotek_tracy_port MATCHES "TRACY_MANUAL_LIFETIME")
        # already patched — rebuild only if the patched install never ran
        if (NOT EXISTS "${_kotek_tracy_marker}")
            set(_kotek_tracy_force_rebuild ON)
        endif()
    elseif (_kotek_tracy_port MATCHES "TRACY_NO_CRASH_HANDLER")
        string(REPLACE "${_kotek_tracy_anchor}" "${_kotek_tracy_patched}"
            _kotek_tracy_port "${_kotek_tracy_port}")
        if (NOT _kotek_tracy_port MATCHES "TRACY_MANUAL_LIFETIME")
            message(FATAL_ERROR "[kotek]: tracy portfile patch did not apply — upstream text drifted, update cmake/windows/vcpkg_nuget_minimal.cmake")
        endif()
        file(WRITE "${_kotek_tracy_portfile}" "${_kotek_tracy_port}")
        set(_kotek_tracy_force_rebuild ON)
        message(STATUS "[kotek]: patched vcpkg tracy port (TRACY_DELAYED_INIT + TRACY_MANUAL_LIFETIME forwarded)")
    endif()
endif()

if (WIN32)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.bat")
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install vulkan:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install zstd:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install rmlui[freetype]:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install freetype:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install gtest:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install bgfx[multithreaded]:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install cgltf:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install dav1d:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install glfw3:${KOTEK_VCPKG_TRIPLET})
    # kotek.core.memory.cpu's default allocator (KOTEK_MEMORY_ALLOCATOR_CPU)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install mimalloc:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install ktx:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install tbb:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install spdlog:${KOTEK_VCPKG_TRIPLET})
    if (_kotek_tracy_force_rebuild)
        # same-version installs are treated as satisfied even when the
        # portfile changed (verified: plain install and --recurse both
        # no-op) — only remove+install actually rebuilds the lib with the
        # manual-lifetime symbols. Runs once, then the marker settles it
        message(STATUS "[kotek]: rebuilding tracy with the manual-lifetime patch (one-time)...")
        execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" remove tracy:${KOTEK_VCPKG_TRIPLET})
        execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install tracy:${KOTEK_VCPKG_TRIPLET}
            RESULT_VARIABLE _kotek_tracy_install_rc)
        if (NOT _kotek_tracy_install_rc EQUAL 0)
            message(FATAL_ERROR "[kotek]: tracy rebuild after the port patch failed (${_kotek_tracy_install_rc})")
        endif()
        file(WRITE "${_kotek_tracy_marker}" "tracy rebuilt with TRACY_DELAYED_INIT+TRACY_MANUAL_LIFETIME\n")
    else()
        execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install tracy:${KOTEK_VCPKG_TRIPLET})
    endif()
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install boost-json:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install etl:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install utfcpp:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install glm:${KOTEK_VCPKG_TRIPLET})

    # this required for dav1d otherwise it won't find due to missing package...
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install pkgconf:${KOTEK_VCPKG_TRIPLET})
else()
    message(FATAL_ERROR "implement for other platforms")
endif()