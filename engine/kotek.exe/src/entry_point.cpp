#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.game/include/kotek_engine.h>

/**
 * @mainpage Kotek
 * 
 * @section doxygen_main_page Table of contents
 * 
 * - @ref doxygen_user_guide
 *  - @ref doxygen_user_guide_getting_started
 *  - @ref doxygen_user_guide_whydoyouneedit
 *  - @ref doxygen_user_guide_whydontyouneedit
 *  - @ref doxygen_user_guide_building_commands
 *  - @ref doxygen_user_guide_examples
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
 *   - @ref doxygen_user_guide_examples_window_and_sdk_and_imgui_and_dedicated_server
 *   - @ref doxygen_user_guide_examples_window_no_renderer_but_sound
 *   - @ref doxygen_user_guide_examples_window_ancient_renderers
 *    - @ref doxygen_user_guide_examples_window_ancient_renderers_directx
 *    - @ref doxygen_user_guide_examples_window_ancient_renderers_opengl
 * - @ref doxygen_faq
 *  - @ref doxygen_faq_why
 *  - @ref doxygen_faq_whatif
 *  - @ref doxygen_faq_realexamples
 * - @ref doxygen_what_standards
 *  - @ref doxygen_standards_about_platforms
 *  - @ref doxygen_standards_about_renderers
 *  - @ref doxygen_standards_about_file_formats
 *  - @ref doxygen_standards_about_engine_side
 *  - @ref doxygen_standards_about_user_side
 * - @ref doxygen_just_for_reading
 *  - @ref doxygen_ideas_for_implementation
 *  - @ref doxygen_philosophy_of_development
 * - @ref doxygen_information_for_developers
 *  - @ref doxygen_information_for_developers_general_information 
 *  - @ref doxygen_information_for_developers_codestyle
 */


/**
 * Entry point of the application of computer OSes.
 * 
 * \param argc is the number of arguments being passed into your program from the command line.
 * \param argv is the array of arguments.
 * \return status code. OS dependent.
 */
int main(int argc, char** argv)
{
	Kotek::Core::ktkMainManager main_manager;

	Kotek::Engine::InitializeEngine(&main_manager);
	Kotek::Engine::ExecuteEngine(&main_manager);
	Kotek::Engine::ShutdownEngine(&main_manager);

	return 0;
}
