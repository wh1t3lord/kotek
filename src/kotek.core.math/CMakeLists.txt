cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.math VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		if ("${KOTEK_TESTS}" STREQUAL "ON")
			find_package(GTest CONFIG REQUIRED)
		endif()
	elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if ("${KOTEK_TESTS}" STREQUAL "ON")
			find_package(GTest CONFIG REQUIRED)
		endif()
	else()
		if ("${KOTEK_TESTS}" STREQUAL "ON")
			find_package(GTest REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()


	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glm REQUIRED)
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			file(GLOB nuget_glm_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Glm.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_glm_folder}" MATCHES "Kotek.Packages.Glm.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package glm exists!")
			else()
				message(FATAL_ERROR "failed to find glm package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()
		else()
	    	find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
	   	endif()
	elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(directxmath REQUIRED)
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			file(GLOB nuget_directxmath_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.DirectXMath.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_directxmath_folder}" MATCHES "Kotek.Packages.DirectXMath.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package directxmath exists!")
			else()
				message(FATAL_ERROR "failed to find directxmath package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()
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
	"include/kotek_std_math_functions_vector.h"
	"include/kotek_std_math_functions_matrix.h"
	"include/kotek_std_math_functions_numeric.h"
	"include/kotek_std_math_functions.h"
	"include/kotek_std_math_matrix4f_view.h"
	"include/kotek_std_math_matrix3f_view.h"
	"include/kotek_std_math_matrix2f_view.h"
	"include/kotek_std_math_matrix1f_view.h"
	"include/kotek_std_math_matrix4f_const_view.h"
	"include/kotek_std_math_matrix3f_const_view.h"
	"include/kotek_std_math_matrix2f_const_view.h"
	"include/kotek_std_math_matrix1f_const_view.h"
	"tests/kotek_core_test_math.cpp"
	"src/kotek_std_math_vector1f.cpp"
	"src/kotek_std_math_vector2f.cpp"
	"src/kotek_std_math_vector3f.cpp"
	"src/kotek_std_math_vector4f.cpp"
	"src/kotek_std_math_matrix4f_view.cpp"
	"src/kotek_std_math_matrix3f_view.cpp"
	"src/kotek_std_math_matrix2f_view.cpp"
	"src/kotek_std_math_matrix1f_view.cpp"
	"src/main_core_math_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glm_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: glm package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_glm_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()
	elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_directxmath_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: directxmath package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_directxmath_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()
	endif()
else()
	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		target_include_directories(${PROJECT_NAME} PUBLIC glm::glm)
	elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		target_include_directories(${PROJECT_NAME} PUBLIC Microsoft::DirectXMath)
	endif()
endif()

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
else()
	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
	elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		target_link_libraries(${PROJECT_NAME} PUBLIC Microsoft::DirectXMath)
	endif()

	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.utility)
