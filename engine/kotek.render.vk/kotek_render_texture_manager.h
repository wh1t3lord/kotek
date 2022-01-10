#pragma once

#include "../kotek.core/kotek_std.h"
#include "kotek_render_graph_data_types.h"
#include "kotek_render_shader_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			constexpr VkFormat kImageFormat =
				VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
			class ktkRenderDevice;
			class kotek_render_graph_resource_storage;
			class kotek_render_upload_heap;
			class ktkRenderResourceManager;
			class ktkRenderGraphResourceManager;
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace ktk
	{
		using pipeline_id_t = ktk::string;
		using render_pass_id_t = ktk::string;
		using texture_id_t = ktk::string;
	} // namespace ktk
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			enum class e_kotek_render_graph_builder_type_t : ktk::enum_base_t
			{
				/// <summary>
				/// Uses backbuffer only, so you have only one render target for
				/// all passes
				/// </summary>
				kRenderBuilderFor_Forward_Only,
				// TODO: implement for outputs but we need to merge into back
				// buffer?
				kRenderBuilderFor_Forward_With_Outputs,
				// TODO: implement for deferred sometime...
				kRenderBuilderFor_Deferred,
				kRenderBuilderFor_Undefined
			};

			enum class
				e_kotek_render_graph_builder_pipeline_rendering_type_t : ktk::
					enum_base_t
			{
				kRenderBuilderBasedOnPipeline_Orthodox,

				// TODO: add support for RTX in new version
				kRenderBuilderBasedOnPipeline_RTX
			};

			enum class e_resource_synchronization_status_t : ktk::enum_base_t
			{
				kEmpty,
				kFromOutputToInput,
				kToInputOnly
			};

			// TODO: think about array textures, because in VkImageCreateInfo we
			// need to specify arrayLayers
			/// <summary>
			/// This enum uses when we want to create a texture from
			/// texture_manager Because user must specify what type of texture
			/// is using by creation function In that case we can't detect type
			/// of view by format if we don't know what user wants from us
			///
			/// Single means we create a texture for 1D, 2D, 3D type and that's
			/// texture is single it means just one file and one information
			/// Array means we have multiple textures and we use view type for
			/// array it's 1D or 2D Cubemap means you have a cubemap which is
			/// had a type 2D from image and from view it's CUBEMAP
			/// </summary>
			enum class e_texture_type_t : ktk::enum_base_t
			{
				kTextureType_Single,
				kTextureType_Array,
				kTextureType_Cubemap_Single,
				kTextureType_Cubemap_Array,
				kTextureType_Unknown = -1
			};

			class ktkRenderGraphPipelineInfo
			{
			public:
				ktkRenderGraphPipelineInfo(
					const VkPipelineInputAssemblyStateCreateInfo&
						state_assembly,
					const VkPipelineRasterizationStateCreateInfo&
						state_rasterization,
					const VkPipelineViewportStateCreateInfo& state_viewport,
					const ktk::vector<VkPipelineColorBlendAttachmentState>&
						color_blend_attachments,
					const VkPipelineDepthStencilStateCreateInfo&
						state_depth_stencil,
					const ktk::vector<VkDynamicState>& dynamic_states,
					const VkPipelineMultisampleStateCreateInfo&
						state_multisample,
					const ktk::vector<VkVertexInputAttributeDescription>&
						vertex_attributes,
					const ktk::vector<VkVertexInputBindingDescription>&
						vertex_bindings,
					const VkPipelineTessellationStateCreateInfo&
						state_tessellation = {},
					ktk::uint32_t subpass_index = 0);

				ktkRenderGraphPipelineInfo(void);
				~ktkRenderGraphPipelineInfo(void);

				const VkPipelineInputAssemblyStateCreateInfo&
				GetPipelineInputAssemblyState(void) const noexcept;

				const VkPipelineRasterizationStateCreateInfo&
				GetPipelineRasterizationState(void) const noexcept;

				const VkPipelineDepthStencilStateCreateInfo&
				GetPipelineDepthStencilState(void) const noexcept;

				const VkPipelineViewportStateCreateInfo&
				GetPipelineViewportState(void) const noexcept;

				const VkPipelineMultisampleStateCreateInfo&
				GetPipelineMultisampleState(void) const noexcept;

				const VkPipelineTessellationStateCreateInfo&
				GetPipelineTessellationState(void) const noexcept;

				ktk::uint32_t GetSubpassIndex(void) const noexcept;

				const ktk::vector<VkVertexInputBindingDescription>&
				GetVertexBindingDescriptions(void) const noexcept;

				const ktk::vector<VkVertexInputAttributeDescription>&
				GetVertexAttributes(void) const noexcept;

				const ktk::vector<VkDynamicState>& GetDynamicStates(
					void) const noexcept;

				const ktk::vector<VkPipelineColorBlendAttachmentState>&
				GetColorBlendAttachments(void) const noexcept;

			private:
				ktk::uint32_t m_subpass_index;
				ktk::vector<VkPipelineColorBlendAttachmentState>
					m_attachments_blend;
				ktk::vector<VkDynamicState> m_dynamic_states;
				ktk::vector<VkVertexInputBindingDescription>
					m_vertex_descriptions;
				ktk::vector<VkVertexInputAttributeDescription>
					m_vertex_attributes;
				VkPipelineInputAssemblyStateCreateInfo m_state_assembly;
				VkPipelineRasterizationStateCreateInfo m_state_rasterization;
				VkPipelineColorBlendStateCreateInfo m_state_color_blend;
				VkPipelineDepthStencilStateCreateInfo m_state_depth_stencil;
				VkPipelineViewportStateCreateInfo m_state_viewport;
				VkPipelineMultisampleStateCreateInfo m_state_multisample;
				VkPipelineDynamicStateCreateInfo m_state_dynamic;
				VkPipelineVertexInputStateCreateInfo m_state_vertex;
				VkPipelineTessellationStateCreateInfo m_state_tessellation;
			};

			class kotek_render_texture_create_info_t
			{
			public:
				kotek_render_texture_create_info_t(
					const VkImageCreateInfo& info_image,
					const VkSamplerCreateInfo& info_sampler) :
					m_info_image(info_image),
					m_info_sampler(info_sampler)
				{
				}

				kotek_render_texture_create_info_t(void) = default;
				~kotek_render_texture_create_info_t(void) = default;

				void setImageCreateInfo(const VkImageCreateInfo& info) noexcept
				{
					this->m_info_image = info;
				}

				const VkImageCreateInfo& getImageCreateInfo(void) const noexcept
				{
					return this->m_info_image;
				}

				void setSamplerCreateInfo(
					const VkSamplerCreateInfo& info) noexcept
				{
					this->m_info_sampler = info;
				}

				const VkSamplerCreateInfo& getSamplerCreateInfo(
					void) const noexcept
				{
					return this->m_info_sampler;
				}

			private:
				VkImageCreateInfo m_info_image;
				VkSamplerCreateInfo m_info_sampler;
			};

			template <typename CreateInfo>
			class kotek_render_texture_info
			{
			public:
				kotek_render_texture_info(
					e_texture_type_t type, CreateInfo info) :
					m_type_texture(type),
					m_info_create(info)
				{
				}

				kotek_render_texture_info(void) :
					m_type_texture(e_texture_type_t::kTextureType_Unknown),
					m_info_create({})
				{
				}

				~kotek_render_texture_info(void) {}

				void setTypeTexture(e_texture_type_t type) noexcept
				{
					this->m_type_texture = type;
				}

				e_texture_type_t getTypeTexture(void) const noexcept
				{
					return this->m_type_texture;
				}

				void setCreateInfo(const CreateInfo& info) noexcept
				{
					this->m_info_create = info;
				}

				const CreateInfo& getCreateInfo(void) const noexcept
				{
					return this->m_info_create;
				}

			private:
				e_texture_type_t m_type_texture;
				CreateInfo m_info_create;
			};

			using kotek_render_texture_create_info_base_t =
				kotek_render_texture_create_info_t;

			using kotek_render_texture_info_t = kotek_render_texture_info<
				kotek_render_texture_create_info_base_t>;

			class kotek_render_graph_storage_input
			{
			public:
				kotek_render_graph_storage_input(void) {}
				~kotek_render_graph_storage_input(void) {}

				/*
				 * If you want to add output image from previous pass as input
				 * image in current pass the other arguments exclude image_name
				 * You can initialize with invalid data, because it doesn't use
				 * in render graph builder for analyzing, you just marked that
				 * You have input image that was output in previous pass e.g.
				 *
				 * You have your graphics pipeline like this
				 * static_level_geometry_pass->imgui_pass->another_pass
				 *
				 * In imgui_pass you declare your image with valid data like
				 * info and texture type, but If you want to use your declared
				 * image from imgui_pass in another_pass you must use addImage
				 * in onSetupInput callback
				 *
				 *
				 */
				void addImage(const ktk::string& image_name,
					const kotek_render_texture_create_info_base_t& info_create,
					e_texture_type_t type) noexcept
				{
					if (image_name.empty())
					{
						KOTEK_ASSERT(false, "you can't pass an empty string");
						return;
					}

					if (this->m_input_images.find(image_name) !=
						this->m_input_images.end())
					{
						KOTEK_ASSERT(false,
							"you can't add the same texture twice [{}]",
							image_name.get_as_is());
						return;
					}

					kotek_render_texture_info_t result;

					result.setCreateInfo(info_create);
					result.setTypeTexture(type);

					this->m_input_images[image_name] = result;
				}

				void addBuffer(const ktk::string& buffer_name,
					const VkBufferCreateInfo& info_buffer) noexcept
				{
					this->m_input_buffers[buffer_name] = info_buffer;
				}

				const ktk::unordered_map<ktk::string,
					kotek_render_texture_info_t>&
				getImages(void) const noexcept
				{
					return this->m_input_images;
				}

				const ktk::unordered_map<ktk::string, VkBufferCreateInfo>&
				getBuffers(void) const noexcept
				{
					return this->m_input_buffers;
				}

				// You must pass in form like:
				// "your_folder_in_root_folder_of_shaders/shader_name, or just
				// shader_name if file contains in root of shaders folder" FILE
				// NAME MUST NOT CONTAIN WORD "main", because main string
				// contains in source code string OR YOU CAN ADD HERE SHADER AS
				// SOURCE CODE STRING ENGINE WILL VALIDATE YOUR INPUTS AND WILL
				// DETECT ERRORS IF YOU PASSED FILE OR SOURCE CODE STRING
				//  WARNIN: USER MUST GENERATE PATH BY ENGINE OR SPECIFY OWN
				//  ABSOLUTE PATH ARGUMENT IS NOT RELATIVE!!!

				// TODO: add support for uber shaders
				void addShader(const ktk::string& pipeline_name,
					shader_type_t type,
					const shader_loading_data_t& data) noexcept
				{
					if (pipeline_name.empty())
					{
						KOTEK_ASSERT(
							false, "you can't pass an empty pipeline name");
						return;
					}

					if (this->m_input_shaders.find(pipeline_name) !=
						this->m_input_shaders.end())
					{
						if (this->m_input_shaders.at(pipeline_name)
								.find(type) !=
							this->m_input_shaders.at(pipeline_name).end())
						{
							KOTEK_ASSERT(false,
								"you can't add the existed shader by type: "
								"[{}]",
								helper::translateShaderTypeToString(type)
									.get_as_is());
							return;
						}
					}

					this->m_input_shaders[pipeline_name][type] = data;
				}

				void addShaderInputData(const ktk::string& pipeline_name,
					ktk::uint32_t descriptor_set_index,
					const shader_input_data_t& data) noexcept
				{
					if (pipeline_name.empty())
					{
						KOTEK_ASSERT(
							false, "you can't pass an empty pipeline name");
						return;
					}

					this->m_input_shaders_data[pipeline_name]
											  [descriptor_set_index]
												  .push_back(data);
					this->m_input_shaders_data.at(pipeline_name)
						.at(descriptor_set_index)
						.back()
						.setDescriptorSetIndex(descriptor_set_index);
				}

				// TODO: add support for adding shaders as bytes

				// TODO: add support that storages depend on what is pipeline
				// orthodox (means not RTX) or RTX or even more...

				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
				getShaders(void) const noexcept
				{
					return this->m_input_shaders;
				}

				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<shader_input_data_t>>>&
				getShadersInputData(void) const noexcept
				{
					return this->m_input_shaders_data;
				}

				const ktk::unordered_map<ktk::string,
					ktkRenderGraphPipelineInfo>&
				GetPipelinesInfo(void) const noexcept
				{
					return this->m_pipelines_info;
				}

				void AddPipelineInfo(const ktk::string& pipeline_name,
					const ktkRenderGraphPipelineInfo& info) noexcept
				{
					this->m_pipelines_info[pipeline_name] = info;
				}

			private:
				ktk::unordered_map<ktk::string, kotek_render_texture_info_t>
					m_input_images;

				ktk::unordered_map<ktk::string,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>
					m_input_shaders;

				ktk::unordered_map<ktk::string,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<shader_input_data_t>>>
					m_input_shaders_data;

				ktk::unordered_map<ktk::string, ktkRenderGraphPipelineInfo>
					m_pipelines_info;

				ktk::unordered_map<ktk::string, VkBufferCreateInfo>
					m_input_buffers;
			};

			class kotek_render_graph_storage_output
			{
			public:
				kotek_render_graph_storage_output(void) : m_is_use_backbuffer_by_default(true) {}
				~kotek_render_graph_storage_output(void) {}

				const ktk::unordered_map<ktk::string,
					kotek_render_texture_info_t>&
				getImages(void) const noexcept
				{
					return this->m_output_images;
				}

				const ktk::unordered_map<ktk::string, VkBufferCreateInfo>&
				getBuffers(void) const noexcept
				{
					return this->m_output_buffers;
				}

				void addImage(const ktk::string& texture_name,
					const kotek_render_texture_create_info_base_t& info,
					e_texture_type_t type) noexcept
				{
					if (this->m_output_images.find(texture_name) !=
						this->m_output_images.end())
					{
						KOTEK_ASSERT(false,
							"you can't add the same texture what you have "
							"already in map!");
					}

					kotek_render_texture_info_t result;

					result.setTypeTexture(type);
					result.setCreateInfo(info);

					this->m_output_images[texture_name] = result;
				}

				void addBuffer(const ktk::string& buffer_name,
					const VkBufferCreateInfo& info) noexcept
				{
					if (this->m_output_buffers.find(buffer_name) !=
						this->m_output_buffers.end())
					{
						KOTEK_ASSERT(false,
							"you can't add buffer which is already added to "
							"map!");
					}

					this->m_output_buffers[buffer_name] = info;
				}

				bool empty(void) const noexcept;

				void SetUseBackBuffer(bool status) noexcept
				{
					this->m_is_use_backbuffer_by_default = status;
				}

				bool IsUseBackBuffer(void) const noexcept
				{
					return this->m_is_use_backbuffer_by_default;
				}

			private:
				bool m_is_use_backbuffer_by_default;
				ktk::unordered_map<ktk::string, kotek_render_texture_info_t>
					m_output_images;
				ktk::unordered_map<ktk::string, VkBufferCreateInfo>
					m_output_buffers;
			};

		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_texture
			{
			public:
				kotek_render_texture(void) :
					m_info({}), m_p_alloc(nullptr), m_p_image(nullptr),
					m_p_image_view(nullptr), m_p_sampler(nullptr),
					m_type_texture(e_texture_type_t::kTextureType_Unknown)
				{
				}

				~kotek_render_texture(void) {}

				void setCreateInfoImage(const VkImageCreateInfo& info) noexcept
				{
					this->m_info = info;
				}

				const VkImageCreateInfo& getCreateInfoImage(void) const noexcept
				{
					return this->m_info;
				}

				void setCreateInfoSampler(
					const VkSamplerCreateInfo& info) noexcept
				{
					this->m_info_sampler = info;
				}

				const VkSamplerCreateInfo& getCreateInfoSampler(
					void) const noexcept
				{
					return this->m_info_sampler;
				}

				VmaAllocation getAllocation(void) const noexcept
				{
					return this->m_p_alloc;
				}

				void setAllocation(VmaAllocation p_saved_pointer) noexcept
				{
					this->m_p_alloc = p_saved_pointer;
				}

				const ktk::string& getPathName(void) const noexcept
				{
					return this->m_path_name;
				}

				void setPathName(const ktk::string& path_name) noexcept
				{
					this->m_path_name = path_name;
				}

				const ktk::string& getTextureName(void) const noexcept
				{
					return this->m_texture_name;
				}

				void setTextureName(const ktk::string& texture_name) noexcept
				{
					this->m_texture_name = texture_name;
				}

				void setImageHandle(VkImage p_image) noexcept
				{
					this->m_p_image = p_image;
				}

				VkImage getImageHandle(void) const noexcept
				{
					return this->m_p_image;
				}

				void setImageViewHandle(VkImageView p_image_view) noexcept
				{
					this->m_p_image_view = p_image_view;
				}

				VkImageView getImageViewHandle(void) const noexcept
				{
					return this->m_p_image_view;
				}

				void setTextureType(e_texture_type_t type) noexcept
				{
					this->m_type_texture = type;
				}

				e_texture_type_t getTextureType(void) const noexcept
				{
					return this->m_type_texture;
				}

				void setImageSamplerHandle(VkSampler p_sampler) noexcept
				{
					this->m_p_sampler = p_sampler;
				}

				VkSampler getImageSamplerHandle(void) const noexcept
				{
					return this->m_p_sampler;
				}

			private:
				e_texture_type_t m_type_texture;
				VkImageCreateInfo m_info;
				VkSamplerCreateInfo m_info_sampler;
				VkImage m_p_image;
				VkImageView m_p_image_view;
				VkSampler m_p_sampler;
				VmaAllocation m_p_alloc;
				ktk::string m_path_name;
				ktk::string m_texture_name;
			};

			template <typename CreateInfoType>
			class kotek_render_graph_resource_info_t
			{
			public:
				kotek_render_graph_resource_info_t(
					const ktk::string& render_pass_name,
					const ktk::string& resource_name,
					const CreateInfoType& info) :
					m_render_pass_name(render_pass_name),
					m_resource_name(resource_name), m_info(info),
					m_status(e_resource_synchronization_status_t::kEmpty),
					m_is_created_from_output(false)
				{
				}

				kotek_render_graph_resource_info_t(void) :
					m_status(e_resource_synchronization_status_t::kEmpty),
					m_is_created_from_output(false)
				{
				}

				kotek_render_graph_resource_info_t(
					const kotek_render_graph_resource_info_t&) = default;
				kotek_render_graph_resource_info_t& operator=(
					const kotek_render_graph_resource_info_t& info) = default;
				kotek_render_graph_resource_info_t(
					kotek_render_graph_resource_info_t&&) = default;
				kotek_render_graph_resource_info_t& operator=(
					kotek_render_graph_resource_info_t&&) = default;

				~kotek_render_graph_resource_info_t(void) {}

				const ktk::string& getRenderPassName(void) const noexcept
				{
					return this->m_render_pass_name;
				}

				void setRenderPassName(
					const ktk::string& render_pass_name) noexcept
				{
					this->m_render_pass_name = render_pass_name;
				}

				const ktk::string& getResourceName(void) const noexcept
				{
					return this->m_resource_name;
				}

				void setResourceName(const ktk::string& resource_name) noexcept
				{
					this->m_resource_name = resource_name;
				}

				const CreateInfoType& getInfo(void) const noexcept
				{
					return this->m_info;
				}

				void setInfo(const CreateInfoType& info) noexcept
				{
					this->m_info = info;
				}

				e_resource_synchronization_status_t getStatus(
					void) const noexcept
				{
					return this->m_status;
				}

				void setStatus(
					e_resource_synchronization_status_t value) noexcept
				{
					this->m_status = value;
				}

				void setCreatedFromOutput(bool status) noexcept
				{
					this->m_is_created_from_output = status;
				}

				bool isCreatedFromOutput(void) const noexcept
				{
					return this->m_is_created_from_output;
				}

			private:
				/// <summary>
				/// That flag means you have to create a synchonization status
				/// as kFromOutputToInput, because if image was created from
				/// output it must use in input
				/// </summary>
				bool m_is_created_from_output;
				e_resource_synchronization_status_t m_status;
				CreateInfoType m_info;
				ktk::string m_render_pass_name;
				ktk::string m_resource_name;
			};

			class kotek_render_graph_texture : public kotek_render_texture
			{
			public:
				kotek_render_graph_texture(const kotek_render_texture& data);
				kotek_render_graph_texture(void) : kotek_render_texture() {}
				~kotek_render_graph_texture(void) {}

				void setInfo(const kotek_render_graph_resource_info_t<
					kotek_render_texture_info_t>& info) noexcept
				{
					this->m_info_graph = info;
				}

				const kotek_render_graph_resource_info_t<
					kotek_render_texture_info_t>&
				getInfo(void) const noexcept
				{
					return this->m_info_graph;
				}

				void setRenderPassName(const ktk::string& name) noexcept
				{
					if (name.empty())
					{
						KOTEK_ASSERT(
							false, "your render pass name can't be empty!");
						return;
					}

					this->m_render_pass_name = name;
				}

				const ktk::string& getRenderPassName(void) const noexcept
				{
					return this->m_render_pass_name;
				}

			private:
				kotek_render_graph_resource_info_t<kotek_render_texture_info_t>
					m_info_graph;
				ktk::string m_render_pass_name;
			};

			/*
			 * This manager doesn't store textures or anything related to
			 * resources Only loads and user handles it
			 */
			class kotek_render_texture_manager
			{
			public:
				kotek_render_texture_manager(ktkRenderDevice* p_device,
					kotek_render_upload_heap* p_heap);

				kotek_render_texture_manager() = delete;

				~kotek_render_texture_manager();

				void initialize();
				void shutdown();

				void uploadTextureWithData(
					kotek_render_texture* p_texture, void* p_data) noexcept;

				// TODO: think about uploading heap, because maybe I need to
				// move it to streaming manager (?)
				void uploadAll(void) noexcept;

				kotek_render_texture createTexture(
					const ktk::string& texture_name,
					const kotek_render_texture_create_info_base_t& info,
					e_texture_type_t type) noexcept;

				kotek_render_graph_texture createTexture(
					const kotek_render_graph_resource_info_t<
						kotek_render_texture_info_t>& info) noexcept;

				void destroyTexture(VmaAllocator p_allocator,
					kotek_render_texture* p_texture) noexcept;

				void destroyTexture(VmaAllocator p_allocator,
					kotek_render_texture& texture) noexcept;

			private:
				void allocateTexture(VmaAllocator p_allocator,
					kotek_render_texture& texture) noexcept;

				bool validateTexture(
					const kotek_render_texture& texture) noexcept;

				/// <summary>
				/// Specifies only flat type (not array) of VkImageViewTyp by
				/// VkImageType
				/// </summary>
				/// <param name="type"></param>
				/// <param name="type_image"></param>
				/// <returns></returns>
				VkImageViewType detectTypeByTextureFormat(
					VkImageType type_image) noexcept;

				/// <summary>
				/// Specifies only ARRAY type of VkImageViewType by VkImageType
				/// </summary>
				/// <param name="type"></param>
				/// <param name="type_image"></param>
				VkImageViewType detectTypeArrayByTextureFormat(
					VkImageType type_image) noexcept;

				/// <summary>
				/// Specifies cubamap view type by VKImageType
				/// For more information use:
				/// https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkImageViewCreateInfo.html
				/// </summary>
				/// <param name="type_image"></param>
				/// <returns>VkImageViewType::</returns>
				VkImageViewType detectTypeCubemapByTextureFormat(
					VkImageType type_image) noexcept;

				VkImageViewType detectTypeCubemapArrayByTextureFormat(
					VkImageType type_image) noexcept;

			private:
				ktkRenderDevice* m_p_device;
				kotek_render_upload_heap* m_p_heap;
			};

			class kotek_render_graph_render_pass
			{
				friend class kotek_render_graph_builder;

			public:
				kotek_render_graph_render_pass(void) :
					m_p_manager_resource_graph{},
					m_p_manager_resource{}
				{
				}
				virtual ~kotek_render_graph_render_pass(void) = default;

				virtual void onSetupInput(
					kotek_render_graph_storage_input& storage,
					ktkRenderDevice* p_device,
					Core::ktkFileSystem* p_file_system)
				{
				}

				virtual void onSetupOutput(
					kotek_render_graph_storage_output& storage,
					ktkRenderDevice* p_device)
				{
				}

				virtual void onCreatedResources(void) {}

				virtual void onUpdate() {}

				virtual void onRender(const ktkRenderGraphNode& node, VkCommandBuffer p_command_buffer) {}

				/// <summary>
				/// Don't set it by your own hands, because this method is
				/// called by render_graph_builder manager
				/// </summary>
				/// <param name="name">that's parameter specifies your name for
				/// describing pass, because all passes referencing by hashed
				/// value and that means for human being it's hard to understand
				/// what is written in hash instead of reading rational
				/// string</param> <returns>nothing</returns>
				void setName(const ktk::string& name) noexcept
				{
					KOTEK_ASSERT(name.empty() == false,
						"you can't set an empty name for this structure, you "
						"must "
						"specify your name rationally");

					this->m_name = name;
				}

				const ktk::string& getName(void) const noexcept
				{
					return this->m_name;
				}

			private:
				void initialize(
					ktkRenderResourceManager* p_manager_resource,
					ktkRenderGraphResourceManager*
						p_manager_resource_graph) noexcept
				{
					KOTEK_ASSERT(p_manager_resource,
						"you can't pass an invalid resource manager pointer");
					KOTEK_ASSERT(p_manager_resource_graph,
						"you can't pass an invalid resource graph manager "
						"pointer");

					this->m_p_manager_resource = p_manager_resource;
					this->m_p_manager_resource_graph = p_manager_resource_graph;
				}

			protected:
				ktkRenderResourceManager* m_p_manager_resource;
				ktkRenderGraphResourceManager* m_p_manager_resource_graph;

			private:
				ktk::string m_name;
			};

			namespace helper
			{
				ktk::string translateRenderGraphBuilderTypeToString(
					e_kotek_render_graph_builder_type_t type) noexcept;

				VkGraphicsPipelineCreateInfo InitializeGraphicsPipeline(
					bool is_use_tesselation,
					const ktkRenderGraphPipelineInfo& info,
					const VkPipelineVertexInputStateCreateInfo* p_state_vertex,
					const VkPipelineColorBlendStateCreateInfo*
						p_state_color_blend,
					const VkPipelineDynamicStateCreateInfo* p_state_dynamic,
					VkPipelineLayout p_layout, VkRenderPass p_pass) noexcept;
			} // namespace helper

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
