#include "../include/kotek_core_containers_string.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <boost/test/unit_test.hpp>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
void string_plus_one_char_symbol()
{
    ktk::cstring instance;

    instance += KOTEK_TEXT("a");

    BOOST_REQUIRE(instance == KOTEK_TEXT("a"));
}

void string_plus_one_tchar_symbol()
{
    ktk::cstring instance;

	instance += KOTEK_TEXT("x");

	BOOST_REQUIRE(instance == KOTEK_TEXT("x"));
}

void string_equality_by_char_string()
{
    ktk::cstring instance(KOTEK_TEXT("test"));

    BOOST_REQUIRE(instance == KOTEK_TEXT("test"));
}

void string_equality_by_tchar_string()
{
    ktk::cstring instance(KOTEK_TEXT("test_tchar"));

	BOOST_REQUIRE(instance == KOTEK_TEXT("test_tchar"));
}
	#endif
#endif

void RegisterTests_String_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
	boost::unit_test::test_suite* p_suite = BOOST_TEST_SUITE("ktk::string");

	p_suite->add(BOOST_TEST_CASE(&string_equality_by_char_string));
	p_suite->add(BOOST_TEST_CASE(&string_equality_by_tchar_string));
	p_suite->add(BOOST_TEST_CASE(&string_plus_one_char_symbol));
	p_suite->add(BOOST_TEST_CASE(&string_plus_one_tchar_symbol));

	boost::unit_test::framework::master_test_suite().add(p_suite);
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
