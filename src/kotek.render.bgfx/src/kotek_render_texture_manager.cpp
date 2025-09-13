#include "../include/kotek_render_texture_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

ktkRenderTextureManager::ktkRenderTextureManager(
	kun_core ktkMainManager* p_main_manager) :
	m_memory_size{}, m_available_memory{}, m_used_memory{},
	m_p_main_manager{p_main_manager}
{
}

ktkRenderTextureManager::~ktkRenderTextureManager(void) {}

void ktkRenderTextureManager::Initialize(kun_ktk size_t memory_size)
{
	this->m_memory_size = memory_size;
	this->m_available_memory = memory_size;

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE(
		"initialized texture manager with: {} Mb <=> {} Kb <=> {} bytes",
		this->m_memory_size / (1024 * 1024), this->m_memory_size / 1024,
		this->m_memory_size);
#endif
}

void ktkRenderTextureManager::Shutdown(void) {}

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK