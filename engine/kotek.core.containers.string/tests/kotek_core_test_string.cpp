#include "../include/kotek_core_containers_string.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <CppUTest/TestHarness.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
TEST_GROUP(String){};

TEST(String, PlusUtf8CharCastedToCharSymbol)
{
    ktk::cstring instance;
    instance += KOTEK_TEXTU("a");
    CHECK(instance == KOTEK_TEXTU("a"));
}

TEST(String, PlusTcharSymbol) 
{
	ktk::cstring instance;
	instance += KOTEK_TEXTU("x");
	CHECK(instance == KOTEK_TEXTU("x"));
}

TEST(String, EqualityByCharString)
{
	ktk::cstring instance(KOTEK_TEXTU("test"));
	CHECK(instance == KOTEK_TEXTU("test"));
}

TEST(String, EqualityByTcharString)
{
	ktk::cstring instance(KOTEK_TEXTU("test_tchar"));
	CHECK(instance == KOTEK_TEXTU("test_tchar"));
}
	#endif
#endif

void RegisterTests_String_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
