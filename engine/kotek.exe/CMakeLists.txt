cmake_minimum_required(VERSION 3.19.3)

project(${KOTEK_PROJECT_NAME_OVERRIDE_KOTEK} VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
        if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
            # Spirv-tools
		    #find_package(SPIRV-Tools CONFIG REQUIRED)
		    #find_package(SPIRV-Tools-opt CONFIG REQUIRED)
		    #find_package(SPIRV-Tools-link CONFIG REQUIRED)
		    #find_package(SPIRV-Tools-lint CONFIG REQUIRED)
        else()
        endif()
    endif()
endif()



add_executable(${PROJECT_NAME} 
    "src/entry_point.cpp"
)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

if ("${KOTEK_SDK}" STREQUAL "ON")
    if (WIN32)
    # TODO: you need to remove that thing and use a cmake package for installation those .dlls!

        if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
        else()
            set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;$(ProjectDir)../../../${KOTEK_DEPS_FOLDER}/wxWidgets/lib/vc_x64_dll/;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
            
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
        endif()
    endif()
endif()

if (UNIX)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/*.ktk" $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMENT "Copying ktk file because non-Windows platforms don't operate with dlls and cmake treat them e.g. .so and .a as one type of library and they go only to library_output_folder and it means that we need to implemenet that functionality for non-Windows platforms that restore Window's cmake functionality that dynamic libraries are copied to specified runtime output directory because dynamic libs on Windows are treated by cmake as runtime objects instead of libraries as on Linux")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/*.so" $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMENT "Copying ktk file because non-Windows platforms don't operate with dlls and cmake treat them e.g. .so and .a as one type of library and they go only to library_output_folder and it means that we need to implemenet that functionality for non-Windows platforms that restore Window's cmake functionality that dynamic libraries are copied to specified runtime output directory because dynamic libs on Windows are treated by cmake as runtime objects instead of libraries as on Linux")
endif()

if ("${KOTEK_MEMORY_LEAK_DETECTION}" STREQUAL "ON")
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
        else()
        endif()
    endif()


    if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
        # Spirv-Tools, TODO: add when you will change all projects to SHARED, STATIC and HYBRID (most of them static, but zircon.game is shared and glad projects too!)
        # if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "SHARED")
        #     target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-shared)
        # elseif("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
        #     target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-static)
        # else()
        #     message(FATAL_ERROR "[${PROJECT_NAME}]: you must specify development type as 'SHARED' or 'STATIC'")
        # endif()

        #target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-static)
        #target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-opt)
        #target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-link)
        #target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-lint)
    else()
    endif()
endif()

#set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/exe")
#set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.game)