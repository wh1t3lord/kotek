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

private:
	/// \~english the v1 seam supports one interleaved vertex stream —
	/// enough of the NRI vertex-input description for it
	static constexpr kun_ktk uint32_t k_max_vertex_attributes = 8;

private:
	ktkRenderDevice* m_p_device{};
	ktkRenderGeometryHandleTable<KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_BUFFERS>
		m_buffers{};
	ktkRenderGeometryHandleTable<KOTEK_DEF_RENDER_NRI_GEOMETRY_MAX_PIPELINES>
		m_pipelines{};
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
