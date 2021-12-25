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
		#pragma region Vector1

		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_default)
		{
			Kotek::ktk::math::vector1f vec;

			BOOST_REQUIRE(vec.Get_X() == 0.0f);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_based_on_number)
		{
			Kotek::ktk::math::vector1f vec(5.0f);

			BOOST_CHECK(vec.Get_X() == 5.0f);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_based_on_struct){
		#ifdef KOTEK_USE_MATH_LIBRARY_GLM
		#endif
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_copy_constructor)
		{
			Kotek::ktk::math::vector1f vec_original(550.5f);
			Kotek::ktk::math::vector1f vec_copy(vec_original);

			BOOST_CHECK(vec_copy.Get_X() == vec_original.Get_X());
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_assignment_operator_based_on_own_type)
		{
			Kotek::ktk::math::vector1f some(50.0f);
			Kotek::ktk::math::vector1f some2 = some;

			BOOST_CHECK(some2.Get_X() == some.Get_X());
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_assignment_operator_based_on_base_type)
		{
			Kotek::ktk::math::base_vec1_t some(51.0f);
			Kotek::ktk::math::vector1f some2 = some;

			BOOST_CHECK(some2.Get_X() == some);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_setter_single_depth)
		{
			Kotek::ktk::math::vector1f test;

			test.Set_X(105.0f);

			BOOST_CHECK(test.Get_X() == 105.0f);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_setter_two_depth)
		{
			Kotek::ktk::math::vector1f test2;

			test2.Set_X(50.0f).Set_X(150.0f);

			BOOST_CHECK(test2.Get_X() == 150.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_plus_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 3.5f;
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 += test2;

			BOOST_CHECK(test1.Get_X() == 9.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_plus_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 3.5f;
			Kotek::ktk::math::vector1f test2 = 5.5f;

			test1 += test2;

			BOOST_CHECK(test1.Get_X() == 9.0f);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_subtract_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 5.5f;
			Kotek::ktk::math::base_decimal_t test2 = 3.5f;

			test1 -= test2;

			BOOST_CHECK(test1.Get_X() == 2.0f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_subtract_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 5.5f;
			Kotek::ktk::math::vector1f test2 = 3.5f;

			test1 -= test2;

			BOOST_CHECK(test1.Get_X() == 2.0f);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_multiply_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector1f test1 = 3.2f;
			Kotek::ktk::math::base_decimal_t test2 = 5.5f;

			test1 *= test2;

			BOOST_CHECK(test1.Get_X() == 17.6f);
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_multiply_equal_operator_based_on_vector_its_per_compunent_multiply)
		{
			Kotek::ktk::math::vector1f test1 = 3.2f;
			Kotek::ktk::math::vector1f test2 = 5.5f;

			test1 *= test2;       

			BOOST_CHECK(test1.Get_X() == 17.6f);
		}

		BOOST_AUTO_TEST_CASE(vector1f_testing_divide_equal_operator_based_on_number_its_scale)
		{
			Kotek::ktk::math::vector1f test1 = 8.4f;
			Kotek::ktk::math::base_decimal_t test2 = 2.6f;

			test1 /= test2;

			BOOST_CHECK(test1.Get_X() == (8.4f / 2.6f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_divide_equal_operator_based_on_vector_its_divide)
		{
			Kotek::ktk::math::vector1f test1 = 8.4f;
			Kotek::ktk::math::vector1f test2 = 2.6f;

			test1 /= test2;

			BOOST_CHECK(test1.Get_X() == (8.4f / 2.6f));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_modulo_equal_operator_based_on_number)
		{
			Kotek::ktk::math::vector1f test1 = 5.3f;
			Kotek::ktk::math::base_decimal_t test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(test1.Get_X() == (std::fmod(5.3f, 2.0f)));
		}

		BOOST_AUTO_TEST_CASE(
			vector1f_testing_modulo_equal_operator_based_on_vector)
		{
			Kotek::ktk::math::vector1f test1 = 5.3f;
			Kotek::ktk::math::vector1f test2 = 2.0f;

			test1 %= test2;

			BOOST_CHECK(test1.Get_X() == (std::fmod(5.3f, 2.0f)));
		}
		#pragma endregion

		#pragma region Vector2

		#pragma endregion

		#pragma region Vector3

		#pragma endregion

		#pragma region Vector4

		#pragma endregion
	#endif
#endif

	} // namespace Core
} // namespace Kotek