#include "../include/kotek_render_geometry_manager.h"

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
	KOTEK_GL_ASSERT();

	glBindVertexArray(this->m_vao_handle);
	KOTEK_GL_ASSERT();

	this->m_p_vertex->Initialize(index_mem, "vertex manager", GL_ARRAY_BUFFER);

	this->m_p_index->Initialize(
		total_memory, "index manager", GL_ELEMENT_ARRAY_BUFFER);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ktkVertex), 0);
	KOTEK_GL_ASSERT();

	glEnableVertexAttribArray(0);
	KOTEK_GL_ASSERT();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	KOTEK_GL_ASSERT();

	glBindVertexArray(0);
	KOTEK_GL_ASSERT();
}

void ktkRenderGeometryManager::Shutdown(void)
{
	glDeleteVertexArrays(1, &this->m_vao_handle);

	if (this->m_p_index)
		this->m_p_index->Shutdown();

	if (this->m_p_vertex)
		this->m_p_vertex->Shutdown();
}

void ktkRenderGeometryManager::AddForUpload(
	const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i, ktk::entity_t id) noexcept
{
	this->m_for_upload.push_back({id, data_v, data_i});
}

void ktkRenderGeometryManager::Update(void) noexcept
{
	for (const auto& entity : this->m_for_upload)
	{
		this->Upload(entity.m_v, entity.m_i, entity.m_id);
	}

	this->m_for_upload.clear();
}

void ktkRenderGeometryManager::Upload(const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i, ktk::entity_t id) noexcept
{
	if (data_v.empty())
		return;

	if (this->m_storage.find(id) == this->m_storage.end())
	{
		this->m_storage[id] =
			this->m_p_vertex->AllocateOffset(sizeof(ktkVertex) * data_v.size());
	}
	else
	{
		this->FreeOffset(id);
		this->m_storage[id] =
			this->m_p_vertex->AllocateOffset(sizeof(ktkVertex) * data_v.size());
	}

	const auto& info = this->m_storage.at(id);

	glBindBuffer(
		this->m_p_vertex->Get_Target(), this->m_p_vertex->Get_Handles()[0]);
	KOTEK_GL_ASSERT();

	glBufferSubData(this->m_p_vertex->Get_Target(), info.offset,
		sizeof(ktkVertex) * data_v.size(), data_v.data());
	KOTEK_GL_ASSERT();

	glBindBuffer(this->m_p_vertex->Get_Target(), 0);
	KOTEK_GL_ASSERT();
}

GLuint ktkRenderGeometryManager::Get_VAO(void) const noexcept
{
	return this->m_vao_handle;
}

void ktkRenderGeometryManager::FreeOffset(ktk::entity_t id)
{
	this->m_p_vertex->FreeOffset(this->m_storage.at(id));
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
