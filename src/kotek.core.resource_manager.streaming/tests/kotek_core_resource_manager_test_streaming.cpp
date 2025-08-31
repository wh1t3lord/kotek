#include "../include/kotek_core_resource_manager_streaming.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.filesystem/include/kotek_core_filesystem.h>
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

TEST(Core, resource_streaming_initialize)
{
	ktkFileSystem fs;

	ktkResourceStreamingManager manager;

	fs.Initialize();

	manager.Initialize(&fs);
	manager.Shutdown();

	fs.Shutdown();
}

TEST(Core, resource_streaming_loading) 
{
	ktkFileSystem fs;

	ktkResourceStreamingManager manager;
	
	fs.Initialize();

	manager.Initialize(&fs);
	manager.Shutdown();

	fs.Shutdown();
}

	#endif
#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK