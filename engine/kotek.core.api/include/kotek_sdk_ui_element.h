#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// <summary>
/// The main interface for binding classes from game library to render
/// library for rendering In that case you can use it like this:
///
/// 1. In game library you create your custom class which overrides this
/// class (e.g. class Game::kotek_sdk_ui_my_custom_element : public
/// Core::ktkISDKUIElement ...)
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
class ktkISDKUIElement
{
public:
	ktkISDKUIElement(void) {}
	virtual ~ktkISDKUIElement(void) {}

	virtual void initialize(void) = 0;
	virtual void shutdown(void) = 0;
	virtual void Draw(ktkMainManager* p_main_manager) = 0;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK