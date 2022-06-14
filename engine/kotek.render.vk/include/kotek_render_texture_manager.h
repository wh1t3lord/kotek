#pragma once

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
			class ktkRenderGraph_resource_storage;
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
			enum class eRenderGraphBuilderType : ktk::enum_base_t
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

			enum class eRenderGraphBuilderPipelineRenderingType : ktk::
				enum_base_t
			{
				kRenderBuilderBasedOnPipeline_Orthodox,

				// TODO: add support for RTX in new version
				kRenderBuilderBasedOnPipeline_RTX
			};

			enum class eResourceSynchronizationStatus : ktk::enum_base_t
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
			enum class eTextureType : ktk::enum_base_t
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

			class ktkRenderTextureCreateInfo
			{
			public:
				ktkRenderTextureCreateInfo(const VkImageCreateInfo& info_image,
					const VkSamplerCreateInfo& info_sampler) :
					m_info_image(info_image),
					m_info_sampler(info_sampler)
				{
				}

				ktkRenderTextureCreateInfo(void) = default;
				~ktkRenderTextureCreateInfo(void) = default;

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
			class ktkRenderTextureInfoBase
			{
			public:
				ktkRenderTextureInfoBase(eTextureType type, CreateInfo info) :
					m_type_texture(type), m_info_create(info)
				{
				}

				ktkRenderTextureInfoBase(void) :
					m_type_texture(eTextureType::kTextureType_Unknown),
					m_info_create({})
				{
				}

				~ktkRenderTextureInfoBase(void) {}

				void SetTypeTexture(eTextureType type) noexcept
				{
					this->m_type_texture = type;
				}

				eTextureType GetTypeTexture(void) const noexcept
				{
					return this->m_type_texture;
				}

				void SetCreateInfo(const CreateInfo& info) noexcept
				{
					this->m_info_create = info;
				}

				const CreateInfo& GetCreateInfo(void) const noexcept
				{
					return this->m_info_create;
				}

			private:
				eTextureType m_type_texture;
				CreateInfo m_info_create;
			};

			using ktkRenderTextureCreateInfoBase = ktkRenderTextureCreateInfo;

			using ktkRenderTextureInfo =
				ktkRenderTextureInfoBase<ktkRenderTextureCreateInfoBase>;

			class ktkRenderGraphStorageInput
			{
			public:
				ktkRenderGraphStorageInput(void) {}
				~ktkRenderGraphStorageInput(void) {}

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
				void AddImage(const ktk::string& image_name,
					const ktkRenderTextureCreateInfoBase& info_create,
					eTextureType type) noexcept
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

					ktkRenderTextureInfo result;

					result.SetCreateInfo(info_create);
					result.SetTypeTexture(type);

					this->m_input_images[image_name] = result;
				}

				void AddBuffer(const ktk::string& buffer_name,
					const VkBufferCreateInfo& info_buffer) noexcept
				{
					this->m_input_buffers[buffer_name] = info_buffer;
				}

				const ktk::unordered_map<ktk::string, ktkRenderTextureInfo>&
				GetImages(void) const noexcept
				{
					return this->m_input_images;
				}

				const ktk::unordered_map<ktk::string, VkBufferCreateInfo>&
				GetBuffers(void) const noexcept
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
				void AddShader(const ktk::string& pipeline_name,
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

				void AddShaderInputData(const ktk::string& pipeline_name,
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
				GetShaders(void) const noexcept
				{
					return this->m_input_shaders;
				}

				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<shader_input_data_t>>>&
				GetShadersInputData(void) const noexcept
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
				ktk::unordered_map<ktk::string, ktkRenderTextureInfo>
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

			class ktkRenderGraphStorageOutput
			{
			public:
				ktkRenderGraphStorageOutput(void) :
					m_is_use_backbuffer_by_default(true)
				{
				}
				~ktkRenderGraphStorageOutput(void) {}

				const ktk::unordered_map<ktk::string, ktkRenderTextureInfo>&
				GetImages(void) const noexcept
				{
					return this->m_output_images;
				}

				const ktk::unordered_map<ktk::string, VkBufferCreateInfo>&
				GetBuffers(void) const noexcept
				{
					return this->m_output_buffers;
				}

				void AddImage(const ktk::string& texture_name,
					const ktkRenderTextureCreateInfoBase& info,
					eTextureType type) noexcept
				{
					if (this->m_output_images.find(texture_name) !=
						this->m_output_images.end())
					{
						KOTEK_ASSERT(false,
							"you can't add the same texture what you have "
							"already in map!");
					}

					ktkRenderTextureInfo result;

					result.SetTypeTexture(type);
					result.SetCreateInfo(info);

					this->m_output_images[texture_name] = result;
				}

				void AddBuffer(const ktk::string& buffer_name,
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

				bool Empty(void) const noexcept;

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
				ktk::unordered_map<ktk::string, ktkRenderTextureInfo>
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
			class ktkRenderTexture
			{
			public:
				ktkRenderTexture(void) :
					m_info({}), m_p_alloc(nullptr), m_p_image(nullptr),
					m_p_image_view(nullptr), m_p_sampler(nullptr),
					m_type_texture(eTextureType::kTextureType_Unknown)
				{
				}

				~ktkRenderTexture(void) {}

				void SetCreateInfoImage(const VkImageCreateInfo& info) noexcept
				{
					this->m_info = info;
				}

				const VkImageCreateInfo& GetCreateInfoImage(void) const noexcept
				{
					return this->m_info;
				}

				void SetCreateInfoSampler(
					const VkSamplerCreateInfo& info) noexcept
				{
					this->m_info_sampler = info;
				}

				const VkSamplerCreateInfo& GetCreateInfoSampler(
					void) const noexcept
				{
					return this->m_info_sampler;
				}

				VmaAllocation GetAllocation(void) const noexcept
				{
					return this->m_p_alloc;
				}

				void SetAllocation(VmaAllocation p_saved_pointer) noexcept
				{
					this->m_p_alloc = p_saved_pointer;
				}

				const ktk::string& GetPathName(void) const noexcept
				{
					return this->m_path_name;
				}

				void SetPathName(const ktk::string& path_name) noexcept
				{
					this->m_path_name = path_name;
				}

				const ktk::string& GetTextureName(void) const noexcept
				{
					return this->m_texture_name;
				}

				void SetTextureName(const ktk::string& texture_name) noexcept
				{
					this->m_texture_name = texture_name;
				}

				void SetImageHandle(VkImage p_image) noexcept
				{
					this->m_p_image = p_image;
				}

				VkImage GetImageHandle(void) const noexcept
				{
					return this->m_p_image;
				}

				void SetImageViewHandle(VkImageView p_image_view) noexcept
				{
					this->m_p_image_view = p_image_view;
				}

				VkImageView GetImageViewHandle(void) const noexcept
				{
					return this->m_p_image_view;
				}

				void SetTextureType(eTextureType type) noexcept
				{
					this->m_type_texture = type;
				}

				eTextureType GetTextureType(void) const noexcept
				{
					return this->m_type_texture;
				}

				void SetImageSamplerHandle(VkSampler p_sampler) noexcept
				{
					this->m_p_sampler = p_sampler;
				}

				VkSampler GetImageSamplerHandle(void) const noexcept
				{
					return this->m_p_sampler;
				}

			private:
				eTextureType m_type_texture;
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
			class ktkRenderGraphResourceInfo
			{
			public:
				ktkRenderGraphResourceInfo(const ktk::string& render_pass_name,
					const ktk::string& resource_name,
					const CreateInfoType& info) :
					m_render_pass_name(render_pass_name),
					m_resource_name(resource_name), m_info(info),
					m_status(eResourceSynchronizationStatus::kEmpty),
					m_is_created_from_output(false)
				{
				}

				ktkRenderGraphResourceInfo(void) :
					m_status(eResourceSynchronizationStatus::kEmpty),
					m_is_created_from_output(false)
				{
				}

				ktkRenderGraphResourceInfo(
					const ktkRenderGraphResourceInfo&) = default;
				ktkRenderGraphResourceInfo& operator=(
					const ktkRenderGraphResourceInfo& info) = default;
				ktkRenderGraphResourceInfo(
					ktkRenderGraphResourceInfo&&) = default;
				ktkRenderGraphResourceInfo& operator=(
					ktkRenderGraphResourceInfo&&) = default;

				~ktkRenderGraphResourceInfo(void) {}

				const ktk::string& GetRenderPassName(void) const noexcept
				{
					return this->m_render_pass_name;
				}

				void SetRenderPassName(
					const ktk::string& render_pass_name) noexcept
				{
					this->m_render_pass_name = render_pass_name;
				}

				const ktk::string& GetResourceName(void) const noexcept
				{
					return this->m_resource_name;
				}

				void SetResourceName(const ktk::string& resource_name) noexcept
				{
					this->m_resource_name = resource_name;
				}

				const CreateInfoType& GetInfo(void) const noexcept
				{
					return this->m_info;
				}

				void SetInfo(const CreateInfoType& info) noexcept
				{
					this->m_info = info;
				}

				eResourceSynchronizationStatus GetStatus(
					void) const noexcept
				{
					return this->m_status;
				}

				void SetStatus(
					eResourceSynchronizationStatus value) noexcept
				{
					this->m_status = value;
				}

				void SetCreatedFromOutput(bool status) noexcept
				{
					this->m_is_created_from_output = status;
				}

				bool IsCreatedFromOutput(void) const noexcept
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
				eResourceSynchronizationStatus m_status;
				CreateInfoType m_info;
				ktk::string m_render_pass_name;
				ktk::string m_resource_name;
			};

			class ktkRenderGraphTexture : public ktkRenderTexture
			{
			public:
				ktkRenderGraphTexture(const ktkRenderTexture& data);
				ktkRenderGraphTexture(void) : ktkRenderTexture() {}
				~ktkRenderGraphTexture(void) {}

				void SetInfo(
					const ktkRenderGraphResourceInfo<ktkRenderTextureInfo>&
						info) noexcept
				{
					this->m_info_graph = info;
				}

				const ktkRenderGraphResourceInfo<ktkRenderTextureInfo>& GetInfo(
					void) const noexcept
				{
					return this->m_info_graph;
				}

				void SetRenderPassName(const ktk::string& name) noexcept
				{
					if (name.empty())
					{
						KOTEK_ASSERT(
							false, "your render pass name can't be empty!");
						return;
					}

					this->m_render_pass_name = name;
				}

				const ktk::string& GetRenderPassName(void) const noexcept
				{
					return this->m_render_pass_name;
				}

			private:
				ktkRenderGraphResourceInfo<ktkRenderTextureInfo> m_info_graph;
				ktk::string m_render_pass_name;
			};

			/*
			 * This manager doesn't store textures or anything related to
			 * resources Only loads and user handles it
			 */
			class ktkRenderTextureManager
			{
			public:
				ktkRenderTextureManager(ktkRenderDevice* p_device,
					kotek_render_upload_heap* p_heap);

				ktkRenderTextureManager() = delete;

				~ktkRenderTextureManager();

				void Initialize();
				void Shutdown();

				void UploadTextureWithData(
					ktkRenderTexture* p_texture, void* p_data) noexcept;

				// TODO: think about uploading heap, because maybe I need to
				// move it to streaming manager (?)
				void UploadAll(void) noexcept;

				ktkRenderTexture CreateTexture(const ktk::string& texture_name,
					const ktkRenderTextureCreateInfoBase& info,
					eTextureType type) noexcept;

				ktkRenderGraphTexture CreateTexture(
					const ktkRenderGraphResourceInfo<ktkRenderTextureInfo>&
						info) noexcept;

				void DestroyTexture(VmaAllocator p_allocator,
					ktkRenderTexture* p_texture) noexcept;

				void DestroyTexture(VmaAllocator p_allocator,
					ktkRenderTexture& texture) noexcept;

			private:
				void AllocateTexture(VmaAllocator p_allocator,
					ktkRenderTexture& texture) noexcept;

				bool ValidateTexture(const ktkRenderTexture& texture) noexcept;

				/// <summary>
				/// Specifies only flat type (not array) of VkImageViewTyp by
				/// VkImageType
				/// </summary>
				/// <param name="type"></param>
				/// <param name="type_image"></param>
				/// <returns></returns>
				VkImageViewType DetectTypeByTextureFormat(
					VkImageType type_image) noexcept;

				/// <summary>
				/// Specifies only ARRAY type of VkImageViewType by VkImageType
				/// </summary>
				/// <param name="type"></param>
				/// <param name="type_image"></param>
				VkImageViewType DetectTypeArrayByTextureFormat(
					VkImageType type_image) noexcept;

				/// <summary>
				/// Specifies cubamap view type by VKImageType
				/// For more information use:
				/// https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkImageViewCreateInfo.html
				/// </summary>
				/// <param name="type_image"></param>
				/// <returns>VkImageViewType::</returns>
				VkImageViewType DetectTypeCubemapByTextureFormat(
					VkImageType type_image) noexcept;

				VkImageViewType DetectTypeCubemapArrayByTextureFormat(
					VkImageType type_image) noexcept;

			private:
				ktkRenderDevice* m_p_device;
				kotek_render_upload_heap* m_p_heap;
			};

			class ktkRenderGraphRenderPass
			{
				friend class ktkRenderGraphBuilder;

			public:
				ktkRenderGraphRenderPass(void) :
					m_p_manager_resource_graph{}, m_p_manager_resource{}
				{
				}
				virtual ~ktkRenderGraphRenderPass(void) = default;

				virtual void OnSetupInput(ktkRenderGraphStorageInput& storage,
					ktkRenderDevice* p_device,
					Core::ktkIFileSystem* p_file_system)
				{
				}

				virtual void OnSetupOutput(ktkRenderGraphStorageOutput& storage,
					ktkRenderDevice* p_device)
				{
				}

				virtual void OnCreatedResources(void) {}

				virtual void OnUpdate() {}

				virtual void OnRender(const ktkRenderGraphNode& node,
					VkCommandBuffer p_command_buffer)
				{
				}

				/// <summary>
				/// Don't set it by your own hands, because this method is
				/// called by render_graph_builder manager
				/// </summary>
				/// <param name="name">that's parameter specifies your name for
				/// describing pass, because all passes referencing by hashed
				/// value and that means for human being it's hard to understand
				/// what is written in hash instead of reading rational
				/// string</param> <returns>nothing</returns>
				void SetName(const ktk::string& name) noexcept
				{
					KOTEK_ASSERT(name.empty() == false,
						"you can't set an empty name for this structure, you "
						"must "
						"specify your name rationally");

					this->m_name = name;
				}

				const ktk::string& GetName(void) const noexcept
				{
					return this->m_name;
				}

			private:
				void Initialize(ktkRenderResourceManager* p_manager_resource,
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
				ktk::string TranslateRenderGraphBuilderTypeToString(
					eRenderGraphBuilderType type) noexcept;

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
