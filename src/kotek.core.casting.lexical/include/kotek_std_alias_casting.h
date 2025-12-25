#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/lexical_cast.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <type_traits>
	#include <cstdlib>
	#include <kotek.core.types.string/include/kotek_core_types_string.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename T, typename S>
T lexical_cast(const S& args)
{
#ifdef KOTEK_USE_BOOST_LIBRARY
	return boost::lexical_cast<T, S>(args);
#elif defined(KOTEK_USE_STD_LIBRARY)
	if constexpr (std::is_arithmetic_v<T>)
	{
		if constexpr (std::is_integral_v<T>)
		{
			const char* p_in = nullptr;

			if constexpr (std::is_pointer_v<T>)
			{
				using no_ptr_t = std::remove_pointer_t<T>;
				using no_ptr_no_const_t =
					std::remove_const_t<no_ptr_t>;

				if constexpr (std::is_same_v<
								  no_ptr_no_const_t,
								  char>)
				{
					p_in = args;
				}
			}
			else if constexpr (std::is_reference_v<T>)
			{
				using no_reference_t =
					std::remove_reference_t<T>;
				using no_reference_no_const_t =
					std::remove_const_t<no_reference_t>;

				if constexpr (std::is_same_v<
								  KUN_KOTEK KUN_KTK cstring,
								  no_reference_no_const_t>)
				{
					p_in = args.c_str();
				}
			}
			else
			{
				using no_const_t = std::remove_const_t<T>;

				if constexpr (std::is_same_v<no_const_t, char>)
				{
					p_in = &args;
				}
				else if constexpr (std::is_same_v<no_const_t, KUN_KOTEK KUN_KTK cstring>)
				{
					p_in = args.c_str();
				}
			}

			return static_cast<T>(std::atoi(p_in));
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			const char* p_in = nullptr;

			if constexpr (std::is_pointer_v<T>)
			{
				using no_ptr_t = std::remove_pointer_t<T>;
				using no_ptr_no_const_t =
					std::remove_const_t<no_ptr_t>;

				if constexpr (std::is_same_v<
								  no_ptr_no_const_t,
								  char>)
				{
					p_in = args;
				}
			}
			else if constexpr (std::is_reference_v<T>)
			{
				using no_reference_t =
					std::remove_reference_t<T>;
				using no_reference_no_const_t =
					std::remove_const_t<no_reference_t>;

				if constexpr (std::is_same_v<
								  KUN_KOTEK KUN_KTK cstring,
								  no_reference_no_const_t>)
				{
					p_in = args.c_str();
				}
			}
			else
			{
				using no_const_t = std::remove_const_t<T>;

				if constexpr (std::is_same_v<no_const_t, char>)
				{
					p_in = &args;
				}
				else if constexpr (std::is_same_v<
									   no_const_t,
									   KUN_KOTEK KUN_KTK
										   cstring>)
				{
					p_in = args.c_str();
				}
			}

			return static_cast<T>(std::atof(args));
		}
		else
		{
			static_assert(
				false,
				"provide implementation for your custom type"
			);
		}
	}
	else
	{
		static_assert(
			false, "provide implementation for your custom type"
		);
	}

	return T();
#else
	#error not implemented
#endif
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
