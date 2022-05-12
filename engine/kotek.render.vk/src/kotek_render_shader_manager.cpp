#include "../include/kotek_render_shader_manager.h"
#include <kotek.core/include/kotek_main_manager.h>
#include "../include/kotek_render_device.h"
#include "../include/kotek_render_texture_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_shader_manager::kotek_render_shader_manager(
				Core::ktkMainManager* p_manager) :
				m_p_render_device(static_cast<ktkRenderDevice*>(
					p_manager->getRenderDevice())),
				m_p_main_manager(p_manager),
				m_p_filesystem(p_manager->GetFileSystem())
			{
				KOTEK_ASSERT(this->m_p_render_device,
					"you can't use invalid device manager");
				KOTEK_ASSERT(this->m_p_filesystem,
					"you can't use invalid filesystem class");
			}

			void kotek_render_shader_manager::initialize() noexcept {}

			void kotek_render_shader_manager::shutdown(void) noexcept {}

			kotek_render_shader_manager::shader_module_t
			kotek_render_shader_manager::loadShader(
				const ktk::string& path, shader_type_t type) noexcept
			{
				KOTEK_CPU_PROFILE();

				shader_module_t result;

				if (path.empty())
				{
					KOTEK_ASSERT(false, "you have passed an empty path",
						path.get_as_is());
					return result;
				}

				if (this->m_p_filesystem->IsValidPath(path) == false)
				{
					KOTEK_ASSERT(false, "you passed an invalid path: [{}]",
						path.get_as_is());
					return result;
				}

				VkShaderModuleCreateInfo info_module = {};

				ktk::vector<ktk::uint32_t> shader_code;

				switch (type)
				{
				case shader_type_t::kShaderType_Vertex:
				{
					shader_code = this->compileShaderToSPIRV(
						path, shaderc_shader_kind::shaderc_vertex_shader);

					break;
				}
				case shader_type_t::kShaderType_Compute:
				{
					shader_code = this->compileShaderToSPIRV(
						path, shaderc_shader_kind::shaderc_compute_shader);

					break;
				}
				case shader_type_t::kShaderType_Pixel:
				{
					shader_code = this->compileShaderToSPIRV(
						path, shaderc_shader_kind::shaderc_fragment_shader);

					break;
				}
				default:
				{
					KOTEK_ASSERT(false, "can't detect type of shader");
					break;
				}
				}

				if (shader_code.empty())
				{
					KOTEK_ASSERT(false,
						"shader code is not valid. Can't compile and "
						"load shader by path: [{}]",
						path.get_as_is());
					return result;
				}

				info_module.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				info_module.pNext = nullptr;
				info_module.pCode = shader_code.data();
				info_module.codeSize =
					shader_code.size() * sizeof(ktk::uint32_t);

				VkDevice p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkShaderModule p_module = nullptr;

				VkResult status = vkCreateShaderModule(
					p_device, &info_module, nullptr, &p_module);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreateShaderModule. See status");

				result.setSPIRVByteCode(shader_code);
				result.setModule(p_module);

				return result;
			}

			kotek_render_shader_manager::shader_module_t
			kotek_render_shader_manager::loadShader(
				const ktk::string& path) noexcept
			{
				KOTEK_CPU_PROFILE();

				shader_module_t result;

				if (path.empty())
				{
					KOTEK_MESSAGE_WARNING("you passed an empty path");
					return result;
				}

				if (this->m_p_filesystem->IsValidPath(path) == false)
				{
					KOTEK_MESSAGE_WARNING(
						"you passed an invalid path: [{}]", path.get_as_is());
					return result;
				}

				shader_type_t type = this->detectType(path);

				if (type == shader_type_t::kShaderType_Unknown)
				{
					KOTEK_MESSAGE_WARNING("can't load unknown shader by type");
					return result;
				}

				result = this->loadShader(path, type);

				return result;
			}

			kotek_render_shader_manager::shader_module_t
			kotek_render_shader_manager::loadShaderAsString(
				const ktk::string& code_as_string, shader_type_t type) noexcept
			{
				KOTEK_CPU_PROFILE();

				shader_module_t result;

				if (code_as_string.empty())
				{
					KOTEK_MESSAGE_WARNING("you can't have an empty code string for loadShaderAsString");
					return result;
				}

				ktk::vector<ktk::uint32_t> shader_code;

				switch (type)
				{
				case shader_type_t::kShaderType_Pixel:
				{
					shader_code =
						this->compileShaderFromStringToSPIRV(code_as_string,
							shaderc_shader_kind::shaderc_fragment_shader);
					break;
				}
				case shader_type_t::kShaderType_Vertex:
				{
					shader_code =
						this->compileShaderFromStringToSPIRV(code_as_string,
							shaderc_shader_kind::shaderc_vertex_shader);
					break;
				}
				case shader_type_t::kShaderType_Compute:
				{
					shader_code =
						this->compileShaderFromStringToSPIRV(code_as_string,
							shaderc_shader_kind::shaderc_compute_shader);
				}
				}

				if (shader_code.empty())
				{
					KOTEK_MESSAGE_WARNING(
						"can't build shader from Vulkan API, because your "
						"shader code is empty");
					return result;
				}

				VkShaderModuleCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				info.flags = 0;
				info.pCode = shader_code.data();
				info.pNext = nullptr;
				info.codeSize = shader_code.size() * sizeof(ktk::uint32_t);

				VkDevice p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "your device is invalid (VkDevice)");

				VkShaderModule p_module = nullptr;

				VkResult status =
					vkCreateShaderModule(p_device, &info, nullptr, &p_module);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreateShaderModule, see status");

				result.setSPIRVByteCode(shader_code);
				result.setModule(p_module);

				return result;
			}

			void kotek_render_shader_manager::destroyShader(
				const shader_module_t& instance) noexcept
			{
				if (instance.getModule() == nullptr)
					return;

				vkDestroyShaderModule(this->m_p_render_device->GetDevice(),
					instance.getModule(), nullptr);
			}

			ktk::vector<ktk::uint32_t>
			kotek_render_shader_manager::compileShaderToSPIRV(
				const ktk::string& path_to_file, shaderc_shader_kind type,
				const ktk::map<ktk::string_legacy, ktk::string_legacy>&
					macros) noexcept
			{
				KOTEK_CPU_PROFILE();

				ktk::vector<ktk::uint32_t> result;

				if (this->m_p_filesystem->IsValidPath(path_to_file) == false)
				{
					KOTEK_MESSAGE_WARNING(
						"invalid path for compiling shader to SPIRV: [{}]",
						path_to_file.get_as_is());

					return result;
				}

				shaderc::Compiler compiler;
				shaderc::CompileOptions user_options;

				for (const auto& pair_macro_name_and_value : macros)
				{
					user_options.AddMacroDefinition(
						pair_macro_name_and_value.first.c_str(),
						pair_macro_name_and_value.second.c_str());
				}

#ifdef KOTEK_DEBUG
#else
				user_options.SetOptimizationLevel(
					shaderc_optimization_level_size);
#endif

				ktk::string temp = this->m_p_filesystem->ReadFile(path_to_file);

				if (temp.empty() == true)
				{
					KOTEK_MESSAGE_WARNING(
						"your shader file contains nothing: [{}]",
						path_to_file.get_as_is());
					return result;
				}

				ktk::string_legacy file_content(
					ktk::cast::to_legacy_string(temp));

				shaderc::SpvCompilationResult module =
					compiler.CompileGlslToSpv(file_content.c_str(), type,
						ktk::cast::to_legacy_string(path_to_file).c_str(),
						user_options);

				auto status = module.GetCompilationStatus();

				if (status != shaderc_compilation_status_success)
				{
					KOTEK_MESSAGE_ERROR("can't build shader: status[{}] {}",
						module.GetCompilationStatus(),
						ktk::cast::to_string(module.GetErrorMessage().c_str()));

					return result;
				}

				result = {module.cbegin(), module.cend()};

				return result;
			}

			ktk::vector<ktk::uint32_t>
			kotek_render_shader_manager::compileShaderFromStringToSPIRV(
				const ktk::string& code_as_string, shaderc_shader_kind type,
				const ktk::map<ktk::string_legacy, ktk::string_legacy>&
					macros) noexcept
			{
				KOTEK_CPU_PROFILE();

				ktk::vector<ktk::uint32_t> result;

				if (code_as_string.empty())
				{
					KOTEK_MESSAGE_WARNING("you have passed an empty string "
										  "which can't be compiled");
					return result;
				}

				shaderc::Compiler compiler;
				shaderc::CompileOptions user_options;

				for (const auto& pair_macro_name_and_value : macros)
				{
					user_options.AddMacroDefinition(
						pair_macro_name_and_value.first.c_str(),
						pair_macro_name_and_value.second.c_str());
				}

#ifdef KOTEK_DEBUG
#else
				user_options.SetOptimizationLevel(
					shaderc_optimization_level_size);
#endif

				shaderc::SpvCompilationResult module =
					compiler.CompileGlslToSpv(
						code_as_string.get_as_legacy().c_str(), type,
						"CompiledFromString", user_options);

				auto status = module.GetCompilationStatus();

				if (status != shaderc_compilation_status_success)
				{
					KOTEK_MESSAGE_ERROR("can't build shader: status[{}] {}",
						module.GetCompilationStatus(),
						ktk::cast::to_string(module.GetErrorMessage().c_str()));

					return result;
				}

				result = {module.cbegin(), module.cend()};

				return result;
			}

			shader_type_t kotek_render_shader_manager::detectType(

				const ktk::string& path_to_file) noexcept
			{
				KOTEK_CPU_PROFILE();

				if (path_to_file.empty())
				{
					KOTEK_MESSAGE_WARNING("you have an empty path, engine "
										  "can't detect type, [{}]",
						path_to_file.get_as_is());
					return shader_type_t::kShaderType_Unknown;
				}

				if (this->m_p_filesystem->IsValidPath(path_to_file) == false)
				{
					KOTEK_MESSAGE_WARNING(
						"invalid path to file, can't analyze this path: [{}]",
						path_to_file.get_as_is());
					return shader_type_t::kShaderType_Unknown;
				}

				ktk::filesystem::path temp(path_to_file);

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("detecting shader for type: [{}]",
					path_to_file.get_as_is());
#endif

				if (temp.has_filename())
				{
					const auto& filename = temp.filename();

					ktk::string temp_filename(
						ktk::cast::to_string(filename.c_str()));

					if (temp_filename.get_as_is().find(_kShaderPrefix_Vertex) !=
						ktk::string::npos)
					{
#ifdef KOTEK_DEBUG
						KOTEK_MESSAGE("detected: Vertex [{}]",
							static_cast<ktk::enum_base_t>(shader_type_t::kShaderType_Vertex));
#endif

						return shader_type_t::kShaderType_Vertex;
					}
					else if (temp_filename.get_as_is().find(
								 _kShaderPrefix_Fragment) != ktk::string::npos)
					{
#ifdef KOTEK_DEBUG
						KOTEK_MESSAGE("detected: Pixel [{}]",
							static_cast<ktk::enum_base_t>(shader_type_t::kShaderType_Pixel));
#endif

						return shader_type_t::kShaderType_Pixel;
					}
					else if (temp_filename.get_as_is().find(
								 _kShaderPrefix_Compute) != ktk::string::npos)
					{
#ifdef KOTEK_DEBUG
						KOTEK_MESSAGE("detected: Compute [{}]",
							static_cast<ktk::enum_base_t>(shader_type_t::kShaderType_Compute));
#endif

						return shader_type_t::kShaderType_Compute;
					}
					else
					{
						KOTEK_MESSAGE_WARNING(
							"can't detect shader type because we can't handle "
							"with this prefix or non prefixed file: [{}]",
							path_to_file.get_as_is());

						return shader_type_t::kShaderType_Unknown;
					}
				}
				else
				{
					KOTEK_MESSAGE_WARNING("you passed an invalid path without "
										  "destination file!!! [{}]",
						path_to_file.get_as_is());

					return shader_type_t::kShaderType_Unknown;
				}

				return shader_type_t::kShaderType_Unknown;
			}

			kotek_render_shader_manager::~kotek_render_shader_manager() {}

			namespace helper
			{
				bool isRTXShaderByType(shader_type_t type) noexcept
				{
					bool is_rtx = true;

					switch (type)
					{
					case shader_type_t::kShaderType_Compute:
					case shader_type_t::kShaderType_Geometry:
					case shader_type_t::kShaderType_Mesh:
					case shader_type_t::kShaderType_Pixel:
					case shader_type_t::kShaderType_Task:
					case shader_type_t::kShaderType_TessellationControl:
					case shader_type_t::kShaderType_TessellationEvaluation:
					case shader_type_t::kShaderType_Vertex:
					{
						is_rtx = false;
						break;
					}
					}

					return is_rtx;
				}

				bool isBufferByDescriptorType(VkDescriptorType type) noexcept
				{
					switch (type)
					{
					case VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
					case VkDescriptorType::
						VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
					case VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
					case VkDescriptorType::
						VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
						return true;
					}

					return false;
				}

				ktk::string translateShaderTypeToString(
					shader_type_t type) noexcept
				{
					switch (type)
					{
					case shader_type_t::kShaderType_Compute:
					{
						return "shader_type_compute";
					}
					case shader_type_t::kShaderType_Geometry:
					{
						return "shader_type_geometry";
					}
					case shader_type_t::kShaderType_Mesh:
					{
						return "shader_type_mesh";
					}
					case shader_type_t::kShaderType_Pixel:
					{
						return "shader_type_pixel";
					}
					case shader_type_t::kShaderType_RTX_AnyHit:
					{
						return "shader_type_rtx_any_hit";
					}
					case shader_type_t::kShaderType_RTX_Callable:
					{
						return "shader_type_rtx_callable";
					}
					case shader_type_t::kShaderType_RTX_ClosesHit:
					{
						return "shader_type_rtx_closes_hit";
					}
					case shader_type_t::kShaderType_RTX_Generation:
					{
						return "shader_type_rtx_generation";
					}
					case shader_type_t::kShaderType_RTX_Intersection:
					{
						return "shader_type_rtx_intersection";
					}
					case shader_type_t::kShaderType_RTX_Miss:
					{
						return "shader_type_rtx_miss";
					}
					case shader_type_t::kShaderType_Task:
					{
						return "shader_type_task";
					}
					case shader_type_t::kShaderType_TessellationControl:
					{
						return "shader_type_tessellation_control";
					}
					case shader_type_t::kShaderType_TessellationEvaluation:
					{
						return "shader_type_tessellation_evaluation";
					}
					case shader_type_t::kShaderType_Unknown:
					{
						return "shader_type_unknown";
					}
					case shader_type_t::kShaderType_Vertex:
					{
						return "shader_type_vertex";
					}
					default:
					{
						KOTEK_ASSERT(false,
							"can't be you passed invalid shader_type_t {} "
							"(can't parse)",
							static_cast<ktk::enum_base_t>(type));

						return "shader_type_INVALID_ENUM_CANT_PARSE";
					}
					}
				}

				ktk::string translateShaderTypeToStringFormat(
					shader_type_t type) noexcept
				{
					switch (type)
					{
					case shader_type_t::kShaderType_Compute:
					{
						return ".comp";
					}
					case shader_type_t::kShaderType_Geometry:
					{
						return ".geom";
					}
					case shader_type_t::kShaderType_Mesh:
					{
						return ".mesh";
					}
					case shader_type_t::kShaderType_Pixel:
					{
						return ".frag";
					}
					case shader_type_t::kShaderType_RTX_AnyHit:
					{
						return ".rahit";
					}
					case shader_type_t::kShaderType_RTX_Callable:
					{
						return ".rcall";
					}
					case shader_type_t::kShaderType_RTX_ClosesHit:
					{
						return ".rchit";
					}
					case shader_type_t::kShaderType_RTX_Generation:
					{
						return ".rgen";
					}
					case shader_type_t::kShaderType_RTX_Intersection:
					{
						return ".rint";
					}
					case shader_type_t::kShaderType_RTX_Miss:
					{
						return ".rmiss";
					}
					case shader_type_t::kShaderType_Task:
					{
						return ".task";
					}
					case shader_type_t::kShaderType_TessellationControl:
					{
						return ".tesc";
					}
					case shader_type_t::kShaderType_TessellationEvaluation:
					{
						return ".tese";
					}
					case shader_type_t::kShaderType_Unknown:
					{
						return "format_unkown (kShaderType_Unknown)";
					}
					case shader_type_t::kShaderType_Vertex:
					{
						return ".vert";
					}
					default:
					{
						KOTEK_ASSERT(false,
							"can't be you passed invalid shader_type_t {} "
							"(can't parse)",
							static_cast<ktk::enum_base_t>(type));

						return "shader_type_INVALID_ENUM_CANT_PARSE";
					}
					}
				}

				ktk::string translateDescriptorTypeToString(
					VkDescriptorType type) noexcept
				{
					return string_VkDescriptorType(type);
				}

				void printBindingInfo(
					const descriptor_set_info_t& info) noexcept
				{
					KOTEK_MESSAGE("\n\n/// Binding ///\n\n");

					KOTEK_MESSAGE("Attached to variable (in shader): {}",
						info.getVariableName().get_as_is());
					KOTEK_MESSAGE("Descriptor type: {}",
						translateDescriptorTypeToString(
							info.getDescriptorType())
							.get_as_is());
					KOTEK_MESSAGE("Descriptor set index: {}",
						info.getDescriptorSetIndex());
					KOTEK_MESSAGE("Binding index: {}", info.getBindingIndex());

					KOTEK_MESSAGE("\n\n/// Binding ///\n\n");
				}

				shader_type_t GetShaderTypeByShaderStageFlagBits(
					VkShaderStageFlagBits bits) noexcept
				{
					shader_type_t result = shader_type_t::kShaderType_Unknown;

					if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT)
					{
						result = shader_type_t::kShaderType_Vertex;
					}
					else if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT)
					{
						result = shader_type_t::kShaderType_Pixel;
					}
					else if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT)
					{
						result = shader_type_t::kShaderType_Compute;
					}
					else if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT)
					{
						result = shader_type_t::kShaderType_Geometry;
					}
					else if (bits ==
						VkShaderStageFlagBits::
							VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT)
					{
						result = shader_type_t::kShaderType_TessellationControl;
					}
					else if (bits ==
						VkShaderStageFlagBits::
							VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT)
					{
						result =
							shader_type_t::kShaderType_TessellationEvaluation;
					}
					else if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_NV)
					{
						result = shader_type_t::kShaderType_Task;
					}
					else if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_KHR)
					{
						result = shader_type_t::kShaderType_RTX_Callable;
					}
					else if (bits ==
						VkShaderStageFlagBits::
							VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR)
					{
						result = shader_type_t::kShaderType_RTX_ClosesHit;
					}
					else if (bits ==
						VkShaderStageFlagBits::
							VK_SHADER_STAGE_INTERSECTION_BIT_KHR)
					{
						result = shader_type_t::kShaderType_RTX_Intersection;
					}
					else if (bits ==
						VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_KHR)
					{
						result = shader_type_t::kShaderType_RTX_AnyHit;
					}
					else
					{
						KOTEK_ASSERT(
							result != shader_type_t::kShaderType_Unknown,
							"can't find an appropriate bit from "
							"VkShaderStageBits, "
							"can't decode!");
					}

					return result;
				}

				VkShaderStageFlagBits GetShaderStageFlagBitsByShaderType(
					shader_type_t type) noexcept
				{
					VkShaderStageFlagBits result = VkShaderStageFlagBits::
						VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;

					if (type == shader_type_t::kShaderType_Vertex)
					{
						result =
							VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
					}
					else if (type == shader_type_t::kShaderType_Pixel)
					{
						result =
							VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
					}
					else if (type == shader_type_t::kShaderType_Compute)
					{
						result =
							VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;
					}
					else if (type == shader_type_t::kShaderType_Geometry)
					{
						result =
							VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT;
					}
					else if (type ==
						shader_type_t::kShaderType_TessellationControl)
					{
						result = VkShaderStageFlagBits::
							VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
					}
					else if (type ==
						shader_type_t::kShaderType_TessellationEvaluation)
					{
						result = VkShaderStageFlagBits::
							VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
					}
					else if (type == shader_type_t::kShaderType_Task)
					{
						result =
							VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_NV;
					}
					else if (type == shader_type_t::kShaderType_RTX_Callable)
					{
						result = VkShaderStageFlagBits::
							VK_SHADER_STAGE_CALLABLE_BIT_KHR;
					}
					else if (type == shader_type_t::kShaderType_RTX_ClosesHit)
					{
						result = VkShaderStageFlagBits::
							VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
					}
					else if (type ==
						shader_type_t::kShaderType_RTX_Intersection)
					{
						result = VkShaderStageFlagBits::
							VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
					}
					else if (type == shader_type_t::kShaderType_RTX_AnyHit)
					{
						result = VkShaderStageFlagBits::
							VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
					}
					else
					{
						KOTEK_ASSERT(result !=
								VkShaderStageFlagBits::
									VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM,
							"can't find an appropriate bit from "
							"VkShaderStageBits, "
							"can't decode!");
					}

					return result;
				}
				VkImageCreateInfo InitializeImageForShaders(int width,
					int height, VkImageLayout image_layout_initial,
					VkImageType image_type, ktk::uint32_t depth_value,
					ktk::uint32_t mip_levels, ktk::uint32_t array_layers,
					VkSampleCountFlagBits samples_count,
					VkImageTiling image_tiling, VkImageUsageFlags image_usage,
					VkSharingMode image_sharing_mode) noexcept
				{
					return InitializeImage(width, height, image_layout_initial,
						image_type, depth_value, mip_levels, array_layers,
						samples_count, image_tiling, image_usage,
						image_sharing_mode);
				}

				VkImageCreateInfo InitializeImageForFramebuffer(int width,
					int height, VkImageLayout image_layout_initial,
					VkImageType image_type, ktk::uint32_t depth_value,
					ktk::uint32_t mip_levels, ktk::uint32_t array_layers,
					VkSampleCountFlagBits samples_count,
					VkImageTiling image_tiling, VkImageUsageFlags image_usage,
					VkSharingMode image_sharing_mode) noexcept
				{
					return InitializeImage(width, height, image_layout_initial,
						image_type, depth_value, mip_levels, array_layers,
						samples_count, image_tiling, image_usage,
						image_sharing_mode);
				}

				VkImageCreateInfo InitializeImage(int width, int height,
					VkImageLayout image_layout_initial, VkImageType image_type,
					ktk::uint32_t depth_value, ktk::uint32_t mip_levels,
					ktk::uint32_t array_layers,
					VkSampleCountFlagBits samples_count,
					VkImageTiling image_tiling, VkImageUsageFlags image_usage,
					VkSharingMode image_sharing_mode) noexcept
				{
					return {.sType = VkStructureType::
								VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
						.imageType = image_type,
						.format = kImageFormat,
						.extent = {.width = static_cast<ktk::uint32_t>(width),
							.height = static_cast<ktk::uint32_t>(height),
							.depth = depth_value},
						.mipLevels = mip_levels,
						.arrayLayers = array_layers,
						.samples = samples_count,
						.tiling = image_tiling,
						.usage = image_usage,
						.sharingMode = image_sharing_mode,
						.initialLayout = image_layout_initial};
				}

				VkSamplerCreateInfo InitializeSampler(VkFilter mag_filter,
					VkFilter min_filter, VkSamplerMipmapMode mip_map_mode,
					VkSamplerAddressMode address_mode_u,
					VkSamplerAddressMode address_mode_v,
					VkSamplerAddressMode address_mode_w, float min_lod,
					float max_lod) noexcept
				{
					return {.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
						.magFilter = mag_filter,
						.minFilter = min_filter,
						.mipmapMode = mip_map_mode,
						.addressModeU = address_mode_u,
						.addressModeV = address_mode_v,
						.addressModeW = address_mode_w,
						.maxAnisotropy = 1.0f, // TODO: use from physical device
					                           // limit information about
					                           // available maxAnisotropy field
						.minLod = min_lod,
						.maxLod = max_lod};
				}

				VkPipelineInputAssemblyStateCreateInfo
				InitializePipelineInputAssemblyState(
					VkPrimitiveTopology topology,
					VkBool32 primitive_restart_enable,
					VkPipelineInputAssemblyStateCreateFlags flags) noexcept
				{
					VkPipelineInputAssemblyStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
					info.topology = topology;
					info.flags = flags;
					info.primitiveRestartEnable = primitive_restart_enable;

					return info;
				}

				VkPipelineRasterizationStateCreateInfo
				InitializePipelineRasterizationState(VkPolygonMode mode_polygon,
					VkCullModeFlags mode_cull, VkFrontFace front_face,
					VkPipelineRasterizationStateCreateFlags flags,
					VkBool32 depth_clamp_enable, float line_width) noexcept
				{
					VkPipelineRasterizationStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
					info.polygonMode = mode_polygon;
					info.cullMode = mode_cull;
					info.frontFace = front_face;
					info.flags = flags;
					info.depthClampEnable = depth_clamp_enable;
					info.lineWidth = line_width;

					return info;
				}

				VkPipelineColorBlendAttachmentState
				InitializePipelineColorBlendAttachmentState(
					VkBool32 blend_enable, VkBlendFactor src_color_blend_factor,
					VkBlendFactor dst_color_blend_factor,
					VkBlendOp color_blend_op,
					VkBlendFactor src_alpha_blend_factor,
					VkBlendFactor dst_alpha_blend_factor,
					VkBlendOp alpha_blend_op,
					VkColorComponentFlags color_write_mask) noexcept
				{
					VkPipelineColorBlendAttachmentState result = {};

					result.blendEnable = blend_enable;
					result.srcColorBlendFactor = src_color_blend_factor;
					result.dstColorBlendFactor = dst_color_blend_factor;
					result.colorBlendOp = color_blend_op;
					result.srcAlphaBlendFactor = src_alpha_blend_factor;
					result.dstAlphaBlendFactor = dst_alpha_blend_factor;
					result.alphaBlendOp = alpha_blend_op;
					result.colorWriteMask = color_write_mask;

					return result;
				}

				VkPipelineColorBlendStateCreateInfo
				InitializePipelineColorBlendState(
					const ktk::vector<VkPipelineColorBlendAttachmentState>&
						states,
					VkBool32 logic_op_enable, VkLogicOp logic_op, float blend_R,
					float blend_G, float blend_B, float blend_A,
					VkPipelineColorBlendStateCreateFlags flags) noexcept
				{
					VkPipelineColorBlendStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
					info.attachmentCount = states.size();
					info.pAttachments = states.data();
					info.logicOpEnable = logic_op_enable;
					info.logicOp = logic_op;
					info.flags = flags;
					info.blendConstants[0] = blend_R;
					info.blendConstants[1] = blend_G;
					info.blendConstants[2] = blend_B;
					info.blendConstants[3] = blend_A;

					return info;
				}

				VkPipelineDepthStencilStateCreateInfo
				InitializePipelineDepthStencilState(VkBool32 depth_test_enable,
					VkBool32 depth_write_enable, VkBool32 stencil_test_enable,
					VkCompareOp depth_compare_op,
					VkCompareOp back_compare_op) noexcept
				{
					VkPipelineDepthStencilStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
					info.depthTestEnable = depth_test_enable;
					info.depthWriteEnable = depth_write_enable;
					info.stencilTestEnable = stencil_test_enable;
					info.depthCompareOp = depth_compare_op;
					info.back.compareOp = back_compare_op;

					return info;
				}

				VkPipelineViewportStateCreateInfo
				InitializePipelineViewportState(ktk::uint32_t viewport_count,
					ktk::uint32_t scissor_count, const VkViewport* p_viewports,
					const VkRect2D* p_scissors,
					VkPipelineViewportStateCreateFlags flags) noexcept
				{
					VkPipelineViewportStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
					info.viewportCount = viewport_count;
					info.scissorCount = scissor_count;
					info.pViewports = p_viewports;
					info.pScissors = p_scissors;
					info.flags = flags;

					return info;
				}

				VkPipelineMultisampleStateCreateInfo
				InitializePipelineMultisampleState(VkBool32 sample_enable,
					VkSampleCountFlagBits rasterization_samples,
					float min_sample_shading, const VkSampleMask* p_mask,
					VkBool32 alpha_to_coverage_enable,
					VkBool32 alpha_to_one_enable) noexcept
				{
					VkPipelineMultisampleStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
					info.sampleShadingEnable = sample_enable;
					info.rasterizationSamples = rasterization_samples;
					info.minSampleShading = min_sample_shading;
					info.pSampleMask = p_mask;
					info.alphaToCoverageEnable = alpha_to_one_enable;
					info.alphaToOneEnable = alpha_to_one_enable;

					return info;
				}

				VkPipelineDynamicStateCreateInfo InitializePipelineDynamicState(
					const ktk::vector<VkDynamicState>& states,
					VkPipelineDynamicStateCreateFlags flags) noexcept
				{
					VkPipelineDynamicStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
					info.pDynamicStates = states.data();
					info.dynamicStateCount = states.size();
					info.flags = flags;

					return info;
				}

				VkPipelineVertexInputStateCreateInfo
				InitializePipelineVertexInputState(
					const ktk::vector<VkVertexInputBindingDescription>&
						descriptions,
					const ktk::vector<VkVertexInputAttributeDescription>&
						attributes,
					VkPipelineVertexInputStateCreateFlags flags) noexcept
				{
					VkPipelineVertexInputStateCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
					info.flags = flags;
					info.pVertexAttributeDescriptions = attributes.data();
					info.vertexAttributeDescriptionCount = attributes.size();
					info.pVertexBindingDescriptions = descriptions.data();
					info.vertexBindingDescriptionCount = descriptions.size();

					return info;
				}

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
					ktk::uint32_t subpass, VkPipeline p_pipeline,
					ktk::uint32_t base_pipeline_index,
					VkPipelineCreateFlags flags) noexcept
				{
					VkGraphicsPipelineCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
					info.subpass = subpass;
					info.basePipelineHandle = p_pipeline;
					info.basePipelineIndex = base_pipeline_index;
					info.flags = flags;
					info.pTessellationState = p_tessellation_state;
					info.renderPass = p_pass;
					info.layout = p_layout;
					info.pDynamicState = p_dynamic_state;
					info.pColorBlendState = p_color_blend_state;
					info.pDepthStencilState = p_depth_stencil_state;
					info.pMultisampleState = p_multisample_state;
					info.pRasterizationState = p_rasterization_state;
					info.pViewportState = p_viewport_state;
					info.pInputAssemblyState = p_input_assembly_state;
					info.pVertexInputState = p_vertex_input_state;

					return info;
				}

				VkPipelineShaderStageCreateInfo InitializePipelineShaderStage(
					shader_type_t type, VkShaderModule p_module) noexcept
				{
					VkPipelineShaderStageCreateInfo result = {};

					if (p_module == nullptr)
					{
						KOTEK_ASSERT(
							false, "can't pass an invalid module pointer");
						return result;
					}

					result.sType =
						VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
					result.pNext = nullptr;
					result.flags = 0;
					result.pSpecializationInfo = nullptr;
					result.pName = "main";
					result.module = p_module;

					switch (type)
					{
					case shader_type_t::kShaderType_Vertex:
					{
						result.stage = VK_SHADER_STAGE_VERTEX_BIT;
						break;
					}
					case shader_type_t::kShaderType_Pixel:
					{
						result.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
						break;
					}
					case shader_type_t::kShaderType_Mesh:
					{
						result.stage = VK_SHADER_STAGE_MESH_BIT_NV;
						break;
					}
					case shader_type_t::kShaderType_Geometry:
					{
						result.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
						break;
					}
					case shader_type_t::kShaderType_Compute:
					{
						result.stage = VK_SHADER_STAGE_COMPUTE_BIT;
						break;
					}
					case shader_type_t::kShaderType_Task:
					{
						result.stage = VK_SHADER_STAGE_TASK_BIT_NV;
						break;
					}
					case shader_type_t::kShaderType_TessellationControl:
					{
						result.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
						break;
					}
					case shader_type_t::kShaderType_TessellationEvaluation:
					{
						result.stage =
							VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
						break;
					}
					default:
					{
						KOTEK_ASSERT(false, "you must specify your stage");
						break;
					}
					}

					return result;
				}
			} // namespace helper

			kotek_render_shader_manager::shader_module_t::shader_module_t(
				void) :
				m_p_module(nullptr)
			{
			}

			kotek_render_shader_manager::shader_module_t::~shader_module_t(void)
			{
			}

			void kotek_render_shader_manager::shader_module_t::setSPIRVByteCode(
				const ktk::vector<ktk::uint32_t>& info) noexcept
			{
				KOTEK_ASSERT(info.empty() == false,
					"you can't set SPIRV module data as empty vector");

				this->m_spv_info = info;
			}

			const ktk::vector<ktk::uint32_t>&
			kotek_render_shader_manager::shader_module_t::getSPIRVByteCode(
				void) const noexcept
			{
				return this->m_spv_info;
			}

			void kotek_render_shader_manager::shader_module_t::setModule(
				VkShaderModule p_module) noexcept
			{
				KOTEK_ASSERT(p_module,
					"you can't pass invalid pointer of VkShaderModule");
				this->m_p_module = p_module;
			}

			VkShaderModule
			kotek_render_shader_manager::shader_module_t::getModule(
				void) const noexcept
			{
				return this->m_p_module;
			}

			shader_loading_data_t::shader_loading_data_t(
				shader_loading_data_type_t type,
				const ktk::string& path_to_file_or_source_code_string) :
				m_type(type),
				m_data(path_to_file_or_source_code_string)
			{
			}

			shader_loading_data_t::shader_loading_data_t(
				shader_loading_data_type_t type, void* p_data) :
				m_type(type),
				m_data(p_data)
			{
			}

			shader_loading_data_t::shader_loading_data_t(void) :
				m_type(shader_loading_data_type_t::
						kShaderLoadingDataType_NotInitialized)
			{
			}

			shader_loading_data_t::~shader_loading_data_t(void) {}

			const ktk::variant<void*, ktk::string>&
			shader_loading_data_t::getData(void) const noexcept
			{
				return this->m_data;
			}

			void shader_loading_data_t::setData(
				const ktk::variant<void*, ktk::string>& data) noexcept
			{
				this->m_data = data;
			}

			shader_loading_data_type_t shader_loading_data_t::getType(
				void) const noexcept
			{
				return this->m_type;
			}

			void shader_loading_data_t::setType(
				shader_loading_data_type_t type) noexcept
			{
				this->m_type = type;
			}

			shader_input_data_t::shader_input_data_t(
				const ktk::string& render_pass_name,
				ktk::uint32_t binding_index, VkDescriptorType type,
				ktk::size_t buffer_size) :
				m_render_pass_name(render_pass_name),
				m_binding_index(binding_index), m_descriptor_type(type),
				m_descriptor_set_index(-1)
			{
				this->SetData(buffer_size);
			}

			shader_input_data_t::shader_input_data_t(
				const ktk::string& render_pass_name,
				ktk::uint32_t binding_index, VkDescriptorType type,
				const ktk::string& texture_name) :
				m_render_pass_name(render_pass_name),
				m_binding_index(binding_index), m_descriptor_type(type),
				m_descriptor_set_index(-1)
			{
				this->SetData(texture_name);
			}

			shader_input_data_t::shader_input_data_t(void) {}

			shader_input_data_t::~shader_input_data_t(void) {}

			void shader_input_data_t::setDescriptorSetIndex(
				ktk::uint32_t descriptor_set_index) noexcept
			{
				this->m_descriptor_set_index = descriptor_set_index;
			}

			ktk::uint32_t shader_input_data_t::getDescriptorSetIndex(
				void) const noexcept
			{
				return ktk::uint32_t();
			}

			ktk::uint32_t shader_input_data_t::getBindingIndex(
				void) const noexcept
			{
				return this->m_binding_index;
			}

			VkDescriptorType shader_input_data_t::getDescriptorType(
				void) const noexcept
			{
				return this->m_descriptor_type;
			}

			ktk::size_t shader_input_data_t::GetData_BufferSize(
				void) const noexcept
			{
				KOTEK_ASSERT(
					helper::isBufferByDescriptorType(this->m_descriptor_type),
					"you can't set this data for images...");

				return std::get<0>(this->m_data);
			}

			ktk::string shader_input_data_t::GetData_RenderGraphTextureName(
				void) const noexcept
			{
				KOTEK_ASSERT(helper::isBufferByDescriptorType(
								 this->m_descriptor_type) == false,
					"you can't set this data for buffers...");

				return std::get<1>(this->m_data);
			}

			const ktk::string& shader_input_data_t::GetRenderPassName(
				void) const noexcept
			{
				return this->m_render_pass_name;
			}

			bool shader_input_data_t::IsDataFor(void) const noexcept
			{
				return helper::isBufferByDescriptorType(
					this->m_descriptor_type);
			}

			void shader_input_data_t::SetData(ktk::size_t buffer_size) noexcept
			{
				KOTEK_ASSERT(
					helper::isBufferByDescriptorType(this->m_descriptor_type),
					"you can't set this data for images...");

				this->m_data = buffer_size;
			}

			void shader_input_data_t::SetData(
				const ktk::string& texture_name) noexcept
			{
				KOTEK_ASSERT(helper::isBufferByDescriptorType(
								 this->m_descriptor_type) == false,
					"you can't set this data for buffers...");

				this->m_data = texture_name;
			}

			descriptor_set_info_t::descriptor_set_info_t(
				ktk::uint32_t descriptor_set_index, ktk::uint32_t binding_index,
				VkDescriptorType type, shader_type_t shader_type,
				const ktk::string& shader_variable_name) :
				m_descriptor_set_index(descriptor_set_index),
				m_binding_index(binding_index), m_type(type),
				m_shader_type(shader_type),
				m_variable_name(shader_variable_name)
			{
			}

			descriptor_set_info_t::descriptor_set_info_t(void) {}

			descriptor_set_info_t::~descriptor_set_info_t(void) {}

			ktk::uint32_t descriptor_set_info_t::getDescriptorSetIndex(
				void) const noexcept
			{
				return this->m_descriptor_set_index;
			}

			ktk::uint32_t descriptor_set_info_t::getBindingIndex(
				void) const noexcept
			{
				return this->m_binding_index;
			}

			VkDescriptorType descriptor_set_info_t::getDescriptorType(
				void) const noexcept
			{
				return this->m_type;
			}

			const ktk::string& descriptor_set_info_t::getVariableName(
				void) const noexcept
			{
				return this->m_variable_name;
			}

			shader_type_t descriptor_set_info_t::GetShaderType(
				void) const noexcept
			{
				return this->m_shader_type;
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
