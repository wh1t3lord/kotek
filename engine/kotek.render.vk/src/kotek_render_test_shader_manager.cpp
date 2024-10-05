#ifdef KOTEK_DEBUG
	#include "../include/kotek_render_device.h"
	#include "../include/kotek_render_shader_manager.h"
	#include <catch2/catch_test_macros.hpp>

namespace Kotek
{
	namespace Render
	{
		void registerTests_ShaderManager_ForModule_Render_VK()
		{
			KOTEK_MESSAGE("registered!");
		}

		/* TODO: перенести тесты в отдельное приложение, остальное тестировать
		   динамически BOOST_AUTO_TEST_CASE(load_shader_by_invalid_name)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);
		            ktk::shared_ptr<vk::kotek_render_device> render_device =
		                std::make_shared<vk::kotek_render_device>();

		            render_device->initialize(main_manager);

		            main_manager.setRenderDevice(render_device);

		            vk::kotek_render_shader_manager instance(&main_manager);

		            instance.initialize();

		            ktk::ustring path_to_file =
		                main_manager.GetFileSystem()->GetFolderByEnum(
		                    Core::folder_index_t::kFolderIndex_Shaders);

		            path_to_file += ktk::kPathSeparator;
		            path_to_file += KOTEK_TEXTU("test.glsl");

		            auto shader_module = instance.loadShader(path_to_file);

		            BOOST_CHECK(shader_module.getModule() == nullptr);

		            instance.destroyShader(shader_module);

		            instance.shutdown();
		            render_device->shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(load_shader_by_valid_name)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            auto render_device =
		   std::make_shared<vk::kotek_render_device>();

		            render_device->initialize(main_manager);

		            main_manager.setRenderDevice(render_device);

		            vk::kotek_render_shader_manager instance(&main_manager);

		            instance.initialize();

		            ktk::ustring path_to_file =
		                main_manager.GetFileSystem()->GetFolderByEnum(
		                    Core::folder_index_t::kFolderIndex_Shaders);

		            path_to_file += ktk::kPathSeparator;
		            path_to_file += KOTEK_TEXTU("test.vert");

		            auto shader_module = instance.loadShader(path_to_file);

		            BOOST_CHECK(shader_module.getModule() != nullptr);

		            instance.destroyShader(shader_module);

		            instance.shutdown();
		            render_device->shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(load_shader_from_string_valid)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            auto render_device =
		   std::make_shared<vk::kotek_render_device>();

		            render_device->initialize(main_manager);

		            main_manager.setRenderDevice(render_device);

		            vk::kotek_render_shader_manager instance(&main_manager);

		            instance.initialize();

		            ktk::string_legacy code =
		                "#version 400\n"
		                "#extension GL_ARB_separate_shader_objects : enable\n"
		                "#extension GL_ARB_shading_language_420pack : enable\n"
		                "layout (std140, binding = 0) uniform vertexBuffer {\n"
		                "    mat4 ProjectionMatrix;\n"
		                "} myVertexBuffer;\n"
		                "layout (location = 0) in vec4 pos;\n"
		                "layout (location = 1) in vec2 inTexCoord;\n"
		                "layout (location = 2) in vec4 inColor;\n"
		                "layout (location = 0) out vec2 outTexCoord;\n"
		                "layout (location = 1) out vec4 outColor;\n"
		                "void main() {\n"
		                "   outColor = inColor;\n"
		                "   outTexCoord = inTexCoord;\n"
		                "   gl_Position = myVertexBuffer.ProjectionMatrix *
		   pos;\n"
		                "}\n";

		            auto result = instance.loadShaderAsString(
		                code, vk::shader_type_t::kShaderType_Vertex);

		            BOOST_CHECK(result.getModule() != nullptr);

		            instance.destroyShader(result);

		            instance.shutdown();
		            render_device->shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(load_shader_from_string_invalid)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            auto render_device =
		   std::make_shared<vk::kotek_render_device>();

		            render_device->initialize(main_manager);
		            main_manager.setRenderDevice(render_device);

		            vk::kotek_render_shader_manager instance(&main_manager);

		            instance.initialize();

		            ktk::string_legacy code =
		                "#version 400\n"
		                "#extension GL_ARB_separate_shader_objects : enable\n"
		                "#extension GL_ARB_shading_language_420pack : enable\n"
		                "layout (std140, binding = 0) uniform vertexBuffer {\n"
		                "    mat4 ProjectionMatrix;\n"
		                "} myVertexBuffer;\n"
		                "layout (location = 0) in vec4 pos;\n"
		                "layout (location = 1) in vec2 inTexCoord;\n"
		                "layout (location = 2) in vec4 inColor;\n"
		                "layout (location = 0) out vec2 outTexCoord;\n"
		                "layout (location = 1) out vec4 outColor;\n"
		                "void main() {\n"
		                "   outColor = inColor;\n"
		                "   outTexCoord = inTexCoord;\n"
		                "   gl_Position123 = myVertexBuffer.ProjectionMatrix *
		   pos;\n"
		                "}\n";

		            auto result = instance.loadShaderAsString(
		                code, vk::shader_type_t::kShaderType_Vertex);

		            BOOST_CHECK(result.getModule() == nullptr);

		            instance.destroyShader(result);

		            instance.shutdown();
		            render_device->shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(load_shader_from_string_but_it_is_wrong_type)
		        {
		            Core::ktkMainManager main_manager(0, nullptr);

		            auto render_device =
		   std::make_shared<vk::kotek_render_device>();

		            render_device->initialize(main_manager);
		            main_manager.setRenderDevice(render_device);

		            vk::kotek_render_shader_manager instance(&main_manager);

		            instance.initialize();

		            ktk::string_legacy code =
		                "#version 400\n"
		                "#extension GL_ARB_separate_shader_objects : enable\n"
		                "#extension GL_ARB_shading_language_420pack : enable\n"
		                "layout (std140, binding = 0) uniform vertexBuffer {\n"
		                "    mat4 ProjectionMatrix;\n"
		                "} myVertexBuffer;\n"
		                "layout (location = 0) in vec4 pos;\n"
		                "layout (location = 1) in vec2 inTexCoord;\n"
		                "layout (location = 2) in vec4 inColor;\n"
		                "layout (location = 0) out vec2 outTexCoord;\n"
		                "layout (location = 1) out vec4 outColor;\n"
		                "void main() {\n"
		                "   outColor = inColor;\n"
		                "   outTexCoord = inTexCoord;\n"
		                "   gl_Position = myVertexBuffer.ProjectionMatrix *
		   pos;\n"
		                "}\n";

		            auto result = instance.loadShaderAsString(
		                code, vk::shader_type_t::kShaderType_Pixel);

		            BOOST_CHECK(result.getModule() == nullptr);

		            instance.destroyShader(result);

		            instance.shutdown();
		            render_device->shutdown();
		        }

		        BOOST_AUTO_TEST_CASE(helper_translate_shader_stage_bits_to_shader_type_t)
		        {
		            Kotek::Render::vk::helper::GetShaderTypeByShaderStageFlagBits(VK_SHADER_STAGE_VERTEX_BIT);
		        }*/
	} // namespace Render
} // namespace Kotek

#endif