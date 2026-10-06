#include "../include/kotek_render_geometry_manager.h"

#include <cstring>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

namespace
{
	/// \~english the seam usage bits -> NRI buffer usage bits
	::nri::BufferUsageBits map_buffer_usage(
		Core::eRenderGeometryBufferUsage usage) noexcept
	{
		using eUsage = Core::eRenderGeometryBufferUsage;

		::nri::BufferUsageBits result = ::nri::BufferUsageBits::NONE;

		if ((usage & eUsage::kVertex) == eUsage::kVertex)
			result |= ::nri::BufferUsageBits::VERTEX_BUFFER;

		if ((usage & eUsage::kIndex) == eUsage::kIndex)
			result |= ::nri::BufferUsageBits::INDEX_BUFFER;

		if ((usage & eUsage::kConstant) == eUsage::kConstant)
			result |= ::nri::BufferUsageBits::CONSTANT_BUFFER;

		if ((usage & eUsage::kStorage) == eUsage::kStorage)
			result |= ::nri::BufferUsageBits::SHADER_RESOURCE_STORAGE;

		if ((usage & eUsage::kIndirect) == eUsage::kIndirect)
			result |= ::nri::BufferUsageBits::ARGUMENT_BUFFER;

		if ((usage & eUsage::kShaderRead) == eUsage::kShaderRead)
			result |= ::nri::BufferUsageBits::SHADER_RESOURCE;

		return result;
	}

	/// \~english the seam buffer memory location: readback heap when the
	/// caller asked for kReadback, GPU-local when kDevice (the UAV
	/// discipline — D3D12 forbids unordered access on upload heaps, and
	/// device-local memory is not CPU-mappable so Upload/Read_Buffer are
	/// invalid there), upload heap otherwise (the B3b Upload_Buffer
	/// contract)
	::nri::MemoryLocation select_memory_location(
		Core::eRenderGeometryBufferUsage usage) noexcept
	{
		using eUsage = Core::eRenderGeometryBufferUsage;

		if ((usage & eUsage::kReadback) == eUsage::kReadback)
			return ::nri::MemoryLocation::HOST_READBACK;

		if ((usage & eUsage::kDevice) == eUsage::kDevice)
			return ::nri::MemoryLocation::DEVICE;

		return ::nri::MemoryLocation::HOST_UPLOAD;
	}

	/// \~english the seam vertex formats -> NRI formats (v1 set)
	::nri::Format map_vertex_format(
		Core::eRenderGeometryVertexFormat format) noexcept
	{
		switch (format)
		{
		case Core::eRenderGeometryVertexFormat::kFloat3:
			return ::nri::Format::RGB32_SFLOAT;
		case Core::eRenderGeometryVertexFormat::kFloat4:
			return ::nri::Format::RGBA32_SFLOAT;
		default:
			break;
		}

		KOTEK_ASSERT(false, "unknown vertex attribute format {}",
			static_cast<int>(format));

		return ::nri::Format::RGB32_SFLOAT;
	}

	/// \~english the seam color formats -> NRI formats (v1 set)
	::nri::Format map_color_format(
		Core::eRenderGeometryColorFormat format) noexcept
	{
		switch (format)
		{
		case Core::eRenderGeometryColorFormat::kRGBA8Unorm:
			return ::nri::Format::RGBA8_UNORM;
		default:
			break;
		}

		KOTEK_ASSERT(false, "unknown color attachment format {}",
			static_cast<int>(format));

		return ::nri::Format::RGBA8_UNORM;
	}
} // namespace

ktkRenderGeometryManager::ktkRenderGeometryManager(void) {}

ktkRenderGeometryManager::~ktkRenderGeometryManager(void)
{
	// Shutdown is the lifecycle, but a manager that dies without one (a
	// failed module init) must not strand table state — the slots are POD,
	// nothing here touches the GPU
}

void ktkRenderGeometryManager::Initialize(
	Core::ktkIRenderDevice* p_render_device)
{
	this->m_p_device =
		dynamic_cast<ktkRenderDevice*>(p_render_device);

	KOTEK_ASSERT(this->m_p_device,
		"the NRI geometry manager must initialize with "
		"nri::ktkRenderDevice");
}

void ktkRenderGeometryManager::Shutdown(void)
{
	// the caller guarantees the GPU is idle (module shutdown order) —
	// release whatever is still live, slot by slot
	const ::nri::CoreInterface& core =
		this->m_p_device->Get_CoreInterface();

	const ktkRenderGeometrySlot* p_pipeline_slots =
		this->m_pipelines.get_slots();

	for (kun_ktk uint32_t index = 0;
		 index < KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES; ++index)
	{
		const ktkRenderGeometrySlot& slot = p_pipeline_slots[index];

		// the compute side state: the binding views (descriptors) die with
		// the pipeline (the descriptor set itself belongs to the pool,
		// wiped below)
		ktkRenderComputePipelineState& compute_state =
			this->m_compute_states[index];

		for (kun_ktk uint32_t binding = 0;
			 binding < k_max_compute_bindings; ++binding)
		{
			if (compute_state.m_p_views[binding])
			{
				core.DestroyDescriptor(
					static_cast<::nri::Descriptor*>(
						compute_state.m_p_views[binding]));
				compute_state.m_p_views[binding] = nullptr;
			}
		}

		compute_state.m_bindings.clear();
		compute_state.m_p_set = nullptr;
		compute_state.m_read_only_mask = 0u;
		compute_state.m_binding_count = 0u;

		if (slot.m_is_alive == false)
			continue;

		if (slot.m_p_object)
			core.DestroyPipeline(
				static_cast<::nri::Pipeline*>(slot.m_p_object));

		if (slot.m_p_aux)
			core.DestroyPipelineLayout(
				static_cast<::nri::PipelineLayout*>(slot.m_p_aux));
	}

	const ktkRenderGeometrySlot* p_buffer_slots =
		this->m_buffers.get_slots();

	for (kun_ktk uint32_t index = 0;
		 index < KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_BUFFERS; ++index)
	{
		const ktkRenderGeometrySlot& slot = p_buffer_slots[index];

		if (slot.m_is_alive == false)
			continue;

		if (slot.m_p_object)
			core.DestroyBuffer(
				static_cast<::nri::Buffer*>(slot.m_p_object));

		if (slot.m_p_aux)
			core.FreeMemory(
				static_cast<::nri::Memory*>(slot.m_p_aux));
	}

	if (this->m_p_descriptor_pool)
	{
		core.DestroyDescriptorPool(this->m_p_descriptor_pool);
		this->m_p_descriptor_pool = nullptr;
	}

	this->m_p_device = nullptr;
}

Core::ktkRenderGeometryBufferHandle
	ktkRenderGeometryManager::Create_Buffer(kun_ktk uint64_t size_bytes,
		Core::eRenderGeometryBufferUsage usage)
{
	if (this->m_p_device == nullptr || size_bytes == 0)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Create_Buffer: no device or a zero size — "
			"invalid handle returned");

		return Core::kInvalidRenderGeometryBufferHandle;
	}

	const ::nri::CoreInterface& core =
		this->m_p_device->Get_CoreInterface();

	::nri::BufferDesc buffer_desc{};
	buffer_desc.size = size_bytes;
	buffer_desc.structureStride = 0;
	buffer_desc.usage = map_buffer_usage(usage);

	::nri::Buffer* p_buffer = nullptr;
	::nri::Result result =
		core.CreateBuffer(*this->m_p_device->Get_Device(),
			buffer_desc, p_buffer);

	if (result != ::nri::Result::SUCCESS || p_buffer == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Create_Buffer({} B) failed, result={}",
			size_bytes, static_cast<int>(result));

		return Core::kInvalidRenderGeometryBufferHandle;
	}

	// HOST_UPLOAD: the synchronous Upload_Buffer contract (a Map/memcpy
	// straight into GPU-readable upload memory — usable from the next
	// submitted frame, no fence); HOST_READBACK for the kReadback buffers
	// (the Read_Buffer contract — the CPU reads what the GPU wrote)
	::nri::MemoryDesc memory_desc{};
	core.GetBufferMemoryDesc(*p_buffer, select_memory_location(usage),
		memory_desc);
	::nri::AllocateMemoryDesc allocate_desc{};
	allocate_desc.size = memory_desc.size;
	allocate_desc.type = memory_desc.type;

	::nri::Memory* p_memory = nullptr;
	result = core.AllocateMemory(*this->m_p_device->Get_Device(),
		allocate_desc, p_memory);

	if (result != ::nri::Result::SUCCESS || p_memory == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry buffer allocation ({} B) failed, result={}",
			memory_desc.size, static_cast<int>(result));

		core.DestroyBuffer(p_buffer);

		return Core::kInvalidRenderGeometryBufferHandle;
	}

	::nri::BindBufferMemoryDesc bind_desc{};
	bind_desc.buffer = p_buffer;
	bind_desc.memory = p_memory;
	bind_desc.offset = 0;

	result = core.BindBufferMemory(&bind_desc, 1);

	if (result != ::nri::Result::SUCCESS)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry buffer bind failed, result={}",
			static_cast<int>(result));

		core.FreeMemory(p_memory);
		core.DestroyBuffer(p_buffer);

		return Core::kInvalidRenderGeometryBufferHandle;
	}

	const kun_ktk uint32_t handle =
		this->m_buffers.allocate(p_buffer, p_memory, size_bytes);

	if (handle == 0u)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry buffer table is full (capacity {}) — "
			"raise KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_BUFFERS",
			KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_BUFFERS);

		core.FreeMemory(p_memory);
		core.DestroyBuffer(p_buffer);

		return Core::kInvalidRenderGeometryBufferHandle;
	}

	// the memory-location side table (Upload_Buffer / Read_Buffer guard
	// the device-local buffers loudly — GPU-local memory is not
	// CPU-mappable)
	this->m_device_local_buffers[this->m_buffers.slot_index(handle)] =
		select_memory_location(usage) == ::nri::MemoryLocation::DEVICE;

	return handle;
}

void ktkRenderGeometryManager::Destroy_Buffer(
	Core::ktkRenderGeometryBufferHandle handle)
{
	ktkRenderGeometrySlot* p_slot = this->m_buffers.resolve(handle);

	if (p_slot == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Destroy_Buffer of an invalid/stale handle "
			"({}) — ignored", handle);

		return;
	}

	if (this->m_p_device)
	{
		const ::nri::CoreInterface& core =
			this->m_p_device->Get_CoreInterface();

		if (p_slot->m_p_object)
			core.DestroyBuffer(
				static_cast<::nri::Buffer*>(p_slot->m_p_object));

		if (p_slot->m_p_aux)
			core.FreeMemory(
				static_cast<::nri::Memory*>(p_slot->m_p_aux));
	}

	this->m_device_local_buffers[
		this->m_buffers.slot_index(handle)] = false;

	this->m_buffers.free(handle);
}

bool ktkRenderGeometryManager::Upload_Buffer(
	Core::ktkRenderGeometryBufferHandle handle,
	kun_ktk uint64_t offset_bytes, const void* p_bytes,
	kun_ktk uint64_t size_bytes)
{
	if (p_bytes == nullptr || size_bytes == 0)
		return false;

	ktkRenderGeometrySlot* p_slot =
		this->m_buffers.resolve(handle);

	if (p_slot == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Upload_Buffer of an invalid/stale handle "
			"({}) — ignored", handle);

		return false;
	}

	if (this->m_device_local_buffers[this->m_buffers.slot_index(handle)])
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Upload_Buffer of a DEVICE-LOCAL buffer ({}) "
			"— GPU-local memory is not CPU-mappable, ignored", handle);

		return false;
	}

	if (this->m_buffers.is_range_valid(handle, offset_bytes, size_bytes) ==
		false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Upload_Buffer range ({} + {} of {} B) does "
			"not fit the buffer — ignored",
			offset_bytes, size_bytes, p_slot->m_size_bytes);

		return false;
	}

	const ::nri::CoreInterface& core =
		this->m_p_device->Get_CoreInterface();

	void* p_destination = core.MapBuffer(
		*static_cast<::nri::Buffer*>(p_slot->m_p_object), offset_bytes,
		size_bytes);

	if (p_destination == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Upload_Buffer map failed ({} + {} B)",
			offset_bytes, size_bytes);

		return false;
	}

	std::memcpy(p_destination, p_bytes, size_bytes);
	core.UnmapBuffer(*static_cast<::nri::Buffer*>(p_slot->m_p_object));

	return true;
}

Core::ktkRenderGeometryPipelineHandle
	ktkRenderGeometryManager::Create_Pipeline(
		const Core::ktkRenderGeometryPipelineDesc& desc)
{
	if (this->m_p_device == nullptr || desc.m_p_attributes == nullptr ||
		desc.m_attribute_count == 0 ||
		desc.m_attribute_count > k_max_vertex_attributes ||
		desc.m_vertex_shader.m_p_bytecode == nullptr ||
		desc.m_vertex_shader.m_size_bytes == 0 ||
		desc.m_pixel_shader.m_p_bytecode == nullptr ||
		desc.m_pixel_shader.m_size_bytes == 0)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Create_Pipeline: invalid description — "
			"invalid handle returned");

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	if ((desc.m_push_constant_bytes % 4u) != 0u ||
		desc.m_push_constant_bytes > 256u)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Create_Pipeline: push_constant_bytes {} "
			"must be a multiple of 4 and <= 256 — invalid handle "
			"returned", desc.m_push_constant_bytes);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	const ::nri::CoreInterface& core =
		this->m_p_device->Get_CoreInterface();
	::nri::Device* p_device = this->m_p_device->Get_Device();

	// the pipeline layout: the one optional root-constant (push-constant)
	// range at register(b0), visible to both graphics stages
	::nri::RootConstantDesc root_constants[1]{};
	root_constants[0].registerIndex = 0;
	root_constants[0].size = desc.m_push_constant_bytes;
	root_constants[0].shaderStages = ::nri::StageBits::VERTEX_SHADER |
		::nri::StageBits::FRAGMENT_SHADER;

	::nri::PipelineLayoutDesc layout_desc{};
	layout_desc.rootRegisterSpace = 0;
	layout_desc.rootConstants =
		desc.m_push_constant_bytes ? root_constants : nullptr;
	layout_desc.rootConstantNum =
		desc.m_push_constant_bytes ? 1u : 0u;
	layout_desc.shaderStages = ::nri::StageBits::VERTEX_SHADER |
		::nri::StageBits::FRAGMENT_SHADER;

	::nri::PipelineLayout* p_layout = nullptr;
	::nri::Result result =
		core.CreatePipelineLayout(*p_device, layout_desc, p_layout);

	if (result != ::nri::Result::SUCCESS || p_layout == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry CreatePipelineLayout failed, result={}",
			static_cast<int>(result));

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	// the vertex input: the caller's attributes over the single
	// interleaved stream
	::nri::VertexAttributeDesc
		attributes[k_max_vertex_attributes]{};

	for (kun_ktk uint32_t index = 0; index < desc.m_attribute_count;
		 ++index)
	{
		const Core::ktkRenderGeometryVertexAttributeDesc& source =
			desc.m_p_attributes[index];

		attributes[index].d3d.semanticName = source.m_p_semantic_name;
		attributes[index].d3d.semanticIndex =
			source.m_semantic_index;
		attributes[index].vk.location = index;
		attributes[index].offset = source.m_offset_bytes;
		attributes[index].format =
			map_vertex_format(source.m_format);
		attributes[index].streamIndex = 0;
	}

	::nri::VertexStreamDesc stream_desc{};
	stream_desc.bindingSlot = 0;
	stream_desc.stepRate = ::nri::VertexStreamStepRate::PER_VERTEX;
	stream_desc.stride =
		static_cast<uint16_t>(desc.m_vertex_stride_bytes);

	::nri::InputAssemblyDesc input_assembly{};
	input_assembly.topology = ::nri::Topology::TRIANGLE_LIST;
	input_assembly.tessControlPointNum = 0;
	input_assembly.primitiveRestart = ::nri::PrimitiveRestart::DISABLED;

	::nri::RasterizationDesc rasterization{};
	rasterization.fillMode = ::nri::FillMode::SOLID;
	// v1 draws WITHOUT culling (task Z24 B3b scope: culling is B3c's)
	rasterization.cullMode = ::nri::CullMode::NONE;
	rasterization.frontCounterClockwise = true;

	::nri::ColorAttachmentDesc color_attachment{};
	color_attachment.format = map_color_format(desc.m_color_format);
	color_attachment.colorBlend = ::nri::BlendDesc{};
	color_attachment.alphaBlend = ::nri::BlendDesc{};
	color_attachment.colorWriteMask = ::nri::ColorWriteBits::RGBA;
	color_attachment.blendEnabled = false;

	::nri::OutputMergerDesc output_merger{};
	output_merger.colors = &color_attachment;
	output_merger.colorNum = 1;

	::nri::ShaderDesc shaders[2]{};
	shaders[0].stage = ::nri::StageBits::VERTEX_SHADER;
	shaders[0].bytecode = desc.m_vertex_shader.m_p_bytecode;
	shaders[0].size = desc.m_vertex_shader.m_size_bytes;
	shaders[0].entryPointName = desc.m_vertex_shader.m_p_entry_point;

	shaders[1].stage = ::nri::StageBits::FRAGMENT_SHADER;
	shaders[1].bytecode = desc.m_pixel_shader.m_p_bytecode;
	shaders[1].size = desc.m_pixel_shader.m_size_bytes;
	shaders[1].entryPointName = desc.m_pixel_shader.m_p_entry_point;

	::nri::VertexInputDesc vertex_input{};
	vertex_input.attributes = attributes;
	vertex_input.attributeNum =
		static_cast<uint8_t>(desc.m_attribute_count);
	vertex_input.streams = &stream_desc;
	vertex_input.streamNum = 1;

	::nri::GraphicsPipelineDesc pipeline_desc{};
	pipeline_desc.pipelineLayout = p_layout;
	pipeline_desc.vertexInput = &vertex_input;
	pipeline_desc.inputAssembly = input_assembly;
	pipeline_desc.rasterization = rasterization;
	pipeline_desc.outputMerger = output_merger;
	pipeline_desc.shaders = shaders;
	pipeline_desc.shaderNum = 2;
	pipeline_desc.flags = ::nri::GraphicsPipelineBits::NONE;
	pipeline_desc.robustness = ::nri::Robustness::DEFAULT;

	::nri::Pipeline* p_pipeline = nullptr;
	result = core.CreateGraphicsPipeline(
		*p_device, pipeline_desc, p_pipeline);

	if (result != ::nri::Result::SUCCESS || p_pipeline == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry CreateGraphicsPipeline failed, result={}",
			static_cast<int>(result));

		core.DestroyPipelineLayout(p_layout);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	const kun_ktk uint32_t handle = this->m_pipelines.allocate(
		p_pipeline, p_layout, desc.m_push_constant_bytes);

	if (handle == 0u)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry pipeline table is full (capacity {}) — "
			"raise KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES",
			KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES);

		core.DestroyPipeline(p_pipeline);
		core.DestroyPipelineLayout(p_layout);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	return handle;
}

void ktkRenderGeometryManager::Destroy_Pipeline(
	Core::ktkRenderGeometryPipelineHandle handle)
{
	ktkRenderGeometrySlot* p_slot = this->m_pipelines.resolve(handle);

	if (p_slot == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Destroy_Pipeline of an invalid/stale handle "
			"({}) — ignored", handle);

		return;
	}

	if (this->m_p_device)
	{
		const ::nri::CoreInterface& core =
			this->m_p_device->Get_CoreInterface();

		if (p_slot->m_p_object)
			core.DestroyPipeline(
				static_cast<::nri::Pipeline*>(p_slot->m_p_object));

		if (p_slot->m_p_aux)
			core.DestroyPipelineLayout(
				static_cast<::nri::PipelineLayout*>(p_slot->m_p_aux));

		// the compute side state (task K11 phase 4): the binding views
		// die with the pipeline
		ktkRenderComputePipelineState& compute_state =
			this->m_compute_states[
				this->m_pipelines.slot_index(handle)];

		for (kun_ktk uint32_t binding = 0;
			 binding < k_max_compute_bindings; ++binding)
		{
			if (compute_state.m_p_views[binding])
			{
				core.DestroyDescriptor(
					static_cast<::nri::Descriptor*>(
						compute_state.m_p_views[binding]));
				compute_state.m_p_views[binding] = nullptr;
			}
		}

		compute_state.m_bindings.clear();
		compute_state.m_p_set = nullptr;
		compute_state.m_read_only_mask = 0u;
		compute_state.m_binding_count = 0u;
	}

	this->m_pipelines.free(handle);
}

Core::ktkRenderGeometryPipelineHandle
	ktkRenderGeometryManager::Create_Compute_Pipeline(
		const Core::ktkRenderGeometryComputePipelineDesc& desc)
{
	if (this->m_p_device == nullptr ||
		desc.m_compute_shader.m_p_bytecode == nullptr ||
		desc.m_compute_shader.m_size_bytes == 0 ||
		desc.m_storage_buffer_count == 0u ||
		desc.m_storage_buffer_count > k_max_compute_bindings)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Create_Compute_Pipeline: invalid description "
			"(device/shape/bindings {}) — invalid handle returned",
			desc.m_storage_buffer_count);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	if ((desc.m_push_constant_bytes % 4u) != 0u ||
		desc.m_push_constant_bytes > 256u)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Create_Compute_Pipeline: push_constant_bytes "
			"{} must be a multiple of 4 and <= 256 — invalid handle "
			"returned", desc.m_push_constant_bytes);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	const ::nri::CoreInterface& core =
		this->m_p_device->Get_CoreInterface();
	::nri::Device* p_device = this->m_p_device->Get_Device();

	// the manager-owned descriptor pool (lazy — created by the first
	// compute pipeline): one descriptor set per pipeline at most, one
	// descriptor per binding — the counters are PER DESCRIPTOR TYPE: the
	// read-only bindings consume 'STRUCTURED_BUFFER' descriptors, the
	// read-write 'STORAGE_STRUCTURED_BUFFER' (both sized for the worst
	// case, all pipelines at the full binding count)
	if (this->m_p_descriptor_pool == nullptr)
	{
		::nri::DescriptorPoolDesc pool_desc{};
		pool_desc.descriptorSetMaxNum =
			KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES;
		pool_desc.structuredBufferMaxNum =
			KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES *
			k_max_compute_bindings;
		pool_desc.storageStructuredBufferMaxNum =
			KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES *
			k_max_compute_bindings;

		::nri::Result result = core.CreateDescriptorPool(*p_device,
			pool_desc, this->m_p_descriptor_pool);

		if (result != ::nri::Result::SUCCESS ||
			this->m_p_descriptor_pool == nullptr)
		{
			KOTEK_MESSAGE_ERROR(
				"[nri] geometry CreateDescriptorPool failed, result={}",
				static_cast<int>(result));

			return Core::kInvalidRenderGeometryPipelineHandle;
		}
	}

	// the pipeline layout: the optional root-constant block at
	// register(b0), the COMPUTE stage only, plus ONE descriptor set
	// (register space 0) with one byte-address range per binding — the
	// READ-ONLY bindings (the desc's mask bit) take the SRV range form
	// (legal on host-uploaded memory), the rest the read-write storage
	// form (GPU-local only — the D3D12 upload-heap UAV rule)
	::nri::RootConstantDesc root_constants[1]{};
	root_constants[0].registerIndex = 0;
	root_constants[0].size = desc.m_push_constant_bytes;
	root_constants[0].shaderStages = ::nri::StageBits::COMPUTE_SHADER;

	::nri::DescriptorRangeDesc
		ranges[k_max_compute_bindings]{};

	// the register counters are PER TYPE CLASS: the read-only bindings
	// occupy the t registers (the SRV descriptor table), the read-write
	// ones the u registers (the UAV table) — the shader declares
	// t0/u0/u1, NRI builds one root table per class from these ranges
	kun_ktk uint32_t srv_register = 0;
	kun_ktk uint32_t uav_register = 0;

	for (kun_ktk uint32_t binding = 0;
		 binding < desc.m_storage_buffer_count; ++binding)
	{
		const bool is_read_only =
			(desc.m_read_only_storage_mask & (1u << binding)) != 0u;

		ranges[binding].baseRegisterIndex = is_read_only
			? srv_register++
			: uav_register++;
		ranges[binding].descriptorNum = 1;
		ranges[binding].descriptorType = is_read_only
			? ::nri::DescriptorType::STRUCTURED_BUFFER
			: ::nri::DescriptorType::STORAGE_STRUCTURED_BUFFER;
		ranges[binding].shaderStages = ::nri::StageBits::COMPUTE_SHADER;
	}

	::nri::DescriptorSetDesc set_desc{};
	set_desc.registerSpace = 0;
	set_desc.ranges = ranges;
	set_desc.rangeNum = desc.m_storage_buffer_count;

	::nri::PipelineLayoutDesc layout_desc{};
	layout_desc.rootRegisterSpace = 0;
	layout_desc.rootConstants =
		desc.m_push_constant_bytes ? root_constants : nullptr;
	layout_desc.rootConstantNum =
		desc.m_push_constant_bytes ? 1u : 0u;
	layout_desc.descriptorSets = &set_desc;
	layout_desc.descriptorSetNum = 1;
	layout_desc.shaderStages = ::nri::StageBits::COMPUTE_SHADER;

	::nri::PipelineLayout* p_layout = nullptr;
	::nri::Result result =
		core.CreatePipelineLayout(*p_device, layout_desc, p_layout);

	if (result != ::nri::Result::SUCCESS || p_layout == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry CreatePipelineLayout (compute) failed, "
			"result={}", static_cast<int>(result));

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	::nri::ShaderDesc shader{};
	shader.stage = ::nri::StageBits::COMPUTE_SHADER;
	shader.bytecode = desc.m_compute_shader.m_p_bytecode;
	shader.size = desc.m_compute_shader.m_size_bytes;
	shader.entryPointName = desc.m_compute_shader.m_p_entry_point;

	::nri::ComputePipelineDesc pipeline_desc{};
	pipeline_desc.pipelineLayout = p_layout;
	pipeline_desc.shader = shader;
	pipeline_desc.flags = ::nri::ComputePipelineBits::NONE;
	pipeline_desc.robustness = ::nri::Robustness::DEFAULT;

	::nri::Pipeline* p_pipeline = nullptr;
	result = core.CreateComputePipeline(*p_device, pipeline_desc,
		p_pipeline);

	if (result != ::nri::Result::SUCCESS || p_pipeline == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry CreateComputePipeline failed, result={}",
			static_cast<int>(result));

		core.DestroyPipelineLayout(p_layout);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	const kun_ktk uint32_t handle = this->m_pipelines.allocate(
		p_pipeline, p_layout, desc.m_push_constant_bytes);

	if (handle == 0u)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry pipeline table is full (capacity {}) — "
			"raise KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES",
			KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES);

		core.DestroyPipeline(p_pipeline);
		core.DestroyPipelineLayout(p_layout);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	// the pipeline's descriptor set from the manager pool
	ktkRenderComputePipelineState& compute_state =
		this->m_compute_states[this->m_pipelines.slot_index(handle)];

	compute_state.m_read_only_mask = desc.m_read_only_storage_mask;
	compute_state.m_binding_count = desc.m_storage_buffer_count;

	result = core.AllocateDescriptorSets(*this->m_p_descriptor_pool,
		*p_layout, 0, &compute_state.m_p_set, 1, 0);

	if (result != ::nri::Result::SUCCESS ||
		compute_state.m_p_set == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry AllocateDescriptorSets failed, result={}",
			static_cast<int>(result));

		this->m_pipelines.free(handle);
		core.DestroyPipeline(p_pipeline);
		core.DestroyPipelineLayout(p_layout);

		return Core::kInvalidRenderGeometryPipelineHandle;
	}

	return handle;
}

bool ktkRenderGeometryManager::Read_Buffer(
	Core::ktkRenderGeometryBufferHandle handle,
	kun_ktk uint64_t offset_bytes, void* p_destination,
	kun_ktk uint64_t size_bytes)
{
	if (p_destination == nullptr || size_bytes == 0)
		return false;

	ktkRenderGeometrySlot* p_slot = this->m_buffers.resolve(handle);

	if (p_slot == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Read_Buffer of an invalid/stale handle ({}) "
			"— ignored", handle);

		return false;
	}

	if (this->m_device_local_buffers[this->m_buffers.slot_index(handle)])
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Read_Buffer of a DEVICE-LOCAL buffer ({}) "
			"— GPU-local memory is not CPU-mappable, ignored", handle);

		return false;
	}

	if (this->m_buffers.is_range_valid(handle, offset_bytes, size_bytes) ==
		false)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Read_Buffer range ({} + {} of {} B) does not "
			"fit the buffer — ignored",
			offset_bytes, size_bytes, p_slot->m_size_bytes);

		return false;
	}

	const ::nri::CoreInterface& core =
		this->m_p_device->Get_CoreInterface();

	void* p_source = core.MapBuffer(
		*static_cast<::nri::Buffer*>(p_slot->m_p_object), offset_bytes,
		size_bytes);

	if (p_source == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] geometry Read_Buffer map failed ({} + {} B)",
			offset_bytes, size_bytes);

		return false;
	}

	std::memcpy(p_destination, p_source, size_bytes);
	core.UnmapBuffer(*static_cast<::nri::Buffer*>(p_slot->m_p_object));

	return true;
}

::nri::Buffer* ktkRenderGeometryManager::Get_NRI_Buffer(
	Core::ktkRenderGeometryBufferHandle handle) noexcept
{
	ktkRenderGeometrySlot* p_slot = this->m_buffers.resolve(handle);

	return p_slot ? static_cast<::nri::Buffer*>(p_slot->m_p_object)
				  : nullptr;
}

::nri::Pipeline* ktkRenderGeometryManager::Get_NRI_Pipeline(
	Core::ktkRenderGeometryPipelineHandle handle) noexcept
{
	ktkRenderGeometrySlot* p_slot = this->m_pipelines.resolve(handle);

	return p_slot ? static_cast<::nri::Pipeline*>(p_slot->m_p_object)
				  : nullptr;
}

::nri::PipelineLayout* ktkRenderGeometryManager::Get_NRI_Pipeline_Layout(
	Core::ktkRenderGeometryPipelineHandle handle) noexcept
{
	ktkRenderGeometrySlot* p_slot = this->m_pipelines.resolve(handle);

	return p_slot
		? static_cast<::nri::PipelineLayout*>(p_slot->m_p_aux)
		: nullptr;
}

kun_ktk uint32_t
	ktkRenderGeometryManager::Get_Pipeline_Push_Constant_Bytes(
		Core::ktkRenderGeometryPipelineHandle handle) const noexcept
{
	const ktkRenderGeometrySlot* p_slot =
		this->m_pipelines.resolve(handle);

	return p_slot ? static_cast<kun_ktk uint32_t>(p_slot->m_size_bytes)
				  : 0u;
}

bool ktkRenderGeometryManager::Is_Buffer_Range_Valid(
	Core::ktkRenderGeometryBufferHandle handle,
	kun_ktk uint64_t offset_bytes, kun_ktk uint64_t size_bytes) const noexcept
{
	return this->m_buffers.is_range_valid(handle, offset_bytes, size_bytes);
}

::nri::DescriptorSet*
	ktkRenderGeometryManager::Get_NRI_Compute_Descriptor_Set(
		Core::ktkRenderGeometryPipelineHandle handle) noexcept
{
	if (this->Is_Compute_Pipeline(handle) == false)
		return nullptr;

	return this->m_compute_states[this->m_pipelines.slot_index(handle)]
		.m_p_set;
}

::nri::DescriptorPool*
	ktkRenderGeometryManager::Get_NRI_Descriptor_Pool(void) const noexcept
{
	return this->m_p_descriptor_pool;
}

bool ktkRenderGeometryManager::Is_Compute_Pipeline(
	Core::ktkRenderGeometryPipelineHandle handle) const noexcept
{
	if (this->m_pipelines.resolve(handle) == nullptr)
		return false;

	return this->m_compute_states[this->m_pipelines.slot_index(handle)]
			   .m_p_set != nullptr;
}

bool ktkRenderGeometryManager::Update_Compute_Binding(
	Core::ktkRenderGeometryPipelineHandle pipeline,
	kun_ktk uint32_t binding_index, Core::ktkRenderGeometryBufferHandle buffer,
	kun_ktk uint64_t offset_bytes, kun_ktk uint64_t size_bytes) noexcept
{
	if (binding_index >= k_max_compute_bindings ||
		this->m_pipelines.resolve(pipeline) == nullptr)
	{
		return false;
	}

	return this->m_compute_states[this->m_pipelines.slot_index(pipeline)]
		.m_bindings.set(binding_index, buffer, offset_bytes, size_bytes);
}

bool ktkRenderGeometryManager::Is_Compute_Binding_Complete(
	Core::ktkRenderGeometryPipelineHandle handle) const noexcept
{
	if (this->m_pipelines.resolve(handle) == nullptr)
		return false;

	const ktkRenderComputePipelineState& compute_state =
		this->m_compute_states[this->m_pipelines.slot_index(handle)];

	return compute_state.m_bindings.is_complete(
		compute_state.m_binding_count);
}

void ktkRenderGeometryManager::Set_Compute_Binding_View(
	Core::ktkRenderGeometryPipelineHandle pipeline,
	kun_ktk uint32_t binding_index, void* p_view) noexcept
{
	if (binding_index >= k_max_compute_bindings ||
		this->m_pipelines.resolve(pipeline) == nullptr)
	{
		return;
	}

	this->m_compute_states[this->m_pipelines.slot_index(pipeline)]
		.m_p_views[binding_index] = p_view;
}

void* ktkRenderGeometryManager::Get_Compute_Binding_View(
	Core::ktkRenderGeometryPipelineHandle pipeline,
	kun_ktk uint32_t binding_index) const noexcept
{
	if (binding_index >= k_max_compute_bindings ||
		this->m_pipelines.resolve(pipeline) == nullptr)
	{
		return nullptr;
	}

	return this->m_compute_states[this->m_pipelines.slot_index(pipeline)]
		.m_p_views[binding_index];
}

bool ktkRenderGeometryManager::Is_Compute_Binding_Read_Only(
	Core::ktkRenderGeometryPipelineHandle pipeline,
	kun_ktk uint32_t binding_index) const noexcept
{
	if (binding_index >= k_max_compute_bindings ||
		this->m_pipelines.resolve(pipeline) == nullptr)
	{
		return false;
	}

	return (this->m_compute_states[this->m_pipelines.slot_index(pipeline)]
				.m_read_only_mask &
			(1u << binding_index)) != 0u;
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
