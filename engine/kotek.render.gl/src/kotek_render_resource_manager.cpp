#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_texture_manager.h"
#include "../include/kotek_render_shader_manager.h"
#include "../include/kotek_render_geometry_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderResourceManager::ktkRenderResourceManager(
		Core::ktkIRenderDevice* p_device, Core::ktkMainManager* p_manager) :
		m_p_render_device{p_device},
		m_p_render_manager_texture{}, m_p_render_manager_shader{},
		m_p_main_manager{p_manager}
	{
	}

	ktkRenderResourceManager::~ktkRenderResourceManager(void)
	{
		if (this->m_p_render_manager_texture)
		{
			delete this->m_p_render_manager_texture;
			this->m_p_render_manager_texture = nullptr;
		}

		if (this->m_p_render_manager_shader)
		{
			delete this->m_p_render_manager_shader;
			this->m_p_render_manager_shader = nullptr;
		}

		if (this->m_p_render_manager_geometry)
		{
			delete this->m_p_render_manager_geometry;
			this->m_p_render_manager_geometry = nullptr;
		}
	}

	void ktkRenderResourceManager::initialize(
		Core::ktkIRenderDevice* p_raw_device,
		Core::ktkIRenderSwapchain* p_raw_swapchain, ktk::size_t memory_size)
	{
		KOTEK_ASSERT(p_raw_device, "you can't pass an invalid interface");
		KOTEK_ASSERT(p_raw_swapchain, "you can't pass an invalid interface");

		this->m_p_render_manager_texture =
			new ktkRenderTextureManager(this->m_p_main_manager);
		this->m_p_render_manager_shader =
			new ktkRenderShaderManager(this->m_p_main_manager);
		this->m_p_render_manager_geometry = new ktkRenderGeometryManager();

		ktk::size_t total_memory = memory_size;

		auto tex_mem =
			ktk::align_down<ktk::size_t>((((memory_size / 100) * 75)), 2);
		this->m_p_render_manager_texture->Initialize(tex_mem);

		total_memory -= tex_mem;

		auto uniform_mem =
			ktk::align_down<ktk::size_t>((((memory_size / 100) * 5)), 2);
		this->m_p_render_manager_shader->Initialize(uniform_mem);

		total_memory -= uniform_mem;

		this->m_p_render_manager_geometry->Initialize(total_memory);
	}

	void ktkRenderResourceManager::shutdown(
		Core::ktkIRenderDevice* p_raw_device)
	{
		KOTEK_ASSERT(p_raw_device, "you can't pass an invalid interface");

		if (this->m_p_render_manager_texture)
			this->m_p_render_manager_texture->Shutdown();

		if (this->m_p_render_manager_shader)
			this->m_p_render_manager_shader->Shutdown();

		if (this->m_p_render_manager_geometry)
			this->m_p_render_manager_geometry->Shutdown();
	}

	void ktkRenderResourceManager::Resize(Core::ktkIRenderDevice* p_raw_device,
		Core::ktkIRenderSwapchain* p_raw_swapchain)
	{
		KOTEK_ASSERT(p_raw_device, "you can't pass an invalid interface");
		KOTEK_ASSERT(p_raw_swapchain, "you can't pass an invalid interface");
	}

	void ktkRenderResourceManager::LoadGeometry(
		ktk::enum_base_t resource_loading_type, ktk::entity_t id)
	{
		Kotek::Core::eResourceLoadingType type =
			static_cast<Kotek::Core::eResourceLoadingType>(
				resource_loading_type);

		switch (type)
		{
		case Kotek::Core::eResourceLoadingType::kModelStatic_Triangle:
		{
			if (this->m_p_render_manager_geometry)
			{
				this->m_p_render_manager_geometry->AddForUpload(
					{{0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f},
						{-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}},
					{0, 1, 3, 1, 2, 3}, id);
			}

			break;
		}
		case Kotek::Core::eResourceLoadingType::kModelStatic_Box:
		{
			if (this->m_p_render_manager_geometry)
			{
			}

			break;
		}
		default:
		{
			KOTEK_ASSERT(false, "not implemented");
		}
		}
	}

	void ktkRenderResourceManager::LoadGeometry(
		ktk::enum_base_t resource_loading_type,
		const ktk::filesystem::path& path_to_file, ktk::entity_t id)
	{
	}

	void ktkRenderResourceManager::Update(void) noexcept
	{
		if (this->m_p_render_manager_geometry)
		{
			this->m_p_render_manager_geometry->Update();
		}
	}

	ktkRenderTextureManager* ktkRenderResourceManager::Get_ManagerTexture(
		void) const noexcept
	{
		return this->m_p_render_manager_texture;
	}

	ktkRenderShaderManager* ktkRenderResourceManager::Get_ManagerShader(
		void) const noexcept
	{
		return this->m_p_render_manager_shader;
	}
	ktkRenderGeometryManager* ktkRenderResourceManager::Get_ManagerGeometry(
		void) const noexcept
	{
		return this->m_p_render_manager_geometry;
	}

	ktkRenderStats* ktkRenderResourceManager::Get_Statistic(
		Core::eRenderStatistics type) noexcept
	{
		ktkRenderStats* p_result{};

		switch (type)
		{
		case Core::eRenderStatistics::kStat_Buffer_Index:
		{
			if (this->m_p_render_manager_geometry)
			{
				p_result =
					this->m_p_render_manager_geometry->Get_StatIndexBuffer();
			}

			break;
		}
		case Core::eRenderStatistics::kStat_Buffer_SSBO_Matrix:
		{
			if (this->m_p_render_manager_geometry)
			{
				p_result = this->m_p_render_manager_geometry
							   ->Get_StatSSBOBufferMatrix();
			}

			break;
		}
		case Core::eRenderStatistics::kStat_Buffer_Vertex:
		{
			if (this->m_p_render_manager_geometry)
			{
				p_result =
					this->m_p_render_manager_geometry->Get_StatVertexBuffer();
			}

			break;
		}
		default:
		{
			KOTEK_ASSERT(false, "can't obtain render stat");
			break;
		}
		}

		return p_result;
	}
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK