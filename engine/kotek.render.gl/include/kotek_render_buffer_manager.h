#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkRenderBufferManager
{
public:
	ktkRenderBufferManager();
	~ktkRenderBufferManager();

	void Initialize(ktk::size_t memory_size, const ktk::cstring& debug_name, GLenum target) noexcept;
	void Shutdown(void);

	const ktk::cstring& Get_DescriptionName(void) const noexcept;

private:
	bool m_is_reallocation;
	ktk::size_t m_memory_size;
	ktk::size_t m_used_memory;
	ktk::size_t m_available_memory;
	ktk::vector<GLuint> m_handles;
	ktk::cstring m_description_name;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK