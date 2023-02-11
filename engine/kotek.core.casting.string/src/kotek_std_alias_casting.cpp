#include "../include/kotek_std_alias_casting.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <boost/algorithm/string.hpp>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <type_traits>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace cast
{
	bool to_bool(const string& your_logical_string_written_in_text) noexcept
	{
        const char* casted =
            reinterpret_cast<const char*>(your_logical_string_written_in_text.c_str());

#ifdef KOTEK_USE_BOOST_LIBRARY
		if (boost::iequals(casted, "no") || boost::iequals(casted, "false") ||
            boost::iequals(casted, "0"))
			return false;
#else
#endif

		return true;
	}

} // namespace cast

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
