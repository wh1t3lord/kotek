#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

class ktkRenderTextureManager
{
public:
	ktkRenderTextureManager(kun_core ktkMainManager* p_main_manager);
	~ktkRenderTextureManager(void);

	void Initialize(kun_ktk size_t memory_size);
	void Shutdown(void);

private:
	// we just collect stats for validating
	kun_ktk size_t m_memory_size;
	kun_ktk size_t m_available_memory;
	kun_ktk size_t m_used_memory;

	kun_core ktkMainManager* m_p_main_manager;
};

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK