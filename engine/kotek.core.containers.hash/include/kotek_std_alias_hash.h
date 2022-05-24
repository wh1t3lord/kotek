#pragma once

#include <boost/container_hash/extensions.hpp>

namespace Kotek
{
	namespace ktk
	{
		template <typename T>
		using hash = boost::hash<T>;
	}
} // namespace Kotek