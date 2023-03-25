#include "../include/kotek_render_data_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkRenderStats::ktkRenderStats(Core::eRenderStatistics type) :
	m_type{type}, m_allocated_memory{}, m_used_memory{}, m_free_memory{}
{
}

ktkRenderStats::ktkRenderStats() :
	m_type{Core::eRenderStatistics::kStat_Unknown}, m_allocated_memory{},
	m_used_memory{}, m_free_memory{}
{
}

ktkRenderStats::~ktkRenderStats() {}

Core::eRenderStatistics ktkRenderStats::Get_Type(void) const noexcept
{
	return this->m_type;
}

void ktkRenderStats::Set_Type(Core::eRenderStatistics type) noexcept
{
	this->m_type = type;
}

ktk::size_t ktkRenderStats::Get_AllocatedMemory(void) const noexcept
{
	return this->m_allocated_memory;
}
void ktkRenderStats::Set_AllocatedMemory(ktk::size_t value) noexcept
{
	this->m_allocated_memory = value;
}

ktk::size_t ktkRenderStats::Get_UsedMemory(void) const noexcept
{
	return this->m_used_memory;
}
void ktkRenderStats::Set_UsedMemory(ktk::size_t value) noexcept
{
	this->m_used_memory = value;
}

ktk::size_t ktkRenderStats::Get_FreeMemory(void) const noexcept
{
	return this->m_free_memory;
}
void ktkRenderStats::Set_FreeMemory(ktk::size_t value) noexcept
{
	this->m_free_memory = value;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK