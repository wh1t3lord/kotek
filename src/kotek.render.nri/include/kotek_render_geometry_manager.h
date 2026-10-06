#pragma once

/// \file kotek_render_geometry_manager.h
/// \~english the NRI implementation of Core::ktkIRenderGeometryManager
/// (task K11 phase 3 / zircon Z24 B3b): the device-level buffer/pipeline
/// table over the vendored NRI (D3D12). Buffers live in HOST_UPLOAD memory
/// (the immediate synchronous Upload_Buffer contract — the bytes are
/// GPU-readable from the next submitted frame with no fence the caller
/// waits; a copy-queue ring is the documented B-later up-scale). Pipelines
/// compile DXIL bytecode through NRI's GraphicsPipelineDesc with one
/// root-constant (push-constant) range when the caller declares it.
/// Module-internal header — NRI types never leave this module.

#include "kotek_render_nri.h"
#include "kotek_render_device.h"
#include "kotek_render_geometry_handle_table.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

class ktkRenderGeometryManager : public Core::ktkIRenderGeometryManager
{
public:
	ktkRenderGeometryManager(void);
	~ktkRenderGeometryManager(void);

	void Initialize(Core::ktkIRenderDevice* p_render_device) override;
	void Shutdown(void) override;

	Core::ktkRenderGeometryBufferHandle Create_Buffer(
		kun_ktk uint64_t size_bytes,
		Core::eRenderGeometryBufferUsage usage) override;

	void Destroy_Buffer(
		Core::ktkRenderGeometryBufferHandle handle) override;

	bool Upload_Buffer(Core::ktkRenderGeometryBufferHandle handle,
		kun_ktk uint64_t offset_bytes, const void* p_bytes,
		kun_ktk uint64_t size_bytes) override;

	Core::ktkRenderGeometryPipelineHandle Create_Pipeline(
		const Core::ktkRenderGeometryPipelineDesc& desc) override;

	void Destroy_Pipeline(
		Core::ktkRenderGeometryPipelineHandle handle) override;

	Core::ktkRenderGeometryPipelineHandle Create_Compute_Pipeline(
		const Core::ktkRenderGeometryComputePipelineDesc& desc) override;

	bool Read_Buffer(Core::ktkRenderGeometryBufferHandle handle,
		kun_ktk uint64_t offset_bytes, void* p_destination,
		kun_ktk uint64_t size_bytes) override;

	/// \~english the frame-context seam (module-internal): resolve an
	/// opaque handle back to the live NRI object, nullptr on a stale /
	/// foreign handle — the context guards loudly, never dereferences a
	/// bad handle
	::nri::Buffer* Get_NRI_Buffer(
		Core::ktkRenderGeometryBufferHandle handle) noexcept;
	::nri::Pipeline* Get_NRI_Pipeline(
		Core::ktkRenderGeometryPipelineHandle handle) noexcept;

	/// \~english the pipeline's layout (the root-constant binds require
	/// the layout bound first — NRI's validation contract:
	/// CmdSetPipelineLayout before CmdSetRootConstants); nullptr on a
	/// bad handle
	::nri::PipelineLayout* Get_NRI_Pipeline_Layout(
		Core::ktkRenderGeometryPipelineHandle handle) noexcept;

	/// \~english the pipeline's declared push-constant size (the slot's
	/// byte size) — Set_Push_Constants validates against it; 0 on a bad
	/// handle
	kun_ktk uint32_t Get_Pipeline_Push_Constant_Bytes(
		Core::ktkRenderGeometryPipelineHandle handle) const noexcept;

	/// \~english the upload-range guard over the buffer table (the context's
	/// storage-binding / copy range checks); false on a stale handle or an
	/// out-of-buffer range
	bool Is_Buffer_Range_Valid(Core::ktkRenderGeometryBufferHandle handle,
		kun_ktk uint64_t offset_bytes,
		kun_ktk uint64_t size_bytes) const noexcept;

	/// \~english the manager-owned descriptor pool (module-internal): the
	/// frame context binds it on the command list before the first
	/// descriptor-set bind of the compute segment (the swapchain begins
	/// its command list WITHOUT a pool — the graphics draw needs none,
	/// the compute tables do)
	::nri::DescriptorPool* Get_NRI_Descriptor_Pool(void) const noexcept;

	/// \~english the frame-context compute seam (module-internal, task K11
	/// phase 4 / zircon Z24 B3c): the compute pipeline's descriptor set
	/// (allocated at creation from the manager-owned pool), nullptr on a
	/// stale handle or a graphics pipeline
	::nri::DescriptorSet* Get_NRI_Compute_Descriptor_Set(
		Core::ktkRenderGeometryPipelineHandle handle) noexcept;

	/// \~english true when the pipeline slot is a COMPUTE pipeline (the
	/// context's Set_Compute_Pipeline guard — binding a graphics pipeline
	/// there is a programmer error, a loud no-op)
	bool Is_Compute_Pipeline(
		Core::ktkRenderGeometryPipelineHandle handle) const noexcept;

	/// \~english the compute binding bookkeeping: true when the binding
	/// CHANGED and the backend view must be (re)created by the context;
	/// false = the cached view is valid. Out-of-range binding -> a loud
	/// false (the context skips the command)
	bool Update_Compute_Binding(
		Core::ktkRenderGeometryPipelineHandle pipeline,
		kun_ktk uint32_t binding_index,
		Core::ktkRenderGeometryBufferHandle buffer,
		kun_ktk uint64_t offset_bytes, kun_ktk uint64_t size_bytes) noexcept;

	/// \~english every storage binding of the pipeline populated (the
	/// Dispatch guard)
	bool Is_Compute_Binding_Complete(
		Core::ktkRenderGeometryPipelineHandle handle) const noexcept;

	/// \~english stores the freshly created binding view (the context owns
	/// the destroy on the next change / pipeline destroy)
	void Set_Compute_Binding_View(
		Core::ktkRenderGeometryPipelineHandle pipeline,
		kun_ktk uint32_t binding_index, void* p_view) noexcept;

	/// \~english the binding's live view (nullptr before the first set) —
	/// UpdateDescriptorRanges consumes it
	void* Get_Compute_Binding_View(
		Core::ktkRenderGeometryPipelineHandle pipeline,
		kun_ktk uint32_t binding_index) const noexcept;

	/// \~english the pipeline's read-only storage mask (the desc bit at
	/// creation — the context picks the read-only view form for those
	/// bindings)
	bool Is_Compute_Binding_Read_Only(
		Core::ktkRenderGeometryPipelineHandle pipeline,
		kun_ktk uint32_t binding_index) const noexcept;

private:
	/// \~english the v1 seam supports one interleaved vertex stream —
	/// enough of the NRI vertex-input description for it
	static constexpr kun_ktk uint32_t k_max_vertex_attributes = 8;

	/// \~english the per-pipeline compute storage-binding capacity (task
	/// K11 phase 4): the cull kernel of the nanite path binds the cluster
	/// table + the indirect buffer + the counter (3) — 8 leaves room for
	/// the HZB/LOD phases without touching callers
	static constexpr kun_ktk uint32_t k_max_compute_bindings = 8;

private:
	/// \~english the compute-pipeline side state, keyed by the pipeline
	/// slot's index (plain arrays like the handle table — value-init is
	/// deterministic); the descriptor views are owned here, destroyed on
	/// rebind / pipeline destroy / Shutdown
	struct ktkRenderComputePipelineState
	{
		::nri::DescriptorSet* m_p_set{};
		void* m_p_views[k_max_compute_bindings]{};
		ktkRenderGeometryComputeBindingCache<k_max_compute_bindings>
			m_bindings{};
		/// \~english the desc's read-only binding mask (bit N: binding N
		/// is the read-only SRV form) — the context's view-creation flag
		kun_ktk uint32_t m_read_only_mask{};
		/// \~english the desc's declared binding count — the Dispatch
		/// completeness guard checks this many bindings, not the
		/// capacity
		kun_ktk uint32_t m_binding_count{};
	};

	ktkRenderComputePipelineState m_compute_states[
		KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES]{};

private:
	ktkRenderDevice* m_p_device{};
	::nri::DescriptorPool* m_p_descriptor_pool{};
	ktkRenderGeometryHandleTable<KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_BUFFERS>
		m_buffers{};
	ktkRenderGeometryHandleTable<KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES>
		m_pipelines{};
	/// \~english the buffer memory-location side table (task K11 phase
	/// 4): true = GPU-local (kDevice) — Upload_Buffer / Read_Buffer
	/// reject those loudly (device memory is not CPU-mappable); keyed by
	/// the buffer slot's index, cleared on Destroy_Buffer
	bool m_device_local_buffers[
		KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_BUFFERS]{};
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
