#pragma once

#include <kotek.render.model.assimp/include/kotek_render_model_assimp.h>
#include <kotek.render.model.cgltf/include/kotek_render_model_cgltf.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_Model(Core::ktkMainManager* p_main_manager);
bool ShutdownModule_Render_Model(Core::ktkMainManager* p_main_manager);

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK