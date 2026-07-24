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
# fetch hits the network and would run on every configure otherwise
execute_process(COMMAND "git" rev-parse HEAD WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg" OUTPUT_VARIABLE _kotek_vcpkg_head OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
if (NOT "${_kotek_vcpkg_head}" STREQUAL "${KOTEK_VCPKG_PINNED_COMMIT}")
    execute_process(COMMAND "git" fetch --depth 1 origin ${KOTEK_VCPKG_PINNED_COMMIT} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    execute_process(COMMAND "git" checkout FETCH_HEAD WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
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
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install ktx:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install tbb:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install spdlog:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install tracy:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install boost-json:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install etl:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install utfcpp:${KOTEK_VCPKG_TRIPLET})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install glm:${KOTEK_VCPKG_TRIPLET})

    # this required for dav1d otherwise it won't find due to missing package...
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install pkgconf:${KOTEK_VCPKG_TRIPLET})
else()
    message(FATAL_ERROR "implement for other platforms")
endif()