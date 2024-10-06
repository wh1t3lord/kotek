#include "../include/kotek_render_buffer_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkRenderBufferManager::ktkRenderBufferManager() :
	m_is_reallocation{}, m_target{}, m_p_allocator{}
{
}

ktkRenderBufferManager::~ktkRenderBufferManager() {}

void ktkRenderBufferManager::Initialize(ktk::size_t memory_size,
	const ktk::cstring& debug_name, GLenum target,
	Core::eRenderStatistics stat_type, GLuint index_binding_in_shader) noexcept
{
	KOTEK_ASSERT(memory_size > 0, "you must pass a valid amount of memory");
	KOTEK_ASSERT(
		debug_name.empty() == false, "you must pass a not empty string");

	this->m_description_name = debug_name;

	// TODO: implement reallocation
	if (this->m_is_reallocation == false)
	{
		GLuint id;
		glGenBuffers(1, &id);
		KOTEK_GL_ASSERT();

		glBindBuffer(target, id);
		KOTEK_GL_ASSERT();

		glBufferData(target, memory_size, nullptr, GL_STATIC_DRAW);
		KOTEK_GL_ASSERT();

		if (index_binding_in_shader != GLuint(-1))
		{
			glBindBufferBase(target, index_binding_in_shader, id);
			KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("binding index: {}", index_binding_in_shader);
#endif
		}

		this->m_target = target;
		this->m_handles.push_back(id);
	}

	this->m_p_allocator = new OffsetAllocator::Allocator(memory_size);

	this->m_stats.Set_Type(stat_type);
	this->m_stats.Set_AllocatedMemory(memory_size);

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Initialized {} with: {} Mb", this->m_description_name,
		static_cast<double>(memory_size) / (1024.0 * 1024.0));
#endif
}

void ktkRenderBufferManager::Shutdown(void)
{
#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Destroying: {} [{}]", this->m_description_name,
		static_cast<double>(this->m_stats.Get_AllocatedMemory()) /
			(1024.0 * 1024.0));
#endif

	for (auto id : this->m_handles)
	{
		glDeleteBuffers(1, &id);
		KOTEK_GL_ASSERT();
	}
}

OffsetAllocator::Allocation ktkRenderBufferManager::AllocateOffset(
	ktk::size_t mem)
{
	this->m_stats.Set_FreeMemory(this->m_stats.Get_AllocatedMemory() - mem);
	this->m_stats.Set_UsedMemory(
		this->m_stats.Get_AllocatedMemory() - this->m_stats.Get_FreeMemory());

	return this->m_p_allocator->allocate(mem);
}

void ktkRenderBufferManager::FreeOffset(const OffsetAllocator::Allocation& info)
{
	this->m_stats.Set_FreeMemory(this->m_stats.Get_FreeMemory() + info.offset);
	this->m_stats.Set_UsedMemory(
		this->m_stats.Get_AllocatedMemory() - this->m_stats.Get_FreeMemory());

	this->m_p_allocator->deallocate(info);
}

const ktk::cstring& ktkRenderBufferManager::Get_DescriptionName(
	void) const noexcept
{
	return this->m_description_name;
}

const ktk::vector<GLuint>& ktkRenderBufferManager::Get_Handles(
	void) const noexcept
{
	return this->m_handles;
}

GLenum ktkRenderBufferManager::Get_Target(void) const noexcept
{
	return this->m_target;
}

ktkRenderStats* ktkRenderBufferManager::Get_Stat(void) noexcept
{
	return &this->m_stats;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK