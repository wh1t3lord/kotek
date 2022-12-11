#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderTextureManager
	{
	public:
		ktkRenderTextureManager(Core::ktkMainManager* p_main_manager);
		~ktkRenderTextureManager(void);

		void Initialize(void);
		void Shutdown(void);

		bool Create_Texture(const ktk::string& texture_name,
			const gl::ktkRenderGraphTextureInfo& info_create) noexcept;

		void Destroy_Texture(const ktk::string& texture_name) noexcept;

	private:
		Core::ktkMainManager* m_p_main_manager;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK