message(STATUS "Downloading vcpkg for downloading big packages because of nuget limitations...")

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
    message(STATUS "You didn't have vcpkg so we clone it")
    execute_process(COMMAND "git" clone https://github.com/microsoft/vcpkg.git WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()


if (WIN32)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.bat")
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install angle:x64-windows)
    # TODO: move all libraries to nuget expect for ANGLE...
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install vulkan:x64-windows)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install zstd:x64-windows)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install rmlui[freetype]:x64-windows)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install assimp:x64-windows)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install freetype:x64-windows)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install gtest:x64-windows)
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg" install bgfx[multithreaded]:x64-windows)
else()
    message(FATAL_ERROR "implement for other platforms")
endif()