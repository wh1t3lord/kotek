#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceStreamingChunk
{
public:
	ktkResourceStreamingChunk() {}
	~ktkResourceStreamingChunk() {}
};

class ktkResourceStreamingManager
{
public:
	ktkResourceStreamingManager();
	~ktkResourceStreamingManager();

	void Initialize();
	void Shutdown();

private:
	unsigned char m_storage[KOTEK_DEF_RESOURCE_STREAMING_CHUNK_SIZE];
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK