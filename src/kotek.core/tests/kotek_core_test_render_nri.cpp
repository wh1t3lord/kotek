#include "../include/kotek_core.h"

#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

	#include <kotek.core.engine_config/include/kotek_std_config.h>

	#include <gtest/gtest.h>

	// the suite exercises the real third-party API on purpose (functional
	// proofs, not mocks): device creation and a 3-frame present on a
	// swap chain. NRI headers come from the pinned clone in
	// kotek/external/nri (task K11); the tests-only link edge to the NRI
	// target is declared in this module's CMakeLists. The geometry
	// handle-table proof (K11 phase 3) includes the module's table header
	// directly — it is deliberately free of NRI types, so no extra link
	// edge is needed
	#include <NRI.h>
	#include <Extensions/NRIDeviceCreation.h>
	#include <Extensions/NRISwapChain.h>

	#include <kotek.render.nri/include/kotek_render_geometry_handle_table.h>

	// the present test binds the swap chain to its own hidden window —
	// never to the engine's HWND (a flip-model swap chain is 1-per-window,
	// and the active backend already owns that one)
	#include <windows.h>

#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

namespace
{
	/// \~english shared GPU gate: SKIP (not fail) when no D3D12 adapter
	/// exists, so CI machines without a GPU stay green
	bool nri_probe_has_d3d12_adapter(void)
	{
		kun_ktk uint32_t adapter_count = 0;
		const nri::Result result =
			nri::nriEnumerateAdapters(nullptr, adapter_count);

		return result == nri::Result::SUCCESS && adapter_count > 0;
	}

	nri::Device* nri_create_test_device(void)
	{
		nri::DeviceCreationDesc device_desc{};
		device_desc.graphicsAPI = nri::GraphicsAPI::D3D12;
		device_desc.enableNRIValidation = true;

		nri::Device* p_device = nullptr;
		const nri::Result result = nri::nriCreateDevice(device_desc, p_device);

		return result == nri::Result::SUCCESS ? p_device : nullptr;
	}

	// (b) parse-level proof: --render_nri_dx12 maps onto the DirectX
	// feature slot (no GPU needed)
	TEST(KotekRenderNRI, CommandLineFlagSelectsDirectXSlot)
	{
		ktkFrameworkConfig config;
		config.Initialize();

		char arg_executable[] = "kotek.exe";
		char arg_flag[] = "--render_nri_dx12";
		char* p_arguments[] = {arg_executable, arg_flag};

		config.SetARGC(2);
		config.SetARGV(p_arguments);

		EXPECT_TRUE(config.IsFeatureEnabled(eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_SpecifiedByUser));
		EXPECT_EQ(config.GetRendererVersionEnum(),
			eEngineSupportedRenderer::kDirectX_Latest);
		EXPECT_TRUE(config.IsUserSpecifiedValidRenderer());

		config.Shutdown();
	}

	// (b) negative control: without the flag no DirectX feature is
	// enabled by the parser, so the startup default keeps bgfx
	TEST(KotekRenderNRI, NoFlagLeavesDirectXSlotUntouched)
	{
		ktkFrameworkConfig config;
		config.Initialize();

		char arg_executable[] = "kotek.exe";
		char* p_arguments[] = {arg_executable};

		config.SetARGC(1);
		config.SetARGV(p_arguments);

		EXPECT_FALSE(config.IsFeatureEnabled(eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_SpecifiedByUser));
		EXPECT_FALSE(config.IsFeatureEnabled(eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_Latest));

		config.Shutdown();
	}

	// the geometry seam's handle table (task K11 phase 3 / zircon Z24
	// B3b): pure bookkeeping proofs — no GPU. The table lives in the NRI
	// module but is deliberately free of NRI types, so the handle
	// semantics (generation-tagged indices, the stale/foreign guards, the
	// capacity + upload-range contracts) are provable headlessly. The
	// device-level half of the seam (real create/upload/destroy against
	// the D3D12 device) is the NRI boot's job: the zircon meshlet pass
	// creates its buffers/pipeline through this exact manager and the
	// boot exits 0 only when the whole frame ran.
	TEST(KotekRenderNRI, GeometryHandleTableBookkeeping)
	{
		using table_t = Render::nri::ktkRenderGeometryHandleTable<4>;

		table_t table;

		// fresh handles: distinct, index-ordered, live
		const kun_ktk uint32_t first =
			table.allocate(reinterpret_cast<void*>(0x1),
				reinterpret_cast<void*>(0x2), 256);
		const kun_ktk uint32_t second =
			table.allocate(reinterpret_cast<void*>(0x3),
				reinterpret_cast<void*>(0x4), 512);

		EXPECT_NE(first, 0u);
		EXPECT_NE(second, 0u);
		EXPECT_NE(first, second);
		EXPECT_EQ(table.get_live_count(), 2u);
		EXPECT_TRUE(table.is_range_valid(first, 0, 256));
		EXPECT_TRUE(table.is_range_valid(first, 128, 128));
		EXPECT_FALSE(table.is_range_valid(first, 128, 129));
		EXPECT_FALSE(table.is_range_valid(first, 257, 0));

		// the zero handle and the out-of-range sentinel never resolve
		EXPECT_EQ(table.resolve(0u), nullptr);
		EXPECT_EQ(table.resolve(0xFFFFFFFFu), nullptr);

		// free makes the handle stale: the slot is gone and a re-create
		// gets the same index under a NEW generation (the stale copy is
		// rejected, not silently re-bound)
		EXPECT_TRUE(table.free(first));

		EXPECT_EQ(table.resolve(first), nullptr);
		EXPECT_EQ(table.get_live_count(), 1u);

		const kun_ktk uint32_t reused =
			table.allocate(reinterpret_cast<void*>(0x5),
				reinterpret_cast<void*>(0x6), 64);

		EXPECT_NE(reused, 0u);
		EXPECT_EQ(reused & 0xFFFFu, first & 0xFFFFu);
		EXPECT_NE(reused, first);
		EXPECT_EQ(table.resolve(first), nullptr);
		EXPECT_NE(table.resolve(reused), nullptr);

		// freeing a stale/foreign handle is a loud no-op, not a crash
		EXPECT_FALSE(table.free(first));
		EXPECT_FALSE(table.free(0xFFFFFFFFu));

		// the capacity contract: the 4th allocation is rejected loudly
		// (the all-zero pattern), the live set stays intact
		EXPECT_NE(table.allocate(nullptr, nullptr, 1), 0u);
		EXPECT_NE(table.allocate(nullptr, nullptr, 1), 0u);
		EXPECT_EQ(table.allocate(nullptr, nullptr, 1), 0u);
		EXPECT_EQ(table.get_live_count(), 4u);

		// the upload-range guard keys off the stored per-slot size
		EXPECT_TRUE(table.is_range_valid(reused, 0, 64));
		EXPECT_FALSE(table.is_range_valid(reused, 0, 65));
	}

	// (a) module lifecycle at the device level: the exact objects the
	// module creates at boot (device -> interfaces -> queue -> command
	// allocator/list -> fence) come up and go down cleanly. The full
	// init->shutdown lifecycle through InitializeModule_Render_NRI is
	// proven by the --render_nri_dx12 boot smoke (exit 0 with no leak
	// asserts beyond the documented residual count)
	TEST(KotekRenderNRI, DeviceLifecycle)
	{
		if (!nri_probe_has_d3d12_adapter())
		{
			GTEST_SKIP() << "no D3D12 adapter on this machine";
		}

		nri::Device* p_device = nri_create_test_device();
		if (!p_device)
		{
			GTEST_SKIP() << "nriCreateDevice failed (no usable D3D12 device)";
		}

		nri::CoreInterface core{};
		nri::Result result = nri::nriGetInterface(
			*p_device, "CoreInterface", sizeof(core), &core);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::Queue* p_queue = nullptr;
		result =
			core.GetQueue(*p_device, nri::QueueType::GRAPHICS, 0, p_queue);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::CommandAllocator* p_allocator = nullptr;
		result = core.CreateCommandAllocator(*p_queue, p_allocator);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::CommandBuffer* p_command_buffer = nullptr;
		result = core.CreateCommandBuffer(*p_allocator, p_command_buffer);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::Fence* p_fence = nullptr;
		result = core.CreateFence(*p_device, 0, p_fence);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		core.DestroyCommandBuffer(p_command_buffer);
		core.DestroyCommandAllocator(p_allocator);
		core.DestroyFence(p_fence);
		nri::nriDestroyDevice(p_device);
	}

	// (c) a swap chain presents 3 frames without error. GPU-gated twice:
	// SKIP when no adapter exists, SKIP when the device cannot be created
	TEST(KotekRenderNRI, SwapChainPresentsThreeFrames)
	{
		if (!nri_probe_has_d3d12_adapter())
		{
			GTEST_SKIP() << "no D3D12 adapter on this machine";
		}

		// hidden top-level window owned by the test (see the include
		// comment above for why the engine's HWND is never used)
		HWND p_hwnd = CreateWindowExW(0, L"Static", L"kotek_nri_test",
			WS_OVERLAPPED, 0, 0, 64, 64, nullptr, nullptr,
			GetModuleHandleW(nullptr), nullptr);
		ASSERT_TRUE(p_hwnd != nullptr);

		nri::Device* p_device = nri_create_test_device();
		if (!p_device)
		{
			DestroyWindow(p_hwnd);
			GTEST_SKIP() << "nriCreateDevice failed (no usable D3D12 device)";
		}

		nri::CoreInterface core{};
		nri::Result result = nri::nriGetInterface(
			*p_device, "CoreInterface", sizeof(core), &core);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::SwapChainInterface swapchain_interface{};
		result = nri::nriGetInterface(*p_device, "SwapChainInterface",
			sizeof(swapchain_interface), &swapchain_interface);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::Queue* p_queue = nullptr;
		result =
			core.GetQueue(*p_device, nri::QueueType::GRAPHICS, 0, p_queue);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::CommandAllocator* p_allocator = nullptr;
		result = core.CreateCommandAllocator(*p_queue, p_allocator);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::CommandBuffer* p_command_buffer = nullptr;
		result = core.CreateCommandBuffer(*p_allocator, p_command_buffer);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::Fence* p_frame_fence = nullptr;
		result = core.CreateFence(*p_device, 0, p_frame_fence);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		nri::SwapChainDesc swapchain_desc{};
		swapchain_desc.window.windows.hwnd = p_hwnd;
		swapchain_desc.queue = p_queue;
		swapchain_desc.width = 64;
		swapchain_desc.height = 64;
		swapchain_desc.textureNum = 2;
		swapchain_desc.format = nri::SwapChainFormat::BT709_G22_8BIT;
		swapchain_desc.flags = nri::SwapChainBits::NONE;

		nri::SwapChain* p_swapchain = nullptr;
		result = swapchain_interface.CreateSwapChain(
			*p_device, swapchain_desc, p_swapchain);
		ASSERT_EQ(result, nri::Result::SUCCESS);

		kun_ktk uint32_t texture_count = 0;
		nri::Texture* const* p_textures =
			swapchain_interface.GetSwapChainTextures(
				*p_swapchain, texture_count);
		ASSERT_GE(texture_count, 2u);
		ASSERT_TRUE(p_textures != nullptr);

		constexpr kun_ktk uint32_t k_max_back_buffers = 4;
		ASSERT_LE(texture_count, k_max_back_buffers);

		nri::Descriptor* p_color_views[k_max_back_buffers]{};
		nri::Fence* p_acquire_fences[k_max_back_buffers]{};
		nri::Fence* p_release_fences[k_max_back_buffers]{};

		for (kun_ktk uint32_t i = 0; i < texture_count; ++i)
		{
			nri::TextureViewDesc view_desc{};
			view_desc.texture = p_textures[i];
			view_desc.type = nri::TextureView::COLOR_ATTACHMENT;
			view_desc.format =
				core.GetTextureDesc(*p_textures[i]).format;
			view_desc.mipNum = 1;
			view_desc.layerNum = 1;
			view_desc.sliceNum = 1;

			result = core.CreateTextureView(view_desc, p_color_views[i]);
			ASSERT_EQ(result, nri::Result::SUCCESS);

			result = core.CreateFence(
				*p_device, nri::SWAPCHAIN_SEMAPHORE, p_acquire_fences[i]);
			ASSERT_EQ(result, nri::Result::SUCCESS);

			result = core.CreateFence(
				*p_device, nri::SWAPCHAIN_SEMAPHORE, p_release_fences[i]);
			ASSERT_EQ(result, nri::Result::SUCCESS);
		}

		// the same frame flow the module's ktkRenderSwapchain::Present
		// runs: acquire -> barrier -> clear -> barrier -> submit ->
		// present, frame-fence paced
		for (kun_ktk uint64_t frame_index = 0; frame_index < 3;
		     ++frame_index)
		{
			core.Wait(*p_frame_fence, frame_index >= 1 ? frame_index : 0);
			core.ResetCommandAllocator(*p_allocator);

			nri::Fence* p_acquire_fence =
				p_acquire_fences[frame_index % texture_count];

			kun_ktk uint32_t texture_index = 0;
			result = swapchain_interface.AcquireNextTexture(
				*p_swapchain, *p_acquire_fence, texture_index);
			ASSERT_EQ(result, nri::Result::SUCCESS);
			ASSERT_LT(texture_index, texture_count);

			nri::Fence* p_release_fence = p_release_fences[texture_index];

			result = core.BeginCommandBuffer(*p_command_buffer, nullptr);
			ASSERT_EQ(result, nri::Result::SUCCESS);

			nri::TextureBarrierDesc texture_barrier{};
			texture_barrier.texture = p_textures[texture_index];
			texture_barrier.before.access = nri::AccessBits::NONE;
			texture_barrier.before.layout = nri::Layout::PRESENT;
			texture_barrier.before.stages = nri::StageBits::NONE;
			texture_barrier.after.access =
				nri::AccessBits::COLOR_ATTACHMENT;
			texture_barrier.after.layout = nri::Layout::COLOR_ATTACHMENT;
			texture_barrier.after.stages = nri::StageBits::COLOR_ATTACHMENT;
			texture_barrier.mipNum = 1;
			texture_barrier.layerNum = 1;
			texture_barrier.planes = nri::PlaneBits::ALL;

			nri::BarrierDesc barrier{};
			barrier.textures = &texture_barrier;
			barrier.textureNum = 1;

			core.CmdBarrier(*p_command_buffer, barrier);

			nri::AttachmentDesc color_attachment{};
			color_attachment.descriptor = p_color_views[texture_index];
			color_attachment.loadOp = nri::LoadOp::CLEAR;
			color_attachment.storeOp = nri::StoreOp::STORE;
			color_attachment.clearValue.color.f.x = 0.2f;
			color_attachment.clearValue.color.f.y = 0.3f;
			color_attachment.clearValue.color.f.z = 0.6f;
			color_attachment.clearValue.color.f.w = 1.0f;

			nri::RenderingDesc rendering{};
			rendering.colors = &color_attachment;
			rendering.colorNum = 1;

			core.CmdBeginRendering(*p_command_buffer, rendering);
			core.CmdEndRendering(*p_command_buffer);

			texture_barrier.before.access =
				nri::AccessBits::COLOR_ATTACHMENT;
			texture_barrier.before.layout = nri::Layout::COLOR_ATTACHMENT;
			texture_barrier.before.stages = nri::StageBits::COLOR_ATTACHMENT;
			texture_barrier.after.access = nri::AccessBits::NONE;
			texture_barrier.after.layout = nri::Layout::PRESENT;
			texture_barrier.after.stages = nri::StageBits::NONE;

			core.CmdBarrier(*p_command_buffer, barrier);

			result = core.EndCommandBuffer(*p_command_buffer);
			ASSERT_EQ(result, nri::Result::SUCCESS);

			nri::FenceSubmitDesc wait_fence{};
			wait_fence.fence = p_acquire_fence;
			wait_fence.stages = nri::StageBits::COLOR_ATTACHMENT;

			nri::FenceSubmitDesc signal_fences[2]{};
			signal_fences[0].fence = p_release_fence;
			signal_fences[1].fence = p_frame_fence;
			signal_fences[1].value = 1 + frame_index;

			nri::QueueSubmitDesc submit{};
			submit.waitFences = &wait_fence;
			submit.waitFenceNum = 1;
			submit.commandBuffers = &p_command_buffer;
			submit.commandBufferNum = 1;
			submit.signalFences = signal_fences;
			submit.signalFenceNum = 2;

			result = core.QueueSubmit(*p_queue, submit);
			ASSERT_EQ(result, nri::Result::SUCCESS);

			result = swapchain_interface.QueuePresent(
				*p_swapchain, *p_release_fence);
			ASSERT_EQ(result, nri::Result::SUCCESS);
		}

		core.DeviceWaitIdle(p_device);

		for (kun_ktk uint32_t i = 0; i < texture_count; ++i)
		{
			core.DestroyFence(p_release_fences[i]);
			core.DestroyFence(p_acquire_fences[i]);
			core.DestroyDescriptor(p_color_views[i]);
		}

		swapchain_interface.DestroySwapChain(p_swapchain);
		core.DestroyCommandBuffer(p_command_buffer);
		core.DestroyCommandAllocator(p_allocator);
		core.DestroyFence(p_frame_fence);
		nri::nriDestroyDevice(p_device);

		DestroyWindow(p_hwnd);
	}
} // namespace

#endif

// link anchor (always defined, external linkage on purpose): gtest TUs in a
// static lib are unreferenced archive members, so the linker drops their obj
// and the tests never register. RegisterAllTests in main_core_dll.cpp
// references every registrar, and main_core_dll.obj is always linked, which
// pulls this TU's obj out of kotek.core.lib — the established idiom of this
// module's runtime tests.
void RegisterTests_RenderNRI_ForModule_Core(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
