﻿#include "../include/kotek_core_containers_string.h"
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

TEST(String, PlusUtf8CharCastedToCharSymbol)
{
	kun_ktk cstring instance;
	instance += KOTEK_TEXTU("a");
	EXPECT_TRUE(instance == KOTEK_TEXTU("a"));
}

TEST(String, PlusTcharSymbol)
{
	kun_ktk cstring instance;
	instance += KOTEK_TEXTU("x");
	EXPECT_TRUE(instance == KOTEK_TEXTU("x"));
}

TEST(String, EqualityByCharString)
{
	kun_ktk cstring instance(KOTEK_TEXTU("test"));
	EXPECT_TRUE(instance == KOTEK_TEXTU("test"));
}

TEST(String, EqualityByTcharString)
{
	kun_ktk cstring instance(KOTEK_TEXTU("test_tchar"));
	EXPECT_TRUE(instance == KOTEK_TEXTU("test_tchar"));
}
	#endif
#endif

void RegisterTests_String_ForModule_Containers_String(){
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
