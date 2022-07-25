#pragma once

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		/// <summary>
		/// The main interface for binding classes from game library to render
		/// library for rendering In that case you can use it like this:
		///
		/// 1. In game library you create your custom class which overrides this
		/// class (e.g. class Game::kotek_sdk_ui_my_custom_element : public
		/// Core::kotek_sdk_ui_element ...)
		/// 2. After that you pass in initializeModule_Game your element and
		/// create them by new operator
		///
		/// g_manager_main.getRenderer()->bindSDKUIElement(new
		/// kotek_sdk_ui_my_custom_element(...));
		///
		/// This is memory-safed operation because g_manager_renderer will watch
		/// on all pointers and destroy them in RAII's manner (e.g. destroying
		/// in destructor of ~kotek_renderer)
		/// </summary>
		class kotek_sdk_ui_element
		{
		public:
			kotek_sdk_ui_element(void) {}
			virtual ~kotek_sdk_ui_element(void) {}

			virtual void initialize(void) = 0;
			virtual void shutdown(void) = 0;
			virtual void Draw(ktkMainManager* p_main_manager) = 0;
		};
	} // namespace Core
} // namespace Kotek