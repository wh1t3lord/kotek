#include "../include/kotek_render_frame_pass_context.h"
#include "../include/kotek_render_geometry_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

ktkRenderFramePassContext::ktkRenderFramePassContext(
	ktkRenderDevice* p_device, ::nri::Descriptor* p_color_view,
	ktkRenderGeometryManager* p_geometry_manager, kun_ktk uint32_t width,
	kun_ktk uint32_t height) :
	m_p_device(p_device),
	m_p_color_view(p_color_view), m_p_geometry_manager(p_geometry_manager),
	m_width(width), m_height(height), m_is_inside_render_pass(false)
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

void ktkRenderFramePassContext::Begin_Render_Pass(void)
{
	if (this->m_is_inside_render_pass)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Begin_Render_Pass while a render pass is already "
			"open — ignored");

		return;
	}

	::nri::AttachmentDesc color_attachment{};
	color_attachment.descriptor = this->m_p_color_view;
	color_attachment.loadOp = ::nri::LoadOp::LOAD;
	color_attachment.storeOp = ::nri::StoreOp::STORE;

	::nri::RenderingDesc rendering{};
	rendering.colors = &color_attachment;
	rendering.colorNum = 1;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdBeginRendering(*this->m_p_device->Get_CommandBuffer(), rendering);

	this->m_is_inside_render_pass = true;
}

void ktkRenderFramePassContext::End_Render_Pass(void)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] End_Render_Pass without an open render pass — "
			"ignored");

		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdEndRendering(*this->m_p_device->Get_CommandBuffer());

	this->m_is_inside_render_pass = false;
}

void ktkRenderFramePassContext::Set_Pipeline(
	Core::ktkRenderGeometryPipelineHandle pipeline)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Pipeline outside a render pass — ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Pipeline: no geometry manager — ignored");

		return;
	}

	::nri::Pipeline* p_pipeline =
		this->m_p_geometry_manager->Get_NRI_Pipeline(pipeline);

	::nri::PipelineLayout* p_layout =
		this->m_p_geometry_manager->Get_NRI_Pipeline_Layout(pipeline);

	if (p_pipeline == nullptr || p_layout == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Pipeline of an invalid/stale handle ({}) — "
			"ignored", pipeline);

		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdSetPipeline(*this->m_p_device->Get_CommandBuffer(),
		*p_pipeline);

	// the layout bind NRI's root-constant contract requires BEFORE any
	// SetRootConstants (the root-constant index is local in the bound
	// pipeline layout — the validation layer enforces the order)
	core.CmdSetPipelineLayout(*this->m_p_device->Get_CommandBuffer(),
		::nri::BindPoint::GRAPHICS, *p_layout);
}

void ktkRenderFramePassContext::Set_Push_Constants(const void* p_data,
	kun_ktk uint32_t size_bytes)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Push_Constants outside a render pass — "
			"ignored");

		return;
	}

	if (p_data == nullptr || size_bytes == 0)
		return;

	// the range 0 root-constant block, both graphics stages
	::nri::SetRootConstantsDesc constants{};
	constants.rootConstantIndex = 0;
	constants.data = p_data;
	constants.size = size_bytes;
	constants.offset = 0;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdSetRootConstants(*this->m_p_device->Get_CommandBuffer(),
		constants);
}

void ktkRenderFramePassContext::Set_Vertex_Buffer(
	Core::ktkRenderGeometryBufferHandle buffer,
	kun_ktk uint64_t offset_bytes, kun_ktk uint32_t stride_bytes,
	kun_ktk uint32_t slot)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Vertex_Buffer outside a render pass — "
			"ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr || slot != 0)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Vertex_Buffer: no geometry manager or a slot "
			"({}) the v1 seam does not serve — ignored",
			slot);

		return;
	}

	::nri::Buffer* p_buffer =
		this->m_p_geometry_manager->Get_NRI_Buffer(buffer);

	if (p_buffer == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Vertex_Buffer of an invalid/stale handle ({}) "
			"— ignored", buffer);

		return;
	}

	::nri::VertexBufferDesc vertex_buffer{};
	vertex_buffer.buffer = p_buffer;
	vertex_buffer.offset = offset_bytes;
	vertex_buffer.stride = stride_bytes;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdSetVertexBuffers(*this->m_p_device->Get_CommandBuffer(), slot,
		&vertex_buffer, 1);
}

void ktkRenderFramePassContext::Set_Index_Buffer(
	Core::ktkRenderGeometryBufferHandle buffer,
	kun_ktk uint64_t offset_bytes,
	Core::eRenderGeometryIndexFormat format)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Index_Buffer outside a render pass — ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Index_Buffer: no geometry manager — ignored");

		return;
	}

	::nri::Buffer* p_buffer =
		this->m_p_geometry_manager->Get_NRI_Buffer(buffer);

	if (p_buffer == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Index_Buffer of an invalid/stale handle ({}) "
			"— ignored", buffer);

		return;
	}

	::nri::IndexType index_type = ::nri::IndexType::UINT32;

	if (format == Core::eRenderGeometryIndexFormat::kUint16)
		index_type = ::nri::IndexType::UINT16;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdSetIndexBuffer(*this->m_p_device->Get_CommandBuffer(),
		*p_buffer, offset_bytes, index_type);
}

void ktkRenderFramePassContext::Draw_Indexed(
	kun_ktk uint32_t index_count, kun_ktk uint32_t instance_count,
	kun_ktk uint32_t first_index, kun_ktk int32_t vertex_offset,
	kun_ktk uint32_t first_instance)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Draw_Indexed outside a render pass — ignored");

		return;
	}

	::nri::DrawIndexedDesc draw{};
	draw.indexNum = index_count;
	draw.instanceNum = instance_count;
	draw.baseIndex = first_index;
	draw.baseVertex = vertex_offset;
	draw.baseInstance = first_instance;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdDrawIndexed(*this->m_p_device->Get_CommandBuffer(), draw);
}

kun_ktk uint32_t ktkRenderFramePassContext::Get_Back_Buffer_Width(
	void) const
{
	return this->m_width;
}

kun_ktk uint32_t ktkRenderFramePassContext::Get_Back_Buffer_Height(
	void) const
{
	return this->m_height;
}

bool ktkRenderFramePassContext::is_inside_render_pass(void) const noexcept
{
	return this->m_is_inside_render_pass;
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
