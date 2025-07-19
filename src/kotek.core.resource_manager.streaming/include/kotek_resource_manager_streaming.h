#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.multithreading.condition_variable\include\kotek_core_containers_multithreading_condition_variable.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceStreamingChunk
{
public:
	ktkResourceStreamingChunk() {}
	~ktkResourceStreamingChunk() {}
};

#define KOTEK_DEF_MAX_RESOURCE_STREAMING_REQUESTS 4
#define KOTEK_DEF_MAX_RESOURCE_STREAMING_BUFFERS 2

class ktkResourceStreamingManager
{
	struct Context
	{
		kun_kotek kun_ktk uint8_t
			buffers[KOTEK_DEF_MAX_RESOURCE_STREAMING_BUFFERS]
				   [KOTEK_DEF_RESOURCE_STREAMING_CHUNK_SIZE];

		kun_kotek kun_ktk kun_mt mutex mtx;
		kun_kotek kun_ktk kun_mt condition_variable cv;

		void reset();
	};

public:
	ktkResourceStreamingManager();
	~ktkResourceStreamingManager();

	void Initialize();
	void Shutdown();

private:
	Context m_contextes[KOTEK_DEF_MAX_RESOURCE_STREAMING_REQUESTS];
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK