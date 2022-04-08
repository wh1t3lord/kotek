#pragma once

#include <kotek.core/include/kotek_std.h>
#include <shaderc/shaderc.hpp>

/*
Standard of shader format naming

There's an example of glslangValidator formats

'file' can end in .<stage> for auto-stage classification, where <stage> is:
        .conf   to provide a config file that replaces the default configuration
                        (see -c option below for generating a template)
        .vert   for a vertex shader
        .tesc   for a tessellation control shader
        .tese   for a tessellation evaluation shader
        .geom   for a geometry shader
        .frag   for a fragment shader
        .comp   for a compute shader
        .mesh   for a mesh shader
        .task   for a task shader
        .rgen    for a ray generation shader
        .rint    for a ray intersection shader
        .rahit   for a ray any hit shader
        .rchit   for a ray closest hit shader
        .rmiss   for a ray miss shader
        .rcall   for a ray callable shader


        // NOT USED
        .glsl   for .vert.glsl, .tesc.glsl, ..., .comp.glsl compound suffixes
        .hlsl   for .vert.hlsl, .tesc.hlsl, ..., .comp.hlsl compound suffixes

        Example: You need to write the name of shader as is, but you must
specificate his content to format file

        Like if you write vertex shader you need to write output file like this

        MyShader.vert <=== we know that is vertex shader

        But you must not write .glsl, .hlsl, .gc or other formats of naming
shader languages. Because it doesnt mean anything and can't handle fast with
analyzing them

*/

namespace Kotek
{
	namespace Core
	{
		class ktkFileSystem;
		class ktkProfiler;
	} // namespace Core
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderDevice;
			class ktkRenderSwapchain;
			class ktkRenderResourceManager;
			class descriptor_set_info_t;
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			enum class shader_type_t : ktk::enum_base_t
			{
				kShaderType_Vertex,
				// @ fragment
				kShaderType_Pixel,
				kShaderType_Geometry,
				kShaderType_Compute,
				kShaderType_Mesh,
				kShaderType_Task,
				kShaderType_TessellationControl,
				kShaderType_TessellationEvaluation,
				kShaderType_RTX_Generation,
				kShaderType_RTX_Intersection,
				kShaderType_RTX_AnyHit,
				kShaderType_RTX_ClosesHit,
				kShaderType_RTX_Miss,
				kShaderType_RTX_Callable,

				kShaderType_Unknown = -1
			};

			enum class shader_loading_data_type_t : ktk::enum_base_t
			{
				kShaderLoadingDataType_FilePathString,
				kShaderLoadingDataType_SourceCodeTextString,
				kShaderLoadingDataType_ByteArrayFile,
				kShaderLoadingDataType_ByteArrayCompiledSPIRV,
				kShaderLoadingDataType_NotInitialized
			};

			constexpr const ktk::tchar* _kShaderPrefix_Vertex =
				KOTEK_TEXT("vert");
			constexpr const ktk::tchar* _kShaderPrefix_Fragment =
				KOTEK_TEXT("frag");
			constexpr const ktk::tchar* _kShaderPrefix_Compute =
				KOTEK_TEXT("comp");
			constexpr const ktk::tchar* _kShaderPrefix_Task =
				KOTEK_TEXT("task");
			constexpr const ktk::tchar* _kShaderPrefix_Mesh =
				KOTEK_TEXT("mesh");
			constexpr const ktk::tchar* _kShaderPrefix_Geometry =
				KOTEK_TEXT("geom");
			constexpr const ktk::tchar* _kShaderPrefix_TessellationEvaluation =
				KOTEK_TEXT("tese");
			constexpr const ktk::tchar* _kShaderPrefix_TessellationControl =
				KOTEK_TEXT("tesc");

			namespace helper
			{
				bool isRTXShaderByType(shader_type_t type) noexcept;

				bool isBufferByDescriptorType(VkDescriptorType type) noexcept;

				ktk::string translateShaderTypeToString(
					shader_type_t type) noexcept;

				ktk::string translateShaderTypeToStringFormat(
					shader_type_t type) noexcept;

				ktk::string translateDescriptorTypeToString(
					VkDescriptorType type) noexcept;

				void printDescriptorSet() noexcept;
				
				void printBindingInfo(
					const descriptor_set_info_t& info) noexcept;
				
				shader_type_t GetShaderTypeByShaderStageFlagBits(
					VkShaderStageFlagBits bits) noexcept;

				VkShaderStageFlagBits GetShaderStageFlagBitsByShaderType(
					shader_type_t type) noexcept;

				// TODO: add default value for mipmaps
				VkImageCreateInfo InitializeImageForShaders(int width,
					int height,
					VkImageLayout image_layout_initial =
						VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageType image_type = VkImageType::VK_IMAGE_TYPE_2D,
					ktk::uint32_t depth_value = 1, ktk::uint32_t mip_levels = 1,
					ktk::uint32_t array_layers = 1,
					VkSampleCountFlagBits samples_count =
						VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VkImageTiling image_tiling =
						VkImageTiling::VK_IMAGE_TILING_OPTIMAL,
					VkImageUsageFlags image_usage =
						VkImageUsageFlagBits::VK_IMAGE_USAGE_SAMPLED_BIT |
						VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT,
					VkSharingMode image_sharing_mode =
						VkSharingMode::VK_SHARING_MODE_EXCLUSIVE) noexcept;

				VkImageCreateInfo InitializeImageForFramebuffer(int width,
					int height,
					VkImageLayout image_layout_initial =
						VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED,
					VkImageType image_type = VkImageType::VK_IMAGE_TYPE_2D,
					ktk::uint32_t depth_value = 1, ktk::uint32_t mip_levels = 1,
					ktk::uint32_t array_layers = 1,
					VkSampleCountFlagBits samples_count =
						VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
					VkImageTiling image_tiling =
						VkImageTiling::VK_IMAGE_TILING_OPTIMAL,
					VkImageUsageFlags image_usage =
						VkImageUsageFlagBits::
							VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
						VkImageUsageFlagBits::VK_IMAGE_USAGE_SAMPLED_BIT |
						VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
					VkSharingMode image_sharing_mode =
						VkSharingMode::VK_SHARING_MODE_EXCLUSIVE) noexcept;

				VkImageCreateInfo InitializeImage(int width, int height,
					VkImageLayout image_layout_initial, VkImageType image_type,
					ktk::uint32_t depth_value, ktk::uint32_t mip_levels,
					ktk::uint32_t array_layers,
					VkSampleCountFlagBits samples_count,
					VkImageTiling image_tiling, VkImageUsageFlags image_usage,
					VkSharingMode image_sharing_mode) noexcept;

				// TODO: create support for anysotropy filtering, specify it in
				// creation when we got an information about our image, we need
				// to read from config or what user specifies ???
				VkSamplerCreateInfo InitializeSampler(
					VkFilter mag_filter = VkFilter::VK_FILTER_NEAREST,
					VkFilter min_filter = VkFilter::VK_FILTER_NEAREST,
					VkSamplerMipmapMode mip_map_mode =
						VK_SAMPLER_MIPMAP_MODE_NEAREST,
					VkSamplerAddressMode address_mode_u =
						VK_SAMPLER_ADDRESS_MODE_REPEAT,
					VkSamplerAddressMode address_mode_v =
						VK_SAMPLER_ADDRESS_MODE_REPEAT,
					VkSamplerAddressMode address_mode_w =
						VK_SAMPLER_ADDRESS_MODE_REPEAT,
					float min_lod = -1000.0f, float max_lod = 1000.0f) noexcept;

				VkPipelineInputAssemblyStateCreateInfo
				InitializePipelineInputAssemblyState(
					VkPrimitiveTopology topology,
					VkBool32 primitive_restart_enable = VK_FALSE,
					VkPipelineInputAssemblyStateCreateFlags flags = 0) noexcept;

				VkPipelineRasterizationStateCreateInfo
				InitializePipelineRasterizationState(VkPolygonMode mode_polygon,
					VkCullModeFlags mode_cull, VkFrontFace front_face,
					VkPipelineRasterizationStateCreateFlags flags = 0,
					VkBool32 depth_clamp_enable = VK_FALSE,
					float line_width = 1.0f) noexcept;

				// TODO: think about blending
				VkPipelineColorBlendAttachmentState
				InitializePipelineColorBlendAttachmentState(
					VkBool32 blend_enable = VK_FALSE,
					VkBlendFactor src_color_blend_factor = VK_BLEND_FACTOR_ONE,
					VkBlendFactor dst_color_blend_factor = VK_BLEND_FACTOR_ZERO,
					VkBlendOp color_blend_op = VK_BLEND_OP_ADD,
					VkBlendFactor src_alpha_blend_factor = VK_BLEND_FACTOR_ONE,
					VkBlendFactor dst_alpha_blend_factor = VK_BLEND_FACTOR_ZERO,
					VkBlendOp alpha_blend_op = VK_BLEND_OP_ADD,
					VkColorComponentFlags color_write_mask =
						VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
						VK_COLOR_COMPONENT_B_BIT |
						VK_COLOR_COMPONENT_A_BIT) noexcept;

				VkPipelineColorBlendStateCreateInfo
				InitializePipelineColorBlendState(
					const ktk::vector<VkPipelineColorBlendAttachmentState>&
						states,
					VkBool32 logic_op_enable = VK_FALSE,
					VkLogicOp logic_op = VK_LOGIC_OP_AND, float blend_R = 1.0f,
					float blend_G = 1.0f, float blend_B = 1.0f,
					float blend_A = 1.0f,
					VkPipelineColorBlendStateCreateFlags flags = 0) noexcept;

				// TODO: specify all arguemnts to fill the structure
				VkPipelineDepthStencilStateCreateInfo
				InitializePipelineDepthStencilState(
					VkBool32 depth_test_enable = VK_TRUE,
					VkBool32 depth_write_enable = VK_TRUE,
					VkBool32 stencil_test_enable = VK_TRUE,
					VkCompareOp depth_compare_op = VK_COMPARE_OP_LESS_OR_EQUAL,
					VkCompareOp back_compare_op =
						VK_COMPARE_OP_ALWAYS) noexcept;

				VkPipelineViewportStateCreateInfo
				InitializePipelineViewportState(ktk::uint32_t viewport_count,
					ktk::uint32_t scissor_count,
					const VkViewport* p_viewports = nullptr,
					const VkRect2D* p_scissors = nullptr,
					VkPipelineViewportStateCreateFlags flags = 0) noexcept;

				VkPipelineMultisampleStateCreateInfo
				InitializePipelineMultisampleState(
					VkBool32 sample_enable = VK_FALSE,
					VkSampleCountFlagBits rasterization_samples =
						VK_SAMPLE_COUNT_1_BIT,
					float min_sample_shading = 1.0f,
					const VkSampleMask* p_mask = nullptr,
					VkBool32 alpha_to_coverage_enable = VK_FALSE,
					VkBool32 alpha_to_one_enable = VK_FALSE) noexcept;

				VkPipelineDynamicStateCreateInfo InitializePipelineDynamicState(
					const ktk::vector<VkDynamicState>& states,
					VkPipelineDynamicStateCreateFlags flags = 0) noexcept;

				VkPipelineVertexInputStateCreateInfo
				InitializePipelineVertexInputState(
					const ktk::vector<VkVertexInputBindingDescription>&
						descriptions,
					const ktk::vector<VkVertexInputAttributeDescription>&
						attributes,
					VkPipelineVertexInputStateCreateFlags flags = 0) noexcept;

				VkGraphicsPipelineCreateInfo InitializeGraphicsPipeline(
					const VkPipelineVertexInputStateCreateInfo*
						p_vertex_input_state,
					const VkPipelineInputAssemblyStateCreateInfo*
						p_input_assembly_state,
					const VkPipelineViewportStateCreateInfo* p_viewport_state,
					const VkPipelineRasterizationStateCreateInfo*
						p_rasterization_state,
					const VkPipelineMultisampleStateCreateInfo*
						p_multisample_state,
					const VkPipelineDepthStencilStateCreateInfo*
						p_depth_stencil_state,
					const VkPipelineColorBlendStateCreateInfo*
						p_color_blend_state,
					const VkPipelineDynamicStateCreateInfo* p_dynamic_state,
					VkPipelineLayout p_layout, VkRenderPass p_pass,
					const VkPipelineTessellationStateCreateInfo*
						p_tessellation_state,
					ktk::uint32_t subpass = 0, VkPipeline p_pipeline = nullptr,
					ktk::uint32_t base_pipeline_index = -1,
					VkPipelineCreateFlags flags = 0) noexcept;

				VkPipelineShaderStageCreateInfo InitializePipelineShaderStage(
					shader_type_t type, VkShaderModule p_module) noexcept;

			} // namespace helper

			// TODO: write other RTX's format shader

			class shader_loading_data_t
			{
			public:
				explicit shader_loading_data_t(shader_loading_data_type_t type,
					const ktk::string& path_to_file_or_source_code_string);

				explicit shader_loading_data_t(
					shader_loading_data_type_t type, void* p_data);

				shader_loading_data_t(void);

				~shader_loading_data_t(void);

				const ktk::variant<void*, ktk::string>& getData(
					void) const noexcept;
				void setData(
					const ktk::variant<void*, ktk::string>& data) noexcept;

				shader_loading_data_type_t getType(void) const noexcept;
				void setType(shader_loading_data_type_t type) noexcept;

			private:
				shader_loading_data_type_t m_type;
				ktk::variant<void*, ktk::string> m_data;
			};

			// TODO: add support for arrays data like array of textures in
			// shader
			class shader_input_data_t
			{
			public:
				shader_input_data_t(const ktk::string& render_pass_name,
					ktk::uint32_t binding_index, VkDescriptorType type,
					ktk::size_t buffer_size);

				shader_input_data_t(const ktk::string& render_pass_name,
					ktk::uint32_t binding_index, VkDescriptorType type,
					const ktk::string& texture_name);

				shader_input_data_t(void);

				~shader_input_data_t(void);

				void setDescriptorSetIndex(
					ktk::uint32_t descriptor_set_index) noexcept;
				ktk::uint32_t getDescriptorSetIndex(void) const noexcept;
				ktk::uint32_t getBindingIndex(void) const noexcept;

				VkDescriptorType getDescriptorType(void) const noexcept;

				ktk::size_t GetData_BufferSize(void) const noexcept;
				ktk::string GetData_RenderGraphTextureName(void) const noexcept;

				const ktk::string& GetRenderPassName(void) const noexcept;

				/// <summary>
				/// If true means for buffer otherwise it's image
				/// TODO: think about growing variant structure here, so we need
				/// enum and result status which is correctly specifies what
				/// kind of data we have here
				/// </summary>
				/// <param name=""></param>
				/// <returns></returns>
				bool IsDataFor(void) const noexcept;

			private:
				void SetData(ktk::size_t buffer_size) noexcept;
				void SetData(const ktk::string& texture_name) noexcept;

			private:
				ktk::uint32_t m_descriptor_set_index;
				ktk::uint32_t m_binding_index;
				VkDescriptorType m_descriptor_type;
				ktk::string m_render_pass_name;
				ktk::variant<ktk::size_t, ktk::string> m_data;
			};

			class descriptor_set_info_t
			{
			public:
				descriptor_set_info_t(ktk::uint32_t descriptor_set_index,
					ktk::uint32_t binding_index, VkDescriptorType type,
					shader_type_t shader_type,
					const ktk::string& shader_variable_name);
				descriptor_set_info_t(void);
				~descriptor_set_info_t(void);

				ktk::uint32_t getDescriptorSetIndex(void) const noexcept;
				ktk::uint32_t getBindingIndex(void) const noexcept;
				VkDescriptorType getDescriptorType(void) const noexcept;
				const ktk::string& getVariableName(void) const noexcept;

				shader_type_t GetShaderType(void) const noexcept;

			private:
				ktk::uint32_t m_descriptor_set_index;
				ktk::uint32_t m_binding_index;
				shader_type_t m_shader_type;
				VkDescriptorType m_type;
				ktk::string m_variable_name;
			};

			/*
			 * This manager doesn't store only loads
			 * Store is for streaming manager
			 */
			class kotek_render_shader_manager
			{
			public:
				class shader_module_t
				{
				public:
					shader_module_t(void);
					~shader_module_t(void);

					void setSPIRVByteCode(
						const ktk::vector<ktk::uint32_t>& info) noexcept;
					const ktk::vector<ktk::uint32_t>& getSPIRVByteCode(
						void) const noexcept;

					void setModule(VkShaderModule p_module) noexcept;
					VkShaderModule getModule(void) const noexcept;

				private:
					ktk::vector<ktk::uint32_t> m_spv_info;
					VkShaderModule m_p_module;
				};

			public:
				kotek_render_shader_manager(Core::ktkMainManager* p_manager);
				~kotek_render_shader_manager(void);

				kotek_render_shader_manager(
					const kotek_render_shader_manager&) = delete;
				kotek_render_shader_manager& operator=(
					const kotek_render_shader_manager&) = delete;
				kotek_render_shader_manager(
					kotek_render_shader_manager&&) = delete;
				kotek_render_shader_manager& operator=(
					kotek_render_shader_manager&&) = delete;

				void initialize(void) noexcept;
				void shutdown(void) noexcept;

				shader_module_t loadShader(
					const ktk::string& path, shader_type_t type) noexcept;

				shader_module_t loadShader(const ktk::string& path) noexcept;

				shader_module_t loadShaderAsString(
					const ktk::string& code_as_string,
					shader_type_t type) noexcept;

				void destroyShader(const shader_module_t& instance) noexcept;

			private:
				/*!
				 * \brief compileShaderToSPIRV compile shader into SPIRV
				 * independent format \param path_to_file is path to file in OS
				 * \param type low level enum from shaderc library
				 * \return compiled code if it's empty vector it means we have
				 * error
				 */

				ktk::vector<ktk::uint32_t> compileShaderToSPIRV(
					const ktk::string& path_to_file, shaderc_shader_kind type,
					const ktk::map<ktk::string_legacy, ktk::string_legacy>&
						macros = ktk::map<ktk::string_legacy,
							ktk::string_legacy>()) noexcept;

				ktk::vector<ktk::uint32_t> compileShaderFromStringToSPIRV(
					const ktk::string& code_as_string, shaderc_shader_kind type,
					const ktk::map<ktk::string_legacy, ktk::string_legacy>&
						macros = ktk::map<ktk::string_legacy,
							ktk::string_legacy>()) noexcept;

				shader_type_t detectType(
					const ktk::string& path_to_file) noexcept;

			private:
				Core::ktkFileSystem* m_p_filesystem;
				Core::ktkMainManager* m_p_main_manager;
				ktkRenderDevice* m_p_render_device;
			};

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
