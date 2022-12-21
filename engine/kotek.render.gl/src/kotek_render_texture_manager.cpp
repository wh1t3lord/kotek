#include "../include/kotek_render_texture_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderTextureManager::ktkRenderTextureManager(
		Core::ktkMainManager* p_main_manager) :
		m_p_main_manager{p_main_manager}
	{
	}

	ktkRenderTextureManager::~ktkRenderTextureManager(void) {}

	void ktkRenderTextureManager::Initialize(void) {}

	void ktkRenderTextureManager::Shutdown(void) {}

	bool ktkRenderTextureManager::Create_Texture(
		const ktk::string& texture_name,
		const gl::ktkRenderGraphTextureInfo& info_create) noexcept
	{
		KOTEK_ASSERT(texture_name.empty() == false,
			"you can't pass an empty texture name");

		return false;
	}

	void ktkRenderTextureManager::Destroy_Texture(
		const ktk::string& texture_name) noexcept
	{
		KOTEK_ASSERT(texture_name.empty() == false,
			"you can't pass an empty texture name");
	}
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK