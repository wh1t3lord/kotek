#pragma once

/// \file kotek_render_frame_pass_context.h
/// \~english the module-side implementation of
/// Core::ktkIRenderFramePassContext (task K11 phase 2 / zircon Z5 P4):
/// the narrow recording surface a host's frame passes see while the
/// swapchain's command buffer is open between the back-buffer barriers.
/// Stack-lived inside ktkRenderSwapchain for one frame — no heap object
/// and no ownership ever crosses the module boundary, and NRI types stay
/// module-internal (the boundary rule: they are spelled ::nri::X because
/// this module's own namespace is Kotek::Render::nri).

#include "kotek_render_nri.h"
#include "kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

class ktkRenderFramePassContext : public Core::ktkIRenderFramePassContext
{
public:
	/// \~english p_device must outlive the context (the swapchain owns
	/// both); p_color_view is the acquired back buffer's color-attachment
	/// descriptor ClearColor records into
	ktkRenderFramePassContext(
		ktkRenderDevice* p_device, ::nri::Descriptor* p_color_view);
	~ktkRenderFramePassContext(void);

	/// \~english records one rendering section with LoadOp::CLEAR over the
	/// acquired back buffer — the exact commands the phase-1 monolithic
	/// Present recorded for its built-in clear
	void ClearColor(float r, float g, float b, float a) override;

private:
	ktkRenderDevice* m_p_device;
	::nri::Descriptor* m_p_color_view;
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
