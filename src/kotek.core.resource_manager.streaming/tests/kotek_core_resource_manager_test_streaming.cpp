#include "../include/kotek_core_resource_manager_streaming.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

TEST(Core, resource_streaming_initialize)
{
	ktkResourceStreamingManager manager;

	manager.Initialize();
	manager.Shutdown();
}

TEST(Core, resource_streaming_loading) 
{
	ktkResourceStreamingManager manager;
	manager.Initialize();
	manager.Shutdown();
}

	#endif
#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK