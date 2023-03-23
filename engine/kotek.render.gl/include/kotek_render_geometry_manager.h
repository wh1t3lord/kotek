#pragma once

#include "../include/kotek_render_buffer_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkRenderGeometryManager
{
public:
	struct ktkVertex
	{
		ktkVertex()
		{
			this->m_position[0] = 0.0f;
			this->m_position[1] = 0.0f;
			this->m_position[2] = 0.0f;
		}

		ktkVertex(float x, float y, float z) { this->Set_Position(x, y, z); }

		~ktkVertex() {}

		void Set_Position(float x, float y, float z) noexcept
		{
			this->m_position[0] = x;
			this->m_position[1] = y;
			this->m_position[2] = z;
		}

		void* Get_Data() noexcept { return this->m_position; }

	private:
		float m_position[3];
	};

public:
	struct ktkGeometry
	{
		ktk::variant<ktk::enum_base_t, ktk::cstring> m_geometry_type;
		ktk::vector<ktkVertex> m_vertex_data;
		ktk::vector<ktk::uint32_t> m_index_data;
	};

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

private:
	void FreeOffset(ktk::entity_t id);

private:
	GLuint m_vao_handle;
	ktkRenderBufferManager* m_p_vertex;
	ktkRenderBufferManager* m_p_index;
	ktk::vector<gl::ktkDrawIndexIndirectCommand> m_indirect_commands;
	ktk::mt::queue<ktkGeometry> m_for_upload;

	// stores offsets for unloading/freeing
	ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
		m_vertex_buffer_offsets;
	ktk::unordered_map<ktk::enum_base_t, OffsetAllocator::Allocation>
		m_index_buffer_offsets;
	ktk::unordered_map<ktk::enum_base_t, ktk::size_t> m_geometry_type;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK