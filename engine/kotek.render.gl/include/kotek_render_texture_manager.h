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

		void Initialize(ktk::size_t memory_size);
		void Shutdown(void);

		bool Create_Texture(const ktk::string& texture_name,
			const gl::ktkRenderGraphTextureInfo& info_create) noexcept;

		void Destroy_Texture(const ktk::string& texture_name) noexcept;

	private:
		// we just collect stats for validating
		ktk::size_t m_memory_size;
		ktk::size_t m_available_memory;
		ktk::size_t m_used_memory;

		Core::ktkMainManager* m_p_main_manager;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK