#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_Shared_DX(Core::ktkMainManager*);
bool ShutdownModule_Render_Shared_DX(Core::ktkMainManager*);

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK