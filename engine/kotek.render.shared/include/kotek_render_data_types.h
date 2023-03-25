#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkRenderStats
{
public:
	ktkRenderStats(Core::eRenderStatistics type);
	ktkRenderStats();
	~ktkRenderStats();

	Core::eRenderStatistics Get_Type(void) const noexcept;
	void Set_Type(Core::eRenderStatistics type) noexcept;

	// bytes
	ktk::size_t Get_AllocatedMemory(void) const noexcept;
	void Set_AllocatedMemory(ktk::size_t value) noexcept;

	// bytes
	ktk::size_t Get_UsedMemory(void) const noexcept;
	void Set_UsedMemory(ktk::size_t value) noexcept;

	// bytes
	ktk::size_t Get_FreeMemory(void) const noexcept;
	void Set_FreeMemory(ktk::size_t value) noexcept;

private:
	Core::eRenderStatistics m_type;
	ktk::size_t m_allocated_memory;
	ktk::size_t m_used_memory;
	ktk::size_t m_free_memory;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK