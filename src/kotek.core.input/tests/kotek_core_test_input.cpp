#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include "../include/kotek_input.h"
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
TEST(Input, InitializationAndShutdown)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_GLFW3);
	input.Shutdown();
}

TEST(Input, CheckDevices)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_GLFW3);

	unsigned char devices[eInputControllerType::kControllerTotalAmountOfEnum];

	input.Get_SupportedControllers(devices, sizeof(devices));

	input.Shutdown();
}

TEST(Input, SingleShotUpdate_GLFW3) 
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_GLFW3);
	ktkInputPlatformBackendArgs_GLFW3 args;
	args.controller = eInputControllerType::kControllerKeyboard;
	args.action = 0;
	args.key = 0;
	input.Update_Controller(&args);

	input.Shutdown();
}

// the exe-side window-callback contract (task K26): kotek.core.window.glfw
// installs GLFW callbacks on ITS (the only initialized) GLFW copy and feeds
// the input manager exactly as exercised here — key and mouse-button events
// through Update_Controller with ktkInputPlatformBackendArgs_GLFW3, cursor
// moves through the prev/current Set_ControllerData dance +
// Set_ControllerUpdate with Update() computing the deltas. This pins the
// contract headlessly; the real window path is the owner's interactive
// check.
TEST(Input, WindowCallbackFeedingContract_GLFW3)
{
	ktkInput input;

	// the exe-side guard: forwarding happens only when the manager is
	// initialized for GLFW3
	EXPECT_EQ(input.Get_PlatformBackend(),
		eInputPlatformBackend::kPlatformBackend_Unknown);

	input.Initialize(eInputPlatformBackend::kPlatformBackend_GLFW3);

	EXPECT_EQ(input.Get_PlatformBackend(),
		eInputPlatformBackend::kPlatformBackend_GLFW3);

	// key event: GLFW_KEY_W (87) press -> kCK_KEY_W
	ktkInputPlatformBackendArgs_GLFW3 args_key;
	args_key.controller = eInputControllerType::kControllerKeyboard;
	args_key.key = 87;
	args_key.action = 1; // GLFW_PRESS
	args_key.scancode = 0;
	args_key.mods = 0;
	input.Update_Controller(&args_key);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_W));

	// mouse-button event: GLFW_MOUSE_BUTTON_RIGHT (1) press -> kCM_KEY_RIGHT
	ktkInputPlatformBackendArgs_GLFW3 args_button;
	args_button.controller = eInputControllerType::kControllerMouse;
	args_button.key = 1;
	args_button.action = 1; // GLFW_PRESS
	args_button.scancode = -1;
	args_button.mods = 0;
	input.Update_Controller(&args_button);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerMouse, eInputAllKeys::kCM_KEY_RIGHT));

	// cursor move (the callback's prev/current dance): initial move from
	// (0,0) to (100,50), then Update() publishes the deltas
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMousePreviousCoordinateXInPixels,
		input.Get_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateXInPixels));
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMousePreviousCoordinateYInPixels,
		input.Get_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateYInPixels));
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMouseCoordinateXInPixels, 100.0f);
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMouseCoordinateYInPixels, 50.0f);
	input.Set_ControllerUpdate(eInputControllerType::kControllerMouse);

	input.Update();

	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::kMouseDeltaX),
		100.0f);
	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::kMouseDeltaY),
		50.0f);

	// second move (100,50) -> (130,90): prev must track the old current,
	// deltas follow
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMousePreviousCoordinateXInPixels,
		input.Get_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateXInPixels));
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMousePreviousCoordinateYInPixels,
		input.Get_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateYInPixels));
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMouseCoordinateXInPixels, 130.0f);
	input.Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMouseCoordinateYInPixels, 90.0f);
	input.Set_ControllerUpdate(eInputControllerType::kControllerMouse);

	input.Update();

	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::
							kMousePreviousCoordinateXInPixels),
		100.0f);
	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::
							kMousePreviousCoordinateYInPixels),
		50.0f);
	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::kMouseDeltaX),
		30.0f);
	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::kMouseDeltaY),
		40.0f);

	// a frame without a move event zeroes the deltas (the per-frame
	// contract the editor camera driver relies on)
	input.Update();

	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::kMouseDeltaX),
		0.0f);
	EXPECT_FLOAT_EQ(input.Get_ControllerData(
						eInputControllerType::kControllerMouse,
						eInputControllerMouseData::kMouseDeltaY),
		0.0f);

	input.Shutdown();
}

	#endif
#endif

void RegisterTests_Input_ForModule_Core(void)
{
#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

	#endif
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK