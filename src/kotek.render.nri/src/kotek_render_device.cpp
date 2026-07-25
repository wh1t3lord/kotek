#include "../include/kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

ktkRenderDevice::ktkRenderDevice(void) : m_width{-1}, m_height{-1} {}

ktkRenderDevice::~ktkRenderDevice(void) {}

void ktkRenderDevice::Initialize(kun_core ktkMainManager* p_main_manager)
{
	KOTEK_ASSERT(this->m_width > 0, "call SetWidth before Initialize");
	KOTEK_ASSERT(this->m_height > 0, "call SetHeight before Initialize");

	kun_core ktkIFrameworkConfig* p_config = p_main_manager->Get_EngineConfig();

	KOTEK_ASSERT(
		p_config, "you must initialize config before calling this method!");

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkWin32OSData* p_platform_data = static_cast<ktkWin32OSData*>(
		p_main_manager->Get_WindowManager()->Get_ActiveWindow()->Get_OSData());
	KOTEK_ASSERT(p_platform_data,
		"window must have valid platform data aka hwnd and etc");

	KOTEK_ASSERT(p_platform_data->hWnd, "HWND is not valid!");

	this->m_p_hwnd = p_platform_data->hWnd;
#else
	#error unknown platform (NRI phase 1 is D3D12-only, task K11)
#endif

	// --vsync (default) / --novsync (task K23), same caching as the bgfx
	// device so the swap chain reads the resolved value from one place
	this->m_vsync_enabled = p_config->Is_VSyncEnabled();

	::nri::DeviceCreationDesc device_desc{};
	device_desc.graphicsAPI = ::nri::GraphicsAPI::D3D12;
	device_desc.callbackInterface.MessageCallback =
		&ktkRenderDevice::On_NRI_Message;
#ifdef KOTEK_DEBUG
	device_desc.enableNRIValidation = true;
	device_desc.enableGraphicsAPIValidation = true;
#endif

	::nri::Result result = ::nri::nriCreateDevice(device_desc, this->m_p_device);

	if (result != ::nri::Result::SUCCESS)
	{
		// no KOTEK_ASSERT here by design: a missing D3D12 adapter is an
		// environment problem, not a code defect — the module entry checks
		// Is_Created() and reports a clean init failure (a GPU-less CI
		// never selects this backend; the gtest suite SKIPs on its own
		// probe)
		KOTEK_MESSAGE_ERROR(
			"[nri] nriCreateDevice(D3D12) failed, result={} — is there a "
			"D3D12-capable adapter?",
			static_cast<int>(result));
		return;
	}

	// NRI C++ API note: NriRef(X) is X& — interface calls dereference the
	// pointers; the interface names must NOT carry the ::nri:: prefix
	// (nriGetInterface strips "nri::" but not "::nri::")
	result = ::nri::nriGetInterface(*this->m_p_device, "CoreInterface",
		sizeof(::nri::CoreInterface), &this->m_core_interface);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] failed to query CoreInterface, result={}",
		static_cast<int>(result));

	result = ::nri::nriGetInterface(*this->m_p_device, "SwapChainInterface",
		sizeof(::nri::SwapChainInterface), &this->m_swapchain_interface);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] failed to query SwapChainInterface, result={}",
		static_cast<int>(result));

	// one GRAPHICS queue is created by default (see DeviceCreationDesc)
	result = this->m_core_interface.GetQueue(
		*this->m_p_device, ::nri::QueueType::GRAPHICS, 0, this->m_p_queue);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] GetQueue(GRAPHICS, 0) failed, result={}",
		static_cast<int>(result));

	result = this->m_core_interface.CreateCommandAllocator(
		*this->m_p_queue, this->m_p_command_allocator);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] CreateCommandAllocator failed, result={}",
		static_cast<int>(result));

	result = this->m_core_interface.CreateCommandBuffer(
		*this->m_p_command_allocator, this->m_p_command_buffer);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] CreateCommandBuffer failed, result={}",
		static_cast<int>(result));

	result = this->m_core_interface.CreateFence(
		*this->m_p_device, 0, this->m_p_frame_fence);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] CreateFence failed, result={}", static_cast<int>(result));

	const ::nri::DeviceDesc& nri_device_desc =
		this->m_core_interface.GetDeviceDesc(*this->m_p_device);

	KOTEK_MESSAGE("[nri] device initialized: {} (NRI v{}, shader model {})",
		nri_device_desc.adapterDesc.name, nri_device_desc.nriVersion,
		nri_device_desc.shaderModel);
}

void ktkRenderDevice::Shutdown(void)
{
	if (this->m_p_device == nullptr)
		return;

	this->GPUFlush();

	if (this->m_p_command_buffer)
	{
		this->m_core_interface.DestroyCommandBuffer(
			this->m_p_command_buffer);
		this->m_p_command_buffer = nullptr;
	}

	if (this->m_p_command_allocator)
	{
		this->m_core_interface.DestroyCommandAllocator(
			this->m_p_command_allocator);
		this->m_p_command_allocator = nullptr;
	}

	if (this->m_p_frame_fence)
	{
		this->m_core_interface.DestroyFence(this->m_p_frame_fence);
		this->m_p_frame_fence = nullptr;
	}

	::nri::nriDestroyDevice(this->m_p_device);
	this->m_p_device = nullptr;
	this->m_p_queue = nullptr;

	KOTEK_MESSAGE("[nri] device shutdown complete");
}

void ktkRenderDevice::Resize(kun_core ktkIRenderSwapchain* p_raw_swapchain,
	kun_core ktkIRenderer* p_raw_renderer,
	kun_core ktkIRenderResourceManager* p_raw_resource_manager, int width,
	int height)
{
	this->m_width = width;
	this->m_height = height;

	p_raw_swapchain->Resize(this, width, height, this->m_vsync_enabled);
	p_raw_renderer->Resize();
}

int ktkRenderDevice::GetWidth(void) const noexcept
{
	return this->m_width;
}

int ktkRenderDevice::GetHeight(void) const noexcept
{
	return this->m_height;
}

void ktkRenderDevice::GPUFlush()
{
	if (this->m_p_device)
		this->m_core_interface.DeviceWaitIdle(this->m_p_device);
}

void ktkRenderDevice::SetWidth(int width) noexcept
{
	this->m_width = width;
}

void ktkRenderDevice::SetHeight(int height) noexcept
{
	this->m_height = height;
}

bool ktkRenderDevice::Is_Created(void) const noexcept
{
	return this->m_p_device != nullptr;
}

void* ktkRenderDevice::Get_HWND(void) const noexcept
{
	return this->m_p_hwnd;
}

bool ktkRenderDevice::Is_VSyncEnabled(void) const noexcept
{
	return this->m_vsync_enabled;
}

::nri::Device* ktkRenderDevice::Get_Device(void) const noexcept
{
	return this->m_p_device;
}

const ::nri::CoreInterface& ktkRenderDevice::Get_CoreInterface(
	void) const noexcept
{
	return this->m_core_interface;
}

const ::nri::SwapChainInterface& ktkRenderDevice::Get_SwapChainInterface(
	void) const noexcept
{
	return this->m_swapchain_interface;
}

::nri::Queue* ktkRenderDevice::Get_Queue(void) const noexcept
{
	return this->m_p_queue;
}

::nri::CommandAllocator* ktkRenderDevice::Get_CommandAllocator(
	void) const noexcept
{
	return this->m_p_command_allocator;
}

::nri::CommandBuffer* ktkRenderDevice::Get_CommandBuffer(void) const noexcept
{
	return this->m_p_command_buffer;
}

::nri::Fence* ktkRenderDevice::Get_FrameFence(void) const noexcept
{
	return this->m_p_frame_fence;
}

void NRI_CALL ktkRenderDevice::On_NRI_Message(::nri::Message message_type,
	const char* p_file, uint32_t line, const char* p_message,
	void* p_user_arg)
{
	switch (message_type)
	{
	case ::nri::Message::INFO:
	{
		KOTEK_MESSAGE("[nri] {}", p_message);
		break;
	}
	case ::nri::Message::WARNING:
	{
		KOTEK_MESSAGE_WARNING("[nri] {} ({}:{})", p_message, p_file, line);
		break;
	}
	case ::nri::Message::ERROR:
	default:
	{
		KOTEK_MESSAGE_ERROR("[nri] {} ({}:{})", p_message, p_file, line);
		break;
	}
	}
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
