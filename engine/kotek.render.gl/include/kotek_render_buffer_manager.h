#pragma once

#include "offsetAllocator.hpp"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkRenderBufferManager
{
public:
	ktkRenderBufferManager();
	~ktkRenderBufferManager();

	void Initialize(ktk::size_t memory_size, const ktk::cstring& debug_name, GLenum target) noexcept;
	void Shutdown(void);

	OffsetAllocator::Allocation AllocateOffset(ktk::size_t mem);
	void FreeOffset(const OffsetAllocator::Allocation& info);

	const ktk::cstring& Get_DescriptionName(void) const noexcept;

	const ktk::vector<GLuint>& Get_Handles(void) const noexcept;

	GLenum Get_Target(void) const noexcept;

private:
	bool m_is_reallocation;
	ktk::size_t m_memory_size;
	ktk::size_t m_used_memory;
	ktk::size_t m_available_memory;
	GLenum m_target;
	OffsetAllocator::Allocator* m_p_allocator;
	ktk::vector<GLuint> m_handles;
	ktk::cstring m_description_name;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK