#include "../include/kotek_std_alias_casting.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/algorithm/string.hpp>
#endif

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <type_traits>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace cast
{

	bool to_bool(const cstring& str) noexcept
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		if (boost::iequals(str.c_str(), "no") ||
		    boost::iequals(str.c_str(), "false") ||
		    boost::iequals(str.c_str(), "0"))
			return false;
#elif defined(KOTEK_USE_STD_LIBRARY)
		if (str.find("no") != KUN_KOTEK KUN_KTK cstring::npos ||
		    str.find("false") !=
		        KUN_KOTEK KUN_KTK cstring::npos ||
		    str.find("0") != KUN_KOTEK KUN_KTK cstring::npos)
			return false;
#else
#endif

		return true;
	}

} // namespace cast

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
