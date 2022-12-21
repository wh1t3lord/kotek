#include "../include/kotek_core.h"
#include <boost/test/unit_test.hpp>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
void test_json_std_vector()
{
 
}

void test_json_std_map() {}

void test_json_vector1f() {}

void test_json_vector2f() {}
 
void test_json_vector3f() {}

void test_json_vector4f() {}

void test_json_matrix2x2f() {}

void test_json_matrix3x3f() {}

void test_json_matrix4x4f() {}

	#endif
#endif

void RegisterTests_Json_ForModule_Core(void)
{
#ifdef KOTEK_USE_TESTS

	boost::unit_test::test_suite* p_suite =
		BOOST_TEST_SUITE("ktk::json");

	p_suite->add(BOOST_TEST_CASE(&test_json_vector1f));
	p_suite->add(BOOST_TEST_CASE(&test_json_vector2f));

	boost::unit_test::framework::master_test_suite().add(p_suite);

	KOTEK_MESSAGE("registered!");
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
