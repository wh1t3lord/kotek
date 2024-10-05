#include "../include/kotek_core.h"
#include <CppUTest/TestHarness.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
TEST_GROUP(Json){};

TEST(Json,test_json_std_vector){}

TEST(Json,test_json_std_map) {}

TEST(Json,test_json_vector1f)
{
	ktk::math::vector1f test(10.0f);

	auto value = ktk::json::value_from(test);

	ktk::math::vector1f deserialized =
		ktk::json::value_to<ktk::math::vector1f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serializer doesn't work well!");
}

TEST(Json,test_json_vector2f)
{
	ktk::math::vector2f test(10.3141f, 20.2515f);

	auto value = ktk::json::value_from(test);

	ktk::math::vector2f deserialized =
		ktk::json::value_to<ktk::math::vector2f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serialize doesn't work well");
}

TEST(Json,test_json_vector3f)
{
	ktk::math::vector3f test(10.3141f, 20.2515f, 3131141.1414f);

	auto value = ktk::json::value_from(test);

	ktk::math::vector3f deserialized =
		ktk::json::value_to<ktk::math::vector3f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serialize doesn't work well");
}

TEST(Json,test_json_vector4f)
{
	ktk::math::vector4f test(10.3141f, 20.2515f, 3131141.1414f, 1000000.18979f);

	auto value = ktk::json::value_from(test);

	ktk::math::vector4f deserialized =
		ktk::json::value_to<ktk::math::vector4f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serialize doesn't work well");
}

TEST(Json,test_json_matrix2x2f)
{
	ktk::math::matrix2x2f test(
		10.3141f, 20.2515f, 3131141.1414f, 1000000.18979f);

	auto value = ktk::json::value_from(test);

	ktk::math::matrix2x2f deserialized =
		ktk::json::value_to<ktk::math::matrix2x2f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serialize doesn't work well");
}

TEST(Json,test_json_matrix3x3f)
{
	ktk::math::matrix3x3f test(10.3141f, 20.2515f, 3131141.1414f,
		1000000.18979f, 141.134f, 3414.124f, 1415.1234f, 341.4f, 124.23f);

	auto value = ktk::json::value_from(test);

	ktk::math::matrix3x3f deserialized =
		ktk::json::value_to<ktk::math::matrix3x3f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serialize doesn't work well");
}

TEST(Json,test_json_matrix4x4f)
{
	ktk::math::matrix4x4f test(10.3141f, 20.2515f, 3131141.1414f,
		1000000.18979f, 141.134f, 3414.124f, 1415.1234f, 341.4f, 124.23f, 113.f,
		313.f, 31313.31f, 313.31f, 3134.3f, 34141.1313f, 314141.12313f);

	auto value = ktk::json::value_from(test);

	ktk::math::matrix4x4f deserialized =
		ktk::json::value_to<ktk::math::matrix4x4f>(value);

	KOTEK_ASSERT(deserialized == test,
		"can't be deserializer or serialize doesn't work well");
}

	#endif
#endif

void RegisterTests_Json_ForModule_Core(void)
{
#ifdef KOTEK_USE_TESTS	
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
