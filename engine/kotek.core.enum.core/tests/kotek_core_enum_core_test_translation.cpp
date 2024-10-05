#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.utility/include/kotek_core_utility.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <CppUTest/TestHarness.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

TEST_GROUP(EnumCoreTranslation){};

TEST(EnumCoreTranslation, TranslationToEnumInvalidCases)
{
	eEngineSupportedRenderer result{};

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("0.0"));

	CHECK(result == eEngineSupportedRenderer::kUnknown);

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("1.9"));

	CHECK(result == eEngineSupportedRenderer::kUnknown);

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("2.9"));

	CHECK(result == eEngineSupportedRenderer::kUnknown);

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("3.9"));

	CHECK(result == eEngineSupportedRenderer::kUnknown);
}

TEST(EnumCoreTranslation, TranslationToEnumValidCase)
{
	eEngineSupportedRenderer result{};

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("1.0"));

	CHECK(result == eEngineSupportedRenderer::kOpenGL_1_0);

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("2.1"));

	CHECK(result == eEngineSupportedRenderer::kOpenGL_2_1);

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("3.2"));

	CHECK(result == eEngineSupportedRenderer::kOpenGL_3_2);

	result = helper::TranslateFromStringToEnum_EngineSupportedRenderer(
		KOTEK_TEXTU("GL"), KOTEK_TEXTU("4.6"));

	CHECK(result == eEngineSupportedRenderer::kOpenGL_4_6);
}
	#endif
#endif

void RegisterTests_Translation_ForModule_Enum_Core(void)
{
#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
	#endif
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
