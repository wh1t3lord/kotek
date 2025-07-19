#include "../include/kotek_resource_manager_streaming.h"
#include <kotek.core.utility/include/kotek_core_utility.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceStreamingManager::ktkResourceStreamingManager() {}

ktkResourceStreamingManager::~ktkResourceStreamingManager()
{
	if (this->m_thread_processing.joinable())
	{
		this->m_thread_processing.join();
	}
}

void ktkResourceStreamingManager::Initialize()
{
	this->m_thread_processing = kun_kotek kun_ktk kun_mt thread(
		&ktkResourceStreamingManager::Process_Requests, this);
}

void ktkResourceStreamingManager::Shutdown() {}

ktkResourceLoadResponse ktkResourceStreamingManager::Load(
	const ktkResourceRequest& request)
{
	return ktkResourceLoadResponse();
}

ktkResourceLoadResponse ktkResourceStreamingManager::Load(
	const ktk_filesystem_path& path)
{
	ktkResourceRequest req(eResourceRequestOperationType::kLoad, path);

	return this->Load(req);
}

ktkResourceSaveResponse ktkResourceStreamingManager::Save(
	const ktkResourceRequest& request)
{
	return ktkResourceSaveResponse();
}

void ktkResourceStreamingManager::Process_Requests()
{
	kun_ktk set_thread_name("streaming processing queue thread");

	while (true)
	{
		if (this->m_queue.empty() == false)
		{
		}
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK