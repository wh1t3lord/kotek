#include "../include/kotek_render_swapchain.h"
#include "../include/kotek_render_frame_pass_context.h"

/// \~english the milestone clear color (task K11 phase 1): RGB(0.2, 0.3, 0.6)
#define KOTEK_DEF_RENDER_NRI_CLEAR_COLOR_R 0.2f
#define KOTEK_DEF_RENDER_NRI_CLEAR_COLOR_G 0.3f
#define KOTEK_DEF_RENDER_NRI_CLEAR_COLOR_B 0.6f

/// \~english the joined pass-name list of the one-time pass-drive evidence
/// log line: 8 passes of ~60-char registered names + separators fit in 512
/// with headroom — raise when the NRI registry legitimately grows past it
#define KOTEK_DEF_RENDER_NRI_PASS_LOG_NAMES_MAX_LENGTH 512

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_NRI

ktkRenderSwapchain::ktkRenderSwapchain(void) {}

ktkRenderSwapchain::~ktkRenderSwapchain(void) {}

void ktkRenderSwapchain::Initialize(Core::ktkIRenderDevice* p_render_device)
{
	ktkRenderDevice* p_device =
		dynamic_cast<ktkRenderDevice*>(p_render_device);

	KOTEK_ASSERT(p_device,
		"swapchain of the NRI backend must be initialized with "
		"nri::ktkRenderDevice");

	this->Create_SwapChain(p_device, p_device->GetWidth(),
		p_device->GetHeight(), p_device->Is_VSyncEnabled());
}

void ktkRenderSwapchain::Shutdown(Core::ktkIRenderDevice* p_render_device)
{
	ktkRenderDevice* p_device =
		dynamic_cast<ktkRenderDevice*>(p_render_device);

	KOTEK_ASSERT(p_device,
		"swapchain of the NRI backend must be shutdown with "
		"nri::ktkRenderDevice");

	// the device is still alive at this point (module shutdown order:
	// swapchain -> resource manager -> device) but nothing may be in
	// flight while we destroy the swap chain
	p_device->GPUFlush();

	this->Destroy_SwapChain(p_device);
}

void ktkRenderSwapchain::Resize(Core::ktkIRenderDevice* p_render_device,
	int width, int height, bool vsync)
{
	ktkRenderDevice* p_device =
		dynamic_cast<ktkRenderDevice*>(p_render_device);

	KOTEK_ASSERT(p_device,
		"swapchain of the NRI backend must be resized with "
		"nri::ktkRenderDevice");

	if (this->m_p_swapchain == nullptr)
		return;

	// NRI has no in-place swap chain resize: recreate (the GPU must be
	// idle before the old swap chain is destroyed)
	p_device->GPUFlush();
	this->Destroy_SwapChain(p_device);
	this->Create_SwapChain(p_device, width, height, vsync);
}

void ktkRenderSwapchain::Present(Core::ktkMainManager* p_main_manager,
	Core::ktkIRenderDevice* p_render_device)
{
	if (this->m_p_swapchain == nullptr)
		return;

	ktkRenderDevice* p_device =
		dynamic_cast<ktkRenderDevice*>(p_render_device);

	KOTEK_ASSERT(p_device,
		"swapchain of the NRI backend must present with "
		"nri::ktkRenderDevice");

	// the built-in frame: the milestone clear recorded through the same
	// pass context the pass-driven path uses — one recording path for
	// both entry points
	frame_acquire_t acquire;

	if (!this->Begin_Frame(p_device, acquire))
		return;

	ktkRenderFramePassContext context(
		p_device, this->m_p_color_views[acquire.texture_index]);

	context.ClearColor(KOTEK_DEF_RENDER_NRI_CLEAR_COLOR_R,
		KOTEK_DEF_RENDER_NRI_CLEAR_COLOR_G, KOTEK_DEF_RENDER_NRI_CLEAR_COLOR_B,
		1.0f);

	this->End_Frame(p_device, acquire);
}

void ktkRenderSwapchain::Present_With_Passes(
	Core::ktkMainManager* p_main_manager,
	Core::ktkIRenderDevice* p_render_device,
	Core::ktkIRenderFramePass* const* pp_passes,
	kun_ktk uint32_t pass_count)
{
	// no passes installed = the built-in frame (the interface contract)
	if ((pp_passes == nullptr) || (pass_count == 0))
	{
		this->Present(p_main_manager, p_render_device);
		return;
	}

	if (this->m_p_swapchain == nullptr)
		return;

	ktkRenderDevice* p_device =
		dynamic_cast<ktkRenderDevice*>(p_render_device);

	KOTEK_ASSERT(p_device,
		"swapchain of the NRI backend must present with "
		"nri::ktkRenderDevice");

	frame_acquire_t acquire;

	if (!this->Begin_Frame(p_device, acquire))
		return;

	if (this->m_pass_drive_logged == false)
	{
		// the boot evidence line (zircon Z5 P4 verification): the frame
		// went through the pass path, not the built-in clear
		kun_kotek kun_ktk static_cstring<
			KOTEK_DEF_RENDER_NRI_PASS_LOG_NAMES_MAX_LENGTH>
			names;

		for (kun_ktk uint32_t pass_index = 0; pass_index < pass_count;
			 ++pass_index)
		{
			const Core::ktkIRenderFramePass* p_pass = pp_passes[pass_index];
			const char* p_name =
				p_pass ? p_pass->Get_Name() : nullptr;

			if (pass_index > 0)
				names += ", ";

			names += p_name ? p_name : "<null>";
		}

		KOTEK_MESSAGE("[nri]: frame passes driven: {} ({})", pass_count,
			names.c_str());

		this->m_pass_drive_logged = true;
	}

	ktkRenderFramePassContext context(
		p_device, this->m_p_color_views[acquire.texture_index]);

	for (kun_ktk uint32_t pass_index = 0; pass_index < pass_count;
		 ++pass_index)
	{
		Core::ktkIRenderFramePass* p_pass = pp_passes[pass_index];

		KOTEK_ASSERT(p_pass, "[nri] frame pass {} is null — skipped",
			pass_index);

		if (p_pass)
		{
			p_pass->Record(&context);
		}
	}

	this->End_Frame(p_device, acquire);
}

bool ktkRenderSwapchain::Begin_Frame(ktkRenderDevice* p_device,
	frame_acquire_t& out_acquire) noexcept
{
	const ::nri::CoreInterface& core = p_device->Get_CoreInterface();
	const ::nri::SwapChainInterface& swapchain_interface =
		p_device->Get_SwapChainInterface();

	::nri::Fence* p_frame_fence = p_device->Get_FrameFence();
	::nri::CommandAllocator* p_command_allocator =
		p_device->Get_CommandAllocator();
	::nri::CommandBuffer* p_command_buffer = p_device->Get_CommandBuffer();

	// frame pacing: the single command allocator of phase 1 may only be
	// reset once the GPU finished the submission that used it
	core.Wait(*p_frame_fence,
		this->m_frame_index >= KOTEK_DEF_RENDER_NRI_QUEUED_FRAMES
			? 1 + this->m_frame_index - KOTEK_DEF_RENDER_NRI_QUEUED_FRAMES
			: 0);
	core.ResetCommandAllocator(*p_command_allocator);

	// acquire (on D3D12 the semaphore fences are dummies — the acquire
	// resolves to the runtime's current back buffer index)
	out_acquire.p_acquire_fence =
		this->m_p_acquire_fences[this->m_frame_index %
		KOTEK_DEF_RENDER_NRI_SWAPCHAIN_BACK_BUFFERS];

	::nri::Result result = swapchain_interface.AcquireNextTexture(
		*this->m_p_swapchain, *out_acquire.p_acquire_fence,
		out_acquire.texture_index);

	if (result != ::nri::Result::SUCCESS)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] AcquireNextTexture failed, result={} — frame skipped",
			static_cast<int>(result));
		return false;
	}

	KOTEK_ASSERT(out_acquire.texture_index < this->m_texture_count,
		"[nri] acquired back buffer index {} is out of range (count {})",
		out_acquire.texture_index, this->m_texture_count);

	if (out_acquire.texture_index >= this->m_texture_count)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] acquired back buffer index {} is out of range (count "
			"{}) — frame skipped",
			out_acquire.texture_index, this->m_texture_count);
		return false;
	}

	out_acquire.p_release_fence =
		this->m_p_release_fences[out_acquire.texture_index];

	result = core.BeginCommandBuffer(*p_command_buffer, nullptr);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] BeginCommandBuffer failed, result={}",
		static_cast<int>(result));

	if (result != ::nri::Result::SUCCESS)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] BeginCommandBuffer failed, result={} — frame skipped",
			static_cast<int>(result));
		return false;
	}

	// PRESENT -> COLOR_ATTACHMENT
	::nri::TextureBarrierDesc texture_barrier{};
	texture_barrier.texture = this->m_p_textures[out_acquire.texture_index];
	texture_barrier.before.access = ::nri::AccessBits::NONE;
	texture_barrier.before.layout = ::nri::Layout::PRESENT;
	texture_barrier.before.stages = ::nri::StageBits::NONE;
	texture_barrier.after.access = ::nri::AccessBits::COLOR_ATTACHMENT;
	texture_barrier.after.layout = ::nri::Layout::COLOR_ATTACHMENT;
	texture_barrier.after.stages = ::nri::StageBits::COLOR_ATTACHMENT;
	texture_barrier.mipNum = 1;
	texture_barrier.layerNum = 1;
	texture_barrier.planes = ::nri::PlaneBits::ALL;

	::nri::BarrierDesc barrier{};
	barrier.textures = &texture_barrier;
	barrier.textureNum = 1;

	core.CmdBarrier(*p_command_buffer, barrier);

	return true;
}

void ktkRenderSwapchain::End_Frame(ktkRenderDevice* p_device,
	const frame_acquire_t& acquire) noexcept
{
	const ::nri::CoreInterface& core = p_device->Get_CoreInterface();
	const ::nri::SwapChainInterface& swapchain_interface =
		p_device->Get_SwapChainInterface();

	::nri::CommandBuffer* p_command_buffer = p_device->Get_CommandBuffer();

	// COLOR_ATTACHMENT -> PRESENT
	::nri::TextureBarrierDesc texture_barrier{};
	texture_barrier.texture = this->m_p_textures[acquire.texture_index];
	texture_barrier.before.access = ::nri::AccessBits::COLOR_ATTACHMENT;
	texture_barrier.before.layout = ::nri::Layout::COLOR_ATTACHMENT;
	texture_barrier.before.stages = ::nri::StageBits::COLOR_ATTACHMENT;
	texture_barrier.after.access = ::nri::AccessBits::NONE;
	texture_barrier.after.layout = ::nri::Layout::PRESENT;
	texture_barrier.after.stages = ::nri::StageBits::NONE;
	texture_barrier.mipNum = 1;
	texture_barrier.layerNum = 1;
	texture_barrier.planes = ::nri::PlaneBits::ALL;

	::nri::BarrierDesc barrier{};
	barrier.textures = &texture_barrier;
	barrier.textureNum = 1;

	core.CmdBarrier(*p_command_buffer, barrier);

	::nri::Result result = core.EndCommandBuffer(*p_command_buffer);
	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] EndCommandBuffer failed, result={}",
		static_cast<int>(result));

	if (result != ::nri::Result::SUCCESS)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] EndCommandBuffer failed, result={} — frame skipped",
			static_cast<int>(result));
		return;
	}

	::nri::FenceSubmitDesc wait_fence{};
	wait_fence.fence = acquire.p_acquire_fence;
	wait_fence.stages = ::nri::StageBits::COLOR_ATTACHMENT;

	::nri::FenceSubmitDesc signal_fences[2]{};
	signal_fences[0].fence = acquire.p_release_fence;
	signal_fences[1].fence = p_device->Get_FrameFence();
	signal_fences[1].value = 1 + this->m_frame_index;

	::nri::QueueSubmitDesc submit{};
	submit.waitFences = &wait_fence;
	submit.waitFenceNum = 1;
	submit.commandBuffers = &p_command_buffer;
	submit.commandBufferNum = 1;
	submit.signalFences = signal_fences;
	submit.signalFenceNum = 2;

	result = core.QueueSubmit(*p_device->Get_Queue(), submit);

	if (result != ::nri::Result::SUCCESS)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] QueueSubmit failed, result={} — frame skipped",
			static_cast<int>(result));
		return;
	}

	result = swapchain_interface.QueuePresent(
		*this->m_p_swapchain, *acquire.p_release_fence);

	if (result != ::nri::Result::SUCCESS)
	{
		KOTEK_MESSAGE_ERROR(
			"[nri] QueuePresent failed, result={}", static_cast<int>(result));
		return;
	}

	++this->m_frame_index;
}

void ktkRenderSwapchain::Create_SwapChain(ktkRenderDevice* p_device,
	int width, int height, bool vsync)
{
	KOTEK_ASSERT(width > 0 && height > 0,
		"[nri] swap chain needs a valid size, got {}x{}", width, height);

	::nri::SwapChainDesc swapchain_desc{};
	swapchain_desc.window.windows.hwnd = p_device->Get_HWND();
	swapchain_desc.queue = p_device->Get_Queue();
	swapchain_desc.width = static_cast<::nri::Dim_t>(width);
	swapchain_desc.height = static_cast<::nri::Dim_t>(height);
	swapchain_desc.textureNum =
		KOTEK_DEF_RENDER_NRI_SWAPCHAIN_BACK_BUFFERS;
	swapchain_desc.format = ::nri::SwapChainFormat::BT709_G22_8BIT;
	swapchain_desc.flags =
		vsync ? ::nri::SwapChainBits::VSYNC : ::nri::SwapChainBits::NONE;

	const ::nri::CoreInterface& core = p_device->Get_CoreInterface();
	const ::nri::SwapChainInterface& swapchain_interface =
		p_device->Get_SwapChainInterface();

	::nri::Result result = swapchain_interface.CreateSwapChain(
		*p_device->Get_Device(), swapchain_desc, this->m_p_swapchain);

	KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
		"[nri] CreateSwapChain({}x{}) failed, result={}", width, height,
		static_cast<int>(result));

	if (result != ::nri::Result::SUCCESS)
		return;

	kun_ktk uint32_t texture_count{};
	this->m_p_textures = swapchain_interface.GetSwapChainTextures(
		*this->m_p_swapchain, texture_count);

	KOTEK_ASSERT(
		texture_count <= KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS,
		"[nri] swap chain reports {} back buffers, the capacity is {} — "
		"raise KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS",
		texture_count, KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS);

	this->m_texture_count = static_cast<kun_ktk uint8_t>(texture_count);

	for (kun_ktk uint8_t i = 0; i < this->m_texture_count; ++i)
	{
		::nri::TextureViewDesc view_desc{};
		view_desc.texture = this->m_p_textures[i];
		view_desc.type = ::nri::TextureView::COLOR_ATTACHMENT;
		view_desc.format =
			core.GetTextureDesc(*this->m_p_textures[i]).format;
		view_desc.mipNum = 1;
		view_desc.layerNum = 1;
		view_desc.sliceNum = 1;

		result =
			core.CreateTextureView(view_desc, this->m_p_color_views[i]);
		KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
			"[nri] CreateTextureView for back buffer {} failed, result={}",
			i, static_cast<int>(result));

		// SWAPCHAIN_SEMAPHORE fences are dummies on D3D12 (no native
		// object) and required by the acquire/present contract
		result = core.CreateFence(*p_device->Get_Device(),
			::nri::SWAPCHAIN_SEMAPHORE, this->m_p_acquire_fences[i]);
		KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
			"[nri] CreateFence(acquire) for back buffer {} failed, "
			"result={}",
			i, static_cast<int>(result));

		result = core.CreateFence(*p_device->Get_Device(),
			::nri::SWAPCHAIN_SEMAPHORE, this->m_p_release_fences[i]);
		KOTEK_ASSERT(result == ::nri::Result::SUCCESS,
			"[nri] CreateFence(release) for back buffer {} failed, "
			"result={}",
			i, static_cast<int>(result));
	}

	this->m_frame_index = 0;

	KOTEK_MESSAGE(
		"[nri] swap chain created: {}x{}, {} back buffers, vsync {}",
		width, height, this->m_texture_count, vsync ? "on" : "off");
}

void ktkRenderSwapchain::Destroy_SwapChain(ktkRenderDevice* p_device)
{
	const ::nri::CoreInterface& core = p_device->Get_CoreInterface();
	const ::nri::SwapChainInterface& swapchain_interface =
		p_device->Get_SwapChainInterface();

	for (kun_ktk uint8_t i = 0;
	     i < KOTEK_DEF_RENDER_NRI_SWAPCHAIN_MAX_BACK_BUFFERS; ++i)
	{
		if (this->m_p_release_fences[i])
		{
			core.DestroyFence(this->m_p_release_fences[i]);
			this->m_p_release_fences[i] = nullptr;
		}

		if (this->m_p_acquire_fences[i])
		{
			core.DestroyFence(this->m_p_acquire_fences[i]);
			this->m_p_acquire_fences[i] = nullptr;
		}

		if (this->m_p_color_views[i])
		{
			core.DestroyDescriptor(this->m_p_color_views[i]);
			this->m_p_color_views[i] = nullptr;
		}
	}

	if (this->m_p_swapchain)
	{
		swapchain_interface.DestroySwapChain(this->m_p_swapchain);
		this->m_p_swapchain = nullptr;
	}

	this->m_p_textures = nullptr;
	this->m_texture_count = 0;
}

KOTEK_END_NAMESPACE_RENDER_NRI
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
