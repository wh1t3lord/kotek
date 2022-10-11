#include "../include/kotek_render_model_assimp.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_Model_ASSIMP(Core::ktkMainManager* p_main_manager)
{
	return true;
}

bool ShutdownModule_Render_Model_ASSIMP(Core::ktkMainManager* p_main_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK