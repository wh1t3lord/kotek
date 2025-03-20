#include "../include/kotek_render_buffer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkRenderBuffer::ktkRenderBuffer() :
#ifdef KOTEK_DEBUG
	m_is_shutdown_was_called{},
#endif

	m_is_reallocation{}, m_target{}, m_p_allocator{}
{
}

ktkRenderBuffer::~ktkRenderBuffer()
{
#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(this->m_is_shutdown_was_called,
		"you forgot to call shutdown for buffer", this->m_description_name);
#endif

	if (this->m_p_allocator)
	{
		delete this->m_p_allocator;
		this->m_p_allocator = nullptr;
	}
}

void ktkRenderBuffer::Initialize(kun_ktk size_t memory_size,
	const ktk_cstring<64>& debug_name, GLenum target,
	kun_core eRenderStatistics stat_type, GLenum usage,
	GLuint index_binding_in_shader) noexcept
{
	KOTEK_ASSERT(memory_size > 0, "you must pass a valid amount of memory");
	KOTEK_ASSERT(
		debug_name.empty() == false, "you must pass a not empty string");

#ifdef KOTEK_DEBUG
	this->m_description_name = debug_name;
#endif

	// TODO: implement reallocation
	if (this->m_is_reallocation == false)
	{
		GLuint id;
		glGenBuffers(1, &id);
		KOTEK_GL_ASSERT();

		glBindBuffer(target, id);
		KOTEK_GL_ASSERT();

		glBufferData(target, memory_size, nullptr, usage);
		KOTEK_GL_ASSERT();

		if (index_binding_in_shader != GLuint(-1))
		{
			glBindBufferBase(target, index_binding_in_shader, id);
			KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("binding index: {}", index_binding_in_shader);
#endif
		}

		glBindBuffer(target, 0);
		KOTEK_GL_ASSERT();

		this->m_target = target;
		this->m_handle = id;
	}

	this->m_p_allocator = new OffsetAllocator::Allocator(memory_size);

	this->m_stats.Set_Type(stat_type);
	this->m_stats.Set_AllocatedMemory(memory_size);

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Initialized {} with: {} Mb", this->m_description_name,
		static_cast<double>(memory_size) / (1024.0 * 1024.0));
#endif
}

void ktkRenderBuffer::Shutdown(void)
{
#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Destroying: {} [{}]", this->m_description_name,
		static_cast<double>(this->m_stats.Get_AllocatedMemory()) /
			(1024.0 * 1024.0));
	this->m_is_shutdown_was_called = true;
#endif

	glDeleteBuffers(1, &this->m_handle);
	KOTEK_GL_ASSERT();
}

OffsetAllocator::Allocation ktkRenderBuffer::AllocateOffset(ktk::size_t mem)
{
	this->m_stats.Set_FreeMemory(this->m_stats.Get_AllocatedMemory() - mem);
	this->m_stats.Set_UsedMemory(
		this->m_stats.Get_AllocatedMemory() - this->m_stats.Get_FreeMemory());

	return this->m_p_allocator->allocate(mem);
}

void ktkRenderBuffer::FreeOffset(const OffsetAllocator::Allocation& info)
{
	this->m_stats.Set_FreeMemory(this->m_stats.Get_FreeMemory() + info.offset);
	this->m_stats.Set_UsedMemory(
		this->m_stats.Get_AllocatedMemory() - this->m_stats.Get_FreeMemory());

	this->m_p_allocator->deallocate(info);
}

const ktk_cstring<64>& ktkRenderBuffer::Get_DescriptionName(void) const noexcept
{
	return this->m_description_name;
}

GLuint ktkRenderBuffer::Get_Handle(void) const noexcept
{
	return this->m_handle;
}

GLenum ktkRenderBuffer::Get_Target(void) const noexcept
{
	return this->m_target;
}

ktkRenderStats* ktkRenderBuffer::Get_Stat(void) noexcept
{
	return &this->m_stats;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK