#include "../include/kotek_core_containers_string.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <catch2/catch_test_macros.hpp>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
TEST_CASE("String plus one char symbol")
{
    ktk::cstring instance;
    instance += KOTEK_TEXTU("a");
    REQUIRE(instance == KOTEK_TEXTU("a"));
}

TEST_CASE("String plus one tchar symbol") 
{
	ktk::cstring instance;
	instance += KOTEK_TEXTU("x");
	REQUIRE(instance == KOTEK_TEXTU("x"));
}

TEST_CASE("String equality by char string") 
{
	ktk::cstring instance(KOTEK_TEXTU("test"));
	REQUIRE(instance == KOTEK_TEXTU("test"));
}

TEST_CASE("String equality by tchar string")
{
	ktk::cstring instance(KOTEK_TEXTU("test_tchar"));
	REQUIRE(instance == KOTEK_TEXTU("test_tchar"));
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
