#pragma once

#include "kotek_model.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_Model_ASSIMP(Core::ktkMainManager* p_main_manager);

bool ShutdownModule_Render_Model_ASSIMP(Core::ktkMainManager* p_main_manager);

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK