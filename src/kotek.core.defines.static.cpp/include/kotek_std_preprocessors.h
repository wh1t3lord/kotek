#pragma once
	#ifdef KOTEK_BUILD_TYPE 
		#define KOTEK_USE_CURRENT_BUILD_TYPE Debug 
	#endif
		#ifdef KOTEK_BUILD_TYPE 
			#define KOTEK_USE_BUILD_TYPE_DEBUG 
		#endif
		#ifdef KOTEK_BOOST_LIBRARY
			#define KOTEK_USE_BOOST_LIBRARY
		#endif

		#ifdef KOTEK_STD_LIBRARY
			#define KOTEK_USE_STD_LIBRARY
		#endif

		#define KOTEK_USE_STD_LIBRARY_NAME Boost

		#if defined(KOTEK_USE_BOOST_LIBRARY) || defined(KOTEK_USE_STD_LIBRARY)
			// use this when we have std implementation like std::any, so we dont need to use it from boost
			#define KOTEK_USE_NOT_CUSTOM_LIBRARY
		#elif defined(KOTEK_CUSTOM_STD_LIBRARY)
			#define KOTEK_USE_CUSTOM_LIBRARY
		#endif
	
#ifndef KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR
	#ifdef _WIN32
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma("warning(push,0)")
	#elif defined(__clang__)
		#define DIAGNOSTIC_HELPER0(x) #x
		#define DIAGNOSTIC_HELPER1(kind, y) DIAGNOSTIC_HELPER0(clang diagnostic kind #y)

		#define PRGM_CLANG(kind, warning) 			_Pragma(DIAGNOSTIC_HELPER1(kind, warning))

		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma("clang diagnostic push") PRGM_CLANG(ignored, -Wall) PRGM_CLANG(ignored, -Wextra)
	#elif defined(__GNUC__)
		#define DIAGNOSTIC_HELPER0(x) #x
		#define DIAGNOSTIC_HELPER1(kind, y) DIAGNOSTIC_HELPER0(GCC diagnostic kind #y)

		#define PRGM_GCC(kind, warning) 			_Pragma(DIAGNOSTIC_HELPER1(kind, warning))

                #define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma("GCC diagnostic push") PRGM_GCC(ignored, -Wimplicit-fallthrough) PRGM_GCC(ignored, -Wunused-function) PRGM_GCC(ignored, -Wunused-parameter) PRGM_GCC(ignored, -Wunused-variable) PRGM_GCC(ignored, -Wmissing-field-initializers) PRGM_GCC(ignored, -Wswitch) PRGM_GCC(ignored, -Wpedantic) PRGM_GCC(ignored, -Wattributes) PRGM_GCC(ignored, -Wignored-qualifiers) PRGM_GCC(ignored, -Wparentheses)
	#else
		#error Unknown compiler send the issue to authors!
	#endif

	#ifdef _WIN32
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma("warning(pop)")
	#elif defined(__clang__)
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma("clang diagnostic pop")
	#elif defined(__GNUC__)
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma("GCC diagnostic pop")
	#else
		#error Unknown compiler send the issue to authors!
	#endif
#else
	#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH
	#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP
#endif
	
	#ifndef KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR
		#define KOTEK_CPP_KEYWORD_CONSTEXPR constexpr
		#define KOTEK_CPP_KEYWORD_NOEXCEPT noexcept 
		#define KOTEK_CPP_KEYWORD_ALIGNAS(your_code_string) alignas(your_code_string)
		#define KOTEK_CPP_KEYWORD_ALIGNOF(your_code_string) alignof(your_code_string)
		#define KOTEK_CPP_KEYWORD_DECLTYPE(expression) decltype(expression)
		#define KOTEK_CPP_KEYWORD_STATIC_ASSERT(expression, comment) static_assert(expression, comment)
		#define KOTEK_CPP_KEYWORD_THREAD_LOCAL thread_local
		#define KOTEK_CPP_KEYWORD_NULLPTR nullptr
		#define KOTEK_CPP_KEYWORD_CHAR_16_T char16_t
		#define KOTEK_CPP_KEYWORD_CHAR_8_T char8_t
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
	
	#ifdef KOTEK_MEMORY_LEAK_DETECTION
		#define KOTEK_USE_MEMORY_LEAK_DETECTION
		#define KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
	#endif
	
	#ifndef NDEBUG
		// for use in terms of all, we should provide for every preprocessor and 
		// the _USE_ form even if it doesn't required 
		// or if it will not be used in practice
		#define KOTEK_USE_DEBUG
	#endif
	
		#ifdef KOTEK_RMLUI_LIBRARY
			#define KOTEK_USE_RMLUI_LIBRARY
		#endif
		
		#define KOTEK_USE_RMLUI_LIBRARY_NAME RmlUi
	
		#ifdef KOTEK_NAMESPACE_KOTEK
			#define KOTEK_USE_NAMESPACE_KOTEK Kotek::
			#define kun_kotek Kotek::
			#define kn_kotek Kotek
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_KOTEK Kotek::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_KOTEK Kotek
			#define KOTEK_BEGIN_NAMESPACE_KOTEK namespace Kotek {
			#define KOTEK_END_NAMESPACE_KOTEK }

			#define KOTEK_NAMESPACE_NAME_LOWERED kotek
		#endif

		#ifdef KOTEK_NAMESPACE_CORE
			#define KOTEK_USE_NAMESPACE_CORE Core::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_core Core::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_core is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_core:: and in comparison kun_kotek kun_core
			/// Their equivalent is kotek::core::
			#define kn_core Core
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_CORE Core::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_CORE Core
			#define KOTEK_BEGIN_NAMESPACE_CORE namespace Core {
			#define KOTEK_END_NAMESPACE_CORE }

			#define KOTEK_NAMESPACE_NAME_CORE_LOWERED core
		#endif

		#ifdef KOTEK_NAMESPACE_KTK
			#define KOTEK_USE_NAMESPACE_KTK ktk::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_ktk ktk::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_ktk is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_ktk:: and in comparison kun_kotek kun_ktk
			/// Their equivalent is kotek::ktk::
			#define kn_ktk ktk
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_KTK ktk::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_KTK ktk
			#define KOTEK_BEGIN_NAMESPACE_KTK namespace ktk {
			#define KOTEK_END_NAMESPACE_KTK }
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER
			#define KOTEK_USE_NAMESPACE_RENDER Render::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render Render::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render:: and in comparison kun_kotek kun_render
			/// Their equivalent is kotek::render::
			#define kn_render Render
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER Render::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER Render
			#define KOTEK_BEGIN_NAMESPACE_RENDER namespace Render {
			#define KOTEK_END_NAMESPACE_RENDER }

			#define KOTEK_NAMESPACE_NAME_RENDER_LOWERED render
		#endif

		#ifdef KOTEK_NAMESPACE_UI
			#define KOTEK_USE_NAMESPACE_UI UI::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_ui UI::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_ui is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_ui:: and in comparison kun_kotek kun_ui
			/// Their equivalent is kotek::ui::
			#define kn_ui UI
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_UI UI::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_UI UI
			#define KOTEK_BEGIN_NAMESPACE_UI namespace UI {
			#define KOTEK_END_NAMESPACE_UI }
		#endif

		#ifdef KOTEK_NAMESPACE_MATH
			#define KOTEK_USE_NAMESPACE_MATH math::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_math math::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_math is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_core::kn_math:: and in comparison kun_kotek kun_core kun_math
			/// Their equivalent is kotek::core::math::
			#define kn_math math
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_MATH math::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_MATH math
			#define KOTEK_BEGIN_NAMESPACE_MATH namespace math {
			#define KOTEK_END_NAMESPACE_MATH }
		#endif

		#ifdef KOTEK_NAMESPACE_GAME
			#define KOTEK_USE_NAMESPACE_GAME Game::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_game Game::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_game is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_game:: and in comparison kun_kotek kun_game
			/// Their equivalent is kotek::game::
			#define kn_game Game
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_GAME Game::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_GAME Game
			#define KOTEK_BEGIN_NAMESPACE_GAME namespace Game {
			#define KOTEK_END_NAMESPACE_GAME }
		#endif

		#ifdef KOTEK_NAMESPACE_ECS
			#define KOTEK_USE_NAMESPACE_ECS ecs::
			#define KOTEK_BEGIN_NAMESPACE_ECS namespace ecs {
			#define KOTEK_END_NAMESPACE_ECS }
		#endif

		#ifdef KOTEK_NAMESPACE_ECS_FRONTEND
			#define KOTEK_USE_NAMESPACE_ECS_FRONTEND frontend::
			#define KOTEK_BEGIN_NAMESPACE_ECS_FRONTEND namespace frontend {
			#define KOTEK_END_NAMESPACE_ECS_FRONTEND }
		#endif

		#ifdef KOTEK_NAMESPACE_ECS_BACKEND
			#define KOTEK_USE_NAMESPACE_ECS_BACKEND backend::
			#define KOTEK_BEGIN_NAMESPACE_ECS_BACKEND namespace backend {
			#define KOTEK_END_NAMESPACE_ECS_BACKEND }
		#endif

		#ifdef KOTEK_NAMESPACE_MT
			#define KOTEK_USE_NAMESPACE_MT mt::
			#define KOTEK_BEGIN_NAMESPACE_MT namespace mt {
			#define KOTEK_END_NAMESPACE_MT }
			#define KUN_MT mt::
			#define kun_mt mt::
		#endif

		#ifdef KOTEK_NAMESPACE_FILESYSTEM
			#define kun_filesystem filesystem::
			#define kbn_filesystem namespace filesystem {
			#define ken_filesystem }
			#define kn_filesystem filesystem
			
			#define KUN_FILESYSTEM filesystem::
			#define KBN_FILESYSTEM namespace filesystem {
			#define KEN_FILESYSTEM }
			#define KN_FILESYSTEM filesystem
			
			#define KOTEK_USE_NAMESPACE_FILESYSTEM filesystem::
			#define KOTEK_BEGIN_NAMESPACE_FILESYSTEM namespace filesystem {
			#define KOTEK_END_NAMESPACE_FILESYSTEM }
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_GL
			#define KOTEK_USE_NAMESPACE_RENDER_GL gl::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render_gl gl::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render_gl is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render::kn_render_gl:: and in comparison kun_kotek kun_render kun_render_gl
			/// Their equivalent is kotek::render::gl::
			#define kn_render_gl gl
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER_GL gl::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER_GL gl
			#define KOTEK_BEGIN_NAMESPACE_RENDER_GL namespace gl {
			#define KOTEK_END_NAMESPACE_RENDER_GL }
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_VK
			#define KOTEK_USE_NAMESPACE_RENDER_VK vk::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render_vk vk::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render_vk is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render::kn_render_vk:: and in comparison kun_kotek kun_render kun_render_vk
			/// Their equivalent is kotek::render::vk::
			#define kn_render_vk vk
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER_VK vk::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER_VK vk
			#define KOTEK_BEGIN_NAMESPACE_RENDER_VK namespace vk {
			#define KOTEK_END_NAMESPACE_RENDER_VK }
		#endif

		#ifdef KOTEK_NAMESPACE_RENDER_DX
			#define KOTEK_USE_NAMESPACE_RENDER_DX dx::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_render_dx dx::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_render_dx is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_render::kn_render_dx:: and in comparison kun_kotek kun_render kun_render_dx
			/// Their equivalent is kotek::render::dx::
			#define kn_render_dx dx
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_RENDER_DX dx::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_RENDER_DX dx
			#define KOTEK_BEGIN_NAMESPACE_RENDER_DX namespace dx {
			#define KOTEK_END_NAMESPACE_RENDER_DX }
		#endif

		#ifdef KOTEK_NAMESPACE_SOUND
			#define KOTEK_USE_NAMESPACE_SOUND Sound::
			/// ~english @brief kun stands for kotek_use_namespace it is reduced version of KOTEK_USE_NAMESPACE_***
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			#define kun_sound Sound::
			/// ~english @brief kn stands for kotek_namespace it is reduced version
			/// you can use it for your 'business' logic when you want to keep feature for renaming namespace through cmake
			/// the difference between this preprocessor and kun_sound is that in first version you don't need to write :: but in this version you have to write :: so it means when I use this preprocessor it will look like this
			/// kn_kotek::kn_sound:: and in comparison kun_kotek kun_sound
			/// Their equivalent is kotek::sound::
			#define kn_sound Sound
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KUN_SOUND Sound::
			/// ~english @brief just upper case version for users which code style in their codebase for preprocessors is upper case
			#define KN_SOUND Sound
			#define KOTEK_BEGIN_NAMESPACE_SOUND namespace Sound {
			#define KOTEK_END_NAMESPACE_SOUND }
		#endif
	
		#ifdef KOTEK_DEVELOPMENT_TYPE_SHARED
			#define KOTEK_USE_DEVELOPMENT_TYPE_SHARED
		#endif
	
        	#define KOTEK_USE_MEMORY_ALLOCATOR_CPU_STD
            
		#define KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME "game.ktk"
	
		#ifdef KOTEK_RENDER_OPENGL
			#define KOTEK_USE_RENDER_OPENGL
		#endif

		#ifdef KOTEK_RENDER_VULKAN
			#define KOTEK_USE_RENDER_VULKAN
		#endif
	
		#ifdef KOTEK_SDK_IMGUI
			#define KOTEK_USE_SDK_IMGUI
			#define KOTEK_USE_UI_IMGUI_LIBRARY_IMGUI
		#endif
	
		#define KOTEK_USE_USER_DATA_CONFIG_NAME "settings"
	
		#define KOTEK_USE_STARTUP_RENDERER kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser
	
		#define KOTEK_USE_STARTUP_RENDERER_VERSION kOpenGLES_3_1
	
		#define KOTEK_USE_LOG_OUTPUT_FILE_NAME "all.log"
	
		#define KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
	
		#define KOTEK_CHECK_FLAG(flags_as_number, your_flag) (flags_as_number & your_flag) == your_flag
		#define KOTEK_SET_FLAG(flags_as_number, your_flag) flags_as_number |= your_flag
		#define KOTEK_REMOVE_FLAG(flags_as_number, your_flag) flags_as_number &= ~your_flag
	
		#define KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(your_type) inline your_type& operator|=(your_type& left, your_type right) { return left = your_type(left|right);} inline your_type& operator&=(your_type& left, your_type right) { return left = your_type(left & right); } inline your_type& operator&=(your_type& left, int right) { return left = your_type(left & right); } inline your_type& operator&=(your_type& left, unsigned int right) { return left = your_type(left & right); }
	
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE char
			#define KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER 1
		
			#define KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
		
			#define KOTEK_USE_LIBRARY_TYPE_EMB

			// definitions for determining the size of containers
			// they are described with KOTEK_DEF_ prefix
			#define KOTEK_DEF_FALLBACK_RENDERERS_COUNT 4
			#define KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT 16
			#define KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT 8
			#define KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT 128
			#define KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT 8
			#define KOTEK_DEF_TEXT_RESOURCE_LOADERS_COUNT 2
			#define KOTEK_DEF_JSON_RESOURCE_LOADERS_COUNT 2
			#define KOTEK_DEF_TEXT_RESOURCE_SAVERS_COUNT 2
			#define KOTEK_DEF_JSON_RESOURCE_SAVERS_COUNT 2
			#define KOTEK_DEF_RESOURCE_LOADERS_TYPE_MAX_COUNT 16
			#define KOTEK_DEF_RESOURCE_SAVER_MANAGER_FILE_POOL_COUNT 10
			#define KOTEK_DEF_RESOURCE_SAVERS_TYPE_MAX_COUNT 16
			#define KOTEK_DEF_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL 4
			#define KOTEK_DEF_RESOURCE_LOADER_MANAGER_SIZE_FILE_POOL 4
			#define KOTEK_DEF_CONSOLE_MAX_QUEUE_SIZE 64
			#define KOTEK_DEF_RESOURCE_STREAMING_CHUNK_SIZE 4096
		
		#define KOTEK_DEF_CONSOLE_TYPE_FOR_ARGUMENT_COUNT unsigned char
	
				#define KOTEK_USE_LOG_LIBRARY_SPDLOG
		
		#ifndef KOTEK_WINDOW_CONSOLE_STRING_VIEW_SIZE
			static_assert(false, "you must define this preprocessor!");
		#else
			#define KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE 3072
		#endif
	