#pragma once

// Resource management structures
#include "kotek_render_command_list_ring.h"
#include "kotek_render_dynamic_buffer_ring.h"
#include "kotek_render_resource_view_heap.h"
#include "kotek_render_shader_manager.h"
#include "kotek_render_static_buffer_pool.h"
#include "kotek_render_texture_manager.h"
#include "kotek_render_upload_heap.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderSwapchain;
			class ktkRenderDevice;
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			// We are queuing (backBufferCount + 0.5) frames, so we need to
			// triple buffer the resources that get modified each frame
			constexpr ktk::uint32_t _kSwapchainBackBuffers = 3;

			// TODO: delete functions about creation resources for swapchain,
			// because render graph resource manager have already implemented it
			// TODO: пересмотреть дизайн и перенести в юзер реализацию, нет
			// стандарта для ресурс манагера в рендере
			class ktkRenderResourceManager
				: public Core::ktkIRenderResourceManager
			{
			public:
				ktkRenderResourceManager(
					ktkRenderDevice* p_device, Core::ktkMainManager* p_manager);
				ktkRenderResourceManager(void) = delete;
				~ktkRenderResourceManager(void);

				ktkRenderResourceManager(
					const ktkRenderResourceManager&) = delete;
				ktkRenderResourceManager& operator=(
					const ktkRenderResourceManager&) = delete;
				ktkRenderResourceManager(ktkRenderResourceManager&&) = delete;
				ktkRenderResourceManager& operator=(
					ktkRenderResourceManager&&) = delete;

				void initialize(Core::ktkIRenderDevice* p_raw_device,
					Core::ktkIRenderSwapchain* p_raw_swapchain,
					ktk::size_t memory_size =
						ktk::kMemoryConvertValue_Megabytes * 32) override;

				void shutdown(Core::ktkIRenderDevice* p_raw_device) override;

				void Resize(Core::ktkIRenderDevice* p_raw_device,
					Core::ktkIRenderSwapchain* p_raw_swapchain) override;

				void LoadGeometry(ktk::enum_base_t resource_loading_type,
					ktk::entity_t id) override;
				void LoadGeometry(ktk::enum_base_t resource_loading_type,
					const ktk::filesystem::path& path_to_file,
					ktk::entity_t id) override;

				kotek_render_dynamic_buffer_ring* GetDynamicBufferRing(
					void) noexcept;

				kotek_render_upload_heap* getUploadHeap(void) noexcept;

				ktkRenderTextureManager* GetTextureManager(void) noexcept;

				kotek_render_resource_view_heap* GetCreatorHeap(void) noexcept;

				kotek_render_shader_manager* getShaderManager(void) noexcept;

				VkRenderPass getSwapchainRenderPass(void) const noexcept;

				const VkFramebuffer getSwapchainFrameBuffer(
					ktk::uint32_t acquired_swapchain_index) const noexcept;

				const VkDescriptorPool getDescriptorPool(void) const noexcept;

				/*
				  VkShaderModule loadShader(Core::ktkMainManager& main_manager,
				                                   const ktk::string& path,
				                                   shader_type_t type) noexcept
				  {
				    return this->m_manager_shader.loadShader(main_manager, path,
				  type);
				  }

				  VkShaderModule loadShader(Core::ktkMainManager& main_manager,
				                                   const ktk::string& path)
				  noexcept
				  {
				    return this->m_manager_shader.loadShader(main_manager,
				  path);
				  }

				  VkShaderModule loadShaderAsString(ktkRenderDevice*
				  p_render_device, const ktk::string& code_as_string,
				  shader_type_t type) noexcept
				  {
				    return
				  this->m_manager_shader.loadShaderAsString(p_render_device,
				                                                     code_as_string,
				  type);
				  }*/

				VkPipelineShaderStageCreateInfo buildShader(
					shader_type_t type, VkShaderModule p_module) noexcept;

				void uploadAllResourcesToGPU(void) noexcept;

				VkImage GetSwapchainImage(
					ktk::uint32_t acquired_index) const noexcept;

			private:
				void createStaticAllocators(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyStaticAllocators(
					ktkRenderDevice* p_render_device) noexcept;

				void createSwapchainRTVs(ktkRenderDevice* p_render_device,
					ktkRenderSwapchain* p_render_swapchain);
				void destroySwapchainRTVs(ktkRenderDevice* p_render_device);

				void createDSV(void);

				void createSwapchainRenderPass(ktkRenderDevice* p_render_device,
					ktkRenderSwapchain* p_render_swapchain);
				void createSwapchainImages(ktkRenderDevice* p_render_device,
					ktkRenderSwapchain* p_render_swapchain);
				void createSwapchainImagesView(ktkRenderDevice* p_render_device,
					ktkRenderSwapchain* p_render_swapchain);
				void createSwapchainFrameBuffers(
					ktkRenderDevice* p_render_device);

				void destroySwapchainRenderPass(
					ktkRenderDevice* p_render_device);
				void destroySwapchainImagesView(
					ktkRenderDevice* p_render_device);
				void destroySwapchainFrameBuffers(
					ktkRenderDevice* p_render_device);

				void Resize(ktkRenderDevice* p_render_device,
					ktkRenderSwapchain* p_render_swapchain);

			private:
				ktk::uint32_t m_swapchain_image_count;
				VkRenderPass m_p_render_pass_swapchain;
				ktkRenderDevice* m_p_device;
				ktk::vector<VkImage> m_swapchain_images;
				ktk::vector<VkImageView> m_swapchain_images_view;
				ktk::vector<VkFramebuffer> m_swapchain_framebuffers;

				kotek_render_static_buffer_pool m_static_buffer_cpu_access;
				kotek_render_static_buffer_pool m_static_buffer_gpu_access_only;
				kotek_render_resource_view_heap m_resource_view_heap;
				kotek_render_dynamic_buffer_ring m_dynamic_buffer_ring;
				kotek_render_upload_heap m_upload_heap;

				kotek_render_shader_manager m_manager_shader;
				ktkRenderTextureManager m_manager_texture;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
