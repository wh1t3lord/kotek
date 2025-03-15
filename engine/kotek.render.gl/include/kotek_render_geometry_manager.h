#pragma once

#include "../include/kotek_render_buffer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

class ktkRenderGeometryManager
{
	struct ktkGeometryCommandInstanceByEnum
	{
		/// @brief buffer_offset_index * sizeof(ktkDrawElementsIndirectCommand)
		/// so we obtain our offset in indirect commands
		kun_ktk enum_base_t indirect_buffer_offset_index;
		OffsetAllocator::Allocation offset_vertex_buffer;
		OffsetAllocator::Allocation offset_index_buffer;
	};

	struct ktkGeometryCommandInstanceByModel
	{
		ktk_cstring_view model_path_name;
		OffsetAllocator::Allocation offset_vertex_buffer;
		OffsetAllocator::Allocation offset_index_buffer;
	};

	using ktk_render_indirect_commands_by_enum_t =
		ktk_array<ktkGeometryCommandInstanceByEnum, 2>;

public:
	ktkRenderGeometryManager();
	~ktkRenderGeometryManager();

	void Initialize(ktk::size_t memory_size);
	void Shutdown(void);

	void AddForUpload(const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		ktk::enum_base_t static_geometry_type) noexcept;
	void AddForUpload(const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		const ktk::cstring& string_path_to_file_name) noexcept;

	void Update(void) noexcept;

	void Upload(const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		ktk::enum_base_t static_geometry_type) noexcept;

	// use std::string_view so it means we store information about path to model
	// on user's side and user gurantees that that path is valid
	void Upload(const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		const ktk::cstring& string_path_to_file_name) noexcept;

	GLuint Get_VAO(void) const noexcept;

	ktkRenderStats* Get_StatIndexBuffer(void) noexcept;
	ktkRenderStats* Get_StatVertexBuffer(void) noexcept;
	ktkRenderStats* Get_StatSSBOBufferMatrix(void) noexcept;

	bool Is_DrawIndirectCommandsChanged(void) noexcept;

	void Rebuild_DrawIndirectCommands(void) noexcept;
	void Rebuild_SSBO_Instancing_Matricies(void) noexcept;

	ktkRenderBuffer* Get_Buffer_DrawIndirectCommands(void) const;

	const ktk_render_indirect_commands_by_enum_t&
	Get_IndirectCommands_PredefinedModels(void) const;

	GLuint Get_CurrentIndirectCommandsInUse() const;

private:
	void FreeOffset(ktk::uint32_t id);

	kun_ktk uint32_t Get_FreeSlotOfIndirectCommand(void) const;

private:
	ktk_array<bool, 50> m_free_slots_of_indirect_commands;
	GLuint m_vao_handle;
	GLuint m_current_indirect_commands_in_use;
	ktkRenderBuffer* m_p_vertex_buffer;
	ktkRenderBuffer* m_p_index_buffer;
	ktkRenderBuffer* m_p_draw_indirect_commands;

	//	ktk::unordered_map<ktk::enum_base_t, gl::ktkDrawIndexIndirectCommand>
	//	m_indirect_commands_models_by_enum;

	ktk_render_indirect_commands_by_enum_t m_indirect_commands_by_enum;

	ktk::unordered_map<ktk::cstring, gl::ktkDrawIndexIndirectCommand>
		m_indirect_commands_models_by_path;

	// stores offsets for unloading/freeing
	ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
		m_vertex_buffer_offsets;
	ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
		m_index_buffer_offsets;
	ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
		m_draw_commands_buffer_offsets;
	ktk::unordered_map<ktk::enum_base_t, ktk::size_t> m_geometry_type;

	ktk::mt::queue<ktkGeometry> m_queue_for_upload;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK