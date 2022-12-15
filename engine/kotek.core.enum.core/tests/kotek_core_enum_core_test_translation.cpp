#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.utility/include/kotek_core_utility.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <boost/test/unit_test.hpp>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
void test_translation_to_enum_invalid_cases()
{
	eEngineSupportedOpenGLVersion result{};

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("0.0");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kUnknown);

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("1.9");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kUnknown);

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("2.9");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kUnknown);

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("3.9");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kUnknown);
}

void test_translation_to_enum_valid_cases()
{
	eEngineSupportedOpenGLVersion result{};

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("1.0");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kOpenGL_1_0);

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("2.1");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kOpenGL_2_1);

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("3.2");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kOpenGL_3_2);

	result =
		helper::TranslateFromStringToEnum_EngineSupportedOpenGLVersion("4.6");

	BOOST_CHECK(result == eEngineSupportedOpenGLVersion::kOpenGL_4_6);
}
	#endif
#endif

void RegisterTests_Translation_ForModule_Enum_Core(void)
{
#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
	boost::unit_test::test_suite* p_suite = BOOST_TEST_SUITE("enum core");

	p_suite->add(BOOST_TEST_CASE(&test_translation_to_enum_invalid_cases));
	p_suite->add(BOOST_TEST_CASE(&test_translation_to_enum_valid_cases));

	boost::unit_test::framework::master_test_suite().add(p_suite);
	#endif
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK