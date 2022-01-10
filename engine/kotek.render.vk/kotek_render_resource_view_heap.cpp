#include "kotek_render_resource_view_heap.h"
#include "kotek_render_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			// TODO: load from sys_info.json
			constexpr ktk::uint32_t _kMaxSets = 8000;

			kotek_render_resource_view_heap::kotek_render_resource_view_heap() :
				m_allocated_descriptor_count(0), m_p_descriptor_pool(nullptr)
			{
			}

			kotek_render_resource_view_heap::~kotek_render_resource_view_heap()
			{
			}

			void kotek_render_resource_view_heap::initialize(
				ktkRenderDevice* p_render_device,
				ktk::uint32_t descriptor_count_cbv,
				ktk::uint32_t descriptor_count_srv,
				ktk::uint32_t descriptor_count_uav,
				ktk::uint32_t descriptor_count_sampler) noexcept
			{
				this->m_allocated_descriptor_count = 0;

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("descriptor count UNIFORM BUFFER AND UNIFORM "
							  "BUFFER DYNAMIC (cbv): {}",
					descriptor_count_cbv);

				KOTEK_MESSAGE(
					"descriptor count COMBINED IMAGE SAMPLER (srv): {}",
					descriptor_count_srv);

				KOTEK_MESSAGE(
					"descirptor count SAMPLER: {}", descriptor_count_sampler);

				KOTEK_MESSAGE("descriptor count STORAGE BUFFER (uav): {}",
					descriptor_count_uav);
#endif

				const VkDescriptorPoolSize p_pools_and_their_sizes[] = {
					{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
						descriptor_count_cbv},
					{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, descriptor_count_cbv},
					{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
						descriptor_count_srv},
					{VK_DESCRIPTOR_TYPE_SAMPLER, descriptor_count_sampler},
					{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, descriptor_count_uav}};

				VkDescriptorPoolCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				info.pNext = nullptr;
				info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
				info.maxSets = _kMaxSets;
				info.poolSizeCount = sizeof(p_pools_and_their_sizes) /
					sizeof(p_pools_and_their_sizes[0]);
				info.pPoolSizes = p_pools_and_their_sizes;

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkResult status = vkCreateDescriptorPool(
					p_device, &info, nullptr, &this->m_p_descriptor_pool);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't create descirptor pool. See status");
			}

			void kotek_render_resource_view_heap::shutdown(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkDestroyDescriptorPool(
					p_device, this->m_p_descriptor_pool, nullptr);
			}

			bool kotek_render_resource_view_heap::AllocDescriptor(
				ktkRenderDevice* p_render_device,
				VkDescriptorSetLayout p_layout, VkDescriptorSet* p_set) noexcept
			{
				// TODO: cpu sync

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkDescriptorSetAllocateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				info.pNext = nullptr;
				info.descriptorPool = this->m_p_descriptor_pool;
				info.descriptorSetCount = 1;
				info.pSetLayouts = &p_layout;

				VkResult status =
					vkAllocateDescriptorSets(p_device, &info, p_set);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"you must initialize device (VkDevice)");

				++this->m_allocated_descriptor_count;

				return true;
			}

			bool kotek_render_resource_view_heap::AllocDescriptor(
				ktkRenderDevice* p_render_device, ktk::int32_t size,
				const VkSampler* p_samplers, VkDescriptorSetLayout* p_layout,
				VkDescriptorSet* p_descriptor) noexcept
			{
				ktk::vector<VkDescriptorSetLayoutBinding> temp(size);

				for (ktk::int32_t i = 0; i < size; ++i)
				{
					temp[i].binding = i;
					temp[i].descriptorType =
						VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
					temp[i].descriptorCount = 1;
					temp[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
					temp[i].pImmutableSamplers =
						p_samplers ? &p_samplers[i] : nullptr;
				}

				return this->createDescriptorSetLayoutAndAllocDescriptorSet(
					p_render_device, &temp, p_layout, p_descriptor);
			}

			bool kotek_render_resource_view_heap::createDescriptorSetLayout(
				ktkRenderDevice* p_render_device,
				ktk::vector<VkDescriptorSetLayoutBinding>*
					p_descriptor_layout_binding,
				VkDescriptorSetLayout* p_layout) noexcept
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkDescriptorSetLayoutCreateInfo info = {};

				info.sType =
					VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				info.pNext = nullptr;
				info.bindingCount = static_cast<ktk::uint32_t>(
					p_descriptor_layout_binding->size());
				info.pBindings = p_descriptor_layout_binding->data();

				VkResult status = vkCreateDescriptorSetLayout(
					p_device, &info, nullptr, p_layout);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't create descriptor set layout. See status");

				return true;
			}

			bool kotek_render_resource_view_heap::
				createDescriptorSetLayoutAndAllocDescriptorSet(
					ktkRenderDevice* p_render_device,
					ktk::vector<VkDescriptorSetLayoutBinding>*
						p_descriptor_layout_binding,
					VkDescriptorSetLayout* p_layout,
					VkDescriptorSet* p_set) noexcept
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkDescriptorSetLayoutCreateInfo info = {};

				info.sType =
					VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				info.pNext = nullptr;
				info.bindingCount = static_cast<ktk::uint32_t>(
					p_descriptor_layout_binding->size());
				info.pBindings = p_descriptor_layout_binding->data();

				VkResult status = vkCreateDescriptorSetLayout(
					p_device, &info, nullptr, p_layout);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't create descriptor set layout. See status");

				return this->AllocDescriptor(p_render_device, *p_layout, p_set);
			}

			void kotek_render_resource_view_heap::freeDescriptor(
				ktkRenderDevice* p_render_device, VkDescriptorSet p_set)
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				--this->m_allocated_descriptor_count;
				vkFreeDescriptorSets(
					p_device, this->m_p_descriptor_pool, 1, &p_set);
			}

			const VkDescriptorPool
			kotek_render_resource_view_heap::getDescriptorPool(
				void) const noexcept
			{
				return this->m_p_descriptor_pool;
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
