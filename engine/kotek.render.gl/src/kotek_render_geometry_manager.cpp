#include "../include/kotek_render_geometry_manager.h"
#include "../include/kotek_render_buffer_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkRenderGeometryManager::ktkRenderGeometryManager() : m_vao_handle{}
{
	this->m_p_index = new ktkRenderBufferManager();
	this->m_p_vertex = new ktkRenderBufferManager();
}

ktkRenderGeometryManager::~ktkRenderGeometryManager()
{
	if (this->m_p_index)
	{
		delete this->m_p_index;
		this->m_p_index = nullptr;
	}

	if (this->m_p_vertex)
	{
		delete this->m_p_vertex;
		this->m_p_vertex = nullptr;
	}
}

void ktkRenderGeometryManager::Initialize(ktk::size_t memory_size)
{
	auto total_memory = memory_size;

	auto index_mem = ktk::align_down<ktk::size_t>((memory_size / 100) * 35, 2);

	total_memory -= index_mem;

	glGenVertexArrays(1, &this->m_vao_handle);

	this->m_p_vertex->Initialize(index_mem, "vertex manager", GL_ARRAY_BUFFER);

	this->m_p_index->Initialize(
		total_memory, "index manager", GL_ELEMENT_ARRAY_BUFFER);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ktkRenderGeometryManager::Shutdown(void) 
{
	glDeleteVertexArrays(1, &this->m_vao_handle);

	if (this->m_p_index)
		this->m_p_index->Shutdown();

	if (this->m_p_vertex)
		this->m_p_vertex->Shutdown();
}

void ktkRenderGeometryManager::Upload(const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i, ktk::entity_t id) noexcept
{
	if (data_v.empty())
		return;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
