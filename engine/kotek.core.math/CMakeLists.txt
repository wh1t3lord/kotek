cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.math VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glm REQUIRED)
		else()
	    	find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
	   	endif()
	elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(directxmath REQUIRED)
		else()
	   		find_package(directxmath REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

message("[${PROJECT_NAME}]: math library is '${KOTEK_MATH_LIBRARY}'")

add_library(${PROJECT_NAME} STATIC 
	"include/kotek_std_alias_math.h"
	"include/kotek_std_math_vector1f.h"
	"include/kotek_std_math_vector2f.h"
	"include/kotek_std_math_vector3f.h"
	"include/kotek_std_math_vector4f.h"
	"include/kotek_std_math_quaternionf.h"
	"include/kotek_std_math_matrix_2x2_f.h"
	"include/kotek_std_math_matrix_3x3_f.h"
	"include/kotek_std_math_matrix_4x4_f.h"
	"include/kotek_std_math.h"
	"include/kotek_core_math.h"
	"tests/kotek_core_test_math.cpp"
	"src/main_core_math_dll.cpp")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	target_include_directories(${PROJECT_NAME} PUBLIC glm::glm)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
	target_include_directories(${PROJECT_NAME} PUBLIC Microsoft::DirectXMath)
endif()

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_link_libraries(${PROJECT_NAME} glm::glm)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    target_link_libraries(${PROJECT_NAME} Microsoft::DirectXMath)
endif()

target_link_libraries(${PROJECT_NAME} kotek.core.defines.static.math)
target_link_libraries(${PROJECT_NAME} kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} kotek.core.types.numerics)