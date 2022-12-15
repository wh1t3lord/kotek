#include "../include/kotek_render_angle_gles23.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_ANGLE_GLES23(Core::ktkMainManager* p_main_manager)
{
	KOTEK_MESSAGE("render module is initialized");

	return true;
}

bool ShutdownModule_Render_ANGLE_GLES23(Core::ktkMainManager* p_main_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK