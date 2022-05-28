#pragma once

#include <atomic>

namespace Kotek
{
	namespace ktk
	{
		namespace mt
		{
			template <typename Type>
			using atomic = std::atomic<Type>;
		} // namespace mt
	}     // namespace ktk
} // namespace Kotek