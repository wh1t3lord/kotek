#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.game/include/kotek_engine.h>

// clang-format off
/**
 * @mainpage Kotek
 *
 * \~english @section doxygen_main_page Table of contents
 *
 * - @ref doxygen_user_guide
 *  - @ref doxygen_user_guide_getting_started "Getting started"
 *	 - @ref doxygen_user_guide_whydoyouneedit "Why do you need it?"
 *	 - @ref doxygen_user_guide_whydontyouneedit "Why you don't need it"
 *  - @ref doxygen_user_guide_building "Building"
 *   - @ref doxygen_user_guide_building_cmake "CMake"
 *		- @ref doxygen_user_guide_building_cmake_commands "Step by Step"
 *		- @ref doxygen_user_guide_building_cmake_commands_description "Description of every flag (macroses) what you can pass"
 *  - @ref doxygen_user_guide_examples "Examples"
 *   - @ref doxygen_user_guide_examples_building "Building examples"
 *    - @ref doxygen_user_guide_examples_building_specify_deps_folder
 *    - @ref doxygen_user_guide_examples_building_different_libraries
 *	 - @ref doxygen_user_guide_examples_callbacks
 *   - @ref doxygen_user_guide_examples_window
 *   - @ref doxygen_user_guide_examples_window_renderer_empty
 *   - @ref doxygen_user_guide_examples_window_switching_renderers
 *   - @ref doxygen_user_guide_examples_window_commandline
 *   - @ref doxygen_user_guide_examples_window_renderer_render_graph
 *    - @ref doxygen_user_guide_examples_window_renderer_render_graph_backbuffer
 *    - @ref doxygen_user_guide_examples_window_renderer_render_graph_triangle
 *    - @ref doxygen_user_guide_examples_window_renderer_render_graph_pbr
 *    - @ref doxygen_user_guide_examples_window_renderer_render_graph_animation
 *    - @ref doxygen_user_guide_examples_window_renderer_render_graph_rtx
 *   - @ref doxygen_user_guide_examples_window_and_sdk
 *   - @ref doxygen_user_guide_examples_window_and_sdk_and_imgui
 *   - @ref
 *doxygen_user_guide_examples_window_and_sdk_and_imgui_and_dedicated_server
 *   - @ref doxygen_user_guide_examples_window_no_renderer_but_sound
 *   - @ref doxygen_user_guide_examples_window_ancient_renderers
 *    - @ref doxygen_user_guide_examples_window_ancient_renderers_directx
 *    - @ref doxygen_user_guide_examples_window_ancient_renderers_opengl
 *   - @ref doxygen_user_guide_examples_plugins
 * - @ref doxygen_faq "Frequintly asked questions (FAQ)"
 *  - @ref doxygen_faq_why
 *  - @ref doxygen_faq_whatif
 *  - @ref doxygen_faq_howtoreadthisdocumentation
 *  - @ref doxygen_faq_realexamples
 * - @ref doxygen_standards
 *  - @ref doxygen_standards_about_architecture
 *  - @ref doxygen_standards_about_platforms
 *  - @ref doxygen_standards_about_renderers
 *  - @ref doxygen_standards_about_file_formats
 *  - @ref doxygen_standards_about_programming_languages
 *  - @ref doxygen_standards_about_ui_frameworks
 *  - @ref doxygen_standards_about_engine_side
 *  - @ref doxygen_standards_about_user_side
 *   - @ref doxygen_standards_about_user_dll
 *   - @ref doxygen_standards_about_user_callback_functions
 *  - @ref doxygen_standards_about_scripting
 *  - @ref doxygen_standards_about_plugins
 *  - @ref doxygen_standards_about_dependencies
 *  - @ref doxygen_standards_about_project_creation
 *  - @ref doxygen_standards_about_cmake_project_flags
 * - @ref doxygen_just_for_reading
 *  - @ref doxygen_ideas_for_implementation
 *  - @ref doxygen_philosophy_of_development
 *  - @ref doxygen_standartization
 * - @ref doxygen_information_for_developers
 *  - @ref doxygen_information_for_developers_general_information
 *  - @ref doxygen_information_for_developers_codestyle
 * 
 * \~russian @section doxygen_main_page Оглавление
 */

/**
 * Entry point of the application of computer OSes.
 *
 * \param argc is the number of arguments being passed into your program from
 * the command line. \param argv is the array of arguments. \return status code.
 * OS dependent.
 *
 * @code
 * // the main function stands for initialization, update and shutdown the
 * system
 *
 * // the general usage is to create Kotek::Core::ktkMainManager instance on
 * stack and call the following functions in specified order:
 *
 * Kotek::Engine::Initialize_Engine(&main_manager);
 * Kotek::Engine::Execute_Engine(&main_manager);
 * Kotek::Engine::Shutdown_Engine(&main_manager);
 * @endcode
 */
// clang-format on

int main(int argc, char** argv)
{
	Kotek::Core::ktkMainManager main_manager(argc, argv);
	Kotek::Engine::InitializeEngine(&main_manager);
	Kotek::Engine::ExecuteEngine(&main_manager);
	Kotek::Engine::ShutdownEngine(&main_manager);

	return 0;
}

// clang-format off
// doxygen_user_guide_building_cmake_commands_description
/**
 * \~english @page doxygen_user_guide_building_cmake_commands_description "Description of every flag (macroses) what you can pass"
 * 
 * - @ref KOTEK_STD_LIBRARY
 * - @ref KOTEK_UI_GAME_LIBRARY
 * - @ref KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR
 * - @ref KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR
 * - @ref KOTEK_CPP_KEYWORD_NOEXCEPT
 * - @ref KOTEK_CPP_KEYWORD_INLINE
 * - @ref KOTEK_CPP_KEYWORD_CONSTEXPR
 * - @ref KOTEK_MEMORY_LEAK_DETECTION
 * - @ref KOTEK_CPP_MEMORY_LEAK_LIBRARY
 * - @ref KOTEK_MEMORY_ALLOCATOR_CPU
 * - @ref KOTEK_NAMESPACE_KOTEK
 * 
 * \page KOTEK_STD_LIBRARY
 * 
 * This flag specifies what your library is. By our standard we support only two libraries it is STL from standard implementation that vendors provide like linux, Windows NT SDK and etc. And we support Boost library.
 * 
 * If argument is empty it means that by default CMake sets to "BOOST" variable and it means that your solution will be generated for Boost library if we don't want to generate solution for Boost library you need to pass STD otherwise if you pass any string that is not BOOST and not STD it means that you will include your own STL-like library.
 * 
 * @warning Engine doesn't support any kind of libraries. Engine supports only STL-like libraries that could override our containers.
 * 
 * Arguments: Empty string, STD, Boost, Any String.
 * 
 * Example if you want to generate for STD: 
 * @code
 *  cmake -DKOTEK_STD_LIBRARY=STD ..
 * @endcode
 * 
 * \page KOTEK_UI_GAME_LIBRARY
 * 
 * This flag specifies what your UI library is. By our standard we support the following libraries:
 * 
 * 1. RmlUi
 * 2. Chromium embedded framework (CEF) 
 * 
 * @warning Current state of CEF is that we can't implement because of package managers for C++ that don't support it well now. When it was real that some of C++ package managers will support CEF compilation (or at least good installation process) we will add, but it is only a plan to support this library for UI.
 * 
 * By default it will set to RMLUI value and it means that engine uses RMLUI library.
 * 
 * Arguments: Empty string, RMLUI, CEF (not supported now).
 * 
 * Example if I want to use CEF (if it would exist) instead of default RMLUI
 * @code
 *	cmake -DKOTEK_UI_GAME_LIBRARY=CEF ..
 * @endcode
 * 
 * @note This flag generates two new macroses KOTEK_UI_GAME_LIBRARY_NAME and KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME. KOTEK_UI_GAME_LIBRARY_NAME is formal naming of library and it is a string (char array) and KOTEK_UI_GAME_LIBRARY_DESCRIPTION_NAME stands for detailed description. But currently they just exist and you can use them as you want in your solution. 
 * 
 * \page KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR
 * 
 * This flag translates as: "Disable all warnings". So it accepts two states you enable a such feature or don't use it.
 * 
 * By default this flag is not used. In order to enable it you need to pass ON word
 * 
 * Example if I want to enable this feature
 * @code
 *	cmake -DKOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR=ON ..
 * @endcode
 * 
 * @note When you enabled this feature it means that you can write KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH and KOTEK_CPP_DISABLE_ALL_WARNINGS_POP. It tries to handle all compiler specific pragmas in order to disable all possible warnings. Sometimes it could be really useful if you have a strict compilation process and for some part of solution that you don't handle at all you want to disable warnings, but you want to keep compilation of your code with treating on warnings (it means it will stop compilation process if compiler finds some compiling warnings).
 * 
 * \page KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR
 * 
 * This flag stands for implement preprocessor for "hiding" language keywords like noexcept, constexpr, etc in order to enable them or disable them or just replace them in code on your specified keyword (@see KOTEK_CPP_KEYWORD_CONSTEXPR, @see KOTEK_CPP_KEYWORD_INLINE, @see KOTEK_CPP_KEYWORD_NOEXCEPT and others).
 * 
 * So by default CMake doesn't use it, but in order to enable it you need to pass ON word.
 * 
 * Example if I want to enable this feature:
 * @code
 *	cmake -DKOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR=ON ..
 * @endcode
 * 
 * \page KOTEK_CPP_KEYWORD_NOEXCEPT
 * 
 * @warning this keyword depends on @see KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR if this macro is diabled the chaning of KOTEK_CPP_KEYWORD_NOEXCEPT doesn't make any sense and all changes will not be generated for solution.
 * 
 * This flag reprensents preprocessor for using in solution in order to replace native noexcept keyword.
 * 
 * You can specify any string 
 * 
 * By default sets to noexcept and it doesn't depend specified you KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR or not. 
 * 
 * Example if I want to change this macro (but you need to be sure that it will not cause compilation error)
 * 
 * @code 
 *	cmake -DKOTEK_CPP_KEYWORD_NOEXCEPT=something ..
 * @endcode
 * 
 * But if you want to generate solution without any noexcept keyword that we used you just need to pass empty string like this:
 * 
 * @code 
 *	cmake -DKOTEK_CPP_KEYWORD_NOEXCEPT="" ..
 * @endcode
 * 
 * \page KOTEK_CPP_KEYWORD_INLINE
 * 
 * @warning this keyword depends on @see KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR if this macro is diabled the chaning of KOTEK_CPP_KEYWORD_INLINE doesn't make any sense and all changes will not be generated for solution
 * 
 * This flag represents preprocessor for using in solution in order to replace native inline keyword.
 * 
 * You can specify any string 
 * 
 * By default sets to inline and it doesn't depend specified you KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR or not.
 * 
 * Example if I want to change this macro (but you need to be sure that it will not cause compilation error)
 * 
 * @code
 *	cmake -DKOTEK_CPP_KEYWORD_INLINE="something" ..
 * @endcode
 * 
 * But if you want to generate solution without any inline keyword that we used you just need to pass empty string like this:
 * 
 * @code
 *	cmake -DKOTEK_CPP_KEYWORD_INLINE="" ..
 * @endcode
 * 
 * \page KOTEK_CPP_KEYWORD_CONSTEXPR
 * 
 * This flag represents preprocessor for using in solution in order to replace native constexpr keyword.
 * 
 * You can specify any string
 * 
 * By default sets to constexpr and it doesn't depend specified you KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR or not.
 * 
 * Example if I want to change this macro (but you need to be sure that it will not cause compilation error)
 * 
 * @code
 *	cmake -DKOTEK_CPP_KEYWORD_CONSTEXPR="something" ..
 * @endcode
 * 
 * But if you want to generate solution without any constexpr keyword that we used you just need to pass empty string like this:
 * 
 * @code
 *	cmake -DKOTEK_CPP_KEYWORD_CONSTEXPR="" ..
 * @endcode
 * 
 * \page KOTEK_MEMORY_LEAK_DETECTION
 * 
 * This flag represents do we enable memory leak detection or not.
 * 
 * @warning this flag depends on CMAKE_BUILD_TYPE value if it is Debug it means that by default sets to ON. So we enable this feature
 * 
 * Arguments: Empty string, ON, Any string.
 * 
 * If you pass a string that is not empty and it is not equal to ON it means that this feature will be disabled.
 * 
 * But you need to use it when CMAKE_BUILD_TYPE=Debug.
 * 
 * Example if I don't want to use memory leak detection when build type is Debug.
 * 
 * @code
 *	cmake -DCMAKE_BUILD_TYPE=Debug -DKOTEK_MEMORY_LEAK_DETECTION=OFF ..
 * @endcode
 * 
 * \page KOTEK_CPP_MEMORY_LEAK_LIBRARY
 * 
 * This library represents what library will be used in solution. 
 * 
 * By default we support Visual Leak Detector on Windows. 
 * 
 * @warning others platforms are not supported, except Windows NT
 * 
 * @warning This macro depends on KOTEK_MEMORY_LEAK_DETECTION value. If this feature is disabled it means that KOTEK_CPP_MEMORY_LEAK_LIBRARY is not affect on solution.
 * 
 * So by default sets to VLD value. It means that solution will use Visual Leak Detector library if it is presented in dependency folder.
 * 
 * Example if I want to change to other library:
 * 
 * @code
 *	cmake -DCMAKE_BUILD_TYPE=Debug -DKOTEK_CPP_MEMORY_LEAK_LIBRARY="XXX" ..
 * @endcode
 * 
 * \page KOTEK_MEMORY_ALLOCATOR_CPU
 * 
 * This flag represents what library will be used for overriding std::allocator or implementing std::allocator and language memory operations like new and delete.
 * 
 * By our standard we support only mimalloc library. But we didn't implement a feature for overriding allocator. Probably it is better to implement through plugin system where user can load his library from outside and use it instead of mimalloc, but we will think.
 * 
 * Arguments: Empty String, Mimalloc, Any String.
 * 
 * Any String stands for your allocator. But now this value represents that you disable mimalloc library for usage. And solution will use default new and delete and default std::allocator for every container what we have.
 * 
 * Example if I don't want to use mimalloc library:
 * 
 * @code 
 *	cmake -DKOTEK_MEMORY_ALLOCATOR_CPU=OFF ..
 * @endcode
 * 
 * 
 * 
 * \~russian @page doxygen_user_guide_building_cmake_commands_description 
 */
// clang-format on

// clang-format off
// doxygen_standards_about_renderers
/**
* \~english @page doxygen_standards_about_renderers "How we standardize Renderers"
* 
* - @ref doxygen_standards_about_renderers_case_command_line "Handling application command line"
* - @ref doxygen_standards_about_renderers_case_config "Handling config"
* - @ref doxygen_standards_about_renderers_case_fallback "Handling fallback"
* 
* It is important to notice that we can't standardize the initialization and shutdown in engine. It means that user must handle what renderer must be initialized, how it knows, and how many renderers user must handle. 
* 
* First of all, we have the following scenarios:
* 
* 1. User wants to specify renderer through command line of application e.g. shortcut, target section
* 2. User wants to specify renderer through serialized data e.g. config aka json (see standart section about text files in our engine)
* 3. Engine must handle a situation where the specified renderer can't be executed well and we have a fallback scenario and we should initialize engine on another renderer what user must have. (probably if you are lazy you can try to use our software renderer implementation), but it supposed that user thinks about a such case and they can implement a new renderer for supporting old devices.
* 
* 
* \~russian @page doxygen_standards_about_renderers "О Рендерерах"
*/

/**
* \~english @page doxygen_standards_about_renderers_case_command_line "Handling command line"
* 
* \~russian @page doxygen_standards_about_renderers_case_command_line ""
*/


/**
* \~english @page doxygen_standards_about_renderers_case_config "Handling config"
* 
* 
* 
* 
* \~russian @page doxygen_standards_about_renderers_case_config ""
*/

/**
* \~english @page doxygen_standards_about_renderers_case_fallback "Handling fallback"
* 
* 
* \~russian @page doxygen_standards_about_renderers_case_fallback ""
*/

// clang-format on
