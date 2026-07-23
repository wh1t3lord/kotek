message(STATUS "Downloading vcpkg for downloading big packages because of nuget limitations...")

# pin vcpkg to the snapshot the dep set is validated against (2026-05-27);
# cloning floating master makes CI builds non-deterministic — a port that
# builds on the owner's machine can be broken upstream two weeks later
set(KOTEK_VCPKG_PINNED_COMMIT "1bf999414d7def6fea4c3c310d613ceed039f929")

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    message(STATUS "You didn't have vcpkg so we clone it")
    execute_process(COMMAND "git" clone https://github.com/microsoft/vcpkg.git WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# fresh clones land on master HEAD — reset to the validated snapshot
execute_process(COMMAND "git" checkout ${KOTEK_VCPKG_PINNED_COMMIT} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")

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