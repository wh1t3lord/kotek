message(STATUS "applying ${CMAKE_CURRENT_LIST_FILE}")

if(MSVC)
    # we force that option because it is important to embed runtime libraries otherwise it will be hard to maintain windows xp and current windows development (or probably other compilers that users might want to use or override manually)
    # and we make shipping the user output .exe or applicaction easily without any troubles
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# for all possible compilers 
add_compile_definitions(
    NOMINMAX
)

# By default (aka no legacy systems like Windows XP) we use C++20 standard
# Otherwise we will fit to 17 because latest official compiler support of Windows XP can provide full C++17 standard support
# todo: add switching model to Windows XP compiling
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "${CMAKE_CURRENT_LIST_FILE} is applied!")