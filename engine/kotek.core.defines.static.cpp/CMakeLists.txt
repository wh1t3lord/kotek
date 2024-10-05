cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.cpp VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_STD_LIBRARY}" STREQUAL "")
	set(KOTEK_STD_LIBRARY "BOOST" CACHE INTERNAL "")
endif()

if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "")
	# By default we use RmlUI util I will finish my library

	# TODO: add CEF only when we have it in vcpkg or any other package managers
	set(KOTEK_UI_GAME_LIBRARY "RMLUI" CACHE INTERNAL "")
endif()

if ("${KOTEK_GAME_OUTPUT_LIBRARY_NAME}" STREQUAL "")
	set(KOTEK_GAME_OUTPUT_LIBRARY_NAME "game.ktk" CACHE INTERNAL "")
endif()

if ("${KOTEK_LOG_OUTPUT_FILE_NAME}" STREQUAL "")
	set(KOTEK_LOG_OUTPUT_FILE_NAME "all.log" CACHE INTERNAL "")
endif()

message("[${PROJECT_NAME}]: KOTEK_STD_LIBRARY=${KOTEK_STD_LIBRARY}")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_BOOST_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME "Boost")
elseif("${KOTEK_STD_LIBRARY}" STREQUAL "STD")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_STD_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME "Standard library")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_CUSTOM_STD_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME ${KOTEK_STD_LIBRARY})
endif()

if ("${KOTEK_SDK_IMGUI}" STREQUAL "" OR "${KOTEK_SDK_IMGUI}" STREQUAL "IMGUI")
	set(KOTEK_SDK_IMGUI "IMGUI" CACHE INTERNAL "")
	set(KOTEK_UI_IMGUI_LIBRARY_IMGUI "" CACHE INTERNAL "")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_SDK_IMGUI)
endif()

# By default we for to use CEF
if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_CEF_LIBRARY)

	# For internal (cmake) purposes
	set(KOTEK_UI_GAME_LIBRARY_NAME "CEF")

	# For C++ code generation
	set(KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME "Chromium Embedded Framework")
elseif("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "RMLUI")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_RMLUI_LIBRARY)

	set(KOTEK_UI_GAME_LIBRARY_NAME "RMLUI")
	set(KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME "RmlUi")
elseif("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "ATHENA")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_ATHENA_LIBRARY)

	set(KOTEK_UI_GAME_LIBRARY_NAME "ATHENA")
	set(KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME "Athena")
else()
	message("[${PROJECT_NAME}] you didn't specify any ui library for this generation")
endif()

if ("${KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_HIDE_DISABLE_WARNINGS_PREPROCESSOR)
endif()

if ("${KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR)
endif()

### C++ NEW KEYWORDS SINCE 11 standard ###
if ("${KOTEK_CPP_KEYWORD_NOEXCEPT}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_NOEXCEPT "noexcept")
endif()


## C++11 ##
if ("${KOTEK_CPP_KEYWORD_CONSTEXPR}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_CONSTEXPR "constexpr")
endif()

if ("${KOTEK_CPP_KEYWORD_ALIGNAS}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_ALIGNAS "alignas")
endif()

if ("${KOTEK_CPP_KEYWORD_ALIGNOF}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_ALIGNOF "alignof")
endif()

if ("${KOTEK_CPP_KEYWORD_DECLTYPE}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_DECLTYPE "decltype")
endif()

if ("${KOTEK_CPP_KEYWORD_STATIC_ASSERT}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_STATIC_ASSERT "static_assert")
endif()

if ("${KOTEK_CPP_KEYWORD_THREAD_LOCAL}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_THREAD_LOCAL "thread_local")
endif()

if ("${KOTEK_CPP_KEYWORD_NULLPTR}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_NULLPTR "nullptr")
endif()

if ("${KOTEK_CPP_KEYWORD_CHAR_16_T}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_CHAR_16_T "char16_t")
endif()

if ("${KOTEK_CPP_KEYWORD_CHAR_8_T}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_CHAR_8_T "char8_t")
endif()
## C++11 ##

## C++14 ##

## C++14 ##

## C++17 ##

## C++17 ##

## C++20 ##
if ("${KOTEK_CPP_KEYWORD_REFLEXPR}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_REFLEXPR "reflexpr")
endif()
## C++20 ##

### C++ NEW KEYWORDS SINCE 11 standard ###

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	if ("${KOTEK_MEMORY_LEAK_DETECTION}" STREQUAL "")
		set(KOTEK_MEMORY_LEAK_DETECTION "ON" CACHE INTERNAL "")
	endif()
endif()

if ("${KOTEK_MEMORY_LEAK_DETECTION}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MEMORY_LEAK_DETECTION)
endif()

if ("${KOTEK_CPP_MEMORY_LEAK_LIBRARY}" STREQUAL "")
	if (WIN32)
		message("[${PROJECT_NAME}]: enabling memory leak detection (built-in)")
		set(KOTEK_CPP_MEMORY_LEAK_LIBRARY "CRT" CACHE INTERNAL "")
	endif()
endif()

if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "")
	set(KOTEK_MEMORY_ALLOCATOR_CPU "MIMALLOC" CACHE INTERNAL "")
endif()

if ("${KOTEK_TESTS}" STREQUAL "ON")
	message("[${PROJECT_NAME}] enabled unit testing we can't use mimalloc by default, turning off mimalloc")
	set(KOTEK_MEMORY_ALLOCATOR_CPU "OFF" CACHE INTERNAL "")
endif()

if ("${KOTEK_STRING_CONFIGURATION}" STREQUAL "" OR "${KOTEK_STRING_CONFIGURATION}" STREQUAL "OPTIMIZED")
	set(KOTEK_STRING_CONFIGURATION "OPTIMIZED" CACHE INTERNAL "")
elseif("${KOTEK_STRING_CONFIGURATION}" STREQUAL "RAW")
	set(KOTEK_STRING_CONFIGURATION "RAW" CACHE INTERNAL "")
else()
	message(FATAL_ERROR "you specified unsupported string configuration: ${KOTEK_STRING_CONFIGURATION}")
endif()

if ("${KOTEK_STRING_CONFIGURATION}" STREQUAL "RAW")
	if ("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "")
		set(KOTEK_STRING_CONFIGURATION_CHAR_TYPE "8" CACHE INTERNAL "")
	else()
		if (NOT ("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "1" 
			OR "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "8"
			OR "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "16"
			OR "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "32"))
			message(FATAL_ERROR "you passed a wrong string for KOTEK_STRING_CONFIGURATION_CHAR_TYPE possible values are: '1' means 'char'; '8' means 'char8_t'; '16' means 'char16_t'; '32' means 'char32_t'; we recommend to use between char8_t or char32_t, don't wchar_t because it is hard to work if you make a complex system.")
		else()
			set(KOTEK_STRING_CONFIGURATION_CHAR_TYPE "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" CACHE INTERNAL "")
		endif()
	endif()
else()
	if ("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "")
		set(KOTEK_STRING_CONFIGURATION_CHAR_TYPE "1" CACHE INTERNAL "")
	else()
		if (NOT ("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "1" 
			OR "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "8"
			OR "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "16"
			OR "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "32"))
			message(FATAL_ERROR "you passed a wrong string for KOTEK_STRING_CONFIGURATION_CHAR_TYPE possible values are: '1' means 'char'; '8' means 'char8_t'; '16' means 'char16_t'; '32' means 'char32_t'; we recommend to use between char8_t or char32_t, don't wchar_t because it is hard to work if you make a complex system.")
		else()
			set(KOTEK_STRING_CONFIGURATION_CHAR_TYPE "${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" CACHE INTERNAL "")
		endif()
	endif()
endif()

### User Data

# file name where user settings are saved it includes every preferences on every possible field in your game/system
if ("${KOTEK_USER_DATA_CONFIG_NAME}" STREQUAL "")
	set(KOTEK_USER_DATA_CONFIG_NAME "settings" CACHE INTERNAL "")
endif()

### Startup renderer

if ("${KOTEK_STARTUP_RENDERER}" STREQUAL "")
	message(FATAL_ERROR "you must specify renderer what you need to load. see documentation.")
endif()

if ("${KOTEK_STARTUP_RENDERER_VERSION}" STREQUAL "")
	message(FATAL_ERROR "you must specify renderer version what you need to load. see documentation.")
endif()

### Namespaces

if ("${KOTEK_NAMESPACE_KOTEK}" STREQUAL "" OR "${KOTEK_NAMESPACE_KOTEK}" STREQUAL "ON")
	if ("${KOTEK_BEGIN_NAMESPACE_KOTEK}" STREQUAL "")
		set(KOTEK_USE_NAMESPACE_KOTEK "Kotek::")
		set(KOTEK_BEGIN_NAMESPACE_KOTEK "Kotek")
	else()
		set(KOTEK_USE_NAMESPACE_KOTEK "${KOTEK_BEGIN_NAMESPACE_KOTEK}::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_KOTEK)
	set(KOTEK_END_NAMESPACE_KOTEK "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_KOTEK)
	set(KOTEK_USE_NAMESPACE_KOTEK "")
	set(KOTEK_BEGIN_NAMESPACE_KOTEK "")
	set(KOTEK_END_NAMESPACE_KOTEK "")
endif()

if ("${KOTEK_NAMESPACE_CORE}" STREQUAL "" OR "${KOTEK_NAMESPACE_CORE}" STREQUAL "ON")
	if ("${KOTEK_BEGIN_NAMESPACE_CORE}" STREQUAL "")
		set(KOTEK_USE_NAMESPACE_CORE "Core::")
		set(KOTEK_BEGIN_NAMESPACE_CORE "Core")
	else()
		set(KOTEK_USE_NAMESPACE_CORE "${KOTEK_BEGIN_NAMESPACE_CORE}::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_CORE)
	set(KOTEK_END_NAMESPACE_CORE "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_CORE)
	set(KOTEK_USE_NAMESPACE_CORE "")
	set(KOTEK_BEGIN_NAMESPACE_CORE "")
	set(KOTEK_END_NAMESPACE_CORE "")
endif()


if ("${KOTEK_NAMESPACE_KTK}" STREQUAL "" OR "${KOTEK_NAMESPACE_KTK}" STREQUAL "ON")
	if ("${KOTEK_BEGIN_NAMESPACE_KTK}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_KTK "ktk")
		set(KOTEK_USE_NAMESPACE_KTK "ktk::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_KTK)
	set(KOTEK_END_NAMESPACE_KTK "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_KTK)
	set(KOTEK_USE_NAMESPACE_KTK "")
	set(KOTEK_BEGIN_NAMESPACE_KTK "")
	set(KOTEK_END_NAMESPACE_KTK "")
endif()


if ("${KOTEK_NAMESPACE_RENDER}" STREQUAL "" OR "${KOTEK_NAMESPACE_RENDER}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_RENDER}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_RENDER "Render")
		set(KOTEK_USE_NAMESPACE_RENDER "Render::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER)
	set(KOTEK_END_NAMESPACE_RENDER "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER)
	set(KOTEK_USE_NAMESPACE_RENDER "")
	set(KOTEK_BEGIN_NAMESPACE_RENDER "")
	set(KOTEK_END_NAMESPACE_RENDER "")
endif()

if ("${KOTEK_NAMESPACE_UI}" STREQUAL "" OR "${KOTEK_NAMESPACE_UI}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_UI}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_UI "UI")
		set(KOTEK_USE_NAMESPACE_UI "UI::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_UI)
	set(KOTEK_END_NAMESPACE_UI "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_UI)
	set(KOTEK_USE_NAMESPACE_UI "")
	set(KOTEK_BEGIN_NAMESPACE_UI "")
	set(KOTEK_END_NAMESPACE_UI "")
endif()

if ("${KOTEK_NAMESPACE_MATH}" STREQUAL "" OR "${KOTEK_NAMESPACE_MATH}" STREQUAL "ON")
	if ("${KOTEK_BEGIN_NAMESPACE_MATH}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_MATH "math")
		set(KOTEK_USE_NAMESPACE_MATH "math::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_MATH)
	set(KOTEK_END_NAMESPACE_MATH "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_MATH)
	set(KOTEK_USE_NAMESPACE_MATH "")
	set(KOTEK_BEGIN_NAMESPACE_MATH "")
	set(KOTEK_END_NAMESPACE_MATH "")
endif()

if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "")
	set(KOTEK_DEVELOPMENT_TYPE "SHARED" CACHE INTERNAL "")
endif()

if ("${KOTEK_NAMESPACE_GAME}" STREQUAL "" OR "${KOTEK_NAMESPACE_GAME}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_GAME}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_GAME "Game")
		set(KOTEK_USE_NAMESPACE_GAME "Game::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_GAME)
	set(KOTEK_END_NAMESPACE_GAME "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_GAME)
	set(KOTEK_USE_NAMESPACE_GAME "")
	set(KOTEK_BEGIN_NAMESPACE_GAME "")
	set(KOTEK_END_NAMESPACE_GAME "")
endif()

if ("${KOTEK_NAMESPACE_ECS}" STREQUAL "" OR "${KOTEK_NAMESPACE_ECS}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_ECS}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_ECS "ecs")
		set(KOTEK_USE_NAMESPACE_ECS "ecs::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_ECS)
	set(KOTEK_END_NAMESPACE_ECS "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_ECS)
	set(KOTEK_USE_NAMESPACE_ECS "")
	set(KOTEK_BEGIN_NAMESPACE_ECS "")
	set(KOTEK_END_NAMESPACE_ECS "")
endif()

if ("${KOTEK_NAMESPACE_ECS_FRONTEND}" STREQUAL "" OR "${KOTEK_NAMESPACE_ECS_FRONTEND}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND "frontend")
		set(KOTEK_USE_NAMESPACE_ECS_FRONTEND "frontend::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_ECS_FRONTEND)
	set(KOTEK_END_NAMESPACE_ECS_FRONTEND "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_ECS_FRONTEND)
	set(KOTEK_USE_NAMESPACE_ECS_FRONTEND "")
	set(KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND "")
	set(KOTEK_END_NAMESPACE_ECS_FRONTEND "")
endif()

if ("${KOTEK_NAMESPACE_ECS_BACKEND}" STREQUAL "" OR "${KOTEK_NAMESPACE_ECS_BACKEND}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_ECS_BACKEND}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_ECS_BACKEND "backend")
		set(KOTEK_USE_NAMESPACE_ECS_BACKEND "backend::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_ECS_BACKEND)
	set(KOTEK_END_NAMESPACE_ECS_BACKEND "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_ECS_BACKEND)
	set(KOTEK_USE_NAMESPACE_ECS_BACKEND "")
	set(KOTEK_BEGIN_NAMESPACE_ECS_BACKEND "")
	set(KOTEK_END_NAMESPACE_ECS_BACKEND "")
endif()

if ("${KOTEK_NAMESPACE_FILESYSTEM}" STREQUAL "" OR "${KOTEK_NAMESPACE_FILESYSTEM}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_FILESYSTEM}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_FILESYSTEM "filesystem")
		set(KOTEK_USE_NAMESPACE_FILESYSTEM "filesystem::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_FILESYSTEM)
	set(KOTEK_END_NAMESPACE_FILESYSTEM "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_FILESYSTEM)
	set(KOTEK_USE_NAMESPACE_FILESYSTEM "")
	set(KOTEK_BEGIN_NAMESPACE_FILESYSTEM "")
	set(KOTEK_END_NAMESPACE_FILESYSTEM "")
endif()

if ("${KOTEK_NAMESPACE_RENDER_GL}" STREQUAL "" OR "${KOTEK_NAMESPACE_RENDER_GL}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_RENDER_GL}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_RENDER_GL "gl")
		set(KOTEK_USE_NAMESPACE_RENDER_GL "gl::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER_GL)
	set(KOTEK_END_NAMESPACE_RENDER_GL "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER_GL)
	set(KOTEK_USE_NAMESPACE_RENDER_GL "")
	set(KOTEK_BEGIN_NAMESPACE_RENDER_GL "")
	set(KOTEK_END_NAMESPACE_RENDER_GL "")
endif()

if ("${KOTEK_NAMESPACE_RENDER_VK}" STREQUAL "" OR "${KOTEK_NAMESPACE_RENDER_VK}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_RENDER_VK}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_RENDER_VK "vk")
		set(KOTEK_USE_NAMESPACE_RENDER_VK "vk::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER_VK)
	set(KOTEK_END_NAMESPACE_RENDER_VK "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER_VK)
	set(KOTEK_USE_NAMESPACE_RENDER_VK "")
	set(KOTEK_BEGIN_NAMESPACE_RENDER_VK "")
	set(KOTEK_END_NAMESPACE_RENDER_VK "")
endif()

if ("${KOTEK_NAMESPACE_RENDER_DX}" STREQUAL "" OR "${KOTEK_NAMESPACE_RENDER_DX}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_RENDER_DX}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_RENDER_DX "dx")
		set(KOTEK_USE_NAMESPACE_RENDER_DX "dx::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER_DX)
	set(KOTEK_END_NAMESPACE_RENDER_DX "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_RENDER_DX)
	set(KOTEK_USE_NAMESPACE_RENDER_DX "")
	set(KOTEK_BEGIN_NAMESPACE_RENDER_DX "")
	set(KOTEK_END_NAMESPACE_RENDER_DX "")
endif()

if ("${KOTEK_NAMESPACE_SOUND}" STREQUAL "" OR "${KOTEK_NAMESPACE_SOUND}" STREQUAL "ON")

	if ("${KOTEK_BEGIN_NAMESPACE_SOUND}" STREQUAL "")
		set(KOTEK_BEGIN_NAMESPACE_SOUND "Sound")
		set(KOTEK_USE_NAMESPACE_SOUND "Sound::")
	endif()

	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_SOUND)
	set(KOTEK_END_NAMESPACE_SOUND "}")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_NAMESPACE_SOUND)
	set(KOTEK_USE_NAMESPACE_SOUND "")
	set(KOTEK_BEGIN_NAMESPACE_SOUND "")
	set(KOTEK_END_NAMESPACE_SOUND "")
endif()


### Namespaces


### Renderers

if ("${KOTEK_RENDER_OPENGL}" STREQUAL "")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_RENDER_OPENGL)
endif()

# TODO: change as OpenGL, because Vulkan is not updated
if ("${KOTEK_RENDER_VULKAN}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_RENDER_VULKAN)
endif()

### Renderers

# TODO: add HYBRID it is a current SHARED, but SHARED is when ALL libraries are dll
if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "SHARED")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE})
	set(KOTEK_DEVELOPMENT_TYPE_PACKAGES "SHARED" CACHE INTERNAL "")
elseif("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE})
	set(KOTEK_DEVELOPMENT_TYPE_PACKAGES "STATIC" CACHE INTERNAL "")

	if ("${KOTEK_GAME_MODULE_FUNCTIONS_FILE}" STREQUAL "")
		message(FATAL_ERROR "you must specify KOTEK_GAME_MODULE_FUNCTIONS_FILE by writting <path/to/your_file_where_standard_functions_for_running_module_are_defined.h>. But you make a path from root of your folder see sandbox example https://gitlab.com/wh1t3lord/sandbox")
	endif()

	if ("${KOTEK_USER_FUNCTION_IMG}" STREQUAL "")
		set(KOTEK_USER_FUNCTION_IMG "InitializeModule_Game")
	endif()

	if ("${KOTEK_USER_FUNCTION_SMG}" STREQUAL "")
		set(KOTEK_USER_FUNCTION_SMG "ShutdownModule_Game")
	endif()

	if ("${KOTEK_USER_FUNCTION_UMG}" STREQUAL "")
		set(KOTEK_USER_FUNCTION_UMG "UpdateModule_Game")
	endif()

	if ("${KOTEK_USER_FUNCTION_IMR}" STREQUAL "")
		set(KOTEK_USER_FUNCTION_IMR "InitializeModule_Render")
	endif()
else()
	message(FATAL_ERROR "you must specify KOTEK_DEVELOPMENT_TYPE as SHARED or STATIC...")
endif()

if ("${KOTEK_LIBRARY_TYPE}" STREQUAL "EMB")
	if ("${KOTEK_DEF_FALLBACK_RENDERERS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_FALLBACK_RENDERERS_COUNT "4")
	endif()

	if ("${KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT "16")
	endif()

	if ("${KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT 8)
	endif()

	if ("${KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT}" STREQUAL "")
		set(KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT 128)
	endif()

	if("${KOTEK_DEF_TEXT_RESOURCE_LOADERS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_TEXT_RESOURCE_LOADERS_COUNT 2)
	endif()

	if ("${KOTEK_DEF_JSON_RESOURCE_LOADERS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_JSON_RESOURCE_LOADERS_COUNT 2)
	endif()

	if ("${KOTEK_DEF_TEXT_RESOURCE_SAVERS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_TEXT_RESOURCE_SAVERS_COUNT 2)
	endif()

	if ("${KOTEK_DEF_JSON_RESOURCE_SAVERS_COUNT}" STREQUAL "")
		set(KOTEK_DEF_JSON_RESOURCE_SAVERS_COUNT 2)
	endif()

	if ("${KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT}" STREQUAL "")
		set(KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT 16)
	endif()

	if ("${KOTEK_RESOURCE_SAVER_MANAGER_FILE_POOL_COUNT}" STREQUAL "")
		set(KOTEK_RESOURCE_SAVER_MANAGER_FILE_POOL_COUNT 10)
	endif()

	if ("${KOTEK_DEF_RESOURCE_SAVERS_TYPE_MAX_COUNT}" STREQUAL "")
		set(KOTEK_DEF_RESOURCE_SAVERS_TYPE_MAX_COUNT 16)
	endif()

	if ("${KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL}" STREQUAL "")
		set(KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL 4)
	endif()
elseif("${KOTEK_LIBRARY_TYPE}" STREQUAL "DYN")
else()
	message(FATAL_ERROR "you must specify KOTEK_LIBRARY_TYPE as DYN or EMB...")
endif()

if ("${KOTEK_LOG_LIBRARY}" STREQUAL "" OR "${KOTEK_LOG_LIBRARY}" STREQUAL "SPDLOG")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_LOG_LIBRARY_SPDLOG)
elseif("${KOTEK_LOG_LIBRARY}" STREQUAL "BOOST")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_LOG_LIBRARY_BOOST)	
elseif("${KOTEK_LOG_LIBRARY}" STREQUAL "CUSTOM")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_LOG_LIBRARY_CUSTOM)
else()
	message(FATAL_ERROR "unsupported log type backend (supported values: BOOST - specifies that user uses boost.log library as log's backend; '' or SPDLOG - empty string means that user uses default backend based on spdlog library; CUSTOM - means user specifies own implementation for logging and overloads existing preprocessors/stuff;): ${KOTEK_LOG_LIBRARY}")
endif()

message("[${PROJECT_NAME}]: standard library is ${KOTEK_STD_LIBRARY_NAME}")
message("[${PROJECT_NAME}]: string configuration is '${KOTEK_STRING_CONFIGURATION}'")
message("[${PROJECT_NAME}]: development is for ${KOTEK_LIBRARY_TYPE} environment")
message("[${PROJECT_NAME}]: log backend is ${KOTEK_LOG_LIBRARY}")

### Generating code
if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_BUILD_TYPE)

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
	#ifdef KOTEK_BUILD_TYPE 
		#define KOTEK_USE_CURRENT_BUILD_TYPE ${CMAKE_BUILD_TYPE} 
	#endif")

	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_BUILD_TYPE 
			#define KOTEK_USE_BUILD_TYPE_DEBUG 
		#endif")
	endif()

	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_BUILD_TYPE 
			#define KOTEK_USE_BUILD_TYPE_RELEASE 
		#endif")
	endif()

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_BOOST_LIBRARY
			#define KOTEK_USE_BOOST_LIBRARY
		#endif

		#ifdef KOTEK_STD_LIBRARY
			#define KOTEK_USE_STD_LIBRARY
		#endif

		#define KOTEK_USE_STD_LIBRARY_NAME ${KOTEK_STD_LIBRARY_NAME}

		#if defined(KOTEK_USE_BOOST_LIBRARY) || defined(KOTEK_USE_STD_LIBRARY)
			// use this when we have std implementation like std::any, so we dont need to use it from boost
			#define KOTEK_USE_NOT_CUSTOM_LIBRARY
		#elif defined(KOTEK_CUSTOM_STD_LIBRARY)
			#define KOTEK_USE_CUSTOM_LIBRARY
		#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
#ifndef KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR
	#ifdef _WIN32
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma(\"warning(push,0)\")
	#elif defined(__clang__)
		#define DIAGNOSTIC_HELPER0(x) #x
		#define DIAGNOSTIC_HELPER1(kind, y) DIAGNOSTIC_HELPER0(clang diagnostic kind #y)

		#define PRGM_CLANG(kind, warning) \
			_Pragma(DIAGNOSTIC_HELPER1(kind, warning))

		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma(\"clang diagnostic push\") PRGM_CLANG(ignored, -Wall) PRGM_CLANG(ignored, -Wextra)
	#elif defined(__GNUC__)
		#define DIAGNOSTIC_HELPER0(x) #x
		#define DIAGNOSTIC_HELPER1(kind, y) DIAGNOSTIC_HELPER0(GCC diagnostic kind #y)

		#define PRGM_GCC(kind, warning) \
			_Pragma(DIAGNOSTIC_HELPER1(kind, warning))

                #define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma(\"GCC diagnostic push\") PRGM_GCC(ignored, -Wimplicit-fallthrough) PRGM_GCC(ignored, -Wunused-function) PRGM_GCC(ignored, -Wunused-parameter) PRGM_GCC(ignored, -Wunused-variable) PRGM_GCC(ignored, -Wmissing-field-initializers) PRGM_GCC(ignored, -Wswitch) PRGM_GCC(ignored, -Wpedantic) PRGM_GCC(ignored, -Wattributes) PRGM_GCC(ignored, -Wignored-qualifiers) PRGM_GCC(ignored, -Wparentheses)
	#else
		#error Unknown compiler send the issue to authors!
	#endif

	#ifdef _WIN32
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma(\"warning(pop)\")
	#elif defined(__clang__)
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma(\"clang diagnostic pop\")
	#elif defined(__GNUC__)
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma(\"GCC diagnostic pop\")
	#else
		#error Unknown compiler send the issue to authors!
	#endif
#else
	#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH
	#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP
#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
	#ifndef KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR
		#define KOTEK_CPP_KEYWORD_CONSTEXPR ${KOTEK_CPP_KEYWORD_CONSTEXPR}
		#define KOTEK_CPP_KEYWORD_NOEXCEPT ${KOTEK_CPP_KEYWORD_NOEXCEPT} 
		#define KOTEK_CPP_KEYWORD_ALIGNAS(your_code_string) ${KOTEK_CPP_KEYWORD_ALIGNAS}(your_code_string)
		#define KOTEK_CPP_KEYWORD_ALIGNOF(your_code_string) ${KOTEK_CPP_KEYWORD_ALIGNOF}(your_code_string)
		#define KOTEK_CPP_KEYWORD_DECLTYPE(expression) ${KOTEK_CPP_KEYWORD_DECLTYPE}(expression)
		#define KOTEK_CPP_KEYWORD_STATIC_ASSERT(expression, comment) ${KOTEK_CPP_KEYWORD_STATIC_ASSERT}(expression, comment)
		#define KOTEK_CPP_KEYWORD_THREAD_LOCAL ${KOTEK_CPP_KEYWORD_THREAD_LOCAL}
		#define KOTEK_CPP_KEYWORD_NULLPTR ${KOTEK_CPP_KEYWORD_NULLPTR}
		#define KOTEK_CPP_KEYWORD_CHAR_16_T ${KOTEK_CPP_KEYWORD_CHAR_16_T}
		#define KOTEK_CPP_KEYWORD_CHAR_8_T ${KOTEK_CPP_KEYWORD_CHAR_8_T}
	#else
		#define KOTEK_CPP_KEYWORD_CONSTEXPR
		#define KOTEK_CPP_KEYWORD_NOEXCEPT 
		#define KOTEK_CPP_KEYWORD_ALIGNAS(your_code_string)
		#define KOTEK_CPP_KEYWORD_ALIGNOF(your_code_string)
		#define KOTEK_CPP_KEYWORD_DECLTYPE(expression)
		#define KOTEK_CPP_KEYWORD_STATIC_ASSERT(expression, comment)
		#define KOTEK_CPP_KEYWORD_THREAD_LOCAL
		#define KOTEK_CPP_KEYWORD_NULLPTR
		#define KOTEK_CPP_KEYWORD_CHAR_16_T
		#define KOTEK_CPP_KEYWORD_CHAR_8_T
	#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
	#ifdef KOTEK_MEMORY_LEAK_DETECTION
		#define KOTEK_USE_MEMORY_LEAK_DETECTION
		#define KOTEK_USE_MEMORY_LEAK_DETECTION_${KOTEK_CPP_MEMORY_LEAK_LIBRARY}
	#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
	#ifndef NDEBUG
		// for use in terms of all, we should provide for every preprocessor and 
		// the _USE_ form even if it doesn't required 
		// or if it will not be used in practice
		#define KOTEK_USE_DEBUG
	#endif
	")

	if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_CEF_LIBRARY
			#define KOTEK_USE_CEF_LIBRARY
		#endif
		")
	elseif("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "RMLUI")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_RMLUI_LIBRARY
			#define KOTEK_USE_RMLUI_LIBRARY
		#endif
		")
	endif()

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} 
	"
		#define KOTEK_USE_${KOTEK_UI_GAME_LIBRARY_NAME}_LIBRARY_NAME ${KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME}
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#ifdef KOTEK_NAMESPACE_KOTEK
			#define KOTEK_USE_NAMESPACE_KOTEK ${KOTEK_USE_NAMESPACE_KOTEK}
			#define kun_kotek ${KOTEK_USE_NAMESPACE_KOTEK}
			#define kn_kotek ${KOTEK_BEGIN_NAMESPACE_KOTEK}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_KOTEK ${KOTEK_USE_NAMESPACE_KOTEK}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_KOTEK ${KOTEK_BEGIN_NAMESPACE_KOTEK}
			#define KOTEK_BEGIN_NAMESPACE_KOTEK namespace ${KOTEK_BEGIN_NAMESPACE_KOTEK} {
			#define KOTEK_END_NAMESPACE_KOTEK ${KOTEK_END_NAMESPACE_KOTEK}
		#endif

		#ifdef KOTEK_NAMESPACE_CORE
			#define KOTEK_USE_NAMESPACE_CORE ${KOTEK_USE_NAMESPACE_CORE}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_core ${KOTEK_USE_NAMESPACE_CORE}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_core is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_core:: and in comparison kun_kotek kun_core
			/// Their equivalent is kotek::core::
			#define kn_core ${KOTEK_BEGIN_NAMESPACE_CORE}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_CORE ${KOTEK_USE_NAMESPACE_CORE}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_CORE ${KOTEK_BEGIN_NAMESPACE_CORE}
			#define KOTEK_BEGIN_NAMESPACE_CORE namespace ${KOTEK_BEGIN_NAMESPACE_CORE} {
			#define KOTEK_END_NAMESPACE_CORE ${KOTEK_END_NAMESPACE_CORE}
		#endif

		#ifdef KOTEK_NAMESPACE_KTK
			#define KOTEK_USE_NAMESPACE_KTK ${KOTEK_USE_NAMESPACE_KTK}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_ktk ${KOTEK_USE_NAMESPACE_KTK}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_ktk is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_ktk:: and in comparison kun_kotek kun_ktk
			/// Their equivalent is kotek::ktk::
			#define kn_ktk ${KOTEK_BEGIN_NAMESPACE_KTK}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_KTK ${KOTEK_USE_NAMESPACE_KTK}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_KTK ${KOTEK_BEGIN_NAMESPACE_KTK}
			#define KOTEK_BEGIN_NAMESPACE_KTK namespace ${KOTEK_BEGIN_NAMESPACE_KTK} {
			#define KOTEK_END_NAMESPACE_KTK ${KOTEK_END_NAMESPACE_KTK}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER
			#define KOTEK_USE_NAMESPACE_RENDER ${KOTEK_USE_NAMESPACE_RENDER}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render ${KOTEK_USE_NAMESPACE_RENDER}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render:: and in comparison kun_kotek kun_render
			/// Their equivalent is kotek::render::
			#define kn_render ${KOTEK_BEGIN_NAMESPACE_RENDER}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER ${KOTEK_USE_NAMESPACE_RENDER}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER ${KOTEK_BEGIN_NAMESPACE_RENDER}
			#define KOTEK_BEGIN_NAMESPACE_RENDER namespace ${KOTEK_BEGIN_NAMESPACE_RENDER} {
			#define KOTEK_END_NAMESPACE_RENDER ${KOTEK_END_NAMESPACE_RENDER}
		#endif

		#ifdef KOTEK_NAMESPACE_UI
			#define KOTEK_USE_NAMESPACE_UI ${KOTEK_USE_NAMESPACE_UI}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_ui ${KOTEK_USE_NAMESPACE_UI}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_ui is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_ui:: and in comparison kun_kotek kun_ui
			/// Their equivalent is kotek::ui::
			#define kn_ui ${KOTEK_BEGIN_NAMESPACE_UI}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_UI ${KOTEK_USE_NAMESPACE_UI}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_UI ${KOTEK_BEGIN_NAMESPACE_UI}
			#define KOTEK_BEGIN_NAMESPACE_UI namespace ${KOTEK_BEGIN_NAMESPACE_UI} {
			#define KOTEK_END_NAMESPACE_UI ${KOTEK_END_NAMESPACE_UI}
		#endif

		#ifdef KOTEK_NAMESPACE_MATH
			#define KOTEK_USE_NAMESPACE_MATH ${KOTEK_USE_NAMESPACE_MATH}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_math ${KOTEK_USE_NAMESPACE_MATH}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_math is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_core::kn_math:: and in comparison kun_kotek kun_core kun_math
			/// Their equivalent is kotek::core::math::
			#define kn_math ${KOTEK_BEGIN_NAMESPACE_MATH}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_MATH ${KOTEK_USE_NAMESPACE_MATH}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_MATH ${KOTEK_BEGIN_NAMESPACE_MATH}
			#define KOTEK_BEGIN_NAMESPACE_MATH namespace ${KOTEK_BEGIN_NAMESPACE_MATH} {
			#define KOTEK_END_NAMESPACE_MATH ${KOTEK_END_NAMESPACE_MATH}
		#endif

		#ifdef KOTEK_NAMESPACE_GAME
			#define KOTEK_USE_NAMESPACE_GAME ${KOTEK_USE_NAMESPACE_GAME}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_game ${KOTEK_USE_NAMESPACE_GAME}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_game is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_game:: and in comparison kun_kotek kun_game
			/// Their equivalent is kotek::game::
			#define kn_game ${KOTEK_BEGIN_NAMESPACE_GAME}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_GAME ${KOTEK_USE_NAMESPACE_GAME}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_GAME ${KOTEK_BEGIN_NAMESPACE_GAME}
			#define KOTEK_BEGIN_NAMESPACE_GAME namespace ${KOTEK_BEGIN_NAMESPACE_GAME} {
			#define KOTEK_END_NAMESPACE_GAME ${KOTEK_END_NAMESPACE_GAME}
		#endif

		#ifdef KOTEK_NAMESPACE_ECS
			#define KOTEK_USE_NAMESPACE_ECS ${KOTEK_USE_NAMESPACE_ECS}
			#define KOTEK_BEGIN_NAMESPACE_ECS namespace ${KOTEK_BEGIN_NAMESPACE_ECS} {
			#define KOTEK_END_NAMESPACE_ECS ${KOTEK_END_NAMESPACE_ECS}
		#endif

		#ifdef KOTEK_NAMESPACE_ECS_FRONTEND
			#define KOTEK_USE_NAMESPACE_ECS_FRONTEND ${KOTEK_USE_NAMESPACE_ECS_FRONTEND}
			#define KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND namespace ${KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND} {
			#define KOTEK_END_NAMESPACE_ECS_FRONTEND ${KOTEK_END_NAMESPACE_ECS_FRONTEND}
		#endif

		#ifdef KOTEK_NAMESPACE_ECS_BACKEND
			#define KOTEK_USE_NAMESPACE_ECS_BACKEND ${KOTEK_USE_NAMESPACE_ECS_BACKEND}
			#define KOTEK_BEGIN_NAMESPACE_ECS_BACKEND namespace ${KOTEK_BEGIN_NAMESPACE_ECS_BACKEND} {
			#define KOTEK_END_NAMESPACE_ECS_BACKEND ${KOTEK_END_NAMESPACE_ECS_BACKEND}
		#endif

		#ifdef KOTEK_NAMESPACE_FILESYSTEM
			#define kun_filesystem ${KOTEK_USE_NAMESPACE_FILESYSTEM}
			#define kbn_filesystem namespace ${KOTEK_BEGIN_NAMESPACE_FILESYSTEM} {
			#define ken_filesystem ${KOTEK_END_NAMESPACE_FILESYSTEM}
			#define kn_filesystem ${KOTEK_BEGIN_NAMESPACE_FILESYSTEM}
			
			#define KUN_FILESYSTEM ${KOTEK_USE_NAMESPACE_FILESYSTEM}
			#define KBN_FILESYSTEM namespace ${KOTEK_BEGIN_NAMESPACE_FILESYSTEM} {
			#define KEN_FILESYSTEM ${KOTEK_END_NAMESPACE_FILESYSTEM}
			#define KN_FILESYSTEM ${KOTEK_BEGIN_NAMESPACE_FILESYSTEM}
			
			#define KOTEK_USE_NAMESPACE_FILESYSTEM ${KOTEK_USE_NAMESPACE_FILESYSTEM}
			#define KOTEK_BEGIN_NAMESPACE_FILESYSTEM namespace ${KOTEK_BEGIN_NAMESPACE_FILESYSTEM} {
			#define KOTEK_END_NAMESPACE_FILESYSTEM ${KOTEK_END_NAMESPACE_FILESYSTEM}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_GL
			#define KOTEK_USE_NAMESPACE_RENDER_GL ${KOTEK_USE_NAMESPACE_RENDER_GL}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render_gl ${KOTEK_USE_NAMESPACE_RENDER_GL}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render_gl is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render::kn_render_gl:: and in comparison kun_kotek kun_render kun_render_gl
			/// Their equivalent is kotek::render::gl::
			#define kn_render_gl ${KOTEK_BEGIN_NAMESPACE_RENDER_GL}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER_GL ${KOTEK_USE_NAMESPACE_RENDER_GL}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER_GL ${KOTEK_BEGIN_NAMESPACE_RENDER_GL}
			#define KOTEK_BEGIN_NAMESPACE_RENDER_GL namespace ${KOTEK_BEGIN_NAMESPACE_RENDER_GL} {
			#define KOTEK_END_NAMESPACE_RENDER_GL ${KOTEK_END_NAMESPACE_RENDER_GL}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_VK
			#define KOTEK_USE_NAMESPACE_RENDER_VK ${KOTEK_USE_NAMESPACE_RENDER_VK}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render_vk ${KOTEK_USE_NAMESPACE_RENDER_VK}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render_vk is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render::kn_render_vk:: and in comparison kun_kotek kun_render kun_render_vk
			/// Their equivalent is kotek::render::vk::
			#define kn_render_vk ${KOTEK_BEGIN_NAMESPACE_RENDER_VK}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER_VK ${KOTEK_USE_NAMESPACE_RENDER_VK}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER_VK ${KOTEK_BEGIN_NAMESPACE_RENDER_VK}
			#define KOTEK_BEGIN_NAMESPACE_RENDER_VK namespace ${KOTEK_BEGIN_NAMESPACE_RENDER_VK} {
			#define KOTEK_END_NAMESPACE_RENDER_VK ${KOTEK_END_NAMESPACE_RENDER_VK}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_DX
			#define KOTEK_USE_NAMESPACE_RENDER_DX ${KOTEK_USE_NAMESPACE_RENDER_DX}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render_dx ${KOTEK_USE_NAMESPACE_RENDER_DX}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render_dx is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render::kn_render_dx:: and in comparison kun_kotek kun_render kun_render_dx
			/// Their equivalent is kotek::render::dx::
			#define kn_render_dx ${KOTEK_BEGIN_NAMESPACE_RENDER_DX}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER_DX ${KOTEK_USE_NAMESPACE_RENDER_DX}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER_DX ${KOTEK_BEGIN_NAMESPACE_RENDER_DX}
			#define KOTEK_BEGIN_NAMESPACE_RENDER_DX namespace ${KOTEK_BEGIN_NAMESPACE_RENDER_DX} {
			#define KOTEK_END_NAMESPACE_RENDER_DX ${KOTEK_END_NAMESPACE_RENDER_DX}
		#endif

		#ifdef KOTEK_NAMESPACE_SOUND
			#define KOTEK_USE_NAMESPACE_SOUND ${KOTEK_USE_NAMESPACE_SOUND}
			/// \~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_sound ${KOTEK_USE_NAMESPACE_SOUND}
			/// \~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_sound is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_sound:: and in comparison kun_kotek kun_sound
			/// Their equivalent is kotek::sound::
			#define kn_sound ${KOTEK_BEGIN_NAMESPACE_SOUND}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_SOUND ${KOTEK_USE_NAMESPACE_SOUND}
			/// \~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_SOUND ${KOTEK_BEGIN_NAMESPACE_SOUND}
			#define KOTEK_BEGIN_NAMESPACE_SOUND namespace ${KOTEK_BEGIN_NAMESPACE_SOUND} {
			#define KOTEK_END_NAMESPACE_SOUND ${KOTEK_END_NAMESPACE_SOUND}
		#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} 
	"
		#ifdef KOTEK_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE}
			#define KOTEK_USE_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE}
		#endif
	")

	if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} 
		"
			#define KOTEK_USER_GAME_MODULE_HEADER_FILE ${KOTEK_GAME_MODULE_FUNCTIONS_FILE}
			#define KOTEK_USER_FUNCTION_INITIALIZE_MODULE_GAME ${KOTEK_USER_FUNCTION_IMG}
			#define KOTEK_USER_FUNCTION_SHUTDOWN_MODULE_GAME ${KOTEK_USER_FUNCTION_SMG}
			#define KOTEK_USER_FUNCTION_UPDATE_MODULE_GAME ${KOTEK_USER_FUNCTION_UMG}
			#define KOTEK_USER_FUNCTION_INITIALIZE_MODULE_RENDER ${KOTEK_USER_FUNCTION_IMR}
		")
	endif()

	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC")
		else()
		endif()
	endif()

	if (NOT "${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "OFF")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_MEMORY_ALLOCATOR_CPU_${KOTEK_MEMORY_ALLOCATOR_CPU}
		")
        else()
            file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
                "
                    #define KOTEK_USE_MEMORY_ALLOCATOR_CPU_STD
                ")
        endif()

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#define KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME \"${KOTEK_GAME_OUTPUT_LIBRARY_NAME}\"
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#ifdef KOTEK_RENDER_OPENGL
			#define KOTEK_USE_RENDER_OPENGL
		#endif

		#ifdef KOTEK_RENDER_VULKAN
			#define KOTEK_USE_RENDER_VULKAN
		#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} 
	"
		#ifdef KOTEK_SDK_IMGUI
			#define KOTEK_USE_SDK_IMGUI
			#define KOTEK_USE_UI_IMGUI_LIBRARY_IMGUI
		#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} 
	"
		#define KOTEK_USE_USER_DATA_CONFIG_NAME \"${KOTEK_USER_DATA_CONFIG_NAME}\"
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#define KOTEK_USE_STARTUP_RENDERER kEngine_Render_Renderer_${KOTEK_STARTUP_RENDERER}
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#define KOTEK_USE_STARTUP_RENDERER_VERSION k${KOTEK_STARTUP_RENDERER_VERSION}
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#define KOTEK_USE_LOG_OUTPUT_FILE_NAME \"${KOTEK_LOG_OUTPUT_FILE_NAME}\"
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
	"
		#define KOTEK_USE_STRING_CONFIGURATION_${KOTEK_STRING_CONFIGURATION}
	")

	if ("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "1")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE char
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER ${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}
		")
	elseif("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "8")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE char${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}_t
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER ${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}
		")
	elseif("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "16")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE char${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}_t
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER ${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}
		")
	elseif("${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}" STREQUAL "32")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE char${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}_t
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER ${KOTEK_STRING_CONFIGURATION_CHAR_TYPE}
		")
	endif()

	if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
		")
	endif()

	if("${KOTEK_LIBRARY_TYPE}" STREQUAL "DYN")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_LIBRARY_TYPE_DYNAMIC
		")
	elseif("${KOTEK_LIBRARY_TYPE}" STREQUAL "EMB")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
			#define KOTEK_USE_LIBRARY_TYPE_EMB

			// definitions for determining the size of containers
			// they are described with KOTEK_DEF_ prefix
			#define KOTEK_DEF_FALLBACK_RENDERERS_COUNT ${KOTEK_DEF_FALLBACK_RENDERERS_COUNT}
			#define KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT ${KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT}
			#define KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT ${KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT}
			#define KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT ${KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT}
			#define KOTEK_DEF_TEXT_RESOURCE_LOADERS_COUNT ${KOTEK_DEF_TEXT_RESOURCE_LOADERS_COUNT}
			#define KOTEK_DEF_JSON_RESOURCE_LOADERS_COUNT ${KOTEK_DEF_JSON_RESOURCE_LOADERS_COUNT}
			#define KOTEK_DEF_TEXT_RESOURCE_SAVERS_COUNT ${KOTEK_DEF_TEXT_RESOURCE_SAVERS_COUNT}
			#define KOTEK_DEF_JSON_RESOURCE_SAVERS_COUNT ${KOTEK_DEF_JSON_RESOURCE_SAVERS_COUNT}
			#define KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT ${KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT}
			#define KOTEK_RESOURCE_SAVER_MANAGER_FILE_POOL_COUNT ${KOTEK_RESOURCE_SAVER_MANAGER_FILE_POOL_COUNT}
			#define KOTEK_DEF_RESOURCE_SAVERS_TYPE_MAX_COUNT ${KOTEK_DEF_RESOURCE_SAVERS_TYPE_MAX_COUNT}
			#define KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL ${KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL}
		")
	endif()

	if ("${KOTEK_LOG_LIBRARY}" STREQUAL "" OR "${KOTEK_LOG_LIBRARY}" STREQUAL "SPDLOG")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
				#define KOTEK_USE_LOG_LIBRARY_SPDLOG
		")
	elseif ("${KOTEK_LOG_LIBRARY}" STREQUAL "BOOST")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
				#define KOTEK_USE_LOG_LIBRARY_BOOST
		")
	elseif ("${KOTEK_LOG_LIBRARY}" STREQUAL "CUSTOM")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}
		"
				#define KOTEK_USE_LOG_LIBRARY_CUSTOM
		")
	endif()

else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_cpp.h"
	"src/main_core_defines_static_cpp_dll.cpp")

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
	# TODO: we need to use CEF as package
	if (WIN32)
		# There's no package so we need to use our pre-compiled solution
		if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
			message("[${PROJECT_NAME}]: CEF is found!")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PATH_TO_CEF})
			target_link_directories(${PROJECT_NAME} PUBLIC ${PATH_TO_CEF_LIB})
		else()
			message(FATAL_ERROR "can't find dependency folder of pre-compiled CEF (Chromium Embeddeed Framework). Disable this project in order to compile the solution.")
		endif()
	endif()
endif()
