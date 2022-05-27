#pragma once

#include <boost/lexical_cast.hpp>

namespace Kotek
{
	namespace ktk
	{
		template <typename T, typename S>
		T lexical_cast(const S& args)
		{
			return boost::lexical_cast<T, S>(args);
		}
	} // namespace ktk
} // namespace Kotek
