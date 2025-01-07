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
	input.Initialize();
	input.Shutdown();
}

TEST(Input, CheckDevices)
{
	ktkInput input;
	input.Initialize();

	unsigned char devices[eInputControllerType::kControllerTotalAmountOfEnum];

	input.Get_SupportedControllers(devices, sizeof(devices));

	input.Shutdown();
}

TEST(Input, SingleShotUpdate) 
{
	ktkInput input;
	input.Initialize();
	ktkInputPlatformBackendArgs_GLFW3 args;
	args.controller = eInputControllerType::kControllerKeyboard;
	input.Update(&args);

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