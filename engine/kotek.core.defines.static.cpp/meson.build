project('kotek.core.defines.static.cpp', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_STD_LIBRARY}', 'STREQUAL', ''
  kotek_std_library = ['BOOST', 'CACHE', 'INTERNAL', '']
endif
if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', ''
  # By default we use RmlUI util I will finish my library
  # TODO: add CEF only when we have it in vcpkg or any other package managers
  kotek_ui_game_library = ['RMLUI', 'CACHE', 'INTERNAL', '']
endif
if '${KOTEK_GAME_OUTPUT_LIBRARY_NAME}', 'STREQUAL', ''
  kotek_game_output_library_name = ['game.ktk', 'CACHE', 'INTERNAL', '']
endif
# message('[${PROJECT_NAME}]: KOTEK_STD_LIBRARY=${KOTEK_STD_LIBRARY}')
if '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'BOOST'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_BOOST_LIBRARY'])
  kotek_std_library_name = 'Boost'
elif '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'STD'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_STD_LIBRARY'])
  kotek_std_library_name = 'Standard library'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_CUSTOM_STD_LIBRARY'])
  kotek_std_library_name = kotek_std_library
endif
if '${KOTEK_SDK_IMGUI}', 'STREQUAL', ''
  kotek_sdk_imgui = ['IMGUI', 'CACHE', 'INTERNAL', '']
  kotek_ui_imgui_library_imgui = ['', 'CACHE', 'INTERNAL', '']
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_SDK_IMGUI'])
endif
# By default we for to use CEF
if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_CEF_LIBRARY'])
  # For internal (cmake) purposes
  kotek_ui_game_library_name = 'CEF'
  # For C++ code generation
  kotek_ui_game_library_description_name = 'Chromium Embedded Framework'
elif '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'RMLUI'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_RMLUI_LIBRARY'])
  kotek_ui_game_library_name = 'RMLUI'
  kotek_ui_game_library_description_name = 'RmlUi'
elif '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'ATHENA'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_ATHENA_LIBRARY'])
  kotek_ui_game_library_name = 'ATHENA'
  kotek_ui_game_library_description_name = 'Athena'
else
  # message('[${PROJECT_NAME}] you didn't specify any ui library for this generation')
endif
if '${KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_HIDE_DISABLE_WARNINGS_PREPROCESSOR'])
endif
if '${KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR'])
endif
if '${KOTEK_CPP_KEYWORD_NOEXCEPT}', 'STREQUAL', ''
  kotek_cpp_keyword_noexcept = 'noexcept'
endif
if '${KOTEK_CPP_KEYWORD_INLINE}', 'STREQUAL', ''
  kotek_cpp_keyword_inline = 'inline'
endif
if '${KOTEK_CPP_KEYWORD_CONSTEXPR}', 'STREQUAL', ''
  kotek_cpp_keyword_constexpr = 'constexpr'
endif
if '${CMAKE_BUILD_TYPE}', 'STREQUAL', 'Debug'
  if '${KOTEK_MEMORY_LEAK_DETECTION}', 'STREQUAL', ''
    kotek_memory_leak_detection = ['ON', 'CACHE', 'INTERNAL', '']
  endif
endif
if '${KOTEK_MEMORY_LEAK_DETECTION}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_MEMORY_LEAK_DETECTION'])
endif
if '${KOTEK_CPP_MEMORY_LEAK_LIBRARY}', 'STREQUAL', ''
  if 'WIN32'
    kotek_cpp_memory_leak_library = ['VLD', 'CACHE', 'INTERNAL', '']
  endif
endif
if '${KOTEK_MEMORY_ALLOCATOR_CPU}', 'STREQUAL', ''
  kotek_memory_allocator_cpu = ['MIMALLOC', 'CACHE', 'INTERNAL', '']
endif
### Namespaces
if '${KOTEK_NAMESPACE_KOTEK}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_KOTEK}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_KOTEK}', 'STREQUAL', ''
    kotek_use_namespace_kotek = 'Kotek::'
    kotek_begin_namespace_kotek = 'Kotek'
  else
    kotek_use_namespace_kotek = '${KOTEK_BEGIN_NAMESPACE_KOTEK}::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_KOTEK'])
  kotek_end_namespace_kotek = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_KOTEK'])
  kotek_use_namespace_kotek = ''
  kotek_begin_namespace_kotek = ''
  kotek_end_namespace_kotek = ''
endif
if '${KOTEK_NAMESPACE_CORE}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_CORE}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_CORE}', 'STREQUAL', ''
    kotek_use_namespace_core = 'Core::'
    kotek_begin_namespace_core = 'Core'
  else
    kotek_use_namespace_core = '${KOTEK_BEGIN_NAMESPACE_CORE}::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_CORE'])
  kotek_end_namespace_core = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_CORE'])
  kotek_use_namespace_core = ''
  kotek_begin_namespace_core = ''
  kotek_end_namespace_core = ''
endif
if '${KOTEK_NAMESPACE_KTK}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_KTK}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_KTK}', 'STREQUAL', ''
    kotek_begin_namespace_ktk = 'ktk'
    kotek_use_namespace_ktk = 'ktk::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_KTK'])
  kotek_end_namespace_ktk = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_KTK'])
  kotek_use_namespace_ktk = ''
  kotek_begin_namespace_ktk = ''
  kotek_end_namespace_ktk = ''
endif
if '${KOTEK_NAMESPACE_RENDER}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_RENDER}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_RENDER}', 'STREQUAL', ''
    kotek_begin_namespace_render = 'Render'
    kotek_use_namespace_render = 'Render::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER'])
  kotek_end_namespace_render = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER'])
  kotek_use_namespace_render = ''
  kotek_begin_namespace_render = ''
  kotek_end_namespace_render = ''
endif
if '${KOTEK_NAMESPACE_UI}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_UI}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_UI}', 'STREQUAL', ''
    kotek_begin_namespace_ui = 'UI'
    kotek_use_namespace_ui = 'UI::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_UI'])
  kotek_end_namespace_ui = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_UI'])
  kotek_use_namespace_ui = ''
  kotek_begin_namespace_ui = ''
  kotek_end_namespace_ui = ''
endif
if '${KOTEK_NAMESPACE_MATH}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_MATH}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_MATH}', 'STREQUAL', ''
    kotek_begin_namespace_math = 'math'
    kotek_use_namespace_math = 'math::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_MATH'])
  kotek_end_namespace_math = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_MATH'])
  kotek_use_namespace_math = ''
  kotek_begin_namespace_math = ''
  kotek_end_namespace_math = ''
endif
if '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', ''
  kotek_development_type = ['SHARED', 'CACHE', 'INTERNAL', '']
endif
if '${KOTEK_NAMESPACE_GAME}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_GAME}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_GAME}', 'STREQUAL', ''
    kotek_begin_namespace_game = 'Game'
    kotek_use_namespace_game = 'Game::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_GAME'])
  kotek_end_namespace_game = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_GAME'])
  kotek_use_namespace_game = ''
  kotek_begin_namespace_game = ''
  kotek_end_namespace_game = ''
endif
if '${KOTEK_NAMESPACE_ECS}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_ECS}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_ECS}', 'STREQUAL', ''
    kotek_begin_namespace_ecs = 'ecs'
    kotek_use_namespace_ecs = 'ecs::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_ECS'])
  kotek_end_namespace_ecs = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_ECS'])
  kotek_use_namespace_ecs = ''
  kotek_begin_namespace_ecs = ''
  kotek_end_namespace_ecs = ''
endif
if '${KOTEK_NAMESPACE_ECS_FRONTEND}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_ECS_FRONTEND}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND}', 'STREQUAL', ''
    kotek_begin_namespace_ecs_frontend = 'frontend'
    kotek_use_namespace_ecs_frontend = 'frontend::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_ECS_FRONTEND'])
  kotek_end_namespace_ecs_frontend = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_ECS_FRONTEND'])
  kotek_use_namespace_ecs_frontend = ''
  kotek_begin_namespace_ecs_frontend = ''
  kotek_end_namespace_ecs_frontend = ''
endif
if '${KOTEK_NAMESPACE_ECS_BACKEND}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_ECS_BACKEND}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_ECS_BACKEND}', 'STREQUAL', ''
    kotek_begin_namespace_ecs_backend = 'backend'
    kotek_use_namespace_ecs_backend = 'backend::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_ECS_BACKEND'])
  kotek_end_namespace_ecs_backend = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_ECS_BACKEND'])
  kotek_use_namespace_ecs_backend = ''
  kotek_begin_namespace_ecs_backend = ''
  kotek_end_namespace_ecs_backend = ''
endif
if '${KOTEK_NAMESPACE_RENDER_GL}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_RENDER_GL}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_RENDER_GL}', 'STREQUAL', ''
    kotek_begin_namespace_render_gl = 'gl'
    kotek_use_namespace_render_gl = 'gl::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER_GL'])
  kotek_end_namespace_render_gl = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER_GL'])
  kotek_use_namespace_render_gl = ''
  kotek_begin_namespace_render_gl = ''
  kotek_end_namespace_render_gl = ''
endif
if '${KOTEK_NAMESPACE_RENDER_VK}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_RENDER_VK}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_RENDER_VK}', 'STREQUAL', ''
    kotek_begin_namespace_render_vk = 'vk'
    kotek_use_namespace_render_vk = 'vk::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER_VK'])
  kotek_end_namespace_render_vk = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER_VK'])
  kotek_use_namespace_render_vk = ''
  kotek_begin_namespace_render_vk = ''
  kotek_end_namespace_render_vk = ''
endif
if '${KOTEK_NAMESPACE_RENDER_DX}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_RENDER_DX}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_RENDER_DX}', 'STREQUAL', ''
    kotek_begin_namespace_render_dx = 'dx'
    kotek_use_namespace_render_dx = 'dx::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER_DX'])
  kotek_end_namespace_render_dx = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_RENDER_DX'])
  kotek_use_namespace_render_dx = ''
  kotek_begin_namespace_render_dx = ''
  kotek_end_namespace_render_dx = ''
endif
if '${KOTEK_NAMESPACE_SOUND}', 'STREQUAL', '', 'OR', '${KOTEK_NAMESPACE_SOUND}', 'STREQUAL', 'ON'
  if '${KOTEK_BEGIN_NAMESPACE_SOUND}', 'STREQUAL', ''
    kotek_begin_namespace_sound = 'Sound'
    kotek_use_namespace_sound = 'Sound::'
  endif
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_SOUND'])
  kotek_end_namespace_sound = '}'
else
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_NAMESPACE_SOUND'])
  kotek_use_namespace_sound = ''
  kotek_begin_namespace_sound = ''
  kotek_end_namespace_sound = ''
endif
### Namespaces
### Renderers
if '${KOTEK_RENDER_OPENGL}', 'STREQUAL', ''
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_RENDER_OPENGL'])
endif
# TODO: change as OpenGL, because Vulkan is not updated
if '${KOTEK_RENDER_VULKAN}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_RENDER_VULKAN'])
endif
### Renderers
# TODO: add HYBRID it is a current SHARED, but SHARED is when ALL libraries are dll
if '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', 'SHARED'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE}'])
  kotek_development_type_packages = ['SHARED', 'CACHE', 'INTERNAL', '']
elif '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', 'STATIC'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE}'])
  kotek_development_type_packages = ['STATIC', 'CACHE', 'INTERNAL', '']
  if '${KOTEK_GAME_MODULE_FUNCTIONS_FILE}', 'STREQUAL', ''
    # message(['FATAL_ERROR', 'you must specify KOTEK_GAME_MODULE_FUNCTIONS_FILE by writting <path/to/your_file_where_standard_functions_for_running_module_are_defined.h>. But you make a path from root of your folder see sandbox example https://gitlab.com/wh1t3lord/sandbox'])
  endif
  if '${KOTEK_USER_FUNCTION_IMG}', 'STREQUAL', ''
    kotek_user_function_img = 'InitializeModule_Game'
  endif
  if '${KOTEK_USER_FUNCTION_SMG}', 'STREQUAL', ''
    kotek_user_function_smg = 'ShutdownModule_Game'
  endif
  if '${KOTEK_USER_FUNCTION_UMG}', 'STREQUAL', ''
    kotek_user_function_umg = 'UpdateModule_Game'
  endif
  if '${KOTEK_USER_FUNCTION_IMR}', 'STREQUAL', ''
    kotek_user_function_imr = 'InitializeModule_Render'
  endif
else
  # message(['FATAL_ERROR', 'you must specify KOTEK_DEVELOPMENT_TYPE as SHARED or STATIC...'])
endif
# message('[${PROJECT_NAME}]: standard library is ${KOTEK_STD_LIBRARY_NAME}')
### Generating code
if 'NOT', '${CMAKE_BUILD_TYPE}', 'STREQUAL', ''
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_BUILD_TYPE'])
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_BUILD_TYPE 
		#define KOTEK_USE_CURRENT_BUILD_TYPE ${CMAKE_BUILD_TYPE} 
		#endif'])
  if '${CMAKE_BUILD_TYPE}', 'STREQUAL', 'Debug'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_BUILD_TYPE 
			#define KOTEK_USE_BUILD_TYPE_DEBUG 
			#endif'])
  endif
  if '${CMAKE_BUILD_TYPE}', 'STREQUAL', 'Release'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_BUILD_TYPE 
			#define KOTEK_USE_BUILD_TYPE_RELEASE 
			#endif'])
  endif
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_BOOST_LIBRARY
			#define KOTEK_USE_BOOST_LIBRARY
		#endif

		#ifdef KOTEK_STD_LIBRARY
			#define KOTEK_USE_STD_LIBRARY
		#endif

		#define KOTEK_USE_STD_LIBRARY_NAME ${KOTEK_STD_LIBRARY_NAME}

		#if defined(KOTEK_USE_BOOST_LIBRARY) || defined(KOTEK_USE_STD_LIBRARY)
			#define KOTEK_USE_NOT_CUSTOM_LIBRARY
		#elif defined(KOTEK_CUSTOM_STD_LIBRARY)
			#define KOTEK_USE_CUSTOM_LIBRARY
		#endif'])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '
	#ifndef KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR
		#define KOTEK_CPP_KEYWORD_CONSTEXPR ${KOTEK_CPP_KEYWORD_CONSTEXPR}
		#define KOTEK_CPP_KEYWORD_INLINE ${KOTEK_CPP_KEYWORD_INLINE}
		#define KOTEK_CPP_KEYWORD_NOEXCEPT ${KOTEK_CPP_KEYWORD_NOEXCEPT} 
	#else
		#define KOTEK_CPP_KEYWORD_CONSTEXPR
		#define KOTEK_CPP_KEYWORD_INLINE
		#define KOTEK_CPP_KEYWORD_NOEXCEPT
	#endif'])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '
	#ifdef KOTEK_MEMORY_LEAK_DETECTION
		#define KOTEK_USE_MEMORY_LEAK_DETECTION
		#define KOTEK_USE_MEMORY_LEAK_DETECTION_${KOTEK_CPP_MEMORY_LEAK_LIBRARY}
	#endif'])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '
	#ifndef NDEBUG
		#define KOTEK_USE_DEBUG
	#endif'])
  if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_CEF_LIBRARY
			#define KOTEK_USE_CEF_LIBRARY
		#endif'])
  elif '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'RMLUI'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_RMLUI_LIBRARY
			#define KOTEK_USE_RMLUI_LIBRARY
		#endif'])
  endif
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define KOTEK_USE_${KOTEK_UI_GAME_LIBRARY_NAME}_LIBRARY_NAME ${KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME}'])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_NAMESPACE_KOTEK
			#define KOTEK_USE_NAMESPACE_KOTEK ${KOTEK_USE_NAMESPACE_KOTEK}
			#define KOTEK_BEGIN_NAMESPACE_KOTEK namespace ${KOTEK_BEGIN_NAMESPACE_KOTEK} {
			#define KOTEK_END_NAMESPACE_KOTEK ${KOTEK_END_NAMESPACE_KOTEK}
		#endif

		#ifdef KOTEK_NAMESPACE_CORE
			#define KOTEK_USE_NAMESPACE_CORE ${KOTEK_USE_NAMESPACE_CORE}
			#define KOTEK_BEGIN_NAMESPACE_CORE namespace ${KOTEK_BEGIN_NAMESPACE_CORE} {
			#define KOTEK_END_NAMESPACE_CORE ${KOTEK_END_NAMESPACE_CORE}
		#endif

		#ifdef KOTEK_NAMESPACE_KTK
			#define KOTEK_USE_NAMESPACE_KTK ${KOTEK_USE_NAMESPACE_KTK}
			#define KOTEK_BEGIN_NAMESPACE_KTK namespace ${KOTEK_BEGIN_NAMESPACE_KTK} {
			#define KOTEK_END_NAMESPACE_KTK ${KOTEK_END_NAMESPACE_KTK}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER
			#define KOTEK_USE_NAMESPACE_RENDER ${KOTEK_USE_NAMESPACE_RENDER}
			#define KOTEK_BEGIN_NAMESPACE_RENDER namespace ${KOTEK_BEGIN_NAMESPACE_RENDER} {
			#define KOTEK_END_NAMESPACE_RENDER ${KOTEK_END_NAMESPACE_RENDER}
		#endif

		#ifdef KOTEK_NAMESPACE_UI
			#define KOTEK_USE_NAMESPACE_UI ${KOTEK_USE_NAMESPACE_UI}
			#define KOTEK_BEGIN_NAMESPACE_UI namespace ${KOTEK_BEGIN_NAMESPACE_UI} {
			#define KOTEK_END_NAMESPACE_UI ${KOTEK_END_NAMESPACE_UI}
		#endif

		#ifdef KOTEK_NAMESPACE_MATH
			#define KOTEK_USE_NAMESPACE_MATH ${KOTEK_USE_NAMESPACE_MATH}
			#define KOTEK_BEGIN_NAMESPACE_MATH namespace ${KOTEK_BEGIN_NAMESPACE_MATH} {
			#define KOTEK_END_NAMESPACE_MATH ${KOTEK_END_NAMESPACE_MATH}
		#endif

		#ifdef KOTEK_NAMESPACE_GAME
			#define KOTEK_USE_NAMESPACE_GAME ${KOTEK_USE_NAMESPACE_GAME}
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

		#ifdef KOTEK_NAMESPACE_RENDER_GL
			#define KOTEK_USE_NAMESPACE_RENDER_GL ${KOTEK_USE_NAMESPACE_RENDER_GL}
			#define KOTEK_BEGIN_NAMESPACE_RENDER_GL namespace ${KOTEK_BEGIN_NAMESPACE_RENDER_GL} {
			#define KOTEK_END_NAMESPACE_RENDER_GL ${KOTEK_END_NAMESPACE_RENDER_GL}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_VK
			#define KOTEK_USE_NAMESPACE_RENDER_VK ${KOTEK_USE_NAMESPACE_RENDER_VK}
			#define KOTEK_BEGIN_NAMESPACE_RENDER_VK namespace ${KOTEK_BEGIN_NAMESPACE_RENDER_VK} {
			#define KOTEK_END_NAMESPACE_RENDER_VK ${KOTEK_END_NAMESPACE_RENDER_VK}
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_DX
			#define KOTEK_USE_NAMESPACE_RENDER_DX ${KOTEK_USE_NAMESPACE_RENDER_DX}
			#define KOTEK_BEGIN_NAMESPACE_RENDER_DX namespace ${KOTEK_BEGIN_NAMESPACE_RENDER_DX} {
			#define KOTEK_END_NAMESPACE_RENDER_DX ${KOTEK_END_NAMESPACE_RENDER_DX}
		#endif

		#ifdef KOTEK_NAMESPACE_SOUND
			#define KOTEK_USE_NAMESPACE_SOUND ${KOTEK_USE_NAMESPACE_SOUND}
			#define KOTEK_BEGIN_NAMESPACE_SOUND namespace ${KOTEK_BEGIN_NAMESPACE_SOUND} {
			#define KOTEK_END_NAMESPACE_SOUND ${KOTEK_END_NAMESPACE_SOUND}
		#endif'])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE}
			#define KOTEK_USE_DEVELOPMENT_TYPE_${KOTEK_DEVELOPMENT_TYPE}
		#endif'])
  if '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', 'STATIC'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define KOTEK_USER_GAME_MODULE_HEADER_FILE ${KOTEK_GAME_MODULE_FUNCTIONS_FILE}
			#define KOTEK_USER_FUNCTION_INITIALIZE_MODULE_GAME ${KOTEK_USER_FUNCTION_IMG}
			#define KOTEK_USER_FUNCTION_SHUTDOWN_MODULE_GAME ${KOTEK_USER_FUNCTION_SMG}
			#define KOTEK_USER_FUNCTION_UPDATE_MODULE_GAME ${KOTEK_USER_FUNCTION_UMG}
			#define KOTEK_USER_FUNCTION_INITIALIZE_MODULE_RENDER ${KOTEK_USER_FUNCTION_IMR}'])
  endif
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define BOOST_USE_WINAPI_VERSION BOOST_WINAPI_VERSION_WIN7'])
    if '${KOTEK_DEVELOPMENT_TYPE_PACKAGES}', 'STREQUAL', 'STATIC'
    else
      # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define BOOST_TEST_NO_MAIN'])
    endif
  endif
  if 'NOT', '${KOTEK_MEMORY_ALLOCATOR_CPU}', 'STREQUAL', 'OFF'
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define KOTEK_USE_MEMORY_ALLOCATOR_CPU_${KOTEK_MEMORY_ALLOCATOR_CPU}'])
  else
    # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define KOTEK_USE_MEMORY_ALLOCATOR_CPU_STD'])
  endif
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#define KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME ', kotek_game_output_library_name, ''])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_RENDER_OPENGL
			#define KOTEK_USE_RENDER_OPENGL
		#endif

		#ifdef KOTEK_RENDER_VULKAN
			#define KOTEK_USE_RENDER_VULKAN
		#endif'])
  # file(['APPEND', kotek_filename_for_generating_preprocessors, '#ifdef KOTEK_SDK_IMGUI
			#define KOTEK_USE_SDK_IMGUI
			#define KOTEK_USE_UI_IMGUI_LIBRARY_IMGUI
		#endif'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_cpp.h', 'src/main_core_defines_static_cpp_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
  # TODO: we need to use CEF as package
  if 'WIN32'
    # There's no package so we need to use our pre-compiled solution
    if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
      # message('[Engine]: CEF is found!')
      # target_include_directories([project_name, 'PUBLIC', path_to_cef])
      # target_link_directories([project_name, 'PUBLIC', path_to_cef_lib])
    else
      # message(['FATAL_ERROR', 'can't find dependency folder of pre-compiled CEF (Chromium Embeddeed Framework). Disable this project in order to compile the solution.'])
    endif
  endif
endif
