#pragma once

#include <thread>
#include <atomic>
#include <semaphore>
#include <mutex>
#include <shared_mutex>

namespace Kotek
{
	namespace ktk
	{
		namespace mt
		{
			template<typename Type>
			using atomic = std::atomic<Type>;

			template<typename Mutex>
			using lock_guard = std::lock_guard<Mutex>;

			using mutex = std::mutex;

			using thread = std::thread;
		}
	} // namespace ktk
} // namespace Kotek