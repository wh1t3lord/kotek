#include "../include/kotek_render_geometry_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace bgfx
{
	ktkRenderGeometryManager::ktkRenderGeometryManager() 
	{
	}

	ktkRenderGeometryManager::~ktkRenderGeometryManager()
	{
		/*
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

		if (this->m_p_draw_indirect_commands)
		{
			delete this->m_p_draw_indirect_commands;
			this->m_p_draw_indirect_commands = nullptr;
		}
		*/
	}

	void ktkRenderGeometryManager::Initialize(ktk::size_t memory_size)
	{
#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("Geometry manager allocated memeory: {} Mb",
			memory_size / (1024 * 1024));
#endif

		/*
		constexpr auto _kDrawCommandsAllocatedMemory =
		    sizeof(ktkDrawElementsIndirectCommand) * 50;

		auto total_memory = memory_size - _kDrawCommandsAllocatedMemory;

		auto vertex_buffer_memory =
		    ktk::align_down<ktk::size_t>((total_memory / 100) * 40, 2);

		total_memory -= vertex_buffer_memory;

		glGenVertexArrays(1, &this->m_vao_handle);
		KOTEK_GL_ASSERT();

		glBindVertexArray(this->m_vao_handle);
		KOTEK_GL_ASSERT();

		this->m_p_vertex_buffer->Initialize(vertex_buffer_memory,
		    "single vertex buffer", GL_ARRAY_BUFFER,
		    kun_core eRenderStatistics::kStat_Buffer_Vertex, GL_DYNAMIC_DRAW);

		total_memory -= vertex_buffer_memory;

		this->m_p_index_buffer->Initialize(vertex_buffer_memory,
		    "single index buffer", GL_ELEMENT_ARRAY_BUFFER,
		    kun_core eRenderStatistics::kStat_Buffer_Index, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ktkVertex), 0);
		KOTEK_GL_ASSERT();

		glEnableVertexAttribArray(0);
		KOTEK_GL_ASSERT();

		glBindVertexArray(0);
		KOTEK_GL_ASSERT();

		this->m_p_draw_indirect_commands->Initialize(
		    _kDrawCommandsAllocatedMemory,
		    "draw indexed (elements) indirect commands buffer",
		    GL_DRAW_INDIRECT_BUFFER,
		    kun_core eRenderStatistics::kStat_Buffer_Indirect_Indexed,
		    GL_DYNAMIC_DRAW);

		glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(),
		    this->m_p_draw_indirect_commands->Get_Handle());
		KOTEK_GL_ASSERT();

		ktkDrawElementsIndirectCommand
		    commands[KOTEK_DEF_RENDER_GL_ES_INDIRECT_DRAWING_TOTAL_COMMANDS];
		std::memset(commands, 0, sizeof(commands));

		glBufferSubData(this->m_p_draw_indirect_commands->Get_Target(), 0,
		    sizeof(commands), commands);
		KOTEK_GL_ASSERT();

		glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(), 0);
		KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("Remainder: {}", total_memory);

		KOTEK_MESSAGE("Draw commands count: {}",
		    _kDrawCommandsAllocatedMemory /
		        sizeof(ktkDrawIndexIndirectCommand));
#endif
*/
	}

	void ktkRenderGeometryManager::Shutdown(void)
	{
		/*
		glDeleteVertexArrays(1, &this->m_vao_handle);

		if (this->m_p_index_buffer)
		    this->m_p_index_buffer->Shutdown();

		if (this->m_p_vertex_buffer)
		    this->m_p_vertex_buffer->Shutdown();

		if (this->m_p_draw_indirect_commands)
		    this->m_p_draw_indirect_commands->Shutdown();
		*/
	}

	void ktkRenderGeometryManager::AddForUpload(
		const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		ktk::enum_base_t static_geometry_type) noexcept
	{
		KOTEK_ASSERT(
			data_v.empty() == false, "you can't pass an empty vertex buffer");
		KOTEK_ASSERT(
			data_i.empty() == false, "you can't pass an empty index buffer");

		//	this->m_queue_for_upload.push({static_geometry_type, data_v,
		//data_i});
	}

	void ktkRenderGeometryManager::AddForUpload(
		const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		const ktk::cstring& string_path_to_file_name) noexcept
	{
		KOTEK_ASSERT(
			data_v.empty() == false, "you can't pass an empty vertex buffer");
		KOTEK_ASSERT(
			data_i.empty() == false, "you can't pass an empty index buffer");

		//	this->m_queue_for_upload.push(
		//		{string_path_to_file_name, data_v, data_i});
	}

	void ktkRenderGeometryManager::Update(void) noexcept
	{
		/*
		while (!this->m_queue_for_upload.empty())
		{
		    ktkGeometry entity;

		    this->m_queue_for_upload.pop(entity);

		    const auto* p_enum =
		        std::get_if<ktk::enum_base_t>(&entity.Get_GeometryType());

		    if (p_enum)
		    {
		        this->Upload(
		            entity.Get_VertexData(), entity.Get_IndexData(), *p_enum);
		    }
		    else
		    {
		        const auto* p_string =
		            std::get_if<ktk::cstring>(&entity.Get_GeometryType());

		        KOTEK_ASSERT(p_string,
		            "something is really terrible, it accepts only two "
		            "variants "
		            "enum of static geometry or string to file path");

		        this->Upload(
		            entity.Get_VertexData(), entity.Get_IndexData(), *p_string);
		    }
		}
		*/
	}

	void ktkRenderGeometryManager::Upload(
		const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		ktk::enum_base_t static_geometry_type) noexcept
	{
		KOTEK_ASSERT(data_v.empty() == false,
			"can't bind empty vertex buffer. Can't render without geometry, "
			"what's the point?");
		KOTEK_ASSERT(data_i.empty() == false,
			"can't bind empty index buffer. Supposed that drawing based on "
			"indexing geometry not just vertecies (not efficient)");
		KOTEK_ASSERT(static_geometry_type !=
				static_cast<ktk::enum_base_t>(
					kun_core eStaticGeometryType::kUnknown),
			"you can't pass an invalid geometry type");
	}

	void ktkRenderGeometryManager::Upload(
		const ktk::vector<ktk::math::vec3f_t>& data_v,
		const ktk::vector<ktk::uint32_t>& data_i,
		const ktk::cstring& string_path_to_file_name) noexcept
	{
		KOTEK_ASSERT(data_v.empty() == false, "can't bind empty vertex buffer");
		KOTEK_ASSERT(data_i.empty() == false, "can't bind empty index buffer");
		KOTEK_ASSERT(string_path_to_file_name.empty() == false,
			"can't register geometry without string to file path");
	}

	KOTEK_END_NAMESPACE_RENDER_BGFX
	KOTEK_END_NAMESPACE_RENDER
	KOTEK_END_NAMESPACE_KOTEK
