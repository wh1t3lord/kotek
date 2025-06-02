#include "../include/kotek_render_texture_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderTextureManager::ktkRenderTextureManager(
		Core::ktkMainManager* p_main_manager) :
		m_memory_size{},
		m_available_memory{}, m_used_memory{}, m_p_main_manager{p_main_manager}
	{
	}

	ktkRenderTextureManager::~ktkRenderTextureManager(void) {}

	void ktkRenderTextureManager::Initialize(ktk::size_t memory_size)
	{
		this->m_memory_size = memory_size;
		this->m_available_memory = memory_size;

#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("initialized texture manager with: {} Mb",
			this->m_memory_size / (1024 * 1024));
#endif
	}

	void ktkRenderTextureManager::Shutdown(void) {}

	bool ktkRenderTextureManager::Create_Texture(
		const ktk::ustring& texture_name,
		const gl::ktkRenderGraphTextureInfo& info_create) noexcept
	{
		KOTEK_ASSERT(texture_name.empty() == false,
			"you can't pass an empty texture name");

		return false;
	}

	void ktkRenderTextureManager::Destroy_Texture(
		const ktk::ustring& texture_name) noexcept
	{
		KOTEK_ASSERT(texture_name.empty() == false,
			"you can't pass an empty texture name");
	}
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK