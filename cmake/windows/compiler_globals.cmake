message(STATUS "applying ${CMAKE_CURRENT_LIST_FILE}")

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# for all possible compilers 
add_compile_definitions(
    NOMINMAX
)

message(STATUS "${CMAKE_CURRENT_LIST_FILE} is applied!")