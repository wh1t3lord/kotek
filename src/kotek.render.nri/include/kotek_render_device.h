#pragma once

/// \file kotek_render_device.h
/// \~english NRI render device (task K11, phase 1: D3D12). Wraps
/// nri::Device, its core/swap-chain interfaces, the graphics queue and the
/// single command allocator/list of the milestone. Module-internal header:
/// NRI types must never leak into interfaces or other modules (the
/// module-boundary rule — every NRI object is created and destroyed only
/// inside kotek.render.nri).
///
/// NOTE: this module lives in namespace Kotek::Render::nri which collides
/// with the global ::nri of the NRI library — every NVIDIA type is spelled
/// ::nri::X on purpose (the same discipline the bgfx module uses for
/// ::bgfx::X).

#include <NRI.h>
#include <Extensions/NRIDeviceCreation.h>
#include <Extensions/NRISwapChain.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

class ktkRenderDevice : public Core::ktkIRenderDevice
{
public:
	ktkRenderDevice(void);
	~ktkRenderDevice(void);

	void Initialize(Core::ktkMainManager* main_manager) override;
	void Shutdown(void) override;
	void Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
		Core::ktkIRenderer* p_raw_renderer,
		Core::ktkIRenderResourceManager* p_raw_resource_manager, int width,
		int height) override;
	int GetWidth(void) const noexcept override;
	int GetHeight(void) const noexcept override;
	void GPUFlush(void) override;

	void SetWidth(int width) noexcept;
	void SetHeight(int height) noexcept;

	/// \~english false when nriCreateDevice failed (no D3D12 adapter,
	/// sdk mismatch...) — the module entry reports init failure then
	/// instead of running on a null device
	bool Is_Created(void) const noexcept;

	void* Get_HWND(void) const noexcept;
	bool Is_VSyncEnabled(void) const noexcept;
	::nri::Device* Get_Device(void) const noexcept;
	const ::nri::CoreInterface& Get_CoreInterface(void) const noexcept;
	const ::nri::SwapChainInterface& Get_SwapChainInterface(
		void) const noexcept;
	::nri::Queue* Get_Queue(void) const noexcept;
	::nri::CommandAllocator* Get_CommandAllocator(void) const noexcept;
	::nri::CommandBuffer* Get_CommandBuffer(void) const noexcept;
	::nri::Fence* Get_FrameFence(void) const noexcept;

private:
	/// \~english routes NRI diagnostics into the engine logger; no
	/// AbortExecution is installed on purpose — a validation complaint
	/// must stay a log line, never a modal dialog or an abort (CI rule)
	static void NRI_CALL On_NRI_Message(::nri::Message message_type,
		const char* p_file, uint32_t line, const char* p_message,
		void* p_user_arg);

private:
	::nri::CoreInterface m_core_interface{};
	::nri::SwapChainInterface m_swapchain_interface{};
	::nri::Device* m_p_device{};
	::nri::Queue* m_p_queue{};
	::nri::CommandAllocator* m_p_command_allocator{};
	::nri::CommandBuffer* m_p_command_buffer{};
	::nri::Fence* m_p_frame_fence{};
	void* m_p_hwnd{};
	int m_width;
	int m_height;
	bool m_vsync_enabled{true};
};

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
