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

	EXPECT_TRUE(Kotek::ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_must_be_equal)
{
	float test1 = 15.1515f;
	float test2 = 15.1515f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1, test2) == true);
}

TEST(Math, equal_function_for_floats_really_close_but_not_equal)
{
	float test1 = 15.151514f;
	float test2 = 15.151513f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_digits)
{
	float test1 = 0.000300f;
	float test2 = 0.000301f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_zeros)
{
	float test1 = 0.0f;
	float test2 = 0.0f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1, test2) == true);
}

TEST(Math, equal_function_for_floats_really_low)
{
	float test1 = 0.000002f;
	float test2 = 0.000001f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1, test2) == false);
}

TEST(Math, equal_function_for_floats_when_we_sum)
{
	float test1 = 3.0f;
	float test2 = 6.0f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1 + test2, 9.0f) == true);
}

TEST(Math, equal_function_for_floats_when_we_sum_dirty)
{
	float test1 = 3.5151f;
	float test2 = 2.521f;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1 + test2, 6.03f) == false);
}

TEST(Math, vector1f_testing_constructor_default)
{
	Kotek::ktk::math::vector1f test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
}

TEST(Math, vector1f_testing_constructor_based_on_number)
{
	Kotek::ktk::math::vector1f vec(5.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
}

		#ifdef KOTEK_USE_MATH_LIBRARY_GLM
TEST(Math, vector1f_testing_constructor_based_on_struct) {}
		#endif

TEST(Math, vector1f_testing_copy_constructor)
{
	Kotek::ktk::math::vector1f vec_original(550.5f);
	Kotek::ktk::math::vector1f vec_copy(vec_original);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()));
}

TEST(Math, vector1f_testing_assignment_operator_based_on_own_type)
{
	Kotek::ktk::math::vector1f some(50.0f);
	Kotek::ktk::math::vector1f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()));
}

TEST(Math, vector1f_testing_assignment_operator_based_on_base_type)
{
	Kotek::ktk::math::base_vec1_t some(51.0f);
	Kotek::ktk::math::vector1f some2 = some;

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_X(), some));
		#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_X(), some.x));
		#endif
}

TEST(Math, vector1f_testing_setter_single_depth)
{
	Kotek::ktk::math::vector1f test;

	test.Set_X(105.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_X(), 105.0f));
}

TEST(Math, vector1f_testing_setter_two_depth)
{
	Kotek::ktk::math::vector1f test2;

	test2.Set_X(50.0f).Set_X(150.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_X(), 150.0f));
}

TEST(Math, vector1f_testing_plus_equal_operator_based_on_number)
{
	Kotek::ktk::math::vector1f test1 = 3.5f;
	Kotek::ktk::math::base_decimal_t test2 = 5.5f;

	test1 += test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 9.0f));
}

TEST(Math, vector1f_testing_plus_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector1f test1 = 3.5f;
	Kotek::ktk::math::vector1f test2 = 5.5f;

	test1 += test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 9.0f));
}

TEST(Math, vector1f_testing_subtract_equal_operator_based_on_number)
{
	Kotek::ktk::math::vector1f test1 = 5.5f;
	Kotek::ktk::math::base_decimal_t test2 = 3.5f;

	test1 -= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 2.0f));
}

TEST(Math, vector1f_testing_subtract_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector1f test1 = 5.5f;
	Kotek::ktk::math::vector1f test2 = 3.5f;

	test1 -= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 2.0f));
}

TEST(Math, vector1f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector1f test1 = 3.2f;
	Kotek::ktk::math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 17.6f));
}

TEST(Math,
	vector1f_testing_multiply_equal_operator_based_on_vector_its_per_compunent_multiply)
{
	Kotek::ktk::math::vector1f test1 = 3.2f;
	Kotek::ktk::math::vector1f test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 17.6f));
}

TEST(Math, vector1f_testing_divide_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector1f test1 = 8.4f;
	Kotek::ktk::math::base_decimal_t test2 = 2.6f;

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.6f)));
}

TEST(Math, vector1f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	Kotek::ktk::math::vector1f test1 = 8.4f;
	Kotek::ktk::math::vector1f test2 = 2.6f;

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.6f)));
}

TEST(Math, vector1f_testing_modulo_equal_operator_based_on_number)
{
	Kotek::ktk::math::vector1f test1 = 5.3f;
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(5.3f, 2.0f))));
}

TEST(Math, vector1f_testing_modulo_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector1f test1 = 5.3f;
	Kotek::ktk::math::vector1f test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(5.3f, 2.0f))));
}

TEST(Math, vector1f_testing_unary_plus_operator)
{
	Kotek::ktk::math::vector1f test1 = 10.0f;

	test1 = +test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
}

TEST(Math, vector1f_testing_unary_minus_operator)
{
	Kotek::ktk::math::vector1f test1 = 10.0f;

	test1 = -test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
}

TEST(Math, vector1f_testing_comparison_equal_zeros)
{
	Kotek::ktk::math::vector1f test1;
	Kotek::ktk::math::vector1f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector1f_testing_comparison_equal_random)
{
	Kotek::ktk::math::vector1f test1(150.15125f);
	Kotek::ktk::math::vector1f test2(150.15125f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector1f_testing_comparison_equal_different)
{
	Kotek::ktk::math::vector1f test1(15.3f);
	Kotek::ktk::math::vector1f test2(15.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_equal_different_dirty)
{
	Kotek::ktk::math::vector1f test1(15.14152f);
	Kotek::ktk::math::vector1f test2(15.14151f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_not_equal_zeros)
{
	Kotek::ktk::math::vector1f test1;
	Kotek::ktk::math::vector1f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_not_equal_different)
{
	Kotek::ktk::math::vector1f test1(5.0f);
	Kotek::ktk::math::vector1f test2(2.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector1f_testing_comparison_not_equal_equal_dirty)
{
	Kotek::ktk::math::vector1f test1(151.25151f);
	Kotek::ktk::math::vector1f test2(151.25151f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector1f_testing_comparison_not_equal_dirty)
{
	Kotek::ktk::math::vector1f test1(150.10502f);
	Kotek::ktk::math::vector1f test2(150.10509f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector1f_testing_cast_operator_xmvector)
{
	Kotek::ktk::math::vector1f test1(150.0f);

	DirectX::XMVECTOR vec = test1;

	float value = DirectX::XMVectorGetX(vec);

	EXPECT_TRUE(Kotek::ktk::is_equal(value, test1.Get_X()));
}
		#endif

TEST(Math, vector1f_testing_binary_plus_operator_both_vectors)
{
	Kotek::ktk::math::vector1f test1(50.5f);
	Kotek::ktk::math::vector1f test2(5.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(new_vector == 56.0f);
}

TEST(Math, vector1f_testing_binary_plus_operator_vector_number)
{
	Kotek::ktk::math::vector1f test1(50.5f);
	Kotek::ktk::math::base_decimal_t test2(5.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(new_vector == 56.0f);
}

TEST(Math, vector1f_testing_binary_subtract_operator_both_vectors)
{
	Kotek::ktk::math::vector1f test1(50.5f);
	Kotek::ktk::math::vector1f test2(0.5f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(new_vector == 50.0f);
}

TEST(Math, vector1f_testing_binary_subtract_operator_vector_number)
{
	Kotek::ktk::math::vector1f test1(50.5f);
	Kotek::ktk::math::base_decimal_t test2(0.5f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(new_vector == 50.0f);
}

TEST(Math, vector1f_testing_binary_mutiply_operator_both_vectors)
{
	Kotek::ktk::math::vector1f test1(5.5f);
	Kotek::ktk::math::vector1f test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(new_vector == 12.1f);
}

TEST(Math, vector1f_testing_binary_multiply_operator_vector_number)
{
	Kotek::ktk::math::vector1f test1(5.5f);
	Kotek::ktk::math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(new_vector == 12.1f);
}

TEST(Math, vector1f_testing_binary_divide_operator_both_vectors)
{
	Kotek::ktk::math::vector1f test1(6.6f);
	Kotek::ktk::math::vector1f test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(new_vector == 33.0f);
}

TEST(Math, vector1f_testing_binary_divide_operator_vector_number)
{
	Kotek::ktk::math::vector1f test1(6.6f);
	Kotek::ktk::math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(new_vector == 33.0f);
}

TEST(Math, vector2f_testing_constructor_default)
{
	Kotek::ktk::math::vector2f test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
}

TEST(Math, vector2f_testing_constructor_based_on_number)
{
	Kotek::ktk::math::vector2f vec(5.0f, 6.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f) &&
		Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
}

TEST(Math, vector2f_testing_constructor_based_on_struct)
{
	Kotek::ktk::math::base_vec2_t data = {5.0f, 6.0f};
	Kotek::ktk::math::vector2f vec(data);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f) &&
		Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
}

TEST(Math, vector2f_testing_copy_constructor)
{
	Kotek::ktk::math::vector2f vec_original(550.5f, 153.2f);
	Kotek::ktk::math::vector2f vec_copy(vec_original);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()) &&
		Kotek::ktk::is_equal(vec_original.Get_Y(), vec_copy.Get_Y()));
}

TEST(Math, vector2f_testing_assignment_operator_based_on_own_type)
{
	Kotek::ktk::math::vector2f some(50.0f, 25.4f);
	Kotek::ktk::math::vector2f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()) &&
		Kotek::ktk::is_equal(some.Get_Y(), some2.Get_Y()));
}

TEST(Math, vector2f_testing_assignment_operator_based_on_base_type)
{
	Kotek::ktk::math::base_vec2_t some(51.0f, 15.3f);
	Kotek::ktk::math::vector2f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_X(), some.x) &&
		Kotek::ktk::is_equal(some2.Get_Y(), some.y));
}

TEST(Math, vector2f_testing_setter_single_depth)
{
	Kotek::ktk::math::vector2f test;

	test.Set_X(105.0f);
	test.Set_Y(103.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_X(), 105.0f) &&
		Kotek::ktk::is_equal(test.Get_Y(), 103.0f));
}

TEST(Math, vector2f_testing_setter_two_depth)
{
	Kotek::ktk::math::vector2f test2;

	test2.Set_X(50.0f).Set_X(150.0f);
	test2.Set_Y(151.3f).Set_Y(425.25f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_X(), 150.0f) &&
		Kotek::ktk::is_equal(test2.Get_Y(), 425.25f));
}

TEST(Math, vector2f_testing_plus_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector2f test1 = {3.5f, 2.5f};
	Kotek::ktk::math::vector2f test2 = {1.5f, 2.0f};

	test1 += test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 5.0f) &&
		Kotek::ktk::is_equal(test1.Get_Y(), 4.5f));
}

TEST(Math, vector2f_testing_subtract_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector2f test1 = {3.5f, 2.5f};
	Kotek::ktk::math::vector2f test2 = {1.5f, 2.0f};

	test1 -= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 2.0f) &&
		Kotek::ktk::is_equal(test1.Get_Y(), 0.5f));
}

TEST(Math, vector2f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector2f test1 = {2.0f, 6.4f};
	Kotek::ktk::math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 11.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 35.2f));
}

TEST(Math,
	vector2f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
{
	Kotek::ktk::math::vector2f test1 = {2.0f, 6.4f};
	Kotek::ktk::math::vector2f test2 = {5.5f, 252.1f};

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 11.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (6.4f * 252.1f)));
}

TEST(Math, vector2f_testing_divide_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector2f test1 = {8.4f, 2.6f};
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (2.6f / 2.0f)));
}

TEST(Math, vector2f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	Kotek::ktk::math::vector2f test1 = {8.4f, 3.5f};
	Kotek::ktk::math::vector2f test2 = {2.0f, 0.5f};

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (3.5f / 0.5f)));
}

TEST(Math, vector2f_testing_modulo_equal_operator_based_on_number)
{
	Kotek::ktk::math::vector2f test1 = {4.0f, 6.0f};
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 2.0f))));
}

TEST(Math, vector2f_testing_modulo_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector2f test1 = {4.0f, 6.0f};
	Kotek::ktk::math::vector2f test2 = {2.0f, 3.0f};

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 3.0f))));
}

TEST(Math, vector2f_testing_unary_plus_operator)
{
	Kotek::ktk::math::vector2f test1 = {10.0f, 5.0f};

	test1 = +test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 5.0f));
}

TEST(Math, vector2f_testing_unary_minus_operator)
{
	Kotek::ktk::math::vector2f test1 = {10.0f, 5.0f};

	test1 = -test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), -5.0f));
}

TEST(Math, vector2f_testing_comparison_equal_zeros)
{
	Kotek::ktk::math::vector2f test1;
	Kotek::ktk::math::vector2f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector2f_testing_comparison_equal_random)
{
	Kotek::ktk::math::vector2f test1(150.15125f, 1515.1414f);
	Kotek::ktk::math::vector2f test2(150.15125f, 1515.1414f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector2f_testing_comparison_equal_different_last_field)
{
	Kotek::ktk::math::vector2f test1(15.3f, 4.4f);
	Kotek::ktk::math::vector2f test2(15.0f, 4.4f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_equal_different_first_field)
{
	Kotek::ktk::math::vector2f test1(15.0f, 4.3f);
	Kotek::ktk::math::vector2f test2(15.0f, 4.4f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_equal_different_dirty_last_field)
{
	Kotek::ktk::math::vector2f test1(15.14152f, 0.0f);
	Kotek::ktk::math::vector2f test2(15.14151f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_equal_different_dirty_first_field)
{
	Kotek::ktk::math::vector2f test1(0.0f, 15.14152f);
	Kotek::ktk::math::vector2f test2(0.0f, 15.14151f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_not_equal_zeros)
{
	Kotek::ktk::math::vector2f test1;
	Kotek::ktk::math::vector2f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_not_equal_different)
{
	Kotek::ktk::math::vector2f test1(5.0f, 0.0f);
	Kotek::ktk::math::vector2f test2(2.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector2f_testing_comparison_not_equal_equal_dirty)
{
	Kotek::ktk::math::vector2f test1(151.25151f, 0.0f);
	Kotek::ktk::math::vector2f test2(151.25151f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector2f_testing_comparison_not_equal_dirty)
{
	Kotek::ktk::math::vector2f test1(150.10502f, 0.0f);
	Kotek::ktk::math::vector2f test2(150.10509f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector2f_testing_cast_operator_xmvector)
{
	Kotek::ktk::math::vector2f test1(150.0f, 151.0f);

	DirectX::XMVECTOR vec = test1;

	float value_x = DirectX::XMVectorGetX(vec);
	float value_y = DirectX::XMVectorGetY(vec);

	EXPECT_TRUE(Kotek::ktk::is_equal(value_x, test1.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(value_y, test1.Get_Y()));
}
		#endif

TEST(Math, vector2f_testing_binary_plus_operator_both_vectors)
{
	Kotek::ktk::math::vector2f test1(50.5f, 2.5f);
	Kotek::ktk::math::vector2f test2(5.5f, 0.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(50.5f + 5.5f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f + 0.5f, new_vector.Get_Y()));
}

TEST(Math, vector2f_testing_binary_subtract_operator_both_vectors)
{
	Kotek::ktk::math::vector2f test1(50.5f, 25.0f);
	Kotek::ktk::math::vector2f test2(0.5f, 5.0f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(50.5f - 0.5f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f - 5.0f, new_vector.Get_Y()));
}

TEST(Math, vector2f_testing_binary_mutiply_operator_both_vectors)
{
	Kotek::ktk::math::vector2f test1(5.5f, 25.5f);
	Kotek::ktk::math::vector2f test2(2.2f, 5.5f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.5f * 5.5f, new_vector.Get_Y()));
}

TEST(Math, vector2f_testing_binary_multiply_operator_vector_number)
{
	Kotek::ktk::math::vector2f test1(5.5f, 2.5f);
	Kotek::ktk::math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f * 2.2f, new_vector.Get_Y()));
}

TEST(Math, vector2f_testing_binary_divide_operator_both_vectors)
{
	Kotek::ktk::math::vector2f test1(6.6f, 3.6f);
	Kotek::ktk::math::vector2f test2(0.2f, 0.4f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.6f / 0.4f, new_vector.Get_Y()));
}

TEST(Math, vector2f_testing_binary_divide_operator_vector_number)
{
	Kotek::ktk::math::vector2f test1(6.6f, 3.6f);
	Kotek::ktk::math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.6f / 0.2f, new_vector.Get_Y()));
}

TEST(Math, vector3f_testing_constructor_default)
{
	Kotek::ktk::math::vector3f test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 0.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 0.0f));
}

TEST(Math, vector3f_testing_constructor_based_on_number)
{
	Kotek::ktk::math::vector3f vec(5.0f, 6.0f, 7.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
}

TEST(Math, vector3f_testing_constructor_based_on_struct)
{
	Kotek::ktk::math::base_vec3_t data = {5.0f, 6.0f, 7.0f};
	Kotek::ktk::math::vector3f vec(data);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
}

TEST(Math, vector3f_testing_copy_constructor)
{
	Kotek::ktk::math::vector3f vec_original(550.5f, 153.2f, 25.25f);
	Kotek::ktk::math::vector3f vec_copy(vec_original);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_Y(), vec_copy.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_Z(), vec_copy.Get_Z()));
}

TEST(Math, vector3f_testing_assignment_operator_based_on_own_type)
{
	Kotek::ktk::math::vector3f some(50.0f, 25.4f, 252.0f);
	Kotek::ktk::math::vector3f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_Y(), some2.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_Z(), some2.Get_Z()));
}

TEST(Math, vector3f_testing_assignment_operator_based_on_base_type)
{
	Kotek::ktk::math::base_vec3_t some(51.0f, 15.3f, 25.0f);
	Kotek::ktk::math::vector3f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_X(), some.x));
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_Y(), some.y));
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_Z(), some.z));
}

TEST(Math, vector3f_testing_setter_single_depth)
{
	Kotek::ktk::math::vector3f test;

	test.Set_X(105.0f);
	test.Set_Y(103.0f);
	test.Set_Z(144.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_X(), 105.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_Y(), 103.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_Z(), 144.0f));
}

TEST(Math, vector3f_testing_setter_two_depth)
{
	Kotek::ktk::math::vector3f test2;

	test2.Set_X(50.0f).Set_X(150.0f);
	test2.Set_Y(151.3f).Set_Y(425.25f);
	test2.Set_Z(131.3f).Set_Z(325.25f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_X(), 150.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_Y(), 425.25f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_Z(), 325.25f));
}

TEST(Math, vector3f_testing_plus_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector3f test1 = {3.5f, 2.5f, 351.0f};
	Kotek::ktk::math::vector3f test2 = {1.5f, 2.0f, 9.0f};

	test1 += test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 4.5f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 360.0f));
}

TEST(Math, vector3f_testing_subtract_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector3f test1 = {3.5f, 2.5f, 252.0f};
	Kotek::ktk::math::vector3f test2 = {1.5f, 2.0f, 3.0f};

	test1 -= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 2.0f) &&
		Kotek::ktk::is_equal(test1.Get_Y(), 0.5f));
}

TEST(Math, vector3f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector3f test1 = {2.0f, 6.4f, 4.4f};
	Kotek::ktk::math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 2.0f * 5.5f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 6.4f * 5.5f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 4.4f * 5.5f));
}

TEST(Math,
	vector3f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
{
	Kotek::ktk::math::vector3f test1 = {2.0f, 6.4f, 25.5f};
	Kotek::ktk::math::vector3f test2 = {5.5f, 252.1f, 60.4f};

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (2.0f * 5.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (6.4f * 252.1f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (25.5f * 60.4f)));
}

TEST(Math, vector3f_testing_divide_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector3f test1 = {8.4f, 2.6f, 25.0f};
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (2.6f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (25.0f / 2.0f)));
}

TEST(Math, vector3f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	Kotek::ktk::math::vector3f test1 = {8.4f, 3.5f, 5.5f};
	Kotek::ktk::math::vector3f test2 = {2.0f, 0.5f, 52.5f};

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (3.5f / 0.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (5.5f / 52.5f)));
}

TEST(Math, vector3f_testing_modulo_equal_operator_based_on_number)
{
	Kotek::ktk::math::vector3f test1 = {4.0f, 6.0f, 8.0f};
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 2.0f))));
}

TEST(Math, vector3f_testing_modulo_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector3f test1 = {4.0f, 6.0f, 8.0f};
	Kotek::ktk::math::vector3f test2 = {2.0f, 3.0f, 4.0f};

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 3.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 4.0f))));
}

TEST(Math, vector3f_testing_unary_plus_operator)
{
	Kotek::ktk::math::vector3f test1 = {10.0f, 5.0f, 15.0f};

	test1 = +test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 15.0f));
}

TEST(Math, vector3f_testing_unary_minus_operator)
{
	Kotek::ktk::math::vector3f test1 = {10.0f, 5.0f, 15.0f};

	test1 = -test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), -5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), -15.0f));
}

TEST(Math, vector3f_testing_comparison_equal_zeros)
{
	Kotek::ktk::math::vector3f test1;
	Kotek::ktk::math::vector3f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector3f_testing_comparison_equal_random)
{
	Kotek::ktk::math::vector3f test1(150.15125f, 1515.1414f, 14.24141f);
	Kotek::ktk::math::vector3f test2(150.15125f, 1515.1414f, 14.24141f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector3f_testing_comparison_equal_different_last_field)
{
	Kotek::ktk::math::vector3f test1(15.3f, 4.4f, 15.15f);
	Kotek::ktk::math::vector3f test2(15.0f, 4.4f, 15.15f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_equal_different_first_field)
{
	Kotek::ktk::math::vector3f test1(15.0f, 4.3f, 15.15f);
	Kotek::ktk::math::vector3f test2(15.0f, 4.4f, 15.15f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_equal_different_dirty_last_field)
{
	Kotek::ktk::math::vector3f test1(15.14152f, 0.0f, 0.0f);
	Kotek::ktk::math::vector3f test2(15.14151f, 0.0f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_equal_different_dirty_first_field)
{
	Kotek::ktk::math::vector3f test1(0.0f, 15.14152f, 0.0f);
	Kotek::ktk::math::vector3f test2(0.0f, 15.14151f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_not_equal_zeros)
{
	Kotek::ktk::math::vector3f test1;
	Kotek::ktk::math::vector3f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_not_equal_different)
{
	Kotek::ktk::math::vector3f test1(5.0f, 0.0f, 0.0f);
	Kotek::ktk::math::vector3f test2(2.0f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector3f_testing_comparison_not_equal_equal_dirty)
{
	Kotek::ktk::math::vector3f test1(151.25151f, 0.0f, 0.0f);
	Kotek::ktk::math::vector3f test2(151.25151f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector3f_testing_comparison_not_equal_dirty)
{
	Kotek::ktk::math::vector3f test1(150.10502f, 0.0f, 1.0f);
	Kotek::ktk::math::vector3f test2(150.10509f, 0.0f, 1.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector3f_testing_cast_operator_xmvector)
{
	Kotek::ktk::math::vector3f test1(150.0f, 151.0f, 153.0f);

	DirectX::XMVECTOR vec = test1;

	float value_x = DirectX::XMVectorGetX(vec);
	float value_y = DirectX::XMVectorGetY(vec);
	float value_z = DirectX::XMVectorGetZ(vec);

	EXPECT_TRUE(Kotek::ktk::is_equal(value_x, test1.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(value_y, test1.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(value_z, test1.Get_Z()));
}
		#endif

TEST(Math, vector3f_testing_binary_plus_operator_both_vectors)
{
	Kotek::ktk::math::vector3f test1(50.5f, 2.5f, 3.5f);
	Kotek::ktk::math::vector3f test2(5.5f, 0.5f, 2.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(50.5f + 5.5f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f + 0.5f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f + 2.5f, new_vector.Get_Z()));
}

TEST(Math, vector3f_testing_binary_subtract_operator_both_vectors)
{
	Kotek::ktk::math::vector3f test1(50.5f, 25.0f, 3.5f);
	Kotek::ktk::math::vector3f test2(0.5f, 5.0f, 2.5f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(50.5f - 0.5f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f - 5.0f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f - 2.5f, new_vector.Get_Z()));
}

TEST(Math, vector3f_testing_binary_mutiply_operator_both_vectors)
{
	Kotek::ktk::math::vector3f test1(5.5f, 25.5f, 3.5f);
	Kotek::ktk::math::vector3f test2(2.2f, 5.5f, 2.5f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.5f * 5.5f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f * 2.5f, new_vector.Get_Z()));
}

TEST(Math, vector3f_testing_binary_multiply_operator_vector_number)
{
	Kotek::ktk::math::vector3f test1(5.5f, 2.5f, 3.5f);
	Kotek::ktk::math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f * 2.2f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f * 2.2f, new_vector.Get_Z()));
}

TEST(Math, vector3f_testing_binary_divide_operator_both_vectors)
{
	Kotek::ktk::math::vector3f test1(6.6f, 3.6f, 3.5f);
	Kotek::ktk::math::vector3f test2(0.2f, 0.4f, 0.5f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.6f / 0.4f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f / 0.5f, new_vector.Get_Z()));
}

TEST(Math, vector3f_testing_binary_divide_operator_vector_number)
{
	Kotek::ktk::math::vector3f test1(6.6f, 3.6f, 2.5f);
	Kotek::ktk::math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.6f / 0.2f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f / 0.2f, new_vector.Get_Z()));
}

TEST(Math, vector4f_testing_constructor_default)
{
	Kotek::ktk::math::vector4f test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 0.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 0.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), 0.0f));
}

TEST(Math, vector4f_testing_constructor_based_on_number)
{
	Kotek::ktk::math::vector4f vec(5.0f, 6.0f, 7.0f, 8.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_W(), 8.0f));
}

TEST(Math, vector4f_testing_constructor_based_on_struct)
{
	Kotek::ktk::math::base_vec4_t data = {5.0f, 6.0f, 7.0f, 8.0f};
	Kotek::ktk::math::vector4f vec(data);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec.Get_W(), 8.0f));
}

TEST(Math, vector4f_testing_copy_constructor)
{
	Kotek::ktk::math::vector4f vec_original(550.5f, 153.2f, 25.25f, 2525.52f);
	Kotek::ktk::math::vector4f vec_copy(vec_original);

	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_Y(), vec_copy.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_Z(), vec_copy.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(vec_original.Get_W(), vec_copy.Get_W()));
}

TEST(Math, vector4f_testing_assignment_operator_based_on_own_type)
{
	Kotek::ktk::math::vector4f some(50.0f, 25.4f, 252.0f, 25215.15f);
	Kotek::ktk::math::vector4f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_Y(), some2.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_Z(), some2.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(some.Get_W(), some2.Get_W()));
}

TEST(Math, vector4f_testing_assignment_operator_based_on_base_type)
{
	Kotek::ktk::math::base_vec4_t some(51.0f, 15.3f, 25.0f, 1511.3f);
	Kotek::ktk::math::vector4f some2 = some;

	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_X(), some.x));
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_Y(), some.y));
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_Z(), some.z));
	EXPECT_TRUE(Kotek::ktk::is_equal(some2.Get_W(), some.w));
}

TEST(Math, vector4f_testing_setter_single_depth)
{
	Kotek::ktk::math::vector4f test;

	test.Set_X(105.0f);
	test.Set_Y(103.0f);
	test.Set_Z(144.0f);
	test.Set_W(1514.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_X(), 105.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_Y(), 103.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_Z(), 144.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test.Get_W(), 1514.0f));
}

TEST(Math, vector4f_testing_setter_two_depth)
{
	Kotek::ktk::math::vector4f test2;

	test2.Set_X(50.0f).Set_X(150.0f);
	test2.Set_Y(151.3f).Set_Y(425.25f);
	test2.Set_Z(131.3f).Set_Z(325.25f);
	test2.Set_W(1414.14f).Set_W(3254.25f);

	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_X(), 150.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_Y(), 425.25f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_Z(), 325.25f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test2.Get_W(), 3254.25f));
}

TEST(Math, vector4f_testing_plus_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector4f test1 = {3.5f, 2.5f, 351.0f, 151.1f};
	Kotek::ktk::math::vector4f test2 = {1.5f, 2.0f, 9.0f, 15.0f};

	test1 += test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (3.5f + 1.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (2.5f + 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (351.0f + 9.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (151.1f + 15.0f)));
}

TEST(Math, vector4f_testing_subtract_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector4f test1 = {3.5f, 2.5f, 252.0f, 16.0f};
	Kotek::ktk::math::vector4f test2 = {1.5f, 2.0f, 3.0f, 4.0f};

	test1 -= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (3.5f - 1.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (2.5f - 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (252.0f - 3.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (16.0f - 4.0f)));
}

TEST(Math, vector4f_testing_multiply_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector4f test1 = {2.0f, 6.4f, 4.4f, 25.25f};
	Kotek::ktk::math::base_decimal_t test2 = 5.5f;

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 2.0f * 5.5f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 6.4f * 5.5f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 4.4f * 5.5f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), 25.25f * 5.5f));
}

TEST(Math,
	vector4f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
{
	Kotek::ktk::math::vector4f test1 = {2.0f, 6.4f, 25.5f, 10.10f};
	Kotek::ktk::math::vector4f test2 = {5.5f, 252.1f, 60.4f, 25.0f};

	test1 *= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (2.0f * 5.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (6.4f * 252.1f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (25.5f * 60.4f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (10.10f * 25.0f)));
}

TEST(Math, vector4f_testing_divide_equal_operator_based_on_number_its_scale)
{
	Kotek::ktk::math::vector4f test1 = {8.4f, 2.6f, 25.0f, 251.0f};
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (2.6f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (25.0f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (251.0f / 2.0f)));
}

TEST(Math, vector4f_testing_divide_equal_operator_based_on_vector_its_divide)
{
	Kotek::ktk::math::vector4f test1 = {8.4f, 3.5f, 5.5f, 251.15f};
	Kotek::ktk::math::vector4f test2 = {2.0f, 0.5f, 52.5f, 151.0f};

	test1 /= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (3.5f / 0.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (5.5f / 52.5f)));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (251.15f / 151.0f)));
}

TEST(Math, vector4f_testing_modulo_equal_operator_based_on_number)
{
	Kotek::ktk::math::vector4f test1 = {4.0f, 6.0f, 8.0f, 151.0f};
	Kotek::ktk::math::base_decimal_t test2 = 2.0f;

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (std::fmod(151.0f, 2.0f))));
}

TEST(Math, vector4f_testing_modulo_equal_operator_based_on_vector)
{
	Kotek::ktk::math::vector4f test1 = {4.0f, 6.0f, 8.0f, 15.0f};
	Kotek::ktk::math::vector4f test2 = {2.0f, 3.0f, 4.0f, 12.0f};

	test1 %= test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 3.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 4.0f))));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), (std::fmod(15.0f, 12.0f))));
}

TEST(Math, vector4f_testing_unary_plus_operator)
{
	Kotek::ktk::math::vector4f test1 = {10.0f, 5.0f, 15.0f, 151.0f};

	test1 = +test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), 5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), 15.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), 151.0f));
}

TEST(Math, vector4f_testing_unary_minus_operator)
{
	Kotek::ktk::math::vector4f test1 = {10.0f, 5.0f, 15.0f, 151.0f};

	test1 = -test1;

	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Y(), -5.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_Z(), -15.0f));
	EXPECT_TRUE(Kotek::ktk::is_equal(test1.Get_W(), -151.0f));
}

TEST(Math, vector4f_testing_comparison_equal_zeros)
{
	Kotek::ktk::math::vector4f test1;
	Kotek::ktk::math::vector4f test2;

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector4f_testing_comparison_equal_random)
{
	Kotek::ktk::math::vector4f test1(
		150.15125f, 1515.1414f, 14.24141f, 1515.3515f);
	Kotek::ktk::math::vector4f test2(
		150.15125f, 1515.1414f, 14.24141f, 1515.3515f);

	EXPECT_TRUE(test1 == test2);
}

TEST(Math, vector4f_testing_comparison_equal_different_last_field)
{
	Kotek::ktk::math::vector4f test1(15.3f, 4.4f, 15.15f, 0.0f);
	Kotek::ktk::math::vector4f test2(15.0f, 4.4f, 15.15f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_equal_different_first_field)
{
	Kotek::ktk::math::vector4f test1(15.0f, 4.3f, 15.15f, 0.0f);
	Kotek::ktk::math::vector4f test2(15.0f, 4.4f, 15.15f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_equal_different_dirty_last_field)
{
	Kotek::ktk::math::vector4f test1(15.14152f, 0.0f, 0.0f, 0.0f);
	Kotek::ktk::math::vector4f test2(15.14151f, 0.0f, 0.0f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_equal_different_dirty_first_field)
{
	Kotek::ktk::math::vector4f test1(0.0f, 15.14152f, 0.0f, 0.0f);
	Kotek::ktk::math::vector4f test2(0.0f, 15.14151f, 0.0f, 0.0f);

	bool result = test1 == test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_not_equal_zeros)
{
	Kotek::ktk::math::vector4f test1;
	Kotek::ktk::math::vector4f test2;

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_not_equal_different)
{
	Kotek::ktk::math::vector4f test1(5.0f, 0.0f, 0.0f, 0.0f);
	Kotek::ktk::math::vector4f test2(2.0f, 0.0f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

TEST(Math, vector4f_testing_comparison_not_equal_equal_dirty)
{
	Kotek::ktk::math::vector4f test1(151.25151f, 0.0f, 0.0f, 0.0f);
	Kotek::ktk::math::vector4f test2(151.25151f, 0.0f, 0.0f, 0.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == false);
}

TEST(Math, vector4f_testing_comparison_not_equal_dirty)
{
	Kotek::ktk::math::vector4f test1(150.10502f, 0.0f, 1.0f, 2.0f);
	Kotek::ktk::math::vector4f test2(150.10509f, 0.0f, 1.0f, 2.0f);

	bool result = test1 != test2;

	EXPECT_TRUE(result == true);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, vector4f_testing_cast_operator_xmvector)
{
	Kotek::ktk::math::vector4f test1(150.0f, 151.0f, 153.0f, 164.0f);

	DirectX::XMVECTOR vec = test1;

	float value_x = DirectX::XMVectorGetX(vec);
	float value_y = DirectX::XMVectorGetY(vec);
	float value_z = DirectX::XMVectorGetZ(vec);
	float value_w = DirectX::XMVectorGetW(vec);

	EXPECT_TRUE(Kotek::ktk::is_equal(value_x, test1.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(value_y, test1.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(value_z, test1.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(value_w, test1.Get_W()));
}
		#endif

TEST(Math, vector4f_testing_binary_plus_operator_both_vectors)
{
	Kotek::ktk::math::vector4f test1(50.5f, 2.5f, 3.5f, 252.5f);
	Kotek::ktk::math::vector4f test2(5.5f, 0.5f, 2.5f, 6.5f);

	auto new_vector = test1 + test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(50.5f + 5.5f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f + 0.5f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f + 2.5f, new_vector.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.5f + 252.5f, new_vector.Get_W()));
}

TEST(Math, vector4f_testing_binary_subtract_operator_both_vectors)
{
	Kotek::ktk::math::vector4f test1(50.5f, 25.0f, 3.5f, 25.5f);
	Kotek::ktk::math::vector4f test2(0.5f, 5.0f, 2.5f, 6.0f);

	auto new_vector = test1 - test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(50.5f - 0.5f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f - 5.0f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f - 2.5f, new_vector.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.5f - 6.0f, new_vector.Get_W()));
}

TEST(Math, vector4f_testing_binary_mutiply_operator_both_vectors)
{
	Kotek::ktk::math::vector4f test1(5.5f, 25.5f, 3.5f, 25.5f);
	Kotek::ktk::math::vector4f test2(2.2f, 5.5f, 2.5f, 25.5f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.5f * 5.5f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f * 2.5f, new_vector.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.5f * 25.5f, new_vector.Get_W()));
}

TEST(Math, vector4f_testing_binary_multiply_operator_vector_number)
{
	Kotek::ktk::math::vector4f test1(5.5f, 2.5f, 3.5f, 15.15f);
	Kotek::ktk::math::base_decimal_t test2(2.2f);

	auto new_vector = test1 * test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f * 2.2f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f * 2.2f, new_vector.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.15f * 2.2f, new_vector.Get_W()));
}

TEST(Math, vector4f_testing_binary_divide_operator_both_vectors)
{
	Kotek::ktk::math::vector4f test1(6.6f, 3.6f, 3.5f, 15.5f);
	Kotek::ktk::math::vector4f test2(0.2f, 0.4f, 0.5f, 5.0f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.6f / 0.4f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.5f / 0.5f, new_vector.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.5f / 5.0f, new_vector.Get_W()));
}

TEST(Math, vector4f_testing_binary_divide_operator_vector_number)
{
	Kotek::ktk::math::vector4f test1(6.6f, 3.6f, 2.5f, 151.5f);
	Kotek::ktk::math::base_decimal_t test2(0.2f);

	auto new_vector = test1 / test2;

	EXPECT_TRUE(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.6f / 0.2f, new_vector.Get_Y()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.5f / 0.2f, new_vector.Get_Z()));
	EXPECT_TRUE(Kotek::ktk::is_equal(151.5f / 0.2f, new_vector.Get_W()));
}

TEST(Math, matrix4x4f_constructor_values)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_constructor_copy_base_type)
{
	Kotek::ktk::math::base_mat4x4_t copy = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
	Kotek::ktk::math::matrix4x4f test(copy);

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_constructor_copy_own_type)
{
	Kotek::ktk::math::base_mat4x4_t copy(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	Kotek::ktk::math::matrix4x4f test(copy);

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_constructor_default)
{
	Kotek::ktk::math::matrix4x4f test;

	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(0.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_assignment_operator_universal_initialization)
{
	Kotek::ktk::math::matrix4x4f test = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test.Get_33()));
}

TEST(Math, matri4x4f_assignment_operator_base_type)
{
	Kotek::ktk::math::base_mat4x4_t base = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	Kotek::ktk::math::matrix4x4f test = base;

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_assignment_plus_operator)
{
	Kotek::ktk::math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test += {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	EXPECT_TRUE(Kotek::ktk::is_equal(17.0f + 1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(18.0f + 2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(19.0f + 3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(20.0f + 4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(21.0f + 5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(22.0f + 6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(23.0f + 7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(24.0f + 8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f + 9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(26.0f + 10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(27.0f + 11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(28.0f + 12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(29.0f + 13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(30.0f + 14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(31.0f + 15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(32.0f + 16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_assignment_minus_operator)
{
	Kotek::ktk::math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test -= {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	EXPECT_TRUE(Kotek::ktk::is_equal(17.0f - 1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(18.0f - 2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(19.0f - 3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(20.0f - 4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(21.0f - 5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(22.0f - 6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(23.0f - 7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(24.0f - 8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f - 9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(26.0f - 10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(27.0f - 11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(28.0f - 12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(29.0f - 13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(30.0f - 14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(31.0f - 15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(32.0f - 16.0f, test.Get_33()));
}

// TODO: add overloads for matrix4x3 and other
TEST(Math, matrix4x4f_assignment_multiply_operator)
{
	Kotek::ktk::math::matrix4x4f copy(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	Kotek::ktk::math::matrix4x4f copy2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	Kotek::ktk::math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test *= {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	Kotek::ktk::vector<Kotek::ktk::math::base_decimal_t> data;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Kotek::ktk::math::base_decimal_t value = 0.0f;

			for (int k = 0; k < 4; ++k)
			{
				value += copy(i, k) * copy2(k, j);
			}

			data.push_back(value);
		}
	}

	Kotek::ktk::size_t current_index = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_TRUE(Kotek::ktk::is_equal(data[current_index], test(i, j)));
			current_index += 1;
		}
	}
}

TEST(Math, matrix4x4f_assignment_multiply_operator_base_decimal)
{
	Kotek::ktk::math::base_decimal_t value = 15.0f;
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test *= value;

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f * value, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f * value, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f * value, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f * value, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f * value, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f * value, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f * value, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f * value, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f * value, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f * value, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f * value, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f * value, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f * value, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f * value, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f * value, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f * value, test.Get_33()));
}

TEST(Math, matrix4x4f_assignment_divide_operator)
{
	Kotek::ktk::math::matrix4x4f copy(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	Kotek::ktk::math::matrix4x4f copy2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	Kotek::ktk::math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test /= {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
		12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			EXPECT_TRUE(Kotek::ktk::is_equal(copy(i, j) / copy2(i, j), test(i, j)));
		}
	}
}

TEST(Math, matrix4x4f_assignment_divide_operator_decimal)
{
	Kotek::ktk::math::base_decimal_t value = 15.0f;
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	Kotek::ktk::math::base_decimal_t factor = 1.f / value;

	test /= value;

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f * factor, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f * factor, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f * factor, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f * factor, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f * factor, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f * factor, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f * factor, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f * factor, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f * factor, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f * factor, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f * factor, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f * factor, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f * factor, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f * factor, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f * factor, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f * factor, test.Get_33()));
}

TEST(Math, matrix4x4f_unary_plus_operator)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test = +test;

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_unary_minus_operator)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test = -test;

	EXPECT_TRUE(Kotek::ktk::is_equal(-1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(-16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_comparison_operator_equal)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	Kotek::ktk::math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(test == test2);
}

TEST(Math, matrix4x4f_comparison_operator_equal_but_one_is_wrong)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	Kotek::ktk::math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, -16.0f);

	EXPECT_TRUE((test == test2) == false);
}

TEST(Math, matrix4x4f_comparison_operator_equal_but_two_is_wrong)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	Kotek::ktk::math::matrix4x4f test2(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, -8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE((test == test2) == false);
}

TEST(Math, matrix4x4f_comparison_operator_not_equal)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	Kotek::ktk::math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, -16.0f);

	EXPECT_TRUE(test != test2);
}

TEST(Math, matrix4x4f_comparison_operator_not_equal_two_wrong)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	Kotek::ktk::math::matrix4x4f test2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		-7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, -15.0f, 16.0f);

	EXPECT_TRUE(test != test2);
}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
TEST(Math, matrix4x4f_cast_operator_xmmatrix)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	DirectX::XMMATRIX casted = test;

	const DirectX::XMVECTOR& vec0 = casted.r[0];
	const DirectX::XMVECTOR& vec1 = casted.r[1];
	const DirectX::XMVECTOR& vec2 = casted.r[2];
	const DirectX::XMVECTOR& vec3 = casted.r[3];

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, DirectX::XMVectorGetX(vec0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, DirectX::XMVectorGetY(vec0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, DirectX::XMVectorGetZ(vec0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, DirectX::XMVectorGetW(vec0)));

	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, DirectX::XMVectorGetX(vec1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, DirectX::XMVectorGetY(vec1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, DirectX::XMVectorGetZ(vec1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, DirectX::XMVectorGetW(vec1)));

	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, DirectX::XMVectorGetX(vec2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, DirectX::XMVectorGetY(vec2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, DirectX::XMVectorGetZ(vec2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, DirectX::XMVectorGetW(vec2)));

	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, DirectX::XMVectorGetX(vec3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, DirectX::XMVectorGetY(vec3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, DirectX::XMVectorGetZ(vec3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, DirectX::XMVectorGetW(vec3)));
}
		#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		#endif

TEST(Math, matrix4x4f_operator_get_element_by_brackets_read_state)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f, test(0, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f, test(0, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f, test(0, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f, test(0, 3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f, test(1, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f, test(1, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f, test(1, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f, test(1, 3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f, test(2, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f, test(2, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f, test(2, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f, test(2, 3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f, test(3, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f, test(3, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f, test(3, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f, test(3, 3)));
}

TEST(Math, matrix4x4f_operator_get_element_by_brackets_write_state)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
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

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f + 1.0f, test(0, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f + 1.0f, test(0, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f + 1.0f, test(0, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f + 1.0f, test(0, 3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f + 1.0f, test(1, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f + 1.0f, test(1, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f + 1.0f, test(1, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f + 1.0f, test(1, 3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f + 1.0f, test(2, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f + 1.0f, test(2, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f + 1.0f, test(2, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f + 1.0f, test(2, 3)));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f + 1.0f, test(3, 0)));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f + 1.0f, test(3, 1)));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f + 1.0f, test(3, 2)));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f + 1.0f, test(3, 3)));
}

TEST(Math, matrix4x4f_setters)
{
	Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	test.Set_00(test.Get_00() + 1.0f);
	test.Set_01(test.Get_01() + 1.0f);
	test.Set_02(test.Get_02() + 1.0f);
	test.Set_03(test.Get_03() + 1.0f);
	test.Set_10(test.Get_10() + 1.0f);
	test.Set_11(test.Get_11() + 1.0f);
	test.Set_12(test.Get_12() + 1.0f);
	test.Set_13(test.Get_13() + 1.0f);
	test.Set_20(test.Get_20() + 1.0f);
	test.Set_21(test.Get_21() + 1.0f);
	test.Set_22(test.Get_22() + 1.0f);
	test.Set_23(test.Get_23() + 1.0f);
	test.Set_30(test.Get_30() + 1.0f);
	test.Set_31(test.Get_31() + 1.0f);
	test.Set_32(test.Get_32() + 1.0f);
	test.Set_33(test.Get_33() + 1.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(1.0f + 1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(2.0f + 1.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(3.0f + 1.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(4.0f + 1.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(5.0f + 1.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(6.0f + 1.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(7.0f + 1.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(8.0f + 1.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(9.0f + 1.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(10.0f + 1.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(11.0f + 1.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(12.0f + 1.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(13.0f + 1.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(14.0f + 1.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(15.0f + 1.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(16.0f + 1.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_plus_operator)
{
	Kotek::ktk::math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test = test +
		Kotek::ktk::math::matrix4x4f(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
			8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(17.0f + 1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(18.0f + 2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(19.0f + 3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(20.0f + 4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(21.0f + 5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(22.0f + 6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(23.0f + 7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(24.0f + 8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f + 9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(26.0f + 10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(27.0f + 11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(28.0f + 12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(29.0f + 13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(30.0f + 14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(31.0f + 15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(32.0f + 16.0f, test.Get_33()));
}

TEST(Math, matrix4x4f_minus_operator)
{
	Kotek::ktk::math::matrix4x4f test(17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f,
		23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f);

	test = test -
		Kotek::ktk::math::matrix4x4f(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
			8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	EXPECT_TRUE(Kotek::ktk::is_equal(17.0f - 1.0f, test.Get_00()));
	EXPECT_TRUE(Kotek::ktk::is_equal(18.0f - 2.0f, test.Get_01()));
	EXPECT_TRUE(Kotek::ktk::is_equal(19.0f - 3.0f, test.Get_02()));
	EXPECT_TRUE(Kotek::ktk::is_equal(20.0f - 4.0f, test.Get_03()));
	EXPECT_TRUE(Kotek::ktk::is_equal(21.0f - 5.0f, test.Get_10()));
	EXPECT_TRUE(Kotek::ktk::is_equal(22.0f - 6.0f, test.Get_11()));
	EXPECT_TRUE(Kotek::ktk::is_equal(23.0f - 7.0f, test.Get_12()));
	EXPECT_TRUE(Kotek::ktk::is_equal(24.0f - 8.0f, test.Get_13()));
	EXPECT_TRUE(Kotek::ktk::is_equal(25.0f - 9.0f, test.Get_20()));
	EXPECT_TRUE(Kotek::ktk::is_equal(26.0f - 10.0f, test.Get_21()));
	EXPECT_TRUE(Kotek::ktk::is_equal(27.0f - 11.0f, test.Get_22()));
	EXPECT_TRUE(Kotek::ktk::is_equal(28.0f - 12.0f, test.Get_23()));
	EXPECT_TRUE(Kotek::ktk::is_equal(29.0f - 13.0f, test.Get_30()));
	EXPECT_TRUE(Kotek::ktk::is_equal(30.0f - 14.0f, test.Get_31()));
	EXPECT_TRUE(Kotek::ktk::is_equal(31.0f - 15.0f, test.Get_32()));
	EXPECT_TRUE(Kotek::ktk::is_equal(32.0f - 16.0f, test.Get_33()));
}
	#endif
#endif

void RegisterTests_Math_ForModule_Core(){
#ifdef KOTEK_USE_TESTS
#endif
}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
