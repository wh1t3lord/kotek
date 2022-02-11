#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderResourceManager
				: public Core::ktkIRenderResourceManager
			{
			public:
				ktkRenderResourceManager(void);
				~ktkRenderResourceManager(void);

				ktkRenderResourceManager(
					const ktkRenderResourceManager&) = delete;
				ktkRenderResourceManager& operator=(
					const ktkRenderResourceManager&) = delete;
				ktkRenderResourceManager(ktkRenderResourceManager&&) = delete;
				ktkRenderResourceManager& operator=(
					ktkRenderResourceManager&&) = delete;

				void initialize(Core::ktkIRenderDevice* p_raw_device,
					Core::ktkIRenderSwapchain* p_raw_swapchain) override;

				void shutdown(Core::ktkIRenderDevice* p_raw_device) override;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek