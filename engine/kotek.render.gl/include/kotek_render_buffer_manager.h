#pragma once

#include "offsetAllocator.hpp"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkRenderBufferManager
{
public:
	/// \~english @brief  
	ktkRenderBufferManager();

	/// \~english @brief 
	~ktkRenderBufferManager();

	/// \~english @brief Method for initializing manager that handles with
	/// allocated buffer with OffsetAllocator::Allocator
	/// @param memory_size the required memory for allocating buffer through
	/// glBufferData calling
	/// @param debug_name for printing information for what you create this
	/// instance (vertex, index, ssbo, etc)
	/// @param target refers to target in OpenGL like GL_ARRAY_BUFFER,
	/// GL_SHADER_STORAGE_BUFFER etc
	/// @param index_binding_in_shader if you pass as -1 it means that it uses
	/// glBindBufferBase it is for SSBO or other features, if you want to create
	/// general index, vertex buffer just don't pass any variable to this
	/// argument. By default it accepts -1.
	void Initialize(ktk::size_t memory_size, const ktk::cstring& debug_name,
		GLenum target, Core::eRenderStatistics stat_type, GLuint index_binding_in_shader = -1) noexcept;

	void Shutdown(void);

	OffsetAllocator::Allocation AllocateOffset(ktk::size_t mem);
	void FreeOffset(const OffsetAllocator::Allocation& info);

	const ktk::cstring& Get_DescriptionName(void) const noexcept;

	const ktk::vector<GLuint>& Get_Handles(void) const noexcept;

	GLenum Get_Target(void) const noexcept;

	ktkRenderStats* Get_Stat(void) noexcept;

private:
	bool m_is_reallocation;
	GLenum m_target;
	OffsetAllocator::Allocator* m_p_allocator;
	ktkRenderStats m_stats;
	ktk::vector<GLuint> m_handles;
	ktk::cstring m_description_name;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK