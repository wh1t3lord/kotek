#include "../include/kotek_render_buffer_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkRenderBufferManager::ktkRenderBufferManager() :
	m_is_reallocation{}, m_memory_size{}, m_used_memory{},
	m_available_memory{}, m_target{}, m_p_allocator{}
{
}

ktkRenderBufferManager::~ktkRenderBufferManager() {}

void ktkRenderBufferManager::Initialize(ktk::size_t memory_size,
	const ktk::cstring& debug_name, GLenum target) noexcept
{
	KOTEK_ASSERT(memory_size > 0, "you must pass a valid amount of memory");
	KOTEK_ASSERT(
		debug_name.empty() == false, "you must pass a not empty string");

	this->m_description_name = debug_name;
	this->m_memory_size = memory_size;

	if (this->m_is_reallocation == false)
	{
		GLuint id;
		glGenBuffers(1, &id);
		KOTEK_GL_ASSERT();

		glBindBuffer(target, id);
		KOTEK_GL_ASSERT();

		glBufferData(target, memory_size, nullptr, GL_STATIC_DRAW);
		KOTEK_GL_ASSERT();

		this->m_target = target;
		this->m_handles.push_back(id);
	}

	this->m_p_allocator = new OffsetAllocator::Allocator(memory_size);

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("Initialized {} with: {} Mb", this->m_description_name,
		static_cast<double>(memory_size) / (1024.0 * 1024.0));
#endif
}

void ktkRenderBufferManager::Shutdown(void)
{
	for (auto id : this->m_handles)
	{
		glDeleteBuffers(1, &id);
		KOTEK_GL_ASSERT();

	}
}

OffsetAllocator::Allocation ktkRenderBufferManager::AllocateOffset(
	ktk::size_t mem)
{
	this->m_available_memory = this->m_memory_size - mem;
	return this->m_p_allocator->allocate(mem);
}

void ktkRenderBufferManager::FreeOffset(const OffsetAllocator::Allocation& info)
{
	this->m_available_memory += info.offset;
	this->m_p_allocator->free(info);
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

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK