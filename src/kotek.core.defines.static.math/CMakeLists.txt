cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.math VERSION 1 LANGUAGES CXX)




if ("${KOTEK_MATH_LIBRARY}" STREQUAL "")
	if (WIN32)
		if ("${KOTEK_CONFIGURATION_TYPE}" STREQUAL "minimal")
			set(KOTEK_MATH_LIBRARY "GLM" CACHE INTERNAL "")
		else()
			set(KOTEK_MATH_LIBRARY "DXM" CACHE INTERNAL "")
		endif()
	else()
		set(KOTEK_MATH_LIBRARY "GLM" CACHE INTERNAL "")
	endif()
endif()

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_GLM)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_DXM)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "EIGEN")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_EIGEN)
endif()

if ("${KOTEK_MATH_LIBRARY_IMPLICIT_CASTING}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_IMPLICIT_CASTING)
endif()

if ("${KOTEK_MATH_LIBRARY_BROADCASTING}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_BROADCASTING)
endif()

if ("${KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED)
endif()

message("[${PROJECT_NAME}]: math library is '${KOTEK_MATH_LIBRARY}'")

if (NOT "${KOTEK_MATH_LIBRARY}" STREQUAL "")
	# the backend choice is a configure-time decision — emit it UNCONDITIONALLY:
	# a gated #ifdef + #else #error form fires for every TU that does not link
	# this module's PUBLIC raw flag (e.g. defines.static.cpp links nothing),
	# which is most of the tree now that the header is shared
	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		set(_kotek_math_backend_define "#define KOTEK_USE_MATH_LIBRARY_GLM")
	elseif ("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		set(_kotek_math_backend_define "#define KOTEK_USE_MATH_LIBRARY_DXM")
	else()
		message(FATAL_ERROR "[${PROJECT_NAME}]: unknown KOTEK_MATH_LIBRARY '${KOTEK_MATH_LIBRARY}' (supported: GLM, DXM)")
	endif()

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

	${_kotek_math_backend_define}

	// todo: implement this please
	#ifdef KOTEK_MATH_LIBRARY_IMPLICIT_CASTING
		#define KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	#endif

	#ifdef KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
		#define KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#endif

	/// @brief \~english if enabled (defined KOTEK_MATH_LIBRARY_BROADCASTING) means
	/// there're operations sum,minus will align matrix/vector dims for example
	/// matrix3x3 + vec2 leads to this = part of matrix3x3 taken as matrix2x2 then summed with vec2
	/// [0][1][2] + [10]   [10][11][ 2]
	/// [3][4][5] + [20] = [23][24][ 5]
	/// [6][7][8]          [ 6][ 7][ 8]
	/// SO if a such macro not defined we strictly follow linear math rules from books
	/// (like sum between arbitrary matrix and vector are not defined)
	#ifdef KOTEK_MATH_LIBRARY_BROADCASTING
		#define KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#endif
	")
else()
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_Math SHUTDOWN ShutdownModule_Core_Defines_Static_Math
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_static_math.h"
	"src/main_core_defines_static_math_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)