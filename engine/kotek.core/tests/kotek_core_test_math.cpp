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
			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_Y(), 1613.44f));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_divide_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector1f test1 = 8.4f;
			Kotek::ktk::math::base_decimal_t test2 = 2.6f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.6f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_divide_equal_operator_based_on_vector_its_divide)
		{
			Kotek::ktk::math::vector1f test1 = 8.4f;
			Kotek::ktk::math::vector1f test2 = 2.6f;

			test1 /= test2;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), (8.4f / 2.6f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_modulo_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 5.3f;
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(5.3f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_modulo_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 5.3f;
			Kotek::ktk::math::vector1f test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(
				Kotek::ktk::is_equal(test1.Get_X(), (std::fmod(5.3f, 2.0f))));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_unary_plus_operator)
		{
			Kotek::ktk::math::vector1f test1 = 10.0f;

			test1 = +test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), 10.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_unary_minus_operator)
		{
			Kotek::ktk::math::vector1f test1 = 10.0f;

			test1 = -test1;

			BOOST_CHECK(Kotek::ktk::is_equal(test1.Get_X(), -10.0f));
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_equal_zeros)
		{
			Kotek::ktk::math::vector1f test1;
			Kotek::ktk::math::vector1f test2;

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_equal_random)
		{
			Kotek::ktk::math::vector1f test1(150.15125f);
			Kotek::ktk::math::vector1f test2(150.15125f);

			BOOST_CHECK(test1 == test2);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_equal_different)
		{
			Kotek::ktk::math::vector1f test1(15.3f);
			Kotek::ktk::math::vector1f test2(15.0f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_equal_different_dirty)
		{
			Kotek::ktk::math::vector1f test1(15.14152f);
			Kotek::ktk::math::vector1f test2(15.14151f);

			bool result = test1 == test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_zeros)
		{
			Kotek::ktk::math::vector1f test1;
			Kotek::ktk::math::vector1f test2;

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_different)
		{
			Kotek::ktk::math::vector1f test1(5.0f);
			Kotek::ktk::math::vector1f test2(2.0f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_equal_dirty)
		{
			Kotek::ktk::math::vector1f test1(151.25151f);
			Kotek::ktk::math::vector1f test2(151.25151f);

			bool result = test1 != test2;

			BOOST_CHECK(result == false);
		}

		BOOST_AUTO_TEST_CASE(vector2f_testing_comparison_not_equal_dirty)
		{
			Kotek::ktk::math::vector1f test1(150.10502f);
			Kotek::ktk::math::vector1f test2(150.10509f);

			bool result = test1 != test2;

			BOOST_CHECK(result == true);
		}

		#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		BOOST_AUTO_TEST_CASE(vector2f_testing_cast_operator_xmvector)
		{
			Kotek::ktk::math::vector1f test1(150.0f);

			DirectX::XMVECTOR vec = test1;

			float value = DirectX::XMVectorGetX(vec);

			BOOST_CHECK(Kotek::ktk::is_equal(value, test1.Get_X()));
		}
		#endif

		BOOST_AUTO_TEST_CASE(vector2f_testing_binary_plus_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::vector1f test2(5.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(new_vector == 56.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_plus_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::base_decimal_t test2(5.5f);

			auto new_vector = test1 + test2;

			BOOST_CHECK(new_vector == 56.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_subtract_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::vector1f test2(0.5f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(new_vector == 50.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_subtract_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(50.5f);
			Kotek::ktk::math::base_decimal_t test2(0.5f);

			auto new_vector = test1 - test2;

			BOOST_CHECK(new_vector == 50.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_mutiply_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(5.5f);
			Kotek::ktk::math::vector1f test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(new_vector == 12.1f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_multiply_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(5.5f);
			Kotek::ktk::math::base_decimal_t test2(2.2f);

			auto new_vector = test1 * test2;

			BOOST_CHECK(new_vector == 12.1f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_divide_operator_both_vectors)
		{
			Kotek::ktk::math::vector1f test1(6.6f);
			Kotek::ktk::math::vector1f test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(new_vector == 33.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector2f_testing_binary_divide_operator_vector_number)
		{
			Kotek::ktk::math::vector1f test1(6.6f);
			Kotek::ktk::math::base_decimal_t test2(0.2f);

			auto new_vector = test1 / test2;

			BOOST_CHECK(new_vector == 33.0f);
		}
		#pragma endregion

		#pragma region Vector3

		#pragma endregion

		#pragma region Vector4

		#pragma endregion
	#endif
#endif

	} // namespace Core
} // namespace Kotek