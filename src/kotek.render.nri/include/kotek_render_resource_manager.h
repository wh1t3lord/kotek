#pragma once

/// \file kotek_render_resource_manager.h
/// \~english NRI render resource manager (task K11). Phase 1 is a
/// placeholder that satisfies ktkIRenderResourceManager: no GPU resources
/// are uploaded yet (the milestone is device + swap chain + clear). NRI
/// types appear only in the .cpp when real uploads land.

#include "kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

class ktkRenderResourceManager : public kun_core ktkIRenderResourceManager
{
public:
	ktkRenderResourceManager(kun_core ktkIRenderDevice* p_device,
		kun_core ktkMainManager* p_manager);
	ktkRenderResourceManager(void) = delete;

	~ktkRenderResourceManager(void);

	ktkRenderResourceManager(const ktkRenderResourceManager&) = delete;
	ktkRenderResourceManager&
	operator=(const ktkRenderResourceManager&) = delete;
	ktkRenderResourceManager(ktkRenderResourceManager&&) = delete;
	ktkRenderResourceManager&
	operator=(ktkRenderResourceManager&&) = delete;

	void Initialize(kun_core ktkIRenderDevice* p_raw_device,
		kun_core ktkIRenderSwapchain* p_raw_swapchain,
		ktk::size_t memory_size =
			ktk::kMemoryConvertValueDenominator_Megabytes * 32) override;

	void Shutdown(kun_core ktkIRenderDevice* p_raw_device) override;

	void Resize(kun_core ktkIRenderDevice* p_raw_device,
		kun_core ktkIRenderSwapchain* p_raw_swapchain) override;

	bool Load_Geometry(const ktk_filesystem_path& path_to_file,
		float* p_vertecies, kun_ktk size_t vertecies_count, float* p_uv,
		kun_ktk size_t uv_count) override;
	bool Load_Geometry(const ktk_filesystem_path& path_to_file,
		unsigned char* p_vertecies, kun_ktk size_t vertecies_raw_size,
		unsigned char* p_uv, kun_ktk size_t uv_raw_size) override;

	kun_render ktkRenderStats*
	Get_Statistic(kun_core eRenderStatistics type) noexcept override;

private:
	kun_core ktkIRenderDevice* m_p_render_device;
	kun_core ktkIRenderSwapchain* m_p_render_swapchain;
	kun_core ktkMainManager* m_p_main_manager;
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
