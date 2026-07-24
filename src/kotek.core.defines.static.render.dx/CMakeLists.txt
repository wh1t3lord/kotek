cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.render.dx VERSION 1 LANGUAGES CXX)




if (WIN32)

	if ("${KOTEK_DIRECTX}" STREQUAL "")
		set(KOTEK_DIRECTX "ON" CACHE INTERNAL "")
	endif()

	if ("${KOTEK_DIRECTX}" STREQUAL "ON")
		list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_DIRECTX)

		# if you set 12 it means we will add all directx versions or those who is equal or lower to "x" value
		set(KOTEK_DIRECTX_VERSION 12 CACHE INTERNAL "")
	endif()

	message("[${PROJECT_NAME}]: DirectX is '${KOTEK_DIRECTX}'")

	if ("${KOTEK_DIRECTX}" STREQUAL "ON")

		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

		#ifdef KOTEK_DIRECTX
			#define KOTEK_USE_DIRECTX
			#define KOTEK_USE_DIRECTX_VERSION ${KOTEK_DIRECTX_VERSION}
		#endif
		")

	else()

		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")

	endif()

else()

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")

endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_Render_DirectX SHUTDOWN ShutdownModule_Core_Defines_Static_Render_DirectX
	"include/kotek_core_defines_static_render_dx.h"
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"src/main_core_defines_static_render_dx_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)