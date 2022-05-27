cmake_minimum_required(VERSION 3.19.3)

project(kotek VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/include/")

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
link_directories("../../${KOTEK_DEPS_FOLDER}/vld/lib/Win64/")
endif()
 
link_directories("../../${KOTEK_DEPS_FOLDER}/ktx/${CMAKE_BUILD_TYPE}/lib/")
link_directories("../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/lib/")

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_executable(${PROJECT_NAME} 
    "src/entry_point.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

if (KOTEK_SDK)
    if (WIN32)
        set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;$(ProjectDir)../../../${KOTEK_DEPS_FOLDER}/wxWidgets/lib/vc_x64_dll/;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    endif()
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
     "${PROJECT_SOURCE_DIR}../../../${KOTEK_DEPS_FOLDER}/vld/bin/Win64/" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    file(GLOB WXWIDGETS_DLLS ${PROJECT_SOURCE_DIR}../../../${KOTEK_DEPS_FOLDER}/wxWidgets/lib/vc_x64_dll/*ud*.dll)
    foreach(CurrentHeaderFile IN LISTS WXWIDGETS_DLLS)
        add_custom_command(
                    TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentHeaderFile} $<TARGET_FILE_DIR:${PROJECT_NAME}>
                    COMMENT "Copying header: ${CurrentHeaderFile}")
    endforeach()
else()
    file(GLOB WXWIDGETS_DLLS ${PROJECT_SOURCE_DIR}../../../${KOTEK_DEPS_FOLDER}/wxWidgets/lib/vc_x64_dll/*u_*.dll)
    foreach(CurrentHeaderFile IN LISTS WXWIDGETS_DLLS)
        add_custom_command(
                    TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentHeaderFile} $<TARGET_FILE_DIR:${PROJECT_NAME}>
                    COMMENT "Copying header: ${CurrentHeaderFile}")
    endforeach()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.game)