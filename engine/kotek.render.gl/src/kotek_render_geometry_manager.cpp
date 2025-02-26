#include "../include/kotek_render_geometry_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gl
{
	ktkRenderGeometryManager::ktkRenderGeometryManager() :
		m_free_slots_of_indirect_commands{}, m_vao_handle{},
		m_current_indirect_commands_in_use{}, m_p_vertex_buffer{},
		m_p_index_buffer{}, m_p_draw_indirect_commands{},
		m_indirect_commands_by_enum{}
	{
		this->m_p_index_buffer = new ktkRenderBuffer();
		this->m_p_vertex_buffer = new ktkRenderBuffer();
		this->m_p_draw_indirect_commands = new ktkRenderBuffer();

		for (auto& it : this->m_indirect_commands_by_enum)
		{
			it.indirect_buffer_offset_index = kun_ktk enum_base_t(-1);
		}
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

		if (this->m_p_draw_indirect_commands)
		{
			delete this->m_p_draw_indirect_commands;
			this->m_p_draw_indirect_commands = nullptr;
		}
	}

	void ktkRenderGeometryManager::Initialize(ktk::size_t memory_size)
	{
#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("Geometry manager allocated memeory: {} Mb",
			memory_size / (1024 * 1024));
#endif

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
			commands[KOTEK_DEF_RENDER_INDIRECT_DRAWING_TOTAL_COMMANDS];
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
	}

	void ktkRenderGeometryManager::Shutdown(void)
	{
		glDeleteVertexArrays(1, &this->m_vao_handle);

		if (this->m_p_index_buffer)
			this->m_p_index_buffer->Shutdown();

		if (this->m_p_vertex_buffer)
			this->m_p_vertex_buffer->Shutdown();

		if (this->m_p_draw_indirect_commands)
			this->m_p_draw_indirect_commands->Shutdown();
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

		this->m_queue_for_upload.push({static_geometry_type, data_v, data_i});
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

		this->m_queue_for_upload.push(
			{string_path_to_file_name, data_v, data_i});
	}

	void ktkRenderGeometryManager::Update(void) noexcept
	{
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

		/*
		if (this->m_indirect_commands_models_by_enum.find(
		        static_geometry_type) ==
		    this->m_indirect_commands_models_by_enum.end())
		{
		    auto& command =
		        this->m_indirect_commands_models_by_enum[static_geometry_type];

		    command.m_count = data_i.size();
		    command.m_instance_count = 1;
		    command.m_base_vertex = 0;
		    command.m_first_index = 0;

		    if (this->m_draw_commands_buffer_offets.find(
		            static_geometry_type) ==
		        this->m_draw_commands_buffer_offets.end())
		    {
		        glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(),
		            this->m_p_draw_indirect_commands->Get_Handle());
		        KOTEK_GL_ASSERT();

		        this->m_draw_commands_buffer_offets[static_geometry_type] =
		            this->m_p_draw_indirect_commands->AllocateOffset(
		                sizeof(ktkDrawIndexIndirectCommand));

		        const auto& info_alloc = this->m_draw_commands_buffer_offets.at(
		            static_geometry_type);

		        glBufferSubData(this->m_p_draw_indirect_commands->Get_Target(),
		            info_alloc.offset, sizeof(ktkDrawIndexIndirectCommand),
		            &command);
		        KOTEK_GL_ASSERT();

		        glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(), 0);
		        KOTEK_GL_ASSERT();
		    }
		}
		else
		{
		    auto& command = this->m_indirect_commands_models_by_enum.at(
		        static_geometry_type);

		    command.m_instance_count += 1;
		}
		*/

		if (this->m_indirect_commands_by_enum[static_geometry_type]
				.indirect_buffer_offset_index == kun_ktk enum_base_t(-1))
		{
			kun_ktk uint32_t freed_offset =
				this->Get_FreeSlotOfIndirectCommand();

			KOTEK_ASSERT(freed_offset != kun_ktk uint32_t(-1),
				"failed to obtained free slot, can't render the requested!");

			if (freed_offset != kun_ktk uint32_t(-1))
			{
				glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(),
					this->m_p_draw_indirect_commands->Get_Handle());
				KOTEK_GL_ASSERT();

				this->m_free_slots_of_indirect_commands[freed_offset] = true;
				ktkGeometryCommandInstanceByEnum& instance =
					this->m_indirect_commands_by_enum[static_geometry_type];

				instance.indirect_buffer_offset_index = freed_offset;
				ktkDrawElementsIndirectCommand* p_command = nullptr;

				p_command = (ktkDrawElementsIndirectCommand*)glMapBufferRange(
					this->m_p_draw_indirect_commands->Get_Target(),
					freed_offset * sizeof(ktkDrawElementsIndirectCommand),
					sizeof(ktkDrawElementsIndirectCommand), GL_MAP_WRITE_BIT);
				KOTEK_GL_ASSERT();

				KOTEK_ASSERT(p_command,
					"something is wrong, driver returned nullptr for data!");

				if (p_command)
				{
					instance.offset_vertex_buffer =
						this->m_p_vertex_buffer->AllocateOffset(
							sizeof(ktkVertex) * data_v.size());

					// TODO: use alias for render not just general uint32_t
					// might break this rendering when user wants to replace
					// uint32_t
					instance.offset_index_buffer =
						this->m_p_index_buffer->AllocateOffset(
							sizeof(kun_ktk uint32_t) * data_i.size());

					p_command->instanceCount = 1;
					p_command->count = data_i.size();
					p_command->baseVertex =
						instance.offset_vertex_buffer.offset;
					p_command->firstIndex = instance.offset_index_buffer.offset;
					p_command->baseInstance = 0;

					glUnmapBuffer(
						this->m_p_draw_indirect_commands->Get_Target());
					KOTEK_GL_ASSERT();

					glBindBuffer(
						this->m_p_draw_indirect_commands->Get_Target(), 0);
					KOTEK_GL_ASSERT();

					glBindBuffer(this->m_p_vertex_buffer->Get_Target(),
						this->m_p_vertex_buffer->Get_Handle());
					KOTEK_GL_ASSERT();

					glBufferSubData(this->m_p_vertex_buffer->Get_Target(),
						instance.offset_vertex_buffer.offset,
						sizeof(ktkVertex) * data_v.size(), data_v.data());
					KOTEK_GL_ASSERT();

					glBindBuffer(this->m_p_vertex_buffer->Get_Target(), 0);
					KOTEK_GL_ASSERT();

					glBindBuffer(this->m_p_index_buffer->Get_Target(),
						this->m_p_index_buffer->Get_Handle());
					KOTEK_GL_ASSERT();

					glBufferSubData(this->m_p_index_buffer->Get_Target(),
						instance.offset_index_buffer.offset,
						sizeof(kun_ktk uint32_t) * data_i.size(),
						data_i.data());
					KOTEK_GL_ASSERT();

					glBindBuffer(this->m_p_index_buffer->Get_Target(), 0);
					KOTEK_GL_ASSERT();

					++this->m_current_indirect_commands_in_use;
				}
			}
		}
		else
		{
			glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(),
				this->m_p_draw_indirect_commands->Get_Handle());
			KOTEK_GL_ASSERT();

			auto& instance =
				this->m_indirect_commands_by_enum[static_geometry_type];

			ktkDrawElementsIndirectCommand* p_command = nullptr;
			glGetBufferSubData(this->m_p_draw_indirect_commands->Get_Target(),
				instance.indirect_buffer_offset_index *
					sizeof(ktkDrawElementsIndirectCommand),
				sizeof(ktkDrawElementsIndirectCommand), p_command);
			KOTEK_GL_ASSERT();

			KOTEK_ASSERT(p_command, "failed to get memory from gpu");

			if (p_command)
			{
				p_command->instanceCount += 1;
			}

			glBindBuffer(this->m_p_draw_indirect_commands->Get_Target(), 0);
			KOTEK_GL_ASSERT();
		}

		/*
		if (this->m_vertex_buffer_offsets.find(static_geometry_type) ==
		    this->m_vertex_buffer_offsets.end())
		{
		    this->m_vertex_buffer_offsets[static_geometry_type] =
		        this->m_p_vertex_buffer->AllocateOffset(
		            sizeof(ktkVertex) * data_v.size());

		    const auto& info_alloc =
		        this->m_vertex_buffer_offsets.at(static_geometry_type);

		    glBindBuffer(this->m_p_vertex_buffer->Get_Target(),
		        this->m_p_vertex_buffer->Get_Handle());
		    KOTEK_GL_ASSERT();

		    glBufferSubData(this->m_p_vertex_buffer->Get_Target(),
		        info_alloc.offset, sizeof(ktkVertex) * data_v.size(),
		        data_v.data());
		    KOTEK_GL_ASSERT();

		    glBindBuffer(this->m_p_vertex_buffer->Get_Target(), 0);
		    KOTEK_GL_ASSERT();
		}

		if (this->m_index_buffer_offsets.find(static_geometry_type) ==
		    this->m_index_buffer_offsets.end())
		{
		    this->m_index_buffer_offsets[static_geometry_type] =
		        this->m_p_index_buffer->AllocateOffset(
		            sizeof(uint32_t) * data_i.size());

		    const auto& info_alloc =
		        this->m_index_buffer_offsets.at(static_geometry_type);

		    glBindBuffer(this->m_p_index_buffer->Get_Target(),
		        this->m_p_index_buffer->Get_Handle());
		    KOTEK_GL_ASSERT();

		    glBufferSubData(this->m_p_index_buffer->Get_Target(),
		        info_alloc.offset, sizeof(uint32_t) * data_i.size(),
		        data_i.data());
		    KOTEK_GL_ASSERT();

		    glBindBuffer(this->m_p_index_buffer->Get_Target(), 0);
		    KOTEK_GL_ASSERT();
		}
		*/

		/*
		if (this->m_storage.find(id) == this->m_storage.end())
		{
		    this->m_storage[id] =
		        this->m_p_vertex->AllocateOffset(sizeof(ktkVertex) *
		data_v.size());
		}
		else
		{
		    this->FreeOffset(id);
		    this->m_storage[id] =
		        this->m_p_vertex->AllocateOffset(sizeof(ktkVertex) *
		data_v.size());
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

	ktkRenderStats* ktkRenderGeometryManager::Get_StatVertexBuffer(
		void) noexcept
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

		return p_result;
	}

	bool ktkRenderGeometryManager::Is_DrawIndirectCommandsChanged(void) noexcept
	{
		// TODO: finish this
		return false;
	}

	void ktkRenderGeometryManager::Rebuild_DrawIndirectCommands(void) noexcept
	{
		// TODO: finish this
	}

	void ktkRenderGeometryManager::Rebuild_SSBO_Instancing_Matricies(
		void) noexcept
	{
		// TODO: finish this
	}

	ktkRenderBuffer* ktkRenderGeometryManager::Get_Buffer_DrawIndirectCommands(
		void) const
	{
		return this->m_p_draw_indirect_commands;
	}

	const ktkRenderGeometryManager::ktk_render_indirect_commands_by_enum_t&
	ktkRenderGeometryManager::Get_IndirectCommands_PredefinedModels(void) const
	{
		return this->m_indirect_commands_by_enum;
	}

	GLuint ktkRenderGeometryManager::Get_CurrentIndirectCommandsInUse() const
	{
		return this->m_current_indirect_commands_in_use;
	}

	void ktkRenderGeometryManager::FreeOffset(ktk::uint32_t id) {}

	kun_ktk uint32_t ktkRenderGeometryManager::Get_FreeSlotOfIndirectCommand(
		void) const
	{
		kun_ktk uint32_t result = -1;

		for (kun_ktk uint32_t i = 0;
			i < KOTEK_DEF_RENDER_INDIRECT_DRAWING_TOTAL_COMMANDS; ++i)
		{
			if (!this->m_free_slots_of_indirect_commands[i])
			{
				result = i;
				break;
			}
		}

		KOTEK_ASSERT(result != kun_ktk uint32_t(-1),
			"out of free commands can't render your geometry!");

		return result;
	}
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
