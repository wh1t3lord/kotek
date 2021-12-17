#include "../kotek_main_manager.h"
#include "../kotek_std.h"
#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Core
	{
		void RegisterTests_String_ForModule_Core()
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("registered!");
#endif
		}

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		BOOST_AUTO_TEST_CASE(
			initialize_and_shutdown_in_ctor_and_dtor_of_main_manager)
		{
			ktkMainManager instance(0, nullptr);
		}

		BOOST_AUTO_TEST_CASE(string_plus_one_char_symbol)
		{
			ktk::string instance;

			instance += "a";

			BOOST_CHECK(instance == "a");
		}

		BOOST_AUTO_TEST_CASE(string_plus_one_tchar_symbol)
		{
			ktk::string instance;

			instance += KOTEK_TEXT("x");

			BOOST_CHECK(instance == KOTEK_TEXT("x"));
		}

		BOOST_AUTO_TEST_CASE(string_equality_by_char_string)
		{
			ktk::string instance("test");

			BOOST_CHECK(instance == "test");
		}

		BOOST_AUTO_TEST_CASE(string_equality_by_tchar_string)
		{
			ktk::string instance(KOTEK_TEXT("test_tchar"));

			BOOST_CHECK(instance == KOTEK_TEXT("test_tchar"));
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_int)
		{
			ktk::string instance(std::numeric_limits<int>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<int>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_unsigned_int)
		{
			ktk::string instance(std::numeric_limits<unsigned int>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<unsigned int>::max())
					.c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_float)
		{
			ktk::string instance(std::numeric_limits<float>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<float>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_double)
		{
			ktk::string instance(std::numeric_limits<double>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<double>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_long_long)
		{
			ktk::string instance(std::numeric_limits<long long>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<long long>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_short_int)
		{
			ktk::string instance(std::numeric_limits<short int>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<short int>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_signed_int)
		{
			ktk::string instance(std::numeric_limits<signed int>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<signed int>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_long_int)
		{
			ktk::string instance(std::numeric_limits<long int>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<long int>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_long_long_int)
		{
			ktk::string instance(std::numeric_limits<long long int>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<long long int>::max())
					.c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_wchar_t)
		{
			ktk::string instance(std::numeric_limits<wchar_t>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<wchar_t>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_char8_t)
		{
			ktk::string instance(std::numeric_limits<char8_t>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<char8_t>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_char16_t)
		{
			ktk::string instance(std::numeric_limits<char16_t>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<char16_t>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_char32_t)
		{
			ktk::string instance(std::numeric_limits<char32_t>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<char32_t>::max()).c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_long_double)
		{
			ktk::string instance(std::numeric_limits<long double>::max());

			BOOST_CHECK(instance ==
				std::to_string(std::numeric_limits<long double>::max())
					.c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_unsigned_long_long_int)
		{
			ktk::string instance(
				std::numeric_limits<unsigned long long int>::max());

			BOOST_CHECK(instance ==
				std::to_string(
					std::numeric_limits<unsigned long long int>::max())
					.c_str());
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_equal_to_number)
		{
			ktk::string instance = 255355;

			BOOST_CHECK(instance == "255355");
		}

		BOOST_AUTO_TEST_CASE(string_construct_by_plus_number)
		{
			ktk::string instance;

			instance += 35;

			BOOST_CHECK(instance == "35");
		}

		BOOST_AUTO_TEST_CASE(string_auto_cast_to_number)
		{
			ktk::string instance = "255";

			int test = instance;

			BOOST_CHECK(test == 255);
		}

		BOOST_AUTO_TEST_CASE(string_recursive_adding_from_global_operator_plus)
		{
			ktk::string instance = "hello_";

			BOOST_CHECK(((instance + ktk::string("world")) +
							ktk::string("kek")) == "hello_worldkek");
		}

		BOOST_AUTO_TEST_CASE(string_const_ref_global_operator_plus)
		{
			auto p_test = [](const ktk::string& test) -> void
			{ BOOST_CHECK((test + ktk::string("kek")) == "hellokek"); };

			p_test("hello");
		}

		BOOST_AUTO_TEST_CASE(strings_both_const_ref_global_operator_plus)
		{
			auto p_test = [](const ktk::string& test,
							  const ktk::string& test2) -> void
			{ BOOST_CHECK((test + test2) == "hellokek"); };

			p_test("hello", "kek");
		}

		BOOST_AUTO_TEST_CASE(
			strings_both_const_ref_global_one_is_legacy_string_operator_plus_2)
		{
			auto p_test = [](const ktk::string& test,
							  const ktk::string_legacy& test2) -> void
			{ BOOST_CHECK((test + test2) == "hellokek"); };

			p_test("hello", "kek");
		}

		#ifdef KOTEK_USE_UNICODE
		BOOST_AUTO_TEST_CASE(
			strings_both_const_ref_global_one_is_unicode_string_operator_plus)
		{
			auto p_test = [](const ktk::string& test,
							  const ktk::string_unicode& test2) -> void
			{ BOOST_CHECK((test + test2) == "hellokek"); };

			p_test("hello", KOTEK_TEXT("kek"));
		}

		BOOST_AUTO_TEST_CASE(
			strings_both_const_ref_global_one_is_unicode_string_operator_plus_compare_with_unicode_string_result)
		{
			auto p_test = [](const ktk::string& test,
							  const ktk::string_unicode& test2) -> void
			{ BOOST_CHECK((test + test2) == KOTEK_TEXT("hellokek")); };

			p_test("hello", KOTEK_TEXT("kek"));
		}
		#endif
	#endif
#endif
	} // namespace Core
} // namespace Kotek
