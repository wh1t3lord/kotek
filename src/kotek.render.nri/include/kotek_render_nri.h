#pragma once

/// \file kotek_render_nri.h
/// \~english Umbrella header of the kotek.render.nri module (task K11):
/// module entry points and the module's capacity constants. Must stay free
/// of NRI types — the module-boundary rule forbids NRI types in anything
/// included from outside this module.

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

/// \~english desired swap chain length (double buffering); the real count
/// is queried back from nri::SwapChainInterface::GetSwapChainTextures
#define KOTEK_DEF_RENDER_NRI_SWAPCHAIN_BACK_BUFFERS 2

/// \~english array capacity for per-back-buffer objects (views, fences);
/// any count the swap chain reports above this is a hard assert
#define KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS 4

/// \~english frames allowed in flight before the CPU waits on the frame
/// fence (1 = the previous submission must be done before re-recording the
/// single command list of phase 1)
#define KOTEK_DEF_RENDER_NRI_QUEUED_FRAMES 1

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
bool InitializeModule_Render_NRI(kun_core ktkMainManager* main_manager);
bool ShutdownModule_Render_NRI(kun_core ktkMainManager* main_manager);
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
