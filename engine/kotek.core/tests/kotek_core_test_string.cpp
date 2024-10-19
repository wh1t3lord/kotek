#include "../include/kotek_core.h"
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

TEST(String, format)
{
	auto str = kun_ktk format("{}", 12);
	EXPECT_TRUE(str == "12");
}

TEST(String, static_format)
{
	auto str = kun_ktk static_format("{}", 12);
	EXPECT_TRUE(str == "12");
}

TEST(String, static_format_custom_size)
{
	auto str = kun_ktk static_format<8>("{}", 12);
	EXPECT_TRUE(str == "12");
}

TEST(String, static_format_wrong_size)
{
	auto str = kun_ktk static_format<1>("{}", 12);
	EXPECT_FALSE(str == "12");
}

TEST(String, static_format_exact_size_without_terminated_null) 
{
	auto str = kun_ktk static_format<2>("{}", 12);
	EXPECT_TRUE(str == "12");
}

	#endif
#endif

void RegisterTests_String_ForModule_Core(void) {}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK

