#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

class ktkRenderBuffer
{
public:
	ktkRenderBuffer();

	~ktkRenderBuffer();

	void Initialize(kun_ktk size_t memory_size, eBufferType buffer_type
#ifdef KOTEK_DEBUG
		,
		const ktk_cstring<64>& debug_name
#endif
		) noexcept;

	void Shutdown(void);

	// TODO: make preprocessor KOTEK_DEF_BUFFER_DEBUG_NAME_LENGTH
	const ktk_cstring<64>& Get_DebugName(void) const noexcept;

	ktkRenderStats* Get_Stat(void) noexcept;

private:
#ifdef KOTEK_DEBUG
	bool m_is_shutdown_was_called;
#endif
	bool m_is_reallocation;

	OffsetAllocator::Allocator* m_p_allocator;

	ktkRenderStats m_stats;

#ifdef KOTEK_DEBUG
	ktk_cstring<64> m_debug_name;
#endif
};

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK