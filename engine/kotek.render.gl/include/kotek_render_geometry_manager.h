#pragma once

#include "../include/kotek_render_buffer_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGeometryManager
	{
	public:
		ktkRenderGeometryManager();
		~ktkRenderGeometryManager();

		void Initialize(ktk::size_t memory_size);
		void Shutdown(void);

		void AddForUpload(const ktk::vector<ktkVertex>& data_v,
			const ktk::vector<ktk::uint32_t>& data_i,
			ktk::enum_base_t static_geometry_type) noexcept;
		void AddForUpload(const ktk::vector<ktkVertex>& data_v,
			const ktk::vector<ktk::uint32_t>& data_i,
			const ktk::cstring& string_path_to_file_name) noexcept;

		void Update(void) noexcept;

		void Upload(const ktk::vector<ktkVertex>& data_v,
			const ktk::vector<ktk::uint32_t>& data_i,
			ktk::enum_base_t static_geometry_type) noexcept;
		void Upload(const ktk::vector<ktkVertex>& data_v,
			const ktk::vector<ktk::uint32_t>& data_i,
			const ktk::cstring& string_path_to_file_name) noexcept;

		GLuint Get_VAO(void) const noexcept;

		ktkRenderStats* Get_StatIndexBuffer(void) noexcept;
		ktkRenderStats* Get_StatVertexBuffer(void) noexcept;
		ktkRenderStats* Get_StatSSBOBufferMatrix(void) noexcept;

		bool Is_DrawIndirectCommandsChanged(void) noexcept;

		void Rebuild_DrawIndirectCommands(void) noexcept;
		void Rebuild_SSBO_Instancing_Matricies(void) noexcept;

		ktkRenderBufferManager* Get_Buffer_DrawIndirectCommands(void) const;

		const ktk::unordered_map<ktk::enum_base_t,
			gl::ktkDrawIndexIndirectCommand>&
		Get_IndirectCommands_PredefinedModels(void) const;

	private:
		void FreeOffset(ktk::entity_t id);

	private:
		GLuint m_vao_handle;
		ktkRenderBufferManager* m_p_vertex_buffer;
		ktkRenderBufferManager* m_p_index_buffer;
		ktkRenderBufferManager* m_p_draw_indirect_commands;

		ktk::unordered_map<ktk::enum_base_t, gl::ktkDrawIndexIndirectCommand>
			m_indirect_commands_models_by_enum;
		ktk::unordered_map<ktk::cstring, gl::ktkDrawIndexIndirectCommand>
			m_indirect_commands_models_by_path;

		// stores offsets for unloading/freeing
		ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
			m_vertex_buffer_offsets;
		ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
			m_index_buffer_offsets;
		ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
			m_draw_commands_buffer_offets;
		ktk::unordered_map<ktk::enum_base_t, ktk::size_t> m_geometry_type;

		ktk::mt::queue<ktkGeometry> m_queue_for_upload;
	};
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK