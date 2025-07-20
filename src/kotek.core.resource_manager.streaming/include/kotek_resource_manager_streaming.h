#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.multithreading.condition_variable\include\kotek_core_containers_multithreading_condition_variable.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>
#include <kotek.core.containers.multithreading.thread/include/kotek_core_containers_multithreading_thread.h>

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
#define KOTEK_DEF_MAX_RESOURCE_STREAMING_REQUESTS 16

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

	// starts worker thread
	void Initialize(ktkIFileSystem* p_filesystem);
	void Shutdown();

	ktkResourceLoadResponse Load(const ktkResourceRequest& request);
	ktkResourceLoadResponse Load(const ktk_filesystem_path& path);

	// todo: implement save operation for resource streaming manager
	ktkResourceSaveResponse Save(const ktkResourceRequest& request);

private:
	void Process_Requests();

private:
	ktkIFileSystem* m_p_filesystem;
	Context m_contextes[KOTEK_DEF_MAX_RESOURCE_STREAMING_REQUESTS];
	ktk_queue<ktkResourceRequest, KOTEK_DEF_MAX_RESOURCE_STREAMING_REQUESTS>
		m_queue;
	kun_kotek kun_ktk kun_mt thread m_thread_processing;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK