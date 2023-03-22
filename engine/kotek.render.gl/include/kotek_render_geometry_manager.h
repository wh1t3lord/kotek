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
		ktk::entity_t m_id;
		ktk::vector<ktkVertex> m_v;
		ktk::vector<ktk::uint32_t> m_i;
	};

public:
	ktkRenderGeometryManager();
	~ktkRenderGeometryManager();

	void Initialize(ktk::size_t memory_size);
	void Shutdown(void);

	void AddForUpload(const ktk::vector<ktkVertex>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i, ktk::entity_t id) noexcept;

	void Update(void) noexcept;

	void Upload(const ktk::vector<ktkVertex>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i, ktk::entity_t id) noexcept;

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
	ktk::unordered_map<ktk::entity_t, OffsetAllocator::Allocation> m_storage;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK