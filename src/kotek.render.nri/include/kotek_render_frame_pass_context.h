#pragma once

/// \file kotek_render_frame_pass_context.h
/// \~english the module-side implementation of
/// Core::ktkIRenderFramePassContext (task K11 phase 2 / zircon Z5 P4,
/// extended with the draw commands in phase 3 / zircon Z24 B3b): the narrow
/// recording surface a host's frame passes see while the swapchain's
/// command buffer is open between the back-buffer barriers. Stack-lived
/// inside ktkRenderSwapchain for one frame — no heap object and no
/// ownership ever crosses the module boundary, and NRI types stay
/// module-internal (the boundary rule: they are spelled ::nri::X because
/// this module's own namespace is Kotek::Render::nri). The opaque geometry
/// handles resolve through the module's geometry manager; a stale handle
/// or an out-of-order call is a loud no-op for that command, never a
/// crash mid-frame.

#include "kotek_render_nri.h"
#include "kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

class ktkRenderGeometryManager;

class ktkRenderFramePassContext : public Core::ktkIRenderFramePassContext
{
public:
	/// \~english p_device must outlive the context (the swapchain owns
	/// both); p_color_view is the acquired back buffer's color-attachment
	/// descriptor ClearColor records into; p_geometry_manager resolves the
	/// frame-level handle commands (may be nullptr — the clear-only path);
	/// width/height are the acquired back-buffer size
	ktkRenderFramePassContext(ktkRenderDevice* p_device,
		::nri::Descriptor* p_color_view,
		ktkRenderGeometryManager* p_geometry_manager,
		kun_ktk uint32_t width, kun_ktk uint32_t height);
	~ktkRenderFramePassContext(void);

	/// \~english records one rendering section with LoadOp::CLEAR over the
	/// acquired back buffer — the exact commands the phase-1 monolithic
	/// Present recorded for its built-in clear
	void ClearColor(float r, float g, float b, float a) override;

	void Begin_Render_Pass(void) override;
	void End_Render_Pass(void) override;
	void Set_Pipeline(
		Core::ktkRenderGeometryPipelineHandle pipeline) override;
	void Set_Push_Constants(const void* p_data,
		kun_ktk uint32_t size_bytes) override;
	void Set_Vertex_Buffer(Core::ktkRenderGeometryBufferHandle buffer,
		kun_ktk uint64_t offset_bytes, kun_ktk uint32_t stride_bytes,
		kun_ktk uint32_t slot) override;
	void Set_Index_Buffer(Core::ktkRenderGeometryBufferHandle buffer,
		kun_ktk uint64_t offset_bytes,
		Core::eRenderGeometryIndexFormat format) override;
	void Draw_Indexed(kun_ktk uint32_t index_count,
		kun_ktk uint32_t instance_count, kun_ktk uint32_t first_index,
		kun_ktk int32_t vertex_offset,
		kun_ktk uint32_t first_instance) override;

	kun_ktk uint32_t Get_Back_Buffer_Width(void) const override;
	kun_ktk uint32_t Get_Back_Buffer_Height(void) const override;

private:
	/// \~english the frame-level command guard: the bind/draw commands are
	/// only legal between Begin_Render_Pass and End_Render_Pass — a
	/// violation is a loud no-op for that command (a programmer error must
	/// not corrupt the open command list)
	bool is_inside_render_pass(void) const noexcept;

private:
	ktkRenderDevice* m_p_device;
	::nri::Descriptor* m_p_color_view;
	ktkRenderGeometryManager* m_p_geometry_manager;
	kun_ktk uint32_t m_width;
	kun_ktk uint32_t m_height;
	bool m_is_inside_render_pass{};
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
