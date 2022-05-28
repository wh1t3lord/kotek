#pragma once

#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.array/include/kotek_core_containers_array.h>
#include <kotek.core.containers.deque/include/kotek_core_containers_deque.h>
#include <kotek.core.containers.dll/include/kotek_core_containers_dll.h>
#include <kotek.core.containers.filesystem.path/include/kotek_core_containers_filesystem_path.h>
#include <kotek.core.containers.function/include/kotek_core_containers_function.h>
#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>
#include <kotek.core.containers.io/include/kotek_core_containers_io.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.map/include/kotek_core_containers_map.h>
#include <kotek.core.containers.microsoft/include/kotek_core_containers_microsoft.h>
#include <kotek.core.containers.multithreading/include/kotek_core_containers_multithreading.h>
#include <kotek.core.containers.pair/include/kotek_core_containers_pair.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>
#include <kotek.core.containers.shared_ptr/include/kotek_core_containers_shared_ptr.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.unique_ptr/include/kotek_core_containers_unique_ptr.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.unordered_set/include/kotek_core_containers_unordered_set.h>
#include <kotek.core.containers.variant/include/kotek_core_containers_variant.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Containers(ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers(ktkMainManager* p_manager);
	}
} // namespace Kotek