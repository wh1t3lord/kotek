#include "../include/kotek_render_frame_pass_context.h"
#include "../include/kotek_render_geometry_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

namespace
{
	/// \~english the seam barrier enums -> NRI bits (task K11 phase 4 /
	/// zircon Z24 B3c); the unmapped seam value is a programmer error —
	/// assert + the safe NONE umbrella
	::nri::AccessBits map_barrier_access(
		Core::eRenderGeometryBarrierAccess access) noexcept
	{
		using eAccess = Core::eRenderGeometryBarrierAccess;

		switch (access)
		{
		case eAccess::kNone:
			return ::nri::AccessBits::NONE;
		case eAccess::kStorage:
			return ::nri::AccessBits::SHADER_RESOURCE_STORAGE;
		case eAccess::kIndirectArgument:
			return ::nri::AccessBits::ARGUMENT_BUFFER;
		case eAccess::kCopySource:
			return ::nri::AccessBits::COPY_SOURCE;
		case eAccess::kCopyDestination:
			return ::nri::AccessBits::COPY_DESTINATION;
		default:
			break;
		}

		KOTEK_ASSERT(false, "unknown barrier access {}",
			static_cast<int>(access));

		return ::nri::AccessBits::NONE;
	}

	::nri::StageBits map_barrier_stage(
		Core::eRenderGeometryBarrierStage stage) noexcept
	{
		using eStage = Core::eRenderGeometryBarrierStage;

		switch (stage)
		{
		case eStage::kNone:
			return ::nri::StageBits::NONE;
		case eStage::kCompute:
			return ::nri::StageBits::COMPUTE_SHADER;
		case eStage::kCopy:
			return ::nri::StageBits::COPY;
		case eStage::kIndirect:
			return ::nri::StageBits::INDIRECT;
		case eStage::kAll:
			return ::nri::StageBits::ALL;
		default:
			break;
		}

		KOTEK_ASSERT(false, "unknown barrier stage {}",
			static_cast<int>(stage));

		return ::nri::StageBits::ALL;
	}
} // namespace

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

void ktkRenderFramePassContext::Set_Compute_Pipeline(
	Core::ktkRenderGeometryPipelineHandle pipeline)
{
	if (this->is_inside_render_pass())
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Pipeline inside a render pass — ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Pipeline: no geometry manager — ignored");

		return;
	}

	::nri::Pipeline* p_pipeline =
		this->m_p_geometry_manager->Get_NRI_Pipeline(pipeline);

	::nri::PipelineLayout* p_layout =
		this->m_p_geometry_manager->Get_NRI_Pipeline_Layout(pipeline);

	if (p_pipeline == nullptr || p_layout == nullptr ||
		this->m_p_geometry_manager->Is_Compute_Pipeline(pipeline) ==
			false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Pipeline of an invalid/stale/graphics "
			"handle ({}) — ignored", pipeline);

		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	// the descriptor tables the dispatches bind live in the manager
	// pool's GPU-visible heap — the swapchain began this command list
	// WITHOUT a pool (the graphics passes need none), so the compute
	// segment binds it explicitly before the first table reference
	// (D3D12 requires SetDescriptorHeaps on the list)
	if (::nri::DescriptorPool* p_pool =
			this->m_p_geometry_manager->Get_NRI_Descriptor_Pool())
	{
		core.CmdSetDescriptorPool(*this->m_p_device->Get_CommandBuffer(),
			*p_pool);
	}

	core.CmdSetPipeline(*this->m_p_device->Get_CommandBuffer(),
		*p_pipeline);

	// the same layout-first contract as the graphics bind (NRI's
	// validation requires CmdSetPipelineLayout before any root
	// constants), at the COMPUTE bind point
	core.CmdSetPipelineLayout(*this->m_p_device->Get_CommandBuffer(),
		::nri::BindPoint::COMPUTE, *p_layout);

	this->m_bound_compute_pipeline = pipeline;
}

void ktkRenderFramePassContext::Set_Compute_Storage_Buffer(
	kun_ktk uint32_t binding_index,
	Core::ktkRenderGeometryBufferHandle buffer,
	kun_ktk uint64_t offset_bytes, kun_ktk uint64_t size_bytes)
{
	if (this->is_inside_render_pass())
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Storage_Buffer inside a render pass — "
			"ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr ||
		this->m_bound_compute_pipeline ==
			Core::kInvalidRenderGeometryPipelineHandle)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Storage_Buffer: no compute pipeline bound "
			"— ignored");

		return;
	}

	::nri::Buffer* p_buffer =
		this->m_p_geometry_manager->Get_NRI_Buffer(buffer);

	if (p_buffer == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Storage_Buffer of an invalid/stale "
			"buffer handle ({}) — ignored", buffer);

		return;
	}

	if (this->m_p_geometry_manager->Is_Buffer_Range_Valid(
			buffer, offset_bytes, size_bytes) == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Storage_Buffer range ({} + {} B) does "
			"not fit the buffer — ignored", offset_bytes, size_bytes);

		return;
	}

	const Core::ktkRenderGeometryPipelineHandle pipeline =
		this->m_bound_compute_pipeline;

	// the change-detecting bookkeeping: an unchanged binding keeps its
	// live view (a Descriptor owns a descriptor handle — recreating it
	// per frame would leak)
	if (this->m_p_geometry_manager->Update_Compute_Binding(pipeline,
			binding_index, buffer, offset_bytes, size_bytes) == false)
	{
		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	// the old view dies BEFORE the new one is created (the slot hands it
	// out one last time)
	if (void* p_old_view =
			this->m_p_geometry_manager->Get_Compute_Binding_View(pipeline,
				binding_index))
	{
		core.DestroyDescriptor(
			static_cast<::nri::Descriptor*>(p_old_view));
	}

	// the byte-address view: the READ-ONLY binding gets the SRV form
	// (host-uploaded memory stays legal), the read-write the UAV form
	// (GPU-local only — the D3D12 upload-heap UAV rule)
	const bool is_read_only =
		this->m_p_geometry_manager->Is_Compute_Binding_Read_Only(
			pipeline, binding_index);

	::nri::BufferViewDesc view_desc{};
	view_desc.buffer = p_buffer;
	view_desc.type = is_read_only
		? ::nri::BufferView::BYTE_ADDRESS_BUFFER
		: ::nri::BufferView::STORAGE_BYTE_ADDRESS_BUFFER;
	view_desc.offset = offset_bytes;
	view_desc.size = size_bytes;

	::nri::Descriptor* p_view = nullptr;
	::nri::Result result = core.CreateBufferView(view_desc, p_view);

	if (result != ::nri::Result::SUCCESS || p_view == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Storage_Buffer view creation failed, "
			"result={} — the binding stays unbound",
			static_cast<int>(result));

		return;
	}

	this->m_p_geometry_manager->Set_Compute_Binding_View(
		pipeline, binding_index, p_view);

	// the descriptor set update (legal until the submit — NRI's update
	// contract; the set is bound at Dispatch)
	::nri::Descriptor* p_view_for_update = p_view;

	::nri::UpdateDescriptorRangeDesc update{};
	update.descriptorSet =
		this->m_p_geometry_manager->Get_NRI_Compute_Descriptor_Set(
			pipeline);
	update.rangeIndex = binding_index;
	update.baseDescriptor = 0;
	update.descriptors = &p_view_for_update;
	update.descriptorNum = 1;

	core.UpdateDescriptorRanges(&update, 1);
}

void ktkRenderFramePassContext::Set_Compute_Push_Constants(
	const void* p_data, kun_ktk uint32_t size_bytes)
{
	if (this->is_inside_render_pass())
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Push_Constants inside a render pass — "
			"ignored");

		return;
	}

	if (this->m_bound_compute_pipeline ==
		Core::kInvalidRenderGeometryPipelineHandle)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Set_Compute_Push_Constants: no compute pipeline "
			"bound — ignored");

		return;
	}

	if (p_data == nullptr || size_bytes == 0)
		return;

	// the range 0 root-constant block, the compute stage
	::nri::SetRootConstantsDesc constants{};
	constants.rootConstantIndex = 0;
	constants.data = p_data;
	constants.size = size_bytes;
	constants.offset = 0;
	constants.bindPoint = ::nri::BindPoint::COMPUTE;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdSetRootConstants(*this->m_p_device->Get_CommandBuffer(),
		constants);
}

void ktkRenderFramePassContext::Dispatch(kun_ktk uint32_t group_count_x,
	kun_ktk uint32_t group_count_y, kun_ktk uint32_t group_count_z)
{
	if (this->is_inside_render_pass())
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Dispatch inside a render pass — ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr ||
		this->m_bound_compute_pipeline ==
			Core::kInvalidRenderGeometryPipelineHandle)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Dispatch: no compute pipeline bound — ignored");

		return;
	}

	if (this->m_p_geometry_manager->Is_Compute_Binding_Complete(
			this->m_bound_compute_pipeline) == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Dispatch: the compute pipeline's storage bindings are "
			"incomplete — ignored (a kernel reading an unbound slot must "
			"never record)");

		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	// the pipeline's descriptor set at the compute bind point, then the
	// dispatch
	::nri::SetDescriptorSetDesc set_desc{};
	set_desc.setIndex = 0;
	set_desc.descriptorSet =
		this->m_p_geometry_manager->Get_NRI_Compute_Descriptor_Set(
			this->m_bound_compute_pipeline);
	set_desc.bindPoint = ::nri::BindPoint::COMPUTE;

	core.CmdSetDescriptorSet(*this->m_p_device->Get_CommandBuffer(),
		set_desc);

	::nri::DispatchDesc dispatch{};
	dispatch.x = group_count_x;
	dispatch.y = group_count_y;
	dispatch.z = group_count_z;

	core.CmdDispatch(*this->m_p_device->Get_CommandBuffer(), dispatch);
}

void ktkRenderFramePassContext::Barrier_Buffer(
	Core::ktkRenderGeometryBufferHandle buffer,
	Core::eRenderGeometryBarrierAccess before_access,
	Core::eRenderGeometryBarrierAccess after_access,
	Core::eRenderGeometryBarrierStage before_stage,
	Core::eRenderGeometryBarrierStage after_stage)
{
	if (this->is_inside_render_pass())
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Barrier_Buffer inside a render pass — ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Barrier_Buffer: no geometry manager — ignored");

		return;
	}

	::nri::Buffer* p_buffer =
		this->m_p_geometry_manager->Get_NRI_Buffer(buffer);

	if (p_buffer == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Barrier_Buffer of an invalid/stale handle ({}) — "
			"ignored", buffer);

		return;
	}

	::nri::BufferBarrierDesc buffer_barrier{};
	buffer_barrier.buffer = p_buffer;
	buffer_barrier.before.access = map_barrier_access(before_access);
	buffer_barrier.before.stages = map_barrier_stage(before_stage);
	buffer_barrier.after.access = map_barrier_access(after_access);
	buffer_barrier.after.stages = map_barrier_stage(after_stage);

	::nri::BarrierDesc barrier{};
	barrier.buffers = &buffer_barrier;
	barrier.bufferNum = 1;

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdBarrier(*this->m_p_device->Get_CommandBuffer(), barrier);
}

void ktkRenderFramePassContext::Copy_Buffer(
	Core::ktkRenderGeometryBufferHandle dst_buffer,
	kun_ktk uint64_t dst_offset, Core::ktkRenderGeometryBufferHandle src_buffer,
	kun_ktk uint64_t src_offset, kun_ktk uint64_t size_bytes)
{
	if (this->is_inside_render_pass())
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Copy_Buffer inside a render pass — ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr || size_bytes == 0)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Copy_Buffer: no geometry manager or a zero size — "
			"ignored");

		return;
	}

	::nri::Buffer* p_dst =
		this->m_p_geometry_manager->Get_NRI_Buffer(dst_buffer);

	::nri::Buffer* p_src =
		this->m_p_geometry_manager->Get_NRI_Buffer(src_buffer);

	if (p_dst == nullptr || p_src == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Copy_Buffer of an invalid/stale handle (dst {}, src "
			"{}), ignored", dst_buffer, src_buffer);

		return;
	}

	if (this->m_p_geometry_manager->Is_Buffer_Range_Valid(dst_buffer,
			dst_offset, size_bytes) == false ||
		this->m_p_geometry_manager->Is_Buffer_Range_Valid(src_buffer,
			src_offset, size_bytes) == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Copy_Buffer range ({} + {} B) does not fit the "
			"buffers — ignored", src_offset, size_bytes);

		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdCopyBuffer(*this->m_p_device->Get_CommandBuffer(), *p_dst,
		dst_offset, *p_src, src_offset, size_bytes);
}

void ktkRenderFramePassContext::Draw_Indexed_Indirect(
	Core::ktkRenderGeometryBufferHandle buffer,
	kun_ktk uint64_t offset_bytes, kun_ktk uint32_t max_draw_count,
	kun_ktk uint32_t stride_bytes,
	Core::ktkRenderGeometryBufferHandle count_buffer,
	kun_ktk uint64_t count_buffer_offset_bytes)
{
	if (this->is_inside_render_pass() == false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Draw_Indexed_Indirect outside a render pass — "
			"ignored");

		return;
	}

	if (this->m_p_geometry_manager == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Draw_Indexed_Indirect: no geometry manager — "
			"ignored");

		return;
	}

	::nri::Buffer* p_buffer =
		this->m_p_geometry_manager->Get_NRI_Buffer(buffer);

	::nri::Buffer* p_count_buffer =
		this->m_p_geometry_manager->Get_NRI_Buffer(count_buffer);

	if (p_buffer == nullptr || p_count_buffer == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] Draw_Indexed_Indirect of an invalid/stale handle "
			"(buffer {}, count {}) — ignored", buffer, count_buffer);

		return;
	}

	const ::nri::CoreInterface& core = this->m_p_device->Get_CoreInterface();

	core.CmdDrawIndexedIndirect(*this->m_p_device->Get_CommandBuffer(),
		*p_buffer, offset_bytes, max_draw_count, stride_bytes,
		p_count_buffer, count_buffer_offset_bytes);
}

bool ktkRenderFramePassContext::is_inside_render_pass(void) const noexcept
{
	return this->m_is_inside_render_pass;
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
