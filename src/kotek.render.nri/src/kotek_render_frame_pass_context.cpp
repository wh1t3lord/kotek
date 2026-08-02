#include "../include/kotek_render_frame_pass_context.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

ktkRenderFramePassContext::ktkRenderFramePassContext(
	ktkRenderDevice* p_device, ::nri::Descriptor* p_color_view) :
	m_p_device(p_device),
	m_p_color_view(p_color_view)
{
	KOTEK_ASSERT(this->m_p_device,
		"the frame pass context needs a valid NRI render device");
	KOTEK_ASSERT(this->m_p_color_view,
		"the frame pass context needs the acquired back buffer's color "
		"view");
}

ktkRenderFramePassContext::~ktkRenderFramePassContext(void) {}

void ktkRenderFramePassContext::ClearColor(float r, float g, float b,
	float a)
{
	::nri::AttachmentDesc color_attachment{};
	color_attachment.descriptor = this->m_p_color_view;
	color_attachment.loadOp = ::nri::LoadOp::CLEAR;
	color_attachment.storeOp = ::nri::StoreOp::STORE;
	color_attachment.clearValue.color.f.x = r;
	color_attachment.clearValue.color.f.y = g;
	color_attachment.clearValue.color.f.z = b;
	color_attachment.clearValue.color.f.w = a;

	::nri::RenderingDesc rendering{};
	rendering.colors = &color_attachment;
	rendering.colorNum = 1;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdBeginRendering(*this->m_p_device->Get_CommandBuffer(), rendering);
	core.CmdEndRendering(*this->m_p_device->Get_CommandBuffer());
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
