#include "../kotek_std.h"
#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Core
	{
		void RegisterTests_Math_ForModule_Core(void)
		{
#ifdef KOTEK_USE_TESTS
			KOTEK_MESSAGE("Registered!");
#endif
		}

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

		#pragma region Utility
		BOOST_AUTO_TEST_CASE(equal_function_for_floats_are_not_equal)
		{
			float test1 = 15.1515f;
			float test2 = 15.1504f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1, test2) == false);
		}

		BOOST_AUTO_TEST_CASE(equal_function_for_floats_must_be_equal)
		{
			float test1 = 15.1515f;
			float test2 = 15.1515f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1, test2) == true);
		}

		BOOST_AUTO_TEST_CASE(
			equal_function_for_floats_really_close_but_not_equal)
		{
			float test1 = 15.151514f;
			float test2 = 15.151513f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1, test2) == false);
		}

		BOOST_AUTO_TEST_CASE(equal_function_for_floats_digits)
		{
			float test1 = 0.000300f;
			float test2 = 0.000301f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1, test2) == false);
		}

		BOOST_AUTO_TEST_CASE(equal_function_for_floats_zeros)
		{
			float test1 = 0.0f;
			float test2 = 0.0f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1, test2) == true);
		}

		BOOST_AUTO_TEST_CASE(equal_function_for_floats_really_low)
		{
			float test1 = 0.000002f;
			float test2 = 0.000001f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1, test2) == false);
		}

		BOOST_AUTO_TEST_CASE(equal_function_for_floats_when_we_sum)
		{
			float test1 = 3.0f;
			float test2 = 6.0f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1 + test2, 9.0f) == true);
		}

		BOOST_AUTO_TEST_CASE(equal_function_for_floats_when_we_sum_dirty)
		{
			float test1 = 3.5151f;
			float test2 = 2.521f;

			BOOST_CHECK(Kotek::ktk::is_equal(test1 + test2, 6.03f) == false);
		}
		#pragma endregion

		#pragma region Vector1

		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_default)
		{
			Kotek::ktk::math::vector1f test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_based_on_number)
		{
			Kotek::ktk::math::vector1f vec(5.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
		}

		#ifdef KOTEK_USE_MATH_LIBRARY_GLM
		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_based_on_struct) {}
		#endif

		BOOST_AUTO_TEST_CASE(vector1f_testing_copy_constructor)
		{
			Kotek::ktk::math::vector1f vec_original(550.5f);
			Kotek::ktk::math::vector1f vec_copy(vec_original);

			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_assignment_operator_based_on_own_type)
		{
			Kotek::ktk::math::vector1f some(50.0f);
			Kotek::ktk::math::vector1f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_assignment_operator_based_on_base_type)
		{
			Kotek::ktk::math::base_vec1_t some(51.0f);
			Kotek::ktk::math::vector1f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_X(), some));
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_setter_single_depth)
		{
			Kotek::ktk::math::vector1f test;

			test.Set_X(105.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_X(), 105.0f));
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_setter_two_depth)
		{
			Kotek::ktk::math::vector1f test2;

			test2.Set_X(50.0f).Set_X(150.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_X(), 150.0f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_plus_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 3.5f;
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 += test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 9.0f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_plus_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 3.5f;
			Kotek::ktk::math::vector1f test2 = 5.5f;

			test1 += test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 9.0f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_subtract_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 5.5f;
			Kotek::ktk::math::base_decimal_t test2 = 3.5f;

			test1 -= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 2.0f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_subtract_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 5.5f;
			Kotek::ktk::math::vector1f test2 = 3.5f;

			test1 -= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 2.0f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_multiply_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector1f test1 = 3.2f;
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 17.6f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_multiply_equal_operator_based_on_vector_its_per_compunent_multiply)
		{
			Kotek::ktk::math::vector1f test1 = 3.2f;
			Kotek::ktk::math::vector1f test2 = 5.5f;

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 17.6f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_divide_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector1f test1 = 8.4f;
			Kotek::ktk::math::base_decimal_t test2 = 2.6f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.6f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_divide_equal_operator_based_on_vector_its_divide)
		{
			Kotek::ktk::math::vector1f test1 = 8.4f;
			Kotek::ktk::math::vector1f test2 = 2.6f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.6f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_modulo_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 5.3f;
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(5.3f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_modulo_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 5.3f;
			Kotek::ktk::math::vector1f test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(5.3f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_unary_plus_operator)
		{
			Kotek::ktk::math::vector1f test1 = 10.0f;

			test1 = +test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_unary_minus_operator)
		{
			Kotek::ktk::math::vector1f test1 = 10.0f;

			test1 = -test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_equal_zeros)
		{
			Kotek::ktk::math::vector1f test1;
			Kotek::ktk::math::vector1f test2;

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_equal_random)
		{
			Kotek::ktk::math::vector1f test1(150.15125f);
			Kotek::ktk::math::vector1f test2(150.15125f);

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_equal_different)
		{
			Kotek::ktk::math::vector1f test1(15.3f);
			Kotek::ktk::math::vector1f test2(15.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_equal_different_dirty)
		{
			Kotek::ktk::math::vector1f test1(15.14152f);
			Kotek::ktk::math::vector1f test2(15.14151f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_not_equal_zeros)
		{
			Kotek::ktk::math::vector1f test1;
			Kotek::ktk::math::vector1f test2;

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_not_equal_different)
		{
			Kotek::ktk::math::vector1f test1(5.0f);
			Kotek::ktk::math::vector1f test2(2.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_not_equal_equal_dirty)
		{
			Kotek::ktk::math::vector1f test1(151.25151f);
			Kotek::ktk::math::vector1f test2(151.25151f);

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_comparison_not_equal_dirty)
		{
			Kotek::ktk::math::vector1f test1(150.10502f);
			Kotek::ktk::math::vector1f test2(150.10509f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		BOOST_AUTO_TEST_CASE(vector1f_testing_cast_operator_xmvector)
		{
			Kotek::ktk::math::vector1f test1(150.0f);

			DirectX::XMVECTOR vec = test1;

			float value = DirectX::XMVectorGetX(vec);

			BOOST_CHECK(Kotek::ktk::is_equal(value, test1.Get_X()));
		}
		#endif

		BOOST_AUTO_TEST_CASE(vector1f_testing_binary_plus_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::vector1f test2(5.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(new_vector == 56.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_plus_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::base_decimal_t test2(5.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(new_vector == 56.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_subtract_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::vector1f test2(0.5f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(new_vector == 50.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_subtract_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::base_decimal_t test2(0.5f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(new_vector == 50.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_mutiply_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(5.5f);
			Kotek::ktk::math::vector1f test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(new_vector == 12.1f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_multiply_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(5.5f);
			Kotek::ktk::math::base_decimal_t test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(new_vector == 12.1f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_divide_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(6.6f);
			Kotek::ktk::math::vector1f test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(new_vector == 33.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_binary_divide_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(6.6f);
			Kotek::ktk::math::base_decimal_t test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(new_vector == 33.0f);
		}
		#pragma endregion

		#pragma region Vector2
		BOOST_AUTO_TEST_CASE(vector2f_testing_constructor_default)
		{
			Kotek::ktk::math::vector2f test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_constructor_based_on_number)
		{
			Kotek::ktk::math::vector2f vec(5.0f, 6.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f) &&
				Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_constructor_based_on_struct)
		{
			Kotek::ktk::math::base_vec2_t data = {5.0f, 6.0f};
			Kotek::ktk::math::vector2f vec(data);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f) &&
				Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_copy_constructor)
		{
			Kotek::ktk::math::vector2f vec_original(550.5f, 153.2f);
			Kotek::ktk::math::vector2f vec_copy(vec_original);

			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()) &&
				Kotek::ktk::is_equal(vec_original.Get_Y(), vec_copy.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_assignment_operator_based_on_own_type)
		{
			Kotek::ktk::math::vector2f some(50.0f, 25.4f);
			Kotek::ktk::math::vector2f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()) &&
				Kotek::ktk::is_equal(some.Get_Y(), some2.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_assignment_operator_based_on_base_type)
		{
			Kotek::ktk::math::base_vec2_t some(51.0f, 15.3f);
			Kotek::ktk::math::vector2f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_X(), some.x) &&
				Kotek::ktk::is_equal(some2.Get_Y(), some.y));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_setter_single_depth)
		{
			Kotek::ktk::math::vector2f test;

			test.Set_X(105.0f);
			test.Set_Y(103.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_X(), 105.0f) &&
				Kotek::ktk::is_equal(test.Get_Y(), 103.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_setter_two_depth)
		{
			Kotek::ktk::math::vector2f test2;

			test2.Set_X(50.0f).Set_X(150.0f);
			test2.Set_Y(151.3f).Set_Y(425.25f);

			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_X(), 150.0f) &&
				Kotek::ktk::is_equal(test2.Get_Y(), 425.25f));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_plus_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector2f test1 = {3.5f, 2.5f};
			Kotek::ktk::math::vector2f test2 = {1.5f, 2.0f};

			test1 += test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 5.0f) &&
				Kotek::ktk::is_equal(test1.Get_Y(), 4.5f));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_subtract_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector2f test1 = {3.5f, 2.5f};
			Kotek::ktk::math::vector2f test2 = {1.5f, 2.0f};

			test1 -= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 2.0f) &&
				Kotek::ktk::is_equal(test1.Get_Y(), 0.5f));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_multiply_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector2f test1 = {2.0f, 6.4f};
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 11.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 35.2f));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
		{
			Kotek::ktk::math::vector2f test1 = {2.0f, 6.4f};
			Kotek::ktk::math::vector2f test2 = {5.5f, 252.1f};

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 11.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (6.4f * 252.1f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_divide_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector2f test1 = {8.4f, 2.6f};
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (2.6f / 2.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_divide_equal_operator_based_on_vector_its_divide)
		{
			Kotek::ktk::math::vector2f test1 = {8.4f, 3.5f};
			Kotek::ktk::math::vector2f test2 = {2.0f, 0.5f};

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (3.5f / 0.5f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_modulo_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector2f test1 = {4.0f, 6.0f};
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_modulo_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector2f test1 = {4.0f, 6.0f};
			Kotek::ktk::math::vector2f test2 = {2.0f, 3.0f};

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 3.0f))));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_unary_plus_operator)
		{
			Kotek::ktk::math::vector2f test1 = {10.0f, 5.0f};

			test1 = +test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 5.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_unary_minus_operator)
		{
			Kotek::ktk::math::vector2f test1 = {10.0f, 5.0f};

			test1 = -test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), -5.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_equal_zeros)
		{
			Kotek::ktk::math::vector2f test1;
			Kotek::ktk::math::vector2f test2;

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_equal_random)
		{
			Kotek::ktk::math::vector2f test1(150.15125f, 1515.1414f);
			Kotek::ktk::math::vector2f test2(150.15125f, 1515.1414f);

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_comparison_equal_different_last_field)
		{
			Kotek::ktk::math::vector2f test1(15.3f, 4.4f);
			Kotek::ktk::math::vector2f test2(15.0f, 4.4f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_comparison_equal_different_first_field)
		{
			Kotek::ktk::math::vector2f test1(15.0f, 4.3f);
			Kotek::ktk::math::vector2f test2(15.0f, 4.4f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_comparison_equal_different_dirty_last_field)
		{
			Kotek::ktk::math::vector2f test1(15.14152f, 0.0f);
			Kotek::ktk::math::vector2f test2(15.14151f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_comparison_equal_different_dirty_first_field)
		{
			Kotek::ktk::math::vector2f test1(0.0f, 15.14152f);
			Kotek::ktk::math::vector2f test2(0.0f, 15.14151f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_zeros)
		{
			Kotek::ktk::math::vector2f test1;
			Kotek::ktk::math::vector2f test2;

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_different)
		{
			Kotek::ktk::math::vector2f test1(5.0f, 0.0f);
			Kotek::ktk::math::vector2f test2(2.0f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_equal_dirty)
		{
			Kotek::ktk::math::vector2f test1(151.25151f, 0.0f);
			Kotek::ktk::math::vector2f test2(151.25151f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_dirty)
		{
			Kotek::ktk::math::vector2f test1(150.10502f, 0.0f);
			Kotek::ktk::math::vector2f test2(150.10509f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		BOOST_AUTO_TEST_CASE(vector2f_testing_cast_operator_xmvector)
		{
			Kotek::ktk::math::vector2f test1(150.0f, 151.0f);

			DirectX::XMVECTOR vec = test1;

			float value_x = DirectX::XMVectorGetX(vec);
			float value_y = DirectX::XMVectorGetY(vec);

			BOOST_CHECK(Kotek::ktk::is_equal(value_x, test1.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(value_y, test1.Get_Y()));
		}
		#endif

		BOOST_AUTO_TEST_CASE(vector2f_testing_binary_plus_operator_both_vectors)
		{
			Kotek::ktk::math::vector2f test1(50.5f, 2.5f);
			Kotek::ktk::math::vector2f test2(5.5f, 0.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(Kotek::ktk::is_equal(50.5f + 5.5f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f + 0.5f, new_vector.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_subtract_operator_both_vectors)
		{
			Kotek::ktk::math::vector2f test1(50.5f, 25.0f);
			Kotek::ktk::math::vector2f test2(0.5f, 5.0f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(Kotek::ktk::is_equal(50.5f - 0.5f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.0f - 5.0f, new_vector.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_mutiply_operator_both_vectors)
		{
			Kotek::ktk::math::vector2f test1(5.5f, 25.5f);
			Kotek::ktk::math::vector2f test2(2.2f, 5.5f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.5f * 5.5f, new_vector.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_multiply_operator_vector_number)
		{
			Kotek::ktk::math::vector2f test1(5.5f, 2.5f);
			Kotek::ktk::math::base_decimal_t test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f * 2.2f, new_vector.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_divide_operator_both_vectors)
		{
			Kotek::ktk::math::vector2f test1(6.6f, 3.6f);
			Kotek::ktk::math::vector2f test2(0.2f, 0.4f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.6f / 0.4f, new_vector.Get_Y()));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_divide_operator_vector_number)
		{
			Kotek::ktk::math::vector2f test1(6.6f, 3.6f);
			Kotek::ktk::math::base_decimal_t test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.6f / 0.2f, new_vector.Get_Y()));
		}
		#pragma endregion

		#pragma region Vector3
		BOOST_AUTO_TEST_CASE(vector3f_testing_constructor_default)
		{
			Kotek::ktk::math::vector3f test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 0.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 0.0f));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_constructor_based_on_number)
		{
			Kotek::ktk::math::vector3f vec(5.0f, 6.0f, 7.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_constructor_based_on_struct)
		{
			Kotek::ktk::math::base_vec3_t data = {5.0f, 6.0f, 7.0f};
			Kotek::ktk::math::vector3f vec(data);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_copy_constructor)
		{
			Kotek::ktk::math::vector3f vec_original(550.5f, 153.2f, 25.25f);
			Kotek::ktk::math::vector3f vec_copy(vec_original);

			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_Y(), vec_copy.Get_Y()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_Z(), vec_copy.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_assignment_operator_based_on_own_type)
		{
			Kotek::ktk::math::vector3f some(50.0f, 25.4f, 252.0f);
			Kotek::ktk::math::vector3f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_Y(), some2.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_Z(), some2.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_assignment_operator_based_on_base_type)
		{
			Kotek::ktk::math::base_vec3_t some(51.0f, 15.3f, 25.0f);
			Kotek::ktk::math::vector3f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_X(), some.x));
			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_Y(), some.y));
			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_Z(), some.z));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_setter_single_depth)
		{
			Kotek::ktk::math::vector3f test;

			test.Set_X(105.0f);
			test.Set_Y(103.0f);
			test.Set_Z(144.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_X(), 105.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_Y(), 103.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_Z(), 144.0f));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_setter_two_depth)
		{
			Kotek::ktk::math::vector3f test2;

			test2.Set_X(50.0f).Set_X(150.0f);
			test2.Set_Y(151.3f).Set_Y(425.25f);
			test2.Set_Z(131.3f).Set_Z(325.25f);

			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_X(), 150.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_Y(), 425.25f));
			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_Z(), 325.25f));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_plus_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector3f test1 = {3.5f, 2.5f, 351.0f};
			Kotek::ktk::math::vector3f test2 = {1.5f, 2.0f, 9.0f};

			test1 += test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 4.5f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 360.0f));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_subtract_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector3f test1 = {3.5f, 2.5f, 252.0f};
			Kotek::ktk::math::vector3f test2 = {1.5f, 2.0f, 3.0f};

			test1 -= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 2.0f) &&
				Kotek::ktk::is_equal(test1.Get_Y(), 0.5f));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_multiply_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector3f test1 = {2.0f, 6.4f, 4.4f};
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 2.0f * 5.5f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 6.4f * 5.5f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 4.4f * 5.5f));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
		{
			Kotek::ktk::math::vector3f test1 = {2.0f, 6.4f, 25.5f};
			Kotek::ktk::math::vector3f test2 = {5.5f, 252.1f, 60.4f};

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (2.0f * 5.5f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (6.4f * 252.1f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (25.5f * 60.4f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_divide_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector3f test1 = {8.4f, 2.6f, 25.0f};
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (2.6f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (25.0f / 2.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_divide_equal_operator_based_on_vector_its_divide)
		{
			Kotek::ktk::math::vector3f test1 = {8.4f, 3.5f, 5.5f};
			Kotek::ktk::math::vector3f test2 = {2.0f, 0.5f, 52.5f};

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (3.5f / 0.5f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (5.5f / 52.5f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_modulo_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector3f test1 = {4.0f, 6.0f, 8.0f};
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_modulo_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector3f test1 = {4.0f, 6.0f, 8.0f};
			Kotek::ktk::math::vector3f test2 = {2.0f, 3.0f, 4.0f};

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 3.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 4.0f))));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_unary_plus_operator)
		{
			Kotek::ktk::math::vector3f test1 = {10.0f, 5.0f, 15.0f};

			test1 = +test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 15.0f));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_unary_minus_operator)
		{
			Kotek::ktk::math::vector3f test1 = {10.0f, 5.0f, 15.0f};

			test1 = -test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), -5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), -15.0f));
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_comparison_equal_zeros)
		{
			Kotek::ktk::math::vector3f test1;
			Kotek::ktk::math::vector3f test2;

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_comparison_equal_random)
		{
			Kotek::ktk::math::vector3f test1(150.15125f, 1515.1414f, 14.24141f);
			Kotek::ktk::math::vector3f test2(150.15125f, 1515.1414f, 14.24141f);

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_comparison_equal_different_last_field)
		{
			Kotek::ktk::math::vector3f test1(15.3f, 4.4f, 15.15f);
			Kotek::ktk::math::vector3f test2(15.0f, 4.4f, 15.15f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_comparison_equal_different_first_field)
		{
			Kotek::ktk::math::vector3f test1(15.0f, 4.3f, 15.15f);
			Kotek::ktk::math::vector3f test2(15.0f, 4.4f, 15.15f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_comparison_equal_different_dirty_last_field)
		{
			Kotek::ktk::math::vector3f test1(15.14152f, 0.0f, 0.0f);
			Kotek::ktk::math::vector3f test2(15.14151f, 0.0f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_comparison_equal_different_dirty_first_field)
		{
			Kotek::ktk::math::vector3f test1(0.0f, 15.14152f, 0.0f);
			Kotek::ktk::math::vector3f test2(0.0f, 15.14151f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_comparison_not_equal_zeros)
		{
			Kotek::ktk::math::vector3f test1;
			Kotek::ktk::math::vector3f test2;

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_comparison_not_equal_different)
		{
			Kotek::ktk::math::vector3f test1(5.0f, 0.0f, 0.0f);
			Kotek::ktk::math::vector3f test2(2.0f, 0.0f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_comparison_not_equal_equal_dirty)
		{
			Kotek::ktk::math::vector3f test1(151.25151f, 0.0f, 0.0f);
			Kotek::ktk::math::vector3f test2(151.25151f, 0.0f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector3f_testing_comparison_not_equal_dirty)
		{
			Kotek::ktk::math::vector3f test1(150.10502f, 0.0f, 1.0f);
			Kotek::ktk::math::vector3f test2(150.10509f, 0.0f, 1.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		BOOST_AUTO_TEST_CASE(vector3f_testing_cast_operator_xmvector)
		{
			Kotek::ktk::math::vector3f test1(150.0f, 151.0f, 153.0f);

			DirectX::XMVECTOR vec = test1;

			float value_x = DirectX::XMVectorGetX(vec);
			float value_y = DirectX::XMVectorGetY(vec);
			float value_z = DirectX::XMVectorGetZ(vec);

			BOOST_CHECK(Kotek::ktk::is_equal(value_x, test1.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(value_y, test1.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(value_z, test1.Get_Z()));
		}
		#endif

		BOOST_AUTO_TEST_CASE(vector3f_testing_binary_plus_operator_both_vectors)
		{
			Kotek::ktk::math::vector3f test1(50.5f, 2.5f, 3.5f);
			Kotek::ktk::math::vector3f test2(5.5f, 0.5f, 2.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(Kotek::ktk::is_equal(50.5f + 5.5f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f + 0.5f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f + 2.5f, new_vector.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_binary_subtract_operator_both_vectors)
		{
			Kotek::ktk::math::vector3f test1(50.5f, 25.0f, 3.5f);
			Kotek::ktk::math::vector3f test2(0.5f, 5.0f, 2.5f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(Kotek::ktk::is_equal(50.5f - 0.5f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.0f - 5.0f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f - 2.5f, new_vector.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_binary_mutiply_operator_both_vectors)
		{
			Kotek::ktk::math::vector3f test1(5.5f, 25.5f, 3.5f);
			Kotek::ktk::math::vector3f test2(2.2f, 5.5f, 2.5f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.5f * 5.5f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f * 2.5f, new_vector.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_binary_multiply_operator_vector_number)
		{
			Kotek::ktk::math::vector3f test1(5.5f, 2.5f, 3.5f);
			Kotek::ktk::math::base_decimal_t test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f * 2.2f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f * 2.2f, new_vector.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_binary_divide_operator_both_vectors)
		{
			Kotek::ktk::math::vector3f test1(6.6f, 3.6f, 3.5f);
			Kotek::ktk::math::vector3f test2(0.2f, 0.4f, 0.5f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.6f / 0.4f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f / 0.5f, new_vector.Get_Z()));
		}

		BOOST_AUTO_TEST_CASE(
			vector3f_testing_binary_divide_operator_vector_number)
		{
			Kotek::ktk::math::vector3f test1(6.6f, 3.6f, 2.5f);
			Kotek::ktk::math::base_decimal_t test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.6f / 0.2f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f / 0.2f, new_vector.Get_Z()));
		}
		#pragma endregion

		#pragma region Vector4
		BOOST_AUTO_TEST_CASE(vector4f_testing_constructor_default)
		{
			Kotek::ktk::math::vector4f test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 0.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 0.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 0.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), 0.0f));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_constructor_based_on_number)
		{
			Kotek::ktk::math::vector4f vec(5.0f, 6.0f, 7.0f, 8.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_W(), 8.0f));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_constructor_based_on_struct)
		{
			Kotek::ktk::math::base_vec4_t data = {5.0f, 6.0f, 7.0f, 8.0f};
			Kotek::ktk::math::vector4f vec(data);

			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_X(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Y(), 6.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_Z(), 7.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(vec.Get_W(), 8.0f));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_copy_constructor)
		{
			Kotek::ktk::math::vector4f vec_original(
				550.5f, 153.2f, 25.25f, 2525.52f);
			Kotek::ktk::math::vector4f vec_copy(vec_original);

			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_X(), vec_copy.Get_X()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_Y(), vec_copy.Get_Y()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_Z(), vec_copy.Get_Z()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(vec_original.Get_W(), vec_copy.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_assignment_operator_based_on_own_type)
		{
			Kotek::ktk::math::vector4f some(50.0f, 25.4f, 252.0f, 25215.15f);
			Kotek::ktk::math::vector4f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_X(), some2.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_Y(), some2.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_Z(), some2.Get_Z()));
			BOOST_CHECK(Kotek::ktk::is_equal(some.Get_W(), some2.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_assignment_operator_based_on_base_type)
		{
			Kotek::ktk::math::base_vec4_t some(51.0f, 15.3f, 25.0f, 1511.3f);
			Kotek::ktk::math::vector4f some2 = some;

			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_X(), some.x));
			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_Y(), some.y));
			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_Z(), some.z));
			BOOST_CHECK(Kotek::ktk::is_equal(some2.Get_W(), some.w));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_setter_single_depth)
		{
			Kotek::ktk::math::vector4f test;

			test.Set_X(105.0f);
			test.Set_Y(103.0f);
			test.Set_Z(144.0f);
			test.Set_W(1514.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_X(), 105.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_Y(), 103.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_Z(), 144.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test.Get_W(), 1514.0f));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_setter_two_depth)
		{
			Kotek::ktk::math::vector4f test2;

			test2.Set_X(50.0f).Set_X(150.0f);
			test2.Set_Y(151.3f).Set_Y(425.25f);
			test2.Set_Z(131.3f).Set_Z(325.25f);
			test2.Set_W(1414.14f).Set_W(3254.25f);

			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_X(), 150.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_Y(), 425.25f));
			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_Z(), 325.25f));
			BOOST_CHECK(Kotek::ktk::is_equal(test2.Get_W(), 3254.25f));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_plus_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector4f test1 = {3.5f, 2.5f, 351.0f, 151.1f};
			Kotek::ktk::math::vector4f test2 = {1.5f, 2.0f, 9.0f, 15.0f};

			test1 += test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (3.5f + 1.5f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (2.5f + 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (351.0f + 9.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), (151.1f + 15.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_subtract_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector4f test1 = {3.5f, 2.5f, 252.0f, 16.0f};
			Kotek::ktk::math::vector4f test2 = {1.5f, 2.0f, 3.0f, 4.0f};

			test1 -= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (3.5f - 1.5f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (2.5f - 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (252.0f - 3.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), (16.0f - 4.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_multiply_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector4f test1 = {2.0f, 6.4f, 4.4f, 25.25f};
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 2.0f * 5.5f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 6.4f * 5.5f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 4.4f * 5.5f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), 25.25f * 5.5f));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_multiply_equal_operator_based_on_vector_its_per_component_multiply)
		{
			Kotek::ktk::math::vector4f test1 = {2.0f, 6.4f, 25.5f, 10.10f};
			Kotek::ktk::math::vector4f test2 = {5.5f, 252.1f, 60.4f, 25.0f};

			test1 *= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (2.0f * 5.5f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (6.4f * 252.1f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (25.5f * 60.4f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), (10.10f * 25.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_divide_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector4f test1 = {8.4f, 2.6f, 25.0f, 251.0f};
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (2.6f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (25.0f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), (251.0f / 2.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_divide_equal_operator_based_on_vector_its_divide)
		{
			Kotek::ktk::math::vector4f test1 = {8.4f, 3.5f, 5.5f, 251.15f};
			Kotek::ktk::math::vector4f test2 = {2.0f, 0.5f, 52.5f, 151.0f};

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.0f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), (3.5f / 0.5f)));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), (5.5f / 52.5f)));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_W(), (251.15f / 151.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_modulo_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector4f test1 = {4.0f, 6.0f, 8.0f, 151.0f};
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_W(), (std::fmod(151.0f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_modulo_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector4f test1 = {4.0f, 6.0f, 8.0f, 15.0f};
			Kotek::ktk::math::vector4f test2 = {2.0f, 3.0f, 4.0f, 12.0f};

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(4.0f, 2.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Y(), (std::fmod(6.0f, 3.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_Z(), (std::fmod(8.0f, 4.0f))));
			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_W(), (std::fmod(15.0f, 12.0f))));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_unary_plus_operator)
		{
			Kotek::ktk::math::vector4f test1 = {10.0f, 5.0f, 15.0f, 151.0f};

			test1 = +test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), 15.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), 151.0f));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_unary_minus_operator)
		{
			Kotek::ktk::math::vector4f test1 = {10.0f, 5.0f, 15.0f, 151.0f};

			test1 = -test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), -5.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Z(), -15.0f));
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_W(), -151.0f));
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_comparison_equal_zeros)
		{
			Kotek::ktk::math::vector4f test1;
			Kotek::ktk::math::vector4f test2;

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_comparison_equal_random)
		{
			Kotek::ktk::math::vector4f test1(
				150.15125f, 1515.1414f, 14.24141f, 1515.3515f);
			Kotek::ktk::math::vector4f test2(
				150.15125f, 1515.1414f, 14.24141f, 1515.3515f);

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_comparison_equal_different_last_field)
		{
			Kotek::ktk::math::vector4f test1(15.3f, 4.4f, 15.15f, 0.0f);
			Kotek::ktk::math::vector4f test2(15.0f, 4.4f, 15.15f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_comparison_equal_different_first_field)
		{
			Kotek::ktk::math::vector4f test1(15.0f, 4.3f, 15.15f, 0.0f);
			Kotek::ktk::math::vector4f test2(15.0f, 4.4f, 15.15f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_comparison_equal_different_dirty_last_field)
		{
			Kotek::ktk::math::vector4f test1(15.14152f, 0.0f, 0.0f, 0.0f);
			Kotek::ktk::math::vector4f test2(15.14151f, 0.0f, 0.0f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_comparison_equal_different_dirty_first_field)
		{
			Kotek::ktk::math::vector4f test1(0.0f, 15.14152f, 0.0f, 0.0f);
			Kotek::ktk::math::vector4f test2(0.0f, 15.14151f, 0.0f, 0.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_comparison_not_equal_zeros)
		{
			Kotek::ktk::math::vector4f test1;
			Kotek::ktk::math::vector4f test2;

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_comparison_not_equal_different)
		{
			Kotek::ktk::math::vector4f test1(5.0f, 0.0f, 0.0f, 0.0f);
			Kotek::ktk::math::vector4f test2(2.0f, 0.0f, 0.0f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_comparison_not_equal_equal_dirty)
		{
			Kotek::ktk::math::vector4f test1(151.25151f, 0.0f, 0.0f, 0.0f);
			Kotek::ktk::math::vector4f test2(151.25151f, 0.0f, 0.0f, 0.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector4f_testing_comparison_not_equal_dirty)
		{
			Kotek::ktk::math::vector4f test1(150.10502f, 0.0f, 1.0f, 2.0f);
			Kotek::ktk::math::vector4f test2(150.10509f, 0.0f, 1.0f, 2.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		BOOST_AUTO_TEST_CASE(vector4f_testing_cast_operator_xmvector)
		{
			Kotek::ktk::math::vector4f test1(150.0f, 151.0f, 153.0f, 164.0f);

			DirectX::XMVECTOR vec = test1;

			float value_x = DirectX::XMVectorGetX(vec);
			float value_y = DirectX::XMVectorGetY(vec);
			float value_z = DirectX::XMVectorGetZ(vec);
			float value_w = DirectX::XMVectorGetW(vec);

			BOOST_CHECK(Kotek::ktk::is_equal(value_x, test1.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(value_y, test1.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(value_z, test1.Get_Z()));
			BOOST_CHECK(Kotek::ktk::is_equal(value_w, test1.Get_W()));
		}
		#endif

		BOOST_AUTO_TEST_CASE(vector4f_testing_binary_plus_operator_both_vectors)
		{
			Kotek::ktk::math::vector4f test1(50.5f, 2.5f, 3.5f, 252.5f);
			Kotek::ktk::math::vector4f test2(5.5f, 0.5f, 2.5f, 6.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(Kotek::ktk::is_equal(50.5f + 5.5f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f + 0.5f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f + 2.5f, new_vector.Get_Z()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(6.5f + 252.5f, new_vector.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_binary_subtract_operator_both_vectors)
		{
			Kotek::ktk::math::vector4f test1(50.5f, 25.0f, 3.5f, 25.5f);
			Kotek::ktk::math::vector4f test2(0.5f, 5.0f, 2.5f, 6.0f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(Kotek::ktk::is_equal(50.5f - 0.5f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.0f - 5.0f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f - 2.5f, new_vector.Get_Z()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.5f - 6.0f, new_vector.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_binary_mutiply_operator_both_vectors)
		{
			Kotek::ktk::math::vector4f test1(5.5f, 25.5f, 3.5f, 25.5f);
			Kotek::ktk::math::vector4f test2(2.2f, 5.5f, 2.5f, 25.5f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(25.5f * 5.5f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f * 2.5f, new_vector.Get_Z()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(25.5f * 25.5f, new_vector.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_binary_multiply_operator_vector_number)
		{
			Kotek::ktk::math::vector4f test1(5.5f, 2.5f, 3.5f, 15.15f);
			Kotek::ktk::math::base_decimal_t test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(Kotek::ktk::is_equal(5.5f * 2.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f * 2.2f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f * 2.2f, new_vector.Get_Z()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(15.15f * 2.2f, new_vector.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_binary_divide_operator_both_vectors)
		{
			Kotek::ktk::math::vector4f test1(6.6f, 3.6f, 3.5f, 15.5f);
			Kotek::ktk::math::vector4f test2(0.2f, 0.4f, 0.5f, 5.0f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.6f / 0.4f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.5f / 0.5f, new_vector.Get_Z()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.5f / 5.0f, new_vector.Get_W()));
		}

		BOOST_AUTO_TEST_CASE(
			vector4f_testing_binary_divide_operator_vector_number)
		{
			Kotek::ktk::math::vector4f test1(6.6f, 3.6f, 2.5f, 151.5f);
			Kotek::ktk::math::base_decimal_t test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(Kotek::ktk::is_equal(6.6f / 0.2f, new_vector.Get_X()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.6f / 0.2f, new_vector.Get_Y()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.5f / 0.2f, new_vector.Get_Z()));
			BOOST_CHECK(
				Kotek::ktk::is_equal(151.5f / 0.2f, new_vector.Get_W()));
		}
		#pragma endregion

		#pragma region Matrix 2x2

		#pragma endregion

		#pragma region Matrix 3x3

		#pragma endregion

		#pragma region Matrix 4x4
		BOOST_AUTO_TEST_CASE(matrix4x4f_constructor_values)
		{
			Kotek::ktk::math::matrix4x4f test(1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
				6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
				15.0f, 16.0f);

			BOOST_CHECK(Kotek::ktk::is_equal(1.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(4.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(5.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(6.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(7.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(8.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(9.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(10.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(11.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(12.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(13.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(14.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(16.0f, test.Get_33()));
		}

		BOOST_AUTO_TEST_CASE(matrix4x4f_constructor_copy_base_type)
		{
			Kotek::ktk::math::base_mat4x4_t copy = {1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
				15.0f, 16.0f};
			Kotek::ktk::math::matrix4x4f test(copy);

			BOOST_CHECK(Kotek::ktk::is_equal(1.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(4.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(5.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(6.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(7.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(8.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(9.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(10.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(11.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(12.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(13.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(14.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(16.0f, test.Get_33()));
		}

		BOOST_AUTO_TEST_CASE(matrix4x4f_constructor_copy_own_type)
		{
			Kotek::ktk::math::base_mat4x4_t copy(1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
				6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
				15.0f, 16.0f);
			Kotek::ktk::math::matrix4x4f test(copy);

			BOOST_CHECK(Kotek::ktk::is_equal(1.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(4.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(5.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(6.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(7.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(8.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(9.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(10.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(11.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(12.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(13.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(14.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(16.0f, test.Get_33()));
		}

		BOOST_AUTO_TEST_CASE(matrix4x4f_constructor_default)
		{
			Kotek::ktk::math::matrix4x4f test;

			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(0.0f, test.Get_33()));
		}

		BOOST_AUTO_TEST_CASE(
			matrix4x4f_assignment_operator_universal_initialization)
		{
			Kotek::ktk::math::matrix4x4f test = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
				6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
				15.0f, 16.0f};

			BOOST_CHECK(Kotek::ktk::is_equal(1.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(4.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(5.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(6.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(7.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(8.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(9.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(10.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(11.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(12.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(13.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(14.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(16.0f, test.Get_33()));
		}

		BOOST_AUTO_TEST_CASE(matri4x4f_assignment_operator_base_type)
		{
			Kotek::ktk::math::base_mat4x4_t base = {1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
				15.0f, 16.0f};

			Kotek::ktk::math::matrix4x4f test = base;

			BOOST_CHECK(Kotek::ktk::is_equal(1.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(4.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(5.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(6.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(7.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(8.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(9.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(10.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(11.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(12.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(13.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(14.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(16.0f, test.Get_33()));
		}

		BOOST_AUTO_TEST_CASE(matrix4x4f_assignment_plus_operator_universal)
		{
			Kotek::ktk::math::matrix4x4f test;

			test += {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
				10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

			BOOST_CHECK(Kotek::ktk::is_equal(1.0f, test.Get_00()));
			BOOST_CHECK(Kotek::ktk::is_equal(2.0f, test.Get_01()));
			BOOST_CHECK(Kotek::ktk::is_equal(3.0f, test.Get_02()));
			BOOST_CHECK(Kotek::ktk::is_equal(4.0f, test.Get_03()));
			BOOST_CHECK(Kotek::ktk::is_equal(5.0f, test.Get_10()));
			BOOST_CHECK(Kotek::ktk::is_equal(6.0f, test.Get_11()));
			BOOST_CHECK(Kotek::ktk::is_equal(7.0f, test.Get_12()));
			BOOST_CHECK(Kotek::ktk::is_equal(8.0f, test.Get_13()));
			BOOST_CHECK(Kotek::ktk::is_equal(9.0f, test.Get_20()));
			BOOST_CHECK(Kotek::ktk::is_equal(10.0f, test.Get_21()));
			BOOST_CHECK(Kotek::ktk::is_equal(11.0f, test.Get_22()));
			BOOST_CHECK(Kotek::ktk::is_equal(12.0f, test.Get_23()));
			BOOST_CHECK(Kotek::ktk::is_equal(13.0f, test.Get_30()));
			BOOST_CHECK(Kotek::ktk::is_equal(14.0f, test.Get_31()));
			BOOST_CHECK(Kotek::ktk::is_equal(15.0f, test.Get_32()));
			BOOST_CHECK(Kotek::ktk::is_equal(16.0f, test.Get_33()));
		}
		#pragma endregion

	#endif
#endif

	} // namespace Core
} // namespace Kotek