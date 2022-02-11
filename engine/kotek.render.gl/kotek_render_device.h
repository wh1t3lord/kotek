#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderDevice : public Core::ktkIRenderDevice
			{
			public:
				ktkRenderDevice(void);
				~ktkRenderDevice(void);

				void Initialize(Core::ktkMainManager& main_manager) override;
				void Shutdown(void) override;
				void Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
					Core::kotek_i_renderer* p_raw_renderer,
					Core::ktkIRenderResourceManager* p_raw_resource_manager,
					int width, int height) override;
				int GetWidth(void) const noexcept override;
				int GetHeight(void) const noexcept override;
				void GPUFlush(void) override;

				void SetWidth(int width) noexcept;
				void SetHeight(int height) noexcept;

			private:
				int m_width;
				int m_height;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek
