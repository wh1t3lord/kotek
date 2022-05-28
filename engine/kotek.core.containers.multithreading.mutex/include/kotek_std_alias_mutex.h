#pragma once

#include <mutex>

namespace Kotek
{
	namespace ktk
	{
		namespace mt
		{
			using mutex = std::mutex;

			template <typename Mutex>
			using lock_guard = std::lock_guard<Mutex>;
		} // namespace mt
	}     // namespace ktk
} // namespace Kotek