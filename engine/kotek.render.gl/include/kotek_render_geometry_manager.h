#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkRenderBufferManager;

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

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
	ktkRenderGeometryManager();
	~ktkRenderGeometryManager();

	void Initialize(ktk::size_t memory_size);
	void Shutdown(void);

	void Upload(const ktk::vector<ktkVertex>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i, ktk::entity_t id) noexcept;

private:
	void FreeOffset(ktk::entity_t id);

private:
	GLuint m_vao_handle;
	ktkRenderBufferManager* m_p_vertex;
	ktkRenderBufferManager* m_p_index;

	// stores offsets for unloading/freeing
	ktk::unordered_map<ktk::entity_t, ktk::size_t> m_storage;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK