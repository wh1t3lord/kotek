#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_device;
		}
	} // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_resource_view_heap
			{
			public:
				kotek_render_resource_view_heap(void);
				~kotek_render_resource_view_heap(void);

				void initialize(kotek_render_device* p_render_device,
					ktk::uint32_t descriptor_count_cbv,
					ktk::uint32_t descriptor_count_srv,
					ktk::uint32_t descriptor_count_uav,
					ktk::uint32_t descriptor_count_sampler) noexcept;

				void shutdown(kotek_render_device* p_render_device) noexcept;

				bool AllocDescriptor(kotek_render_device* p_render_device,
					VkDescriptorSetLayout p_layout,
					VkDescriptorSet* p_set) noexcept;

				bool AllocDescriptor(kotek_render_device* p_render_device,
					ktk::int32_t size, const VkSampler* p_samplers,
					VkDescriptorSetLayout* p_layout,
					VkDescriptorSet* p_descriptor) noexcept;

				bool createDescriptorSetLayout(
					kotek_render_device* p_render_device,
					ktk::vector<VkDescriptorSetLayoutBinding>*
						p_desriptor_layout_binding,
					VkDescriptorSetLayout* p_layout) noexcept;

				bool createDescriptorSetLayoutAndAllocDescriptorSet(
					kotek_render_device* p_render_device,
					ktk::vector<VkDescriptorSetLayoutBinding>*
						p_descriptor_layout_binding,
					VkDescriptorSetLayout* p_layout,
					VkDescriptorSet* p_set) noexcept;

				void freeDescriptor(kotek_render_device* p_render_device,
					VkDescriptorSet p_set);

				const VkDescriptorPool getDescriptorPool(void) const noexcept;

			private:
				int m_allocated_descriptor_count;
				VkDescriptorPool m_p_descriptor_pool;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
