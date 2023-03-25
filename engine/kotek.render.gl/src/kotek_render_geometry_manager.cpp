#include "../include/kotek_render_geometry_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkRenderGeometryManager::ktkRenderGeometryManager() :
	m_vao_handle{}, m_p_vertex_buffer{}, m_p_index_buffer{},
	m_p_ssbo_instance_matricies_buffer{}
{
	this->m_p_index_buffer = new ktkRenderBufferManager();
	this->m_p_vertex_buffer = new ktkRenderBufferManager();
	this->m_p_ssbo_instance_matricies_buffer = new ktkRenderBufferManager();
}

ktkRenderGeometryManager::~ktkRenderGeometryManager()
{
	if (this->m_p_index_buffer)
	{
		delete this->m_p_index_buffer;
		this->m_p_index_buffer = nullptr;
	}

	if (this->m_p_vertex_buffer)
	{
		delete this->m_p_vertex_buffer;
		this->m_p_vertex_buffer = nullptr;
	}

	if (this->m_p_ssbo_instance_matricies_buffer)
	{
		delete this->m_p_ssbo_instance_matricies_buffer;
		this->m_p_ssbo_instance_matricies_buffer = nullptr;
	}
}

void ktkRenderGeometryManager::Initialize(ktk::size_t memory_size)
{
#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Geometry manager allocated memeory: {} Mb",
		memory_size / (1024 * 1024));
#endif

	auto total_memory = memory_size;

	auto vertex_buffer_memory =
		ktk::align_down<ktk::size_t>((memory_size / 100) * 40, 2);

	total_memory -= vertex_buffer_memory;

	glGenVertexArrays(1, &this->m_vao_handle);
	KOTEK_GL_ASSERT();

	glBindVertexArray(this->m_vao_handle);
	KOTEK_GL_ASSERT();

	this->m_p_vertex_buffer->Initialize(vertex_buffer_memory,
		"single vertex buffer", GL_ARRAY_BUFFER,
		Core::eRenderStatistics::kStat_Buffer_Vertex);

	total_memory -= vertex_buffer_memory;

	this->m_p_index_buffer->Initialize(vertex_buffer_memory,
		"single index buffer", GL_ELEMENT_ARRAY_BUFFER,
		Core::eRenderStatistics::kStat_Buffer_Index);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ktkVertex), 0);
	KOTEK_GL_ASSERT();

	glEnableVertexAttribArray(0);
	KOTEK_GL_ASSERT();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	KOTEK_GL_ASSERT();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	KOTEK_GL_ASSERT();

	glBindVertexArray(0);
	KOTEK_GL_ASSERT();

	// TODO: read from render settings file about total instance buffer
	auto ssbo_matrix_memory = ktk::align_down<ktk::size_t>(
		(memory_size / 100) * 20, sizeof(ktk::math::mat4x4f_t));

	this->m_p_ssbo_instance_matricies_buffer->Initialize(ssbo_matrix_memory,
		"SSBO Instancing matricies", GL_SHADER_STORAGE_BUFFER,
		Core::eRenderStatistics::kStat_Buffer_SSBO_Matrix, 3);

	total_memory -= ssbo_matrix_memory;

	this->m_ssbo_instance_matricies_indexes.reserve(
		ssbo_matrix_memory / sizeof(ktk::math::mat4x4f_t));

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Instancing total count objects: {}",
		ssbo_matrix_memory / sizeof(ktk::math::mat4x4f_t));
#endif

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Remainder: {}", total_memory);
#endif
}

void ktkRenderGeometryManager::Shutdown(void)
{
	glDeleteVertexArrays(1, &this->m_vao_handle);

	if (this->m_p_index_buffer)
		this->m_p_index_buffer->Shutdown();

	if (this->m_p_vertex_buffer)
		this->m_p_vertex_buffer->Shutdown();

	if (this->m_p_ssbo_instance_matricies_buffer)
		this->m_p_ssbo_instance_matricies_buffer->Shutdown();
}

void ktkRenderGeometryManager::AddForUpload(
	const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i,
	ktk::enum_base_t static_geometry_type) noexcept
{
	KOTEK_ASSERT(
		data_v.empty() == false, "you can't pass an empty vertex buffer");
	KOTEK_ASSERT(
		data_i.empty() == false, "you can't pass an empty index buffer");

	this->m_queue_for_upload.push({static_geometry_type, data_v, data_i});
}

void ktkRenderGeometryManager::AddForUpload(
	const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i,
	const ktk::cstring& string_path_to_file_name) noexcept
{
	KOTEK_ASSERT(
		data_v.empty() == false, "you can't pass an empty vertex buffer");
	KOTEK_ASSERT(
		data_i.empty() == false, "you can't pass an empty index buffer");

	this->m_queue_for_upload.push({string_path_to_file_name, data_v, data_i});
}

void ktkRenderGeometryManager::Update(void) noexcept
{
	while (!this->m_queue_for_upload.empty())
	{
		ktkGeometry entity;

		this->m_queue_for_upload.pop(entity);

		const auto* p_enum =
			std::get_if<ktk::enum_base_t>(&entity.m_geometry_type);

		if (p_enum)
		{
			this->Upload(entity.m_vertex_data, entity.m_index_data, *p_enum);
		}
		else
		{
			const auto* p_string =
				std::get_if<ktk::cstring>(&entity.m_geometry_type);

			KOTEK_ASSERT(p_string,
				"something is really terrible, it accepts only two variants "
				"enum of static geometry or string to file path");

			this->Upload(entity.m_vertex_data, entity.m_index_data, *p_string);
		}
	}
}

void ktkRenderGeometryManager::Upload(const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i,
	ktk::enum_base_t static_geometry_type) noexcept
{
	KOTEK_ASSERT(data_v.empty() == false, "can't bind empty vertex buffer");
	KOTEK_ASSERT(data_i.empty() == false, "can't bind empty index buffer");
	KOTEK_ASSERT(static_geometry_type !=
			static_cast<ktk::enum_base_t>(Core::eStaticGeometryType::kUnknown),
		"you can't pass an invalid geometry type");

	/*
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
	*/
}

void ktkRenderGeometryManager::Upload(const ktk::vector<ktkVertex>& data_v,
	const ktk::vector<ktk::uint32_t>& data_i,
	const ktk::cstring& string_path_to_file_name) noexcept
{
	KOTEK_ASSERT(data_v.empty() == false, "can't bind empty vertex buffer");
	KOTEK_ASSERT(data_i.empty() == false, "can't bind empty index buffer");
	KOTEK_ASSERT(string_path_to_file_name.empty() == false,
		"can't register geometry without string to file path");
}

GLuint ktkRenderGeometryManager::Get_VAO(void) const noexcept
{
	return this->m_vao_handle;
}

ktkRenderStats* ktkRenderGeometryManager::Get_StatIndexBuffer(void) noexcept
{
	ktkRenderStats* p_result{};

	if (this->m_p_index_buffer)
		p_result = this->m_p_index_buffer->Get_Stat();

	return p_result;
}

ktkRenderStats* ktkRenderGeometryManager::Get_StatVertexBuffer(void) noexcept
{
	ktkRenderStats* p_result{};

	if (this->m_p_vertex_buffer)
		p_result = this->m_p_vertex_buffer->Get_Stat();

	return p_result;
}

ktkRenderStats* ktkRenderGeometryManager::Get_StatSSBOBufferMatrix(
	void) noexcept
{
	ktkRenderStats* p_result{};

	if (this->m_p_ssbo_instance_matricies_buffer)
		p_result = this->m_p_ssbo_instance_matricies_buffer->Get_Stat();

	return p_result;
}

void ktkRenderGeometryManager::FreeOffset(ktk::entity_t id) {}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
