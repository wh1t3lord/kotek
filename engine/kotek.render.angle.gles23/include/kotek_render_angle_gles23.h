#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_ANGLE_GLES23(
	kun_kotek kun_core ktkMainManager* main_manager, kun_kotek kun_core eEngineSupportedRenderer version);
bool ShutdownModule_Render_ANGLE_GLES23(kun_kotek kun_core ktkMainManager* main_manager);

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK