#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include "../include/kotek_input.h"
#include <gtest/gtest.h>

/// \file kotek_core_test_input_winapi.cpp
/// \~english functional proofs of the WINAPI input backend (task K17
/// phase 2): the VK->GLFW translation and the press/release/repeat state
/// machine are exercised through the real Update_Controller path — the
/// assertions on Is_KeyPressed/Is_KeyReleased ARE the translation check
/// (a wrong VK mapping registers the wrong eInputAllKeys and fails here).

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

namespace
{
	ktkInputPlatformBackendArgs_WINAPI make_keyboard_args(
		int vk, int action, int mods = 0)
	{
		ktkInputPlatformBackendArgs_WINAPI args{};
		args.controller = eInputControllerType::kControllerKeyboard;
		args.key = vk;
		args.scancode = 0;
		args.action = action;
		args.mods = mods;
		return args;
	}

	ktkInputPlatformBackendArgs_WINAPI make_mouse_args(
		int button, int action)
	{
		ktkInputPlatformBackendArgs_WINAPI args{};
		args.controller = eInputControllerType::kControllerMouse;
		args.key = button;
		args.scancode = -1;
		args.action = action;
		args.mods = 0;
		return args;
	}
} // namespace

// an ASCII letter: VK 'A' (0x41) must register as kCK_KEY_A — proves the
// pass-through range of the translator end to end
TEST(InputWinApi, LetterPressRelease)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_WINAPI);

	auto args = make_keyboard_args(0x41, 1); // VK 'A', press
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));
	EXPECT_FALSE(input.Is_KeyReleased(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));

	args.action = 0; // release (copy-assignment is deleted by the const
	// backend member — mutate like the sibling test does)
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyReleased(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));

	input.Shutdown();
}

// a special key outside the ASCII range: VK_F1 (0x70) -> GLFW_KEY_F1 ->
// kCK_KEY_F1 — proves the function-key range rule
TEST(InputWinApi, FunctionKeyRegisters)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_WINAPI);

	auto args = make_keyboard_args(0x70, 1); // VK_F1
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_F1));
	EXPECT_FALSE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_F10));

	input.Shutdown();
}

// escape: VK_ESCAPE (0x1B) -> GLFW_KEY_ESCAPE -> kCK_KEY_ESCAPE — proves
// the hand-mapped special range
TEST(InputWinApi, EscapeRegisters)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_WINAPI);

	auto args = make_keyboard_args(0x1B, 1);
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard,
		eInputAllKeys::kCK_KEY_ESCAPE));

	input.Shutdown();
}

// an unmappable VK (VK_SEPARATOR, 0x6C — no glfw counterpart) must be
// ignored, never crash and never corrupt the state of real keys
TEST(InputWinApi, UnmappableKeyIsIgnored)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_WINAPI);

	auto args = make_keyboard_args(0x6C, 1); // VK_SEPARATOR
	input.Update_Controller(&args);

	EXPECT_FALSE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));

	args.key = 0x41; // VK 'A', press (mutation: copy-assignment is
	args.action = 1;   // deleted by the const backend member)
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));

	input.Shutdown();
}

// the engine's tick model: a first press is a single-shot "pressed"
// (ticks=1), an auto-repeat promotes the key to "holding" (ticks=max) —
// so after a repeat Is_KeyPressed is false and Is_KeyHolding is true
TEST(InputWinApi, AutoRepeatPromotesToHolding)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_WINAPI);

	auto args = make_keyboard_args(0x41, 1);
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));

	args.action = 2; // auto-repeat (mutation: copy-assignment is deleted
	// by the const backend member)
	input.Update_Controller(&args);

	EXPECT_FALSE(input.Is_KeyPressed(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A));
	EXPECT_TRUE(input.Is_KeyHolding(
		eInputControllerType::kControllerKeyboard, eInputAllKeys::kCK_KEY_A,
		16));

	input.Shutdown();
}

// mouse: win32 button codes match glfw's — left(0) -> kCM_KEY_LEFT
TEST(InputWinApi, MouseButtonRegisters)
{
	ktkInput input;
	input.Initialize(eInputPlatformBackend::kPlatformBackend_WINAPI);

	auto args = make_mouse_args(0, 1); // left button down
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyPressed(
		eInputControllerType::kControllerMouse, eInputAllKeys::kCM_KEY_LEFT));

	args.action = 0; // left button up (mutation: copy-assignment is
	// deleted by the const backend member)
	input.Update_Controller(&args);

	EXPECT_TRUE(input.Is_KeyReleased(
		eInputControllerType::kControllerMouse, eInputAllKeys::kCM_KEY_LEFT));

	input.Shutdown();
}

	#endif
#endif

// link anchor (always defined, external linkage on purpose): gtest TUs in a
// static lib are unreferenced archive members, so the linker drops their obj
// and the tests never register — RegisterAllTests in main_core_dll.cpp
// references every registrar, which pulls this TU's obj out of the archive
void RegisterTests_InputWinApi_ForModule_Core(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
