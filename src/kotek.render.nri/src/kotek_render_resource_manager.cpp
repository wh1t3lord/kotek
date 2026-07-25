#include "../include/kotek_render_resource_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

ktkRenderResourceManager::ktkRenderResourceManager(
	kun_core ktkIRenderDevice* p_device, kun_core ktkMainManager* p_manager) :
	m_p_render_device(p_device),
	m_p_render_swapchain(nullptr),
	m_p_main_manager(p_manager)
{
}

ktkRenderResourceManager::~ktkRenderResourceManager(void) {}

void ktkRenderResourceManager::Initialize(
	kun_core ktkIRenderDevice* p_raw_device,
	kun_core ktkIRenderSwapchain* p_raw_swapchain, ktk::size_t memory_size)
{
	KOTEK_ASSERT(p_raw_device,
		"you must pass a valid render device to the NRI resource manager");

	this->m_p_render_device = p_raw_device;
	this->m_p_render_swapchain = p_raw_swapchain;

	// phase 1 (task K11): nothing to allocate yet — device + swap chain +
	// clear color is the milestone; buffers/textures/pipelines land with
	// the passes split (Z5)
	KOTEK_MESSAGE(
		"[nri] resource manager initialized (no uploads in phase 1)");
}

void ktkRenderResourceManager::Shutdown(
	kun_core ktkIRenderDevice* p_raw_device)
{
	this->m_p_render_device = nullptr;
	this->m_p_render_swapchain = nullptr;
}

void ktkRenderResourceManager::Resize(
	kun_core ktkIRenderDevice* p_raw_device,
	kun_core ktkIRenderSwapchain* p_raw_swapchain)
{
}

bool ktkRenderResourceManager::Load_Geometry(
	const ktk_filesystem_path& path_to_file, float* p_vertecies,
	kun_ktk size_t vertecies_count, float* p_uv, kun_ktk size_t uv_count)
{
	// a warning, not an assert: loading content on the NRI backend must
	// degrade, never abort the process (task K11 phase 1)
	KOTEK_MESSAGE_WARNING(
		"[nri] Load_Geometry is not implemented in phase 1 (file ignored)");
	return false;
}

bool ktkRenderResourceManager::Load_Geometry(
	const ktk_filesystem_path& path_to_file, unsigned char* p_vertecies,
	kun_ktk size_t vertecies_raw_size, unsigned char* p_uv,
	kun_ktk size_t uv_raw_size)
{
	KOTEK_MESSAGE_WARNING(
		"[nri] Load_Geometry is not implemented in phase 1 (file ignored)");
	return false;
}

kun_render ktkRenderStats* ktkRenderResourceManager::Get_Statistic(
	kun_core eRenderStatistics type) noexcept
{
	return nullptr;
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
