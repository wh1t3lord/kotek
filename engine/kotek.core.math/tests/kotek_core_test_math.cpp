#include "../include/kotek_core_math.h"

#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.utility/include/kotek_core_utility.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <gtest/gtest.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

TEST(Math, equal_function_for_floats_are_not_equal)
{
	float test1 = 15.1515f;
	float test2 = 15.1504f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_must_be_equal)
{
	float test1 = 15.1515f;
	float test2 = 15.1515f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1, test2) == true);
}

TEST(Math, equal_function_for_floats_really_close_but_not_equal)
{
	float test1 = 15.151514f;
	float test2 = 15.151513f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_digits)
{
	float test1 = 0.000300f;
	float test2 = 0.000301f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_zeros)
{
	float test1 = 0.0f;
	float test2 = 0.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1, test2) == true);
}

TEST(Math, equal_function_for_floats_really_low)
{
	float test1 = 0.000002f;
	float test2 = 0.000001f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_when_we_sum)
{
	float test1 = 3.0f;
	float test2 = 6.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1 + test2, 9.0f) == true);
}

TEST(Math, equal_function_for_floats_when_we_sum_dirty)
{
	float test1 = 3.5151f;
	float test2 = 2.521f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1 + test2, 6.03f) == false);
}

TEST(Math, vector1f_testing_constructor_default)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 0.0f));
}

TEST(Math, vector1f_testing_constructor_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f vec(5.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f));
}

		#ifdef KOTEK_USE_MATH_LIBRARY_GLM
TEST(Math, vector1f_testing_constructor_based_on_struct) {}
		#endif

TEST(Math, vector1f_testing_copy_constructor)
{
	kn_kotek::kn_ktk::kn_math::vector1f vec_original(550.5f);
	kn_kotek::kn_ktk::kn_math::vector1f vec_copy(vec_original);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.x(), vec_copy.x()));
}

TEST(Math, vector1f_testing_assignment_operator_based_on_own_type)
{
	kn_kotek::kn_ktk::kn_math::vector1f some(50.0f);
	kn_kotek::kn_ktk::kn_math::vector1f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.x(), some2.x()));
}

TEST(Math, vector1f_testing_assignment_operator_based_on_base_type)
{
	kn_kotek::kn_ktk::kn_math::base_vec1_t some(51.0f);
	kn_kotek::kn_ktk::kn_math::vector1f some2 = some;

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.x(), some));
		#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.x(), some.x));
		#endif
}

TEST(Math, vector1f_testing_setter_single_depth)
{
	kn_kotek::kn_ktk::kn_math::vector1f test;

	test.x() = 105.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.x(), 105.0f));
}

TEST(Math, vector1f_testing_plus_equal_operator_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 3.5f;
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 5.5f;

	test1 += test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 9.0f));
}

TEST(Math, vector1f_testing_plus_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 3.5f;
	kn_kotek::kn_ktk::kn_math::vector1f test2 = 5.5f;

	test1 += test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 9.0f));
}

TEST(Math, vector1f_testing_subtract_equal_operator_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 5.5f;
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 3.5f;

	test1 -= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 2.0f));
}

TEST(Math, vector1f_testing_subtract_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 5.5f;
	kn_kotek::kn_ktk::kn_math::vector1f test2 = 3.5f;

	test1 -= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 2.0f));
}

TEST(Math, vector1f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 3.2f;
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 17.6f));
}

TEST(Math,
	vector1f_testing_multiply_equal_operator_based_on_vector_its_per_compunent_multiply)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 3.2f;
	kn_kotek::kn_ktk::kn_math::vector1f test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 17.6f));
}

TEST(Math, vector1f_testing_divide_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 8.4f;
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.6f;

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.6f)));
}

TEST(Math, vector1f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 8.4f;
	kn_kotek::kn_ktk::kn_math::vector1f test2 = 2.6f;

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.6f)));
}

TEST(Math, vector1f_testing_modulo_equal_operator_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 5.3f;
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(5.3f, 2.0f))));
}

TEST(Math, vector1f_testing_modulo_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 5.3f;
	kn_kotek::kn_ktk::kn_math::vector1f test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(5.3f, 2.0f))));
}

TEST(Math, vector1f_testing_unary_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 10.0f;

	test1 = +test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 10.0f));
}

TEST(Math, vector1f_testing_unary_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1 = 10.0f;

	test1 = -test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), -10.0f));
}

TEST(Math, vector1f_testing_comparison_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1;
	kn_kotek::kn_ktk::kn_math::vector1f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector1f_testing_comparison_equal_random)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(150.15125f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(150.15125f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector1f_testing_comparison_equal_different)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(15.3f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(15.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_equal_different_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(15.14152f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(15.14151f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_not_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1;
	kn_kotek::kn_ktk::kn_math::vector1f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_not_equal_different)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(5.0f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(2.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector1f_testing_comparison_not_equal_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(151.25151f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(151.25151f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_not_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(150.10502f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(150.10509f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector1f_testing_cast_operator_xmvector)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(150.0f);

	DirectX::XMVECTOR vec = test1;

	float value = DirectX::XMVectorGetX(vec);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value, test1.x()));
}
		#endif

TEST(Math, vector1f_testing_binary_plus_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(50.5f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(5.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(new_vector == 56.0f);
}

TEST(Math, vector1f_testing_binary_plus_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(50.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(5.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(new_vector == 56.0f);
}

TEST(Math, vector1f_testing_binary_subtract_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(50.5f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(0.5f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(new_vector == 50.0f);
}

TEST(Math, vector1f_testing_binary_subtract_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(50.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(0.5f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(new_vector == 50.0f);
}

TEST(Math, vector1f_testing_binary_mutiply_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(5.5f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(new_vector == 12.1f);
}

TEST(Math, vector1f_testing_binary_multiply_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(5.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(new_vector == 12.1f);
}

TEST(Math, vector1f_testing_binary_divide_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(6.6f);
	kn_kotek::kn_ktk::kn_math::vector1f test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(new_vector == 33.0f);
}

TEST(Math, vector1f_testing_binary_divide_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector1f test1(6.6f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(new_vector == 33.0f);
}

TEST(Math, vector2f_testing_constructor_default)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 0.0f));
}

TEST(Math, vector2f_testing_constructor_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector2f vec(5.0f, 6.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec.y(), 6.0f));
}

TEST(Math, vector2f_testing_constructor_based_on_struct)
{
	kn_kotek::kn_ktk::kn_math::base_vec2_t data = {5.0f, 6.0f};
	kn_kotek::kn_ktk::kn_math::vector2f vec(data);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec.y(), 6.0f));
}

TEST(Math, vector2f_testing_copy_constructor)
{
	kn_kotek::kn_ktk::kn_math::vector2f vec_original(550.5f, 153.2f);
	kn_kotek::kn_ktk::kn_math::vector2f vec_copy(vec_original);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.x(), vec_copy.x()) &&
		kn_kotek::kn_ktk::is_equal(vec_original.y(), vec_copy.y()));
}

TEST(Math, vector2f_testing_assignment_operator_based_on_own_type)
{
	kn_kotek::kn_ktk::kn_math::vector2f some(50.0f, 25.4f);
	kn_kotek::kn_ktk::kn_math::vector2f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.x(), some2.x()) &&
		kn_kotek::kn_ktk::is_equal(some.y(), some2.y()));
}

TEST(Math, vector2f_testing_assignment_operator_based_on_base_type)
{
	kn_kotek::kn_ktk::kn_math::base_vec2_t some(51.0f, 15.3f);
	kn_kotek::kn_ktk::kn_math::vector2f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.x(), some.x) &&
		kn_kotek::kn_ktk::is_equal(some2.y(), some.y));
}

TEST(Math, vector2f_testing_setter_single_depth)
{
	kn_kotek::kn_ktk::kn_math::vector2f test;

	test.x() = 105.0f;
	test.y() = 103.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.x(), 105.0f) &&
		kn_kotek::kn_ktk::is_equal(test.y(), 103.0f));
}

TEST(Math, vector2f_testing_plus_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {3.5f, 2.5f};
	kn_kotek::kn_ktk::kn_math::vector2f test2 = {1.5f, 2.0f};

	test1 += test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(test1.y(), 4.5f));
}

TEST(Math, vector2f_testing_subtract_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {3.5f, 2.5f};
	kn_kotek::kn_ktk::kn_math::vector2f test2 = {1.5f, 2.0f};

	test1 -= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 2.0f) &&
		kn_kotek::kn_ktk::is_equal(test1.y(), 0.5f));
}

TEST(Math, vector2f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {2.0f, 6.4f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 11.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 35.2f));
}

TEST(Math,
	vector2f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {2.0f, 6.4f};
	kn_kotek::kn_ktk::kn_math::vector2f test2 = {5.5f, 252.1f};

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 11.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (6.4f * 252.1f)));
}

TEST(Math, vector2f_testing_divide_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {8.4f, 2.6f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (2.6f / 2.0f)));
}

TEST(Math, vector2f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {8.4f, 3.5f};
	kn_kotek::kn_ktk::kn_math::vector2f test2 = {2.0f, 0.5f};

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (3.5f / 0.5f)));
}

TEST(Math, vector2f_testing_modulo_equal_operator_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {4.0f, 6.0f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (std::fmod(6.0f, 2.0f))));
}

TEST(Math, vector2f_testing_modulo_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {4.0f, 6.0f};
	kn_kotek::kn_ktk::kn_math::vector2f test2 = {2.0f, 3.0f};

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (std::fmod(6.0f, 3.0f))));
}

TEST(Math, vector2f_testing_unary_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {10.0f, 5.0f};

	test1 = +test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 10.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 5.0f));
}

TEST(Math, vector2f_testing_unary_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1 = {10.0f, 5.0f};

	test1 = -test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), -10.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), -5.0f));
}

TEST(Math, vector2f_testing_comparison_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1;
	kn_kotek::kn_ktk::kn_math::vector2f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector2f_testing_comparison_equal_random)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(150.15125f, 1515.1414f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(150.15125f, 1515.1414f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector2f_testing_comparison_equal_different_last_field)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(15.3f, 4.4f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(15.0f, 4.4f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_equal_different_first_field)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(15.0f, 4.3f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(15.0f, 4.4f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_equal_different_dirty_last_field)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(15.14152f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(15.14151f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_equal_different_dirty_first_field)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(0.0f, 15.14152f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(0.0f, 15.14151f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_not_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1;
	kn_kotek::kn_ktk::kn_math::vector2f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_not_equal_different)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(5.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(2.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector2f_testing_comparison_not_equal_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(151.25151f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(151.25151f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_not_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(150.10502f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(150.10509f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector2f_testing_cast_operator_xmvector)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(150.0f, 151.0f);

	DirectX::XMVECTOR vec = test1;

	float value_x = DirectX::XMVectorGetX(vec);
	float value_y = DirectX::XMVectorGetY(vec);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_x, test1.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_y, test1.y()));
}
		#endif

TEST(Math, vector2f_testing_binary_plus_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(50.5f, 2.5f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(5.5f, 0.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(50.5f + 5.5f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f + 0.5f, new_vector.y()));
}

TEST(Math, vector2f_testing_binary_subtract_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(50.5f, 25.0f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(0.5f, 5.0f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(50.5f - 0.5f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f - 5.0f, new_vector.y()));
}

TEST(Math, vector2f_testing_binary_mutiply_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(5.5f, 25.5f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(2.2f, 5.5f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.5f * 2.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.5f * 5.5f, new_vector.y()));
}

TEST(Math, vector2f_testing_binary_multiply_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(5.5f, 2.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.5f * 2.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f * 2.2f, new_vector.y()));
}

TEST(Math, vector2f_testing_binary_divide_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(6.6f, 3.6f);
	kn_kotek::kn_ktk::kn_math::vector2f test2(0.2f, 0.4f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.6f / 0.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.6f / 0.4f, new_vector.y()));
}

TEST(Math, vector2f_testing_binary_divide_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector2f test1(6.6f, 3.6f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.6f / 0.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.6f / 0.2f, new_vector.y()));
}

TEST(Math, vector3f_testing_constructor_default)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 0.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 0.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 0.0f));
}

TEST(Math, vector3f_testing_constructor_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector3f vec(5.0f, 6.0f, 7.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.y(), 6.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.z(), 7.0f));
}

TEST(Math, vector3f_testing_constructor_based_on_struct)
{
	kn_kotek::kn_ktk::kn_math::base_vec3_t data = {5.0f, 6.0f, 7.0f};
	kn_kotek::kn_ktk::kn_math::vector3f vec(data);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.y(), 6.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.z(), 7.0f));
}

TEST(Math, vector3f_testing_copy_constructor)
{
	kn_kotek::kn_ktk::kn_math::vector3f vec_original(550.5f, 153.2f, 25.25f);
	kn_kotek::kn_ktk::kn_math::vector3f vec_copy(vec_original);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.x(), vec_copy.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.y(), vec_copy.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.z(), vec_copy.z()));
}

TEST(Math, vector3f_testing_assignment_operator_based_on_own_type)
{
	kn_kotek::kn_ktk::kn_math::vector3f some(50.0f, 25.4f, 252.0f);
	kn_kotek::kn_ktk::kn_math::vector3f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.x(), some2.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.y(), some2.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.z(), some2.z()));
}

TEST(Math, vector3f_testing_assignment_operator_based_on_base_type)
{
	kn_kotek::kn_ktk::kn_math::base_vec3_t some(51.0f, 15.3f, 25.0f);
	kn_kotek::kn_ktk::kn_math::vector3f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.x(), some.x));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.y(), some.y));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.z(), some.z));
}

TEST(Math, vector3f_testing_setter_single_depth)
{
	kn_kotek::kn_ktk::kn_math::vector3f test;

	test.x() = 105.0f;
	test.y() = 103.0f;
	test.z() = 144.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.x(), 105.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.y(), 103.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.z(), 144.0f));
}

TEST(Math, vector3f_testing_plus_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {3.5f, 2.5f, 351.0f};
	kn_kotek::kn_ktk::kn_math::vector3f test2 = {1.5f, 2.0f, 9.0f};

	test1 += test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 4.5f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 360.0f));
}

TEST(Math, vector3f_testing_subtract_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {3.5f, 2.5f, 252.0f};
	kn_kotek::kn_ktk::kn_math::vector3f test2 = {1.5f, 2.0f, 3.0f};

	test1 -= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 2.0f) &&
		kn_kotek::kn_ktk::is_equal(test1.y(), 0.5f));
}

TEST(Math, vector3f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {2.0f, 6.4f, 4.4f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 2.0f * 5.5f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 6.4f * 5.5f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 4.4f * 5.5f));
}

TEST(Math,
	vector3f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {2.0f, 6.4f, 25.5f};
	kn_kotek::kn_ktk::kn_math::vector3f test2 = {5.5f, 252.1f, 60.4f};

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (2.0f * 5.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (6.4f * 252.1f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (25.5f * 60.4f)));
}

TEST(Math, vector3f_testing_divide_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {8.4f, 2.6f, 25.0f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (2.6f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (25.0f / 2.0f)));
}

TEST(Math, vector3f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {8.4f, 3.5f, 5.5f};
	kn_kotek::kn_ktk::kn_math::vector3f test2 = {2.0f, 0.5f, 52.5f};

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (3.5f / 0.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (5.5f / 52.5f)));
}

TEST(Math, vector3f_testing_modulo_equal_operator_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {4.0f, 6.0f, 8.0f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (std::fmod(6.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (std::fmod(8.0f, 2.0f))));
}

TEST(Math, vector3f_testing_modulo_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {4.0f, 6.0f, 8.0f};
	kn_kotek::kn_ktk::kn_math::vector3f test2 = {2.0f, 3.0f, 4.0f};

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (std::fmod(6.0f, 3.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (std::fmod(8.0f, 4.0f))));
}

TEST(Math, vector3f_testing_unary_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {10.0f, 5.0f, 15.0f};

	test1 = +test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 10.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 15.0f));
}

TEST(Math, vector3f_testing_unary_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1 = {10.0f, 5.0f, 15.0f};

	test1 = -test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), -10.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), -5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), -15.0f));
}

TEST(Math, vector3f_testing_comparison_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1;
	kn_kotek::kn_ktk::kn_math::vector3f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector3f_testing_comparison_equal_random)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(150.15125f, 1515.1414f, 14.24141f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(150.15125f, 1515.1414f, 14.24141f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector3f_testing_comparison_equal_different_last_field)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(15.3f, 4.4f, 15.15f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(15.0f, 4.4f, 15.15f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_equal_different_first_field)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(15.0f, 4.3f, 15.15f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(15.0f, 4.4f, 15.15f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_equal_different_dirty_last_field)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(15.14152f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(15.14151f, 0.0f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_equal_different_dirty_first_field)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(0.0f, 15.14152f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(0.0f, 15.14151f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_not_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1;
	kn_kotek::kn_ktk::kn_math::vector3f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_not_equal_different)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(5.0f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(2.0f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector3f_testing_comparison_not_equal_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(151.25151f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(151.25151f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_not_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(150.10502f, 0.0f, 1.0f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(150.10509f, 0.0f, 1.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector3f_testing_cast_operator_xmvector)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(150.0f, 151.0f, 153.0f);

	DirectX::XMVECTOR vec = test1;

	float value_x = DirectX::XMVectorGetX(vec);
	float value_y = DirectX::XMVectorGetY(vec);
	float value_z = DirectX::XMVectorGetZ(vec);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_x, test1.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_y, test1.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_z, test1.z()));
}
		#endif

TEST(Math, vector3f_testing_binary_plus_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(50.5f, 2.5f, 3.5f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(5.5f, 0.5f, 2.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(50.5f + 5.5f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f + 0.5f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f + 2.5f, new_vector.z()));
}

TEST(Math, vector3f_testing_binary_subtract_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(50.5f, 25.0f, 3.5f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(0.5f, 5.0f, 2.5f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(50.5f - 0.5f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f - 5.0f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f - 2.5f, new_vector.z()));
}

TEST(Math, vector3f_testing_binary_mutiply_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(5.5f, 25.5f, 3.5f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(2.2f, 5.5f, 2.5f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.5f * 2.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.5f * 5.5f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f * 2.5f, new_vector.z()));
}

TEST(Math, vector3f_testing_binary_multiply_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(5.5f, 2.5f, 3.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.5f * 2.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f * 2.2f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f * 2.2f, new_vector.z()));
}

TEST(Math, vector3f_testing_binary_divide_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(6.6f, 3.6f, 3.5f);
	kn_kotek::kn_ktk::kn_math::vector3f test2(0.2f, 0.4f, 0.5f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.6f / 0.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.6f / 0.4f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f / 0.5f, new_vector.z()));
}

TEST(Math, vector3f_testing_binary_divide_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector3f test1(6.6f, 3.6f, 2.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.6f / 0.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.6f / 0.2f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f / 0.2f, new_vector.z()));
}

TEST(Math, vector4f_testing_constructor_default)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 0.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 0.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 0.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), 0.0f));
}

TEST(Math, vector4f_testing_constructor_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector4f vec(5.0f, 6.0f, 7.0f, 8.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.y(), 6.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.z(), 7.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.w(), 8.0f));
}

TEST(Math, vector4f_testing_constructor_based_on_struct)
{
	kn_kotek::kn_ktk::kn_math::base_vec4_t data = {5.0f, 6.0f, 7.0f, 8.0f};
	kn_kotek::kn_ktk::kn_math::vector4f vec(data);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.x(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.y(), 6.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.z(), 7.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec.w(), 8.0f));
}

TEST(Math, vector4f_testing_copy_constructor)
{
	kn_kotek::kn_ktk::kn_math::vector4f vec_original(550.5f, 153.2f, 25.25f, 2525.52f);
	kn_kotek::kn_ktk::kn_math::vector4f vec_copy(vec_original);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.x(), vec_copy.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.y(), vec_copy.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.z(), vec_copy.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec_original.w(), vec_copy.w()));
}

TEST(Math, vector4f_testing_assignment_operator_based_on_own_type)
{
	kn_kotek::kn_ktk::kn_math::vector4f some(50.0f, 25.4f, 252.0f, 25215.15f);
	kn_kotek::kn_ktk::kn_math::vector4f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.x(), some2.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.y(), some2.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.z(), some2.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some.w(), some2.w()));
}

TEST(Math, vector4f_testing_assignment_operator_based_on_base_type)
{
	kn_kotek::kn_ktk::kn_math::base_vec4_t some(51.0f, 15.3f, 25.0f, 1511.3f);
	kn_kotek::kn_ktk::kn_math::vector4f some2 = some;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.x(), some.x));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.y(), some.y));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.z(), some.z));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(some2.w(), some.w));
}

TEST(Math, vector4f_testing_setter_single_depth)
{
	kn_kotek::kn_ktk::kn_math::vector4f test;

	test.x() = 105.0f;
	test.y() = 103.0f;
	test.z() = 144.0f;
	test.w() = 1514.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.x(), 105.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.y(), 103.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.z(), 144.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test.w(), 1514.0f));
}

TEST(Math, vector4f_testing_plus_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {3.5f, 2.5f, 351.0f, 151.1f};
	kn_kotek::kn_ktk::kn_math::vector4f test2 = {1.5f, 2.0f, 9.0f, 15.0f};

	test1 += test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (3.5f + 1.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (2.5f + 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (351.0f + 9.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (151.1f + 15.0f)));
}

TEST(Math, vector4f_testing_subtract_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {3.5f, 2.5f, 252.0f, 16.0f};
	kn_kotek::kn_ktk::kn_math::vector4f test2 = {1.5f, 2.0f, 3.0f, 4.0f};

	test1 -= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (3.5f - 1.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (2.5f - 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (252.0f - 3.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (16.0f - 4.0f)));
}

TEST(Math, vector4f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {2.0f, 6.4f, 4.4f, 25.25f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 2.0f * 5.5f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 6.4f * 5.5f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 4.4f * 5.5f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), 25.25f * 5.5f));
}

TEST(Math,
	vector4f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {2.0f, 6.4f, 25.5f, 10.10f};
	kn_kotek::kn_ktk::kn_math::vector4f test2 = {5.5f, 252.1f, 60.4f, 25.0f};

	test1 *= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (2.0f * 5.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (6.4f * 252.1f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (25.5f * 60.4f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (10.10f * 25.0f)));
}

TEST(Math, vector4f_testing_divide_equal_operator_based_on_number_its_scale)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {8.4f, 2.6f, 25.0f, 251.0f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (2.6f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (25.0f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (251.0f / 2.0f)));
}

TEST(Math, vector4f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {8.4f, 3.5f, 5.5f, 251.15f};
	kn_kotek::kn_ktk::kn_math::vector4f test2 = {2.0f, 0.5f, 52.5f, 151.0f};

	test1 /= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (8.4f / 2.0f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (3.5f / 0.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (5.5f / 52.5f)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (251.15f / 151.0f)));
}

TEST(Math, vector4f_testing_modulo_equal_operator_based_on_number)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {4.0f, 6.0f, 8.0f, 151.0f};
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (std::fmod(6.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (std::fmod(8.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (std::fmod(151.0f, 2.0f))));
}

TEST(Math, vector4f_testing_modulo_equal_operator_based_on_vector)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {4.0f, 6.0f, 8.0f, 15.0f};
	kn_kotek::kn_ktk::kn_math::vector4f test2 = {2.0f, 3.0f, 4.0f, 12.0f};

	test1 %= test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), (std::fmod(6.0f, 3.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), (std::fmod(8.0f, 4.0f))));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), (std::fmod(15.0f, 12.0f))));
}

TEST(Math, vector4f_testing_unary_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {10.0f, 5.0f, 15.0f, 151.0f};

	test1 = +test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), 10.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), 5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), 15.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), 151.0f));
}

TEST(Math, vector4f_testing_unary_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1 = {10.0f, 5.0f, 15.0f, 151.0f};

	test1 = -test1;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.x(), -10.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.y(), -5.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.z(), -15.0f));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(test1.w(), -151.0f));
}

TEST(Math, vector4f_testing_comparison_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1;
	kn_kotek::kn_ktk::kn_math::vector4f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector4f_testing_comparison_equal_random)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(
		150.15125f, 1515.1414f, 14.24141f, 1515.3515f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(
		150.15125f, 1515.1414f, 14.24141f, 1515.3515f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector4f_testing_comparison_equal_different_last_field)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(15.3f, 4.4f, 15.15f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(15.0f, 4.4f, 15.15f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_equal_different_first_field)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(15.0f, 4.3f, 15.15f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(15.0f, 4.4f, 15.15f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_equal_different_dirty_last_field)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(15.14152f, 0.0f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(15.14151f, 0.0f, 0.0f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_equal_different_dirty_first_field)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(0.0f, 15.14152f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(0.0f, 15.14151f, 0.0f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_not_equal_zeros)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1;
	kn_kotek::kn_ktk::kn_math::vector4f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_not_equal_different)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(5.0f, 0.0f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(2.0f, 0.0f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector4f_testing_comparison_not_equal_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(151.25151f, 0.0f, 0.0f, 0.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(151.25151f, 0.0f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_not_equal_dirty)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(150.10502f, 0.0f, 1.0f, 2.0f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(150.10509f, 0.0f, 1.0f, 2.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector4f_testing_cast_operator_xmvector)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(150.0f, 151.0f, 153.0f, 164.0f);

	DirectX::XMVECTOR vec = test1;

	float value_x = DirectX::XMVectorGetX(vec);
	float value_y = DirectX::XMVectorGetY(vec);
	float value_z = DirectX::XMVectorGetZ(vec);
	float value_w = DirectX::XMVectorGetW(vec);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_x, test1.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_y, test1.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_z, test1.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(value_w, test1.w()));
}
		#endif

TEST(Math, vector4f_testing_binary_plus_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(50.5f, 2.5f, 3.5f, 252.5f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(5.5f, 0.5f, 2.5f, 6.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(50.5f + 5.5f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f + 0.5f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f + 2.5f, new_vector.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.5f + 252.5f, new_vector.w()));
}

TEST(Math, vector4f_testing_binary_subtract_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(50.5f, 25.0f, 3.5f, 25.5f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(0.5f, 5.0f, 2.5f, 6.0f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(50.5f - 0.5f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f - 5.0f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f - 2.5f, new_vector.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.5f - 6.0f, new_vector.w()));
}

TEST(Math, vector4f_testing_binary_mutiply_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(5.5f, 25.5f, 3.5f, 25.5f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(2.2f, 5.5f, 2.5f, 25.5f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.5f * 2.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.5f * 5.5f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f * 2.5f, new_vector.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.5f * 25.5f, new_vector.w()));
}

TEST(Math, vector4f_testing_binary_multiply_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(5.5f, 2.5f, 3.5f, 15.15f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.5f * 2.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f * 2.2f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f * 2.2f, new_vector.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.15f * 2.2f, new_vector.w()));
}

TEST(Math, vector4f_testing_binary_divide_operator_both_vectors)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(6.6f, 3.6f, 3.5f, 15.5f);
	kn_kotek::kn_ktk::kn_math::vector4f test2(0.2f, 0.4f, 0.5f, 5.0f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.6f / 0.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.6f / 0.4f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.5f / 0.5f, new_vector.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.5f / 5.0f, new_vector.w()));
}

TEST(Math, vector4f_testing_binary_divide_operator_vector_number)
{
	kn_kotek::kn_ktk::kn_math::vector4f test1(6.6f, 3.6f, 2.5f, 151.5f);
	kn_kotek::kn_ktk::kn_math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.6f / 0.2f, new_vector.x()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.6f / 0.2f, new_vector.y()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.5f / 0.2f, new_vector.z()));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(151.5f / 0.2f, new_vector.w()));
}

TEST(Math, matrix4x4f_constructor_values)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_constructor_copy_base_type)
{
	kn_kotek::kn_ktk::kn_math::base_mat4x4_t copy = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(copy);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_constructor_copy_own_type)
{
	kn_kotek::kn_ktk::kn_math::base_mat4x4_t copy(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(copy);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_constructor_default)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(0.0f, test[3][3]));
}

TEST(Math, matrix4x4f_assignment_operator_universal_initialization)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test[3][3]));
}

TEST(Math, matri4x4f_assignment_operator_base_type)
{
	kn_kotek::kn_ktk::kn_math::base_mat4x4_t base = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	kn_kotek::kn_ktk::kn_math::matrix4x4f test = base;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_assignment_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test += {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(17.0f + 1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(18.0f + 2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(19.0f + 3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(20.0f + 4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(21.0f + 5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(22.0f + 6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(23.0f + 7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(24.0f + 8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f + 9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(26.0f + 10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(27.0f + 11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(28.0f + 12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(29.0f + 13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(30.0f + 14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(31.0f + 15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(32.0f + 16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_assignment_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test -= {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(17.0f - 1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(18.0f - 2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(19.0f - 3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(20.0f - 4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(21.0f - 5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(22.0f - 6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(23.0f - 7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(24.0f - 8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f - 9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(26.0f - 10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(27.0f - 11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(28.0f - 12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(29.0f - 13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(30.0f - 14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(31.0f - 15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(32.0f - 16.0f, test[3][3]));
}

// TODO: add overloads for matrix4x3 and other
TEST(Math, matrix4x4f_assignment_multiply_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f copy(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f copy2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	kn_kotek::kn_ktk::kn_math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test *= {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	kn_kotek::kn_ktk::vector<kn_kotek::kn_ktk::kn_math::base_decimal_t> data;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			kn_kotek::kn_ktk::kn_math::base_decimal_t value = 0.0f;

			for (int k = 0; k < 4; ++k)
			{
				value += copy(i, k) * copy2(k, j);
			}

			data.push_back(value);
		}
	}

	kn_kotek::kn_ktk::size_t current_index = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(data[current_index], test(i, j)));
			current_index += 1;
		}
	}
}

TEST(Math, matrix4x4f_assignment_multiply_operator_base_decimal)
{
	kn_kotek::kn_ktk::kn_math::base_decimal_t value = 15.0f;
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test *= value;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f * value, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f * value, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f * value, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f * value, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f * value, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f * value, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f * value, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f * value, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f * value, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f * value, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f * value, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f * value, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f * value, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f * value, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f * value, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f * value, test[3][3]));
}

TEST(Math, matrix4x4f_assignment_divide_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f copy(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f copy2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	kn_kotek::kn_ktk::kn_math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test /= {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_TRUE(
				kn_kotek::kn_ktk::is_equal(copy(i, j) / copy2(i, j), test(i, j)));
		}
	}
}

TEST(Math, matrix4x4f_assignment_divide_operator_decimal)
{
	kn_kotek::kn_ktk::kn_math::base_decimal_t value = 15.0f;
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	kn_kotek::kn_ktk::kn_math::base_decimal_t factor = 1.f / value;

	test /= value;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f * factor, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f * factor, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f * factor, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f * factor, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f * factor, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f * factor, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f * factor, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f * factor, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f * factor, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f * factor, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f * factor, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f * factor, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f * factor, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f * factor, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f * factor, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f * factor, test[3][3]));
}

TEST(Math, matrix4x4f_unary_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test = +test;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_unary_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test = -test;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(-16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_comparison_operator_equal)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(test == test2);
}

TEST(Math, matrix4x4f_comparison_operator_equal_but_one_is_wrong)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, -16.0f);

	EXPECT_TRUE((test == test2) == false);
}

TEST(Math, matrix4x4f_comparison_operator_equal_but_two_is_wrong)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f test2(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE((test == test2) == false);
}

TEST(Math, matrix4x4f_comparison_operator_not_equal)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, -16.0f);

	EXPECT_TRUE(test != test2);
}

TEST(Math, matrix4x4f_comparison_operator_not_equal_two_wrong)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	kn_kotek::kn_ktk::kn_math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		-7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, -15.0f, 16.0f);

	EXPECT_TRUE(test != test2);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, matrix4x4f_cast_operator_xmmatrix)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	DirectX::XMMATRIX casted = test;

	const DirectX::XMVECTOR& vec0 = casted.r[0];
	const DirectX::XMVECTOR& vec1 = casted.r[1];
	const DirectX::XMVECTOR& vec2 = casted.r[2];
	const DirectX::XMVECTOR& vec3 = casted.r[3];

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, DirectX::XMVectorGetX(vec0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, DirectX::XMVectorGetY(vec0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, DirectX::XMVectorGetZ(vec0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, DirectX::XMVectorGetW(vec0)));

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, DirectX::XMVectorGetX(vec1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, DirectX::XMVectorGetY(vec1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, DirectX::XMVectorGetZ(vec1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, DirectX::XMVectorGetW(vec1)));

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, DirectX::XMVectorGetX(vec2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, DirectX::XMVectorGetY(vec2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, DirectX::XMVectorGetZ(vec2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, DirectX::XMVectorGetW(vec2)));

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, DirectX::XMVectorGetX(vec3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, DirectX::XMVectorGetY(vec3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, DirectX::XMVectorGetZ(vec3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, DirectX::XMVectorGetW(vec3)));
}
		#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		#endif

TEST(Math, matrix4x4f_operator_get_element_by_brackets_read_state)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f, test(0, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f, test(0, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f, test(0, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f, test(0, 3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f, test(1, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f, test(1, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f, test(1, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f, test(1, 3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f, test(2, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f, test(2, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f, test(2, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f, test(2, 3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f, test(3, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f, test(3, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f, test(3, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f, test(3, 3)));
}

TEST(Math, matrix4x4f_operator_get_element_by_brackets_write_state)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test(0, 0) = test(0, 0) + 1.0f;
	test(0, 1) = test(0, 1) + 1.0f;
	test(0, 2) = test(0, 2) + 1.0f;
	test(0, 3) = test(0, 3) + 1.0f;
	test(1, 0) = test(1, 0) + 1.0f;
	test(1, 1) = test(1, 1) + 1.0f;
	test(1, 2) = test(1, 2) + 1.0f;
	test(1, 3) = test(1, 3) + 1.0f;
	test(2, 0) = test(2, 0) + 1.0f;
	test(2, 1) = test(2, 1) + 1.0f;
	test(2, 2) = test(2, 2) + 1.0f;
	test(2, 3) = test(2, 3) + 1.0f;
	test(3, 0) = test(3, 0) + 1.0f;
	test(3, 1) = test(3, 1) + 1.0f;
	test(3, 2) = test(3, 2) + 1.0f;
	test(3, 3) = test(3, 3) + 1.0f;

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f + 1.0f, test(0, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f + 1.0f, test(0, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f + 1.0f, test(0, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f + 1.0f, test(0, 3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f + 1.0f, test(1, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f + 1.0f, test(1, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f + 1.0f, test(1, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f + 1.0f, test(1, 3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f + 1.0f, test(2, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f + 1.0f, test(2, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f + 1.0f, test(2, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f + 1.0f, test(2, 3)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f + 1.0f, test(3, 0)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f + 1.0f, test(3, 1)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f + 1.0f, test(3, 2)));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f + 1.0f, test(3, 3)));
}

TEST(Math, matrix4x4f_setters)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test[0][0] = (test[0][0] + 1.0f);
	test[0][1] = (test[0][1] + 1.0f);
	test[0][2] = (test[0][2] + 1.0f);
	test[0][3] = (test[0][3] + 1.0f);
	test[1][0] = (test[1][0] + 1.0f);
	test[1][1] = (test[1][1] + 1.0f);
	test[1][2] = (test[1][2] + 1.0f);
	test[1][3] = (test[1][3] + 1.0f);
	test[2][0] = (test[2][0] + 1.0f);
	test[2][1] = (test[2][1] + 1.0f);
	test[2][2] = (test[2][2] + 1.0f);
	test[2][3] = (test[2][3] + 1.0f);
	test[3][0] = (test[3][0] + 1.0f);
	test[3][1] = (test[3][1] + 1.0f);
	test[3][2] = (test[3][2] + 1.0f);
	test[3][3] = (test[3][3] + 1.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(1.0f + 1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(2.0f + 1.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(3.0f + 1.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(4.0f + 1.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(5.0f + 1.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(6.0f + 1.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(7.0f + 1.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(8.0f + 1.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(9.0f + 1.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(10.0f + 1.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(11.0f + 1.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(12.0f + 1.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(13.0f + 1.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(14.0f + 1.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(15.0f + 1.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(16.0f + 1.0f, test[3][3]));
}

TEST(Math, matrix4x4f_plus_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test = test +
		kn_kotek::kn_ktk::kn_math::matrix4x4f(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
			8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(17.0f + 1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(18.0f + 2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(19.0f + 3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(20.0f + 4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(21.0f + 5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(22.0f + 6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(23.0f + 7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(24.0f + 8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f + 9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(26.0f + 10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(27.0f + 11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(28.0f + 12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(29.0f + 13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(30.0f + 14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(31.0f + 15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(32.0f + 16.0f, test[3][3]));
}

TEST(Math, matrix4x4f_minus_operator)
{
	kn_kotek::kn_ktk::kn_math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test = test -
		kn_kotek::kn_ktk::kn_math::matrix4x4f(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
			8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(17.0f - 1.0f, test[0][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(18.0f - 2.0f, test[0][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(19.0f - 3.0f, test[0][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(20.0f - 4.0f, test[0][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(21.0f - 5.0f, test[1][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(22.0f - 6.0f, test[1][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(23.0f - 7.0f, test[1][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(24.0f - 8.0f, test[1][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(25.0f - 9.0f, test[2][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(26.0f - 10.0f, test[2][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(27.0f - 11.0f, test[2][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(28.0f - 12.0f, test[2][3]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(29.0f - 13.0f, test[3][0]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(30.0f - 14.0f, test[3][1]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(31.0f - 15.0f, test[3][2]));
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(32.0f - 16.0f, test[3][3]));
}

TEST(Math, vector1f_constructors)
{
	kn_kotek::kn_ktk::kn_math::vector1f vec1(10.0f, 5.0f, 1.0f, -1.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec1.x(), 10.0f));

	kn_kotek::kn_ktk::kn_math::vector1f vec2(5.0f, -1.0f, 2.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec2.x(), 5.0f));

	kn_kotek::kn_ktk::kn_math::vector1f vec3(2.212f, 141.1f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec3.x(), 2.212f));

	kn_kotek::kn_ktk::kn_math::vector1f vec4(1241.1414f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec4.x(), 1241.1414f));

	float arr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	float arr3[3] = {1.310f, 11.1f, 3113.0f};
	float arr2[2] = {3113.0f, 1.310f};
	float arr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector1f vec5(arr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec5.x(), 11.1f));

	kn_kotek::kn_ktk::kn_math::vector1f vec6(arr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec6.x(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector1f vec7(arr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec7.x(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector1f vec8(arr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec8.x(), -13.0f));

	kn_kotek::kn_ktk::kn_math::vector1f vec9(&arr1[0]);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec9.x(), -13.0f));

	float* p_val = nullptr;
	float val = 3.11f;
	p_val = &val;

	kn_kotek::kn_ktk::kn_math::vector1f vec10(p_val);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec10.x(), 3.11f));

	const float carr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	const float carr3[3] = {1.310f, 11.1f, 3113.0f};
	const float carr2[2] = {3113.0f, 1.310f};
	const float carr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector1f vec11(carr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec11.x(), 11.1f));

	kn_kotek::kn_ktk::kn_math::vector1f vec12(carr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec12.x(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector1f vec13(carr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec13.x(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector1f vec14(carr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec14.x(), -13.0f));
}

TEST(Math, vector2f_contsructors)
{
	kn_kotek::kn_ktk::kn_math::vector2f vec1(10.0f, 5.0f, 1.0f, -1.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec1.x(), 10.0f) &&
		kn_kotek::kn_ktk::is_equal(vec1.y(), 5.0f));

	kn_kotek::kn_ktk::kn_math::vector2f vec2(5.0f, -1.0f, 2.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec2.x(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec2.y(), -1.0f));

	kn_kotek::kn_ktk::kn_math::vector2f vec3(2.212f, 141.1f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec3.x(), 2.212f) &&
		kn_kotek::kn_ktk::is_equal(vec3.y(), 141.1f));

	kn_kotek::kn_ktk::kn_math::vector2f vec4(1241.1414f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec4.x(), 1241.1414f) &&
		kn_kotek::kn_ktk::is_equal(vec4.y(), 0.0f));

	float arr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	float arr3[3] = {1.310f, 11.1f, 3113.0f};
	float arr2[2] = {3113.0f, 1.310f};
	float arr1[1] = {-13.0f};

	kn_kotek::kn_ktk::kn_math::vector2f vec5(arr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec5.x(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec5.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector2f vec6(arr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec6.x(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec6.y(), 11.1f));

	kn_kotek::kn_ktk::kn_math::vector2f vec7(arr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec7.x(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec7.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector2f vec8(arr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec8.x(), -13.0f));

	kn_kotek::kn_ktk::kn_math::vector2f vec9(&arr1[0]);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec9.x(), -13.0f));

	float* p_val = nullptr;
	float val = 3.11f;
	p_val = &val;

	kn_kotek::kn_ktk::kn_math::vector2f vec10(p_val);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec10.x(), 3.11f));

	const float carr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	const float carr3[3] = {1.310f, 11.1f, 3113.0f};
	const float carr2[2] = {3113.0f, 1.310f};
	const float carr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector2f vec11(carr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec11.x(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec11.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector2f vec12(carr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec12.x(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec12.y(), 11.1f));

	kn_kotek::kn_ktk::kn_math::vector2f vec13(carr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec13.x(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec13.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector2f vec14(carr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec14.x(), -13.0f));
}

TEST(Math, vector3f_constructors)
{
	kn_kotek::kn_ktk::kn_math::vector3f vec1(10.0f, 5.0f, 1.0f, -1.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec1.x(), 10.0f) &&
		kn_kotek::kn_ktk::is_equal(vec1.y(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec1.z(), 1.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec2(5.0f, -1.0f, 2.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec2.x(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec2.y(), -1.0f) &&
		kn_kotek::kn_ktk::is_equal(vec2.z(), 2.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec3(2.212f, 141.1f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec3.x(), 2.212f) &&
		kn_kotek::kn_ktk::is_equal(vec3.y(), 141.1f) &&
		kn_kotek::kn_ktk::is_equal(vec3.z(), 0.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec4(1241.1414f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec4.x(), 1241.1414f) &&
		kn_kotek::kn_ktk::is_equal(vec4.y(), 0.0f) &&
		kn_kotek::kn_ktk::is_equal(vec4.z(), 0.0f));

	float arr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	float arr3[3] = {1.310f, 11.1f, 3113.0f};
	float arr2[2] = {3113.0f, 1.310f};
	float arr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector3f vec5(arr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec5.x(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec5.y(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec5.z(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec6(arr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec6.x(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec6.y(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec6.z(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec7(arr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec7.x(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec7.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector3f vec8(arr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec8.x(), -13.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec9(&arr1[0]);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec9.x(), -13.0f));

	float* p_val = nullptr;
	float val = 3.11f;
	p_val = &val;

	kn_kotek::kn_ktk::kn_math::vector3f vec10(p_val);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec10.x(), 3.11f));

	const float carr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	const float carr3[3] = {1.310f, 11.1f, 3113.0f};
	const float carr2[2] = {3113.0f, 1.310f};
	const float carr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector3f vec11(carr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec11.x(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec11.y(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec11.z(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec12(carr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec12.x(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec12.y(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec12.z(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector3f vec13(carr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec13.x(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec13.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector3f vec14(carr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec14.x(), -13.0f));
}

TEST(Math, vector4f_constructors)
{
	kn_kotek::kn_ktk::kn_math::vector4f vec1(10.0f, 5.0f, 1.0f, -1.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec1.x(), 10.0f) &&
		kn_kotek::kn_ktk::is_equal(vec1.y(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec1.z(), 1.0f) &&
		kn_kotek::kn_ktk::is_equal(vec1.w(), -1.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec2(5.0f, -1.0f, 2.0f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec2.x(), 5.0f) &&
		kn_kotek::kn_ktk::is_equal(vec2.y(), -1.0f) &&
		kn_kotek::kn_ktk::is_equal(vec2.z(), 2.0f) &&
		kn_kotek::kn_ktk::is_equal(vec2.w(), 0.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec3(2.212f, 141.1f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec3.x(), 2.212f) &&
		kn_kotek::kn_ktk::is_equal(vec3.y(), 141.1f) &&
		kn_kotek::kn_ktk::is_equal(vec3.z(), 0.0f) &&
		kn_kotek::kn_ktk::is_equal(vec3.w(), 0.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec4(1241.1414f);

	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec4.x(), 1241.1414f) &&
		kn_kotek::kn_ktk::is_equal(vec4.y(), 0.0f) &&
		kn_kotek::kn_ktk::is_equal(vec4.z(), 0.0f) &&
		kn_kotek::kn_ktk::is_equal(vec4.w(), 0.0f));

	float arr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	float arr3[3] = {1.310f, 11.1f, 3113.0f};
	float arr2[2] = {3113.0f, 1.310f};
	float arr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector4f vec5(arr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec5.x(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec5.y(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec5.z(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec5.w(), -13.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec6(arr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec6.x(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec6.y(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec6.z(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec7(arr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec7.x(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec7.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector4f vec8(arr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec8.x(), -13.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec9(&arr1[0]);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec9.x(), -13.0f));

	float* p_val = nullptr;
	float val = 3.11f;
	p_val = &val;

	kn_kotek::kn_ktk::kn_math::vector4f vec10(p_val);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec10.x(), 3.11f));

	const float carr4[4] = {11.1f, 1.310f, 3113.0f, -13.0f};
	const float carr3[3] = {1.310f, 11.1f, 3113.0f};
	const float carr2[2] = {3113.0f, 1.310f};
	const float carr1[1] = {
		-13.0f,
	};

	kn_kotek::kn_ktk::kn_math::vector4f vec11(carr4);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec11.x(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec11.y(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec11.z(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec11.w(), -13.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec12(carr3);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec12.x(), 1.310f) &&
		kn_kotek::kn_ktk::is_equal(vec12.y(), 11.1f) &&
		kn_kotek::kn_ktk::is_equal(vec12.z(), 3113.0f));

	kn_kotek::kn_ktk::kn_math::vector4f vec13(carr2);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec13.x(), 3113.0f) &&
		kn_kotek::kn_ktk::is_equal(vec13.y(), 1.310f));

	kn_kotek::kn_ktk::kn_math::vector4f vec14(carr1);
	EXPECT_TRUE(kn_kotek::kn_ktk::is_equal(vec14.x(), -13.0f));
}

	#endif
#endif

void RegisterTests_Math_ForModule_Core()
{
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
