#include "../include/kotek_render_shader_manager.h"
#include "../include/kotek_render_buffer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

ktkRenderShaderManager::ktkRenderShaderManager(
	kun_core ktkMainManager* p_main_manager) :
	m_is_reallocation_feature_supported{}, m_total_memory{}, m_current_memory{},
	m_p_main_manager{p_main_manager}
{
	KOTEK_ASSERT(p_main_manager, "must be valid");

	this->m_p_filesystem = p_main_manager->GetFileSystem();
}

ktkRenderShaderManager::~ktkRenderShaderManager(void) {}

// TODO: implement reallocation
void ktkRenderShaderManager::Initialize(
	kun_ktk size_t value_in_bytes, bool enable_reallocation_feature)
{
	this->m_is_reallocation_feature_supported = enable_reallocation_feature;
	this->m_total_memory = value_in_bytes;
	this->m_current_memory = this->m_total_memory;

#ifdef KOTEK_DEBUG
	auto p_translate_callback = [](bool val) -> const char*
	{
		if (val)
			return "enabled";
		else
			return "disabled";
	};

	KOTEK_MESSAGE("allocated memory for shader manager: {} Mb ({} Kb), "
				  "reallocation feature: {}",
		(static_cast<float>(value_in_bytes) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Megabytes)),
		(static_cast<float>(value_in_bytes) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Kilobytes)),
		p_translate_callback(enable_reallocation_feature));
#endif
}

void ktkRenderShaderManager::Shutdown(void)
{
#ifdef KOTEK_DEBUG
	bool deleted_all_shaders = true;
	for (const auto& [shader_handle_id, delete_status] :
		this->m_user_called_destroy_shaders)
	{
		if (delete_status == false)
		{
			deleted_all_shaders = false;
			KOTEK_ASSERT(delete_status,
				"forgot to call Destroy_Shader from shader manager! Shader "
				"handle: {}",
				shader_handle_id);
		}
	}

	KOTEK_ASSERT(deleted_all_shaders,
		"you forget to issue Destroy_Shader calling in your renderer "
		"implementation! Not all shader resources are destroyed!!!");

	bool deleted_all_buffers = true;
	for (const auto& [buffer_handle_id, delete_status] :
		this->m_user_called_destroy_buffers)
	{
		if (delete_status == false)
		{
			deleted_all_buffers = false;
			KOTEK_ASSERT(delete_status,
				"forgot to call Destroy_Buffer from shader manager! Buffer "
				"handle: {}",
				buffer_handle_id);
		}
	}

	KOTEK_ASSERT(deleted_all_buffers,
		"you forget to issue Destroy_Buffer calling in your renderer "
		"implementation! Not all shader's buffer resources are "
		"destroyed!!!");

	bool deleted_all_programs = true;
	for (const auto& [program_handle_id, delete_status] :
		this->m_user_called_destroy_programs)
	{
		if (delete_status == false)
		{
			KOTEK_ASSERT(delete_status,
				"forgot to call Destroy_Program from shader manager! "
				"Program "
				"handle: {}",
				program_handle_id);
		}
	}

	KOTEK_ASSERT(deleted_all_programs,
		"you forget to issue Destroy_Program calling in your renderer "
		"implementation! Not all programs resources are destroyed!!!");
#endif
}

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
