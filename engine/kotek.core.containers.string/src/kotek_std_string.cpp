#include "../include/kotek_std_string.h"

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>

#include <utf8cpp/utf8.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/algorithm/string.hpp>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

std::size_t hash_value(const ktk::ustring& instance)
{
	ktk::hash<ktk::ustring> result;
	return result(instance);
}

void to_lower(cstring& str)
{
	#ifdef KOTEK_USE_BOOST_LIBRARY
	boost::algorithm::to_lower(str);
	#elif defined(KOTEK_USE_STD_LIBRARY)
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return std::tolower(c); });
	#else
	// your custom implementation
	#endif
}

cstring to_lower(const cstring& str)
{
	#ifdef KOTEK_USE_BOOST_LIBRARY
	return boost::algorithm::to_lower_copy(str);
	#elif defined(KOTEK_USE_STD_LIBRARY)
	cstring result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
	#else
	// your custom implementation
	#endif
}

u8string convert_utf16_to_utf8(const u16string_view& str)
{
	return utf8::utf16tou8(str);
}

u8string convert_utf32_to_utf8(const u32string_view& str)
{
	return utf8::utf32tou8(str);
}

#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
