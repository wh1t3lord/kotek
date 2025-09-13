#include "../include/kotek_render_data_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

ktkShaderModule::ktkShaderModule(void) :
	m_shader_type{bgfx::eShaderType::kShaderType_Unknown}
{
}

ktkShaderModule::~ktkShaderModule(void) {}

ktkBufferModule::ktkBufferModule(void) {}

ktkBufferModule::~ktkBufferModule(void) {}

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK