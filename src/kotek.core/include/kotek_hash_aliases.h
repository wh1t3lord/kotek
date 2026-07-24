#pragma once

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>

#ifdef KOTEK_USE_STD_LIBRARY

namespace std
{
	#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	template <size_t StrSize>
	struct hash<KUN_KOTEK KUN_KTK static_cstring<StrSize>>
	{
		size_t operator()(
			const KUN_KOTEK KUN_KTK static_cstring<StrSize>& str
		) const
		{
			return hash<KUN_KOTEK KUN_KTK cstring_view>()(
				str.c_str()
			);
		}
	};

	template <>
	struct hash<KUN_KOTEK KUN_KTK static_cstring_view>
	{
		size_t operator()(
			const KUN_KOTEK KUN_KTK static_cstring_view& view
		) const
		{
			static_assert(
				std::is_same_v<
					KUN_KOTEK KUN_KTK cstring_view,
					KUN_KOTEK KUN_KTK static_cstring_view> ==
					false,
				"supposed to be different, try to make own "
			    "type otherwise you broke something"
			);
			return hash<KUN_KOTEK KUN_KTK cstring_view>()(
				view.data()
			);
		}
	};
	#endif
} // namespace std

#elif defined(KOTEK_USE_BOOST_LIBRARY)
#else
#endif