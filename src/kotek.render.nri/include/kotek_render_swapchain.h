#pragma once

/// \file kotek_render_swapchain.h
/// \~english NRI swap chain (task K11, phase 1: D3D12 on the GLFW window's
/// HWND). Owns the nri::SwapChain, the per-back-buffer color-attachment
/// views and the acquire/release semaphore fences; Present() records the
/// clear-color frame into the device's command list. Module-internal
/// header — NRI types never leave this module (and they are spelled
/// ::nri::X because this module's own namespace is Kotek::Render::nri).

#include "kotek_render_nri.h"
#include "kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

class ktkRenderSwapchain : public Core::ktkIRenderSwapchain
{
public:
	ktkRenderSwapchain(void);
	~ktkRenderSwapchain(void);

	void Initialize(Core::ktkIRenderDevice* p_render_device) override;

	void Shutdown(Core::ktkIRenderDevice* p_render_device) override;

	void Resize(Core::ktkIRenderDevice* p_render_device, int width,
		int height, bool vsync) override;

	/// \~english presents one clear-color frame: acquire back buffer ->
	/// barrier PRESENT -> COLOR_ATTACHMENT -> CmdBeginRendering with
	/// LoadOp::CLEAR (the milestone color) -> CmdEndRendering -> barrier
	/// back -> QueueSubmit -> QueuePresent, paced by the device's frame
	/// fence (KOTEK_DEF_RENDER_NRI_QUEUED_FRAMES)
	void Present(Core::ktkMainManager* p_main_manager,
		Core::ktkIRenderDevice* p_render_device) override;

private:
	/// \~english (re)creates the swap chain and everything derived from
	/// it (views, fences) for the given size; used by Initialize and
	/// Resize
	void Create_SwapChain(ktkRenderDevice* p_device, int width, int height,
		bool vsync);

	/// \~english destroys everything Create_SwapChain made (reverse
	/// order); safe on a partially constructed state
	void Destroy_SwapChain(ktkRenderDevice* p_device);

private:
	::nri::SwapChain* m_p_swapchain{};
	/// \~english borrowed pointers into NRI's swap chain (NRI owns them)
	::nri::Texture* const* m_p_textures{};
	::nri::Descriptor* m_p_color_views
		[KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS]{};
	::nri::Fence* m_p_acquire_fences
		[KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS]{};
	::nri::Fence* m_p_release_fences
		[KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS]{};
	kun_ktk uint8_t m_texture_count{};
	kun_ktk uint64_t m_frame_index{};
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
