#include "../include/kotek_core.h"

#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

	#include <kotek.core.math/include/kotek_core_math.h>
	#include <kotek.core.math/include/kotek_std_math_matrixnf_view.h>
	#include <kotek.core.math/include/kotek_std_math_matrixnf_const_view.h>
	#include <kotek.core.math/include/kotek_std_math_vectornf_view.h>
	#include <kotek.core.math/include/kotek_std_math_vectornf_const_view.h>

	#include <gtest/gtest.h>

	// GLM is used as the reference implementation: every check below
	// computes the same expression through kotek's public math API
	// (whatever backend is configured) and through raw glm calls, then
	// compares them. Under KOTEK_MATH_LIBRARY=GLM this validates the test
	// logic itself; under KOTEK_MATH_LIBRARY=DXM it proves that the
	// DirectXMath backend honors the same observable contract
	// (column-major e(column, row), c(column) views, same algebra).
	#include <glm/glm.hpp>
	#include <glm/gtc/quaternion.hpp>
	#include <glm/gtc/type_ptr.hpp>

#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

namespace
{
	constexpr float k_tolerance = 1e-5f;

	void expect_near_vec2(
		const ktk::math::vector2f& actual, const glm::vec2& expected)
	{
		EXPECT_NEAR(actual.x(), expected.x, k_tolerance);
		EXPECT_NEAR(actual.y(), expected.y, k_tolerance);
	}

	void expect_near_vec3(
		const ktk::math::vector3f& actual, const glm::vec3& expected)
	{
		EXPECT_NEAR(actual.x(), expected.x, k_tolerance);
		EXPECT_NEAR(actual.y(), expected.y, k_tolerance);
		EXPECT_NEAR(actual.z(), expected.z, k_tolerance);
	}

	void expect_near_vec4(
		const ktk::math::vector4f& actual, const glm::vec4& expected)
	{
		EXPECT_NEAR(actual.x(), expected.x, k_tolerance);
		EXPECT_NEAR(actual.y(), expected.y, k_tolerance);
		EXPECT_NEAR(actual.z(), expected.z, k_tolerance);
		EXPECT_NEAR(actual.w(), expected.w, k_tolerance);
	}

	void expect_near_mat2(
		const ktk::math::matrix2x2f& actual, const glm::mat2& expected)
	{
		for (ktk::math::math_id_t column = 0; column < 2; ++column)
		{
			for (ktk::math::math_id_t row = 0; row < 2; ++row)
			{
				EXPECT_NEAR(actual.e(column, row),
					expected[column][row], k_tolerance);
			}
		}
	}

	void expect_near_mat3(
		const ktk::math::matrix3x3f& actual, const glm::mat3& expected)
	{
		for (ktk::math::math_id_t column = 0; column < 3; ++column)
		{
			for (ktk::math::math_id_t row = 0; row < 3; ++row)
			{
				EXPECT_NEAR(actual.e(column, row),
					expected[column][row], k_tolerance);
			}
		}
	}

	void expect_near_mat4(
		const ktk::math::matrix4x4f& actual, const glm::mat4& expected)
	{
		for (ktk::math::math_id_t column = 0; column < 4; ++column)
		{
			for (ktk::math::math_id_t row = 0; row < 4; ++row)
			{
				EXPECT_NEAR(actual.e(column, row),
					expected[column][row], k_tolerance);
			}
		}
	}

	void expect_near_quat(const ktk::math::quaternionf& actual,
		const glm::quat& expected)
	{
		EXPECT_NEAR(actual.x(), expected.x, k_tolerance);
		EXPECT_NEAR(actual.y(), expected.y, k_tolerance);
		EXPECT_NEAR(actual.z(), expected.z, k_tolerance);
		EXPECT_NEAR(actual.w(), expected.w, k_tolerance);
	}
} // namespace

TEST(MathBackend, vector1f_operations_match_glm)
{
	ktk::math::vector1f a(3.0f);
	ktk::math::vector1f b(1.5f);

	EXPECT_NEAR(ktk::math::get_math_length(a), glm::length(glm::vec1(3.0f)),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_dot(a, b),
		glm::dot(glm::vec1(3.0f), glm::vec1(1.5f)), k_tolerance);

	ktk::math::vector1f sum = a + b;
	EXPECT_NEAR(sum.x(), 4.5f, k_tolerance);

	ktk::math::vector1f difference = a - b;
	EXPECT_NEAR(difference.x(), 1.5f, k_tolerance);

	ktk::math::vector1f product = a * b;
	EXPECT_NEAR(product.x(), 4.5f, k_tolerance);

	ktk::math::vector1f quotient = a / b;
	EXPECT_NEAR(quotient.x(), 2.0f, k_tolerance);

	// normalize of a 1D vector must keep the sign, like glm does
	ktk::math::vector1f negative(-4.0f);
	EXPECT_NEAR(ktk::math::get_math_normalize(negative).x(),
		glm::normalize(glm::vec1(-4.0f)).x, k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_normalize(a).x(),
		glm::normalize(glm::vec1(3.0f)).x, k_tolerance);

	EXPECT_TRUE(a == ktk::math::vector1f(3.0f));
	EXPECT_TRUE(a != b);
	EXPECT_NEAR((-a).x(), -3.0f, k_tolerance);
}

TEST(MathBackend, vector2f_operations_match_glm)
{
	ktk::math::vector2f a(3.0f, 4.0f);
	ktk::math::vector2f b(1.0f, -2.0f);

	const glm::vec2 ga(3.0f, 4.0f);
	const glm::vec2 gb(1.0f, -2.0f);

	expect_near_vec2(a + b, ga + gb);
	expect_near_vec2(a - b, ga - gb);
	expect_near_vec2(a * b, ga * gb);
	expect_near_vec2(a / b, ga / gb);
	expect_near_vec2(a * 2.5f, ga * 2.5f);
	expect_near_vec2(-a, -ga);

	EXPECT_NEAR(ktk::math::get_math_dot(a, b), glm::dot(ga, gb),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_length(a), glm::length(ga),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_length_squared(a),
		glm::dot(ga, ga), k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_distance(a, b),
		glm::distance(ga, gb), k_tolerance);
	expect_near_vec2(ktk::math::get_math_normalize(a),
		glm::normalize(ga));

	// array constructor must read contiguous (x, y)
	const float raw[2] = {7.0f, 8.0f};
	ktk::math::vector2f from_array(raw, 2);
	EXPECT_NEAR(from_array.x(), 7.0f, k_tolerance);
	EXPECT_NEAR(from_array.y(), 8.0f, k_tolerance);
}

TEST(MathBackend, vector3f_operations_match_glm)
{
	ktk::math::vector3f a(1.0f, 2.0f, 3.0f);
	ktk::math::vector3f b(-2.0f, 0.0f, 1.0f);

	const glm::vec3 ga(1.0f, 2.0f, 3.0f);
	const glm::vec3 gb(-2.0f, 0.0f, 1.0f);

	expect_near_vec3(a + b, ga + gb);
	expect_near_vec3(a - b, ga - gb);
	expect_near_vec3(a * b, ga * gb);
	expect_near_vec3(a / b, ga / gb);
	expect_near_vec3(a * 3.0f, ga * 3.0f);
	expect_near_vec3(-a, -ga);

	EXPECT_NEAR(ktk::math::get_math_dot(a, b), glm::dot(ga, gb),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_length(a), glm::length(ga),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_length_squared(b),
		glm::dot(gb, gb), k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_distance(a, b),
		glm::distance(ga, gb), k_tolerance);
	expect_near_vec3(ktk::math::get_math_normalize(a),
		glm::normalize(ga));

	// cross is the handedness-sensitive operation: proves the DXM
	// backend keeps the same orientation as glm
	expect_near_vec3(ktk::math::get_math_cross(a, b),
		glm::cross(ga, gb));
	expect_near_vec3(
		ktk::math::get_math_cross(ktk::math::vector3f(1.0f, 0.0f, 0.0f),
			ktk::math::vector3f(0.0f, 1.0f, 0.0f)),
		glm::cross(glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)));
}

TEST(MathBackend, vector4f_operations_match_glm)
{
	ktk::math::vector4f a(1.0f, -2.0f, 3.0f, -4.0f);
	ktk::math::vector4f b(2.0f, 1.0f, -1.0f, 2.0f);

	const glm::vec4 ga(1.0f, -2.0f, 3.0f, -4.0f);
	const glm::vec4 gb(2.0f, 1.0f, -1.0f, 2.0f);

	expect_near_vec4(a + b, ga + gb);
	expect_near_vec4(a - b, ga - gb);
	expect_near_vec4(a * b, ga * gb);
	expect_near_vec4(a / b, ga / gb);
	expect_near_vec4(a * 0.5f, ga * 0.5f);
	expect_near_vec4(-a, -ga);

	EXPECT_NEAR(ktk::math::get_math_dot(a, b), glm::dot(ga, gb),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_length(a), glm::length(ga),
		k_tolerance);
	EXPECT_NEAR(ktk::math::get_math_length_squared(a),
		glm::dot(ga, ga), k_tolerance);
	expect_near_vec4(ktk::math::get_math_normalize(a),
		glm::normalize(ga));
}

TEST(MathBackend, matrix2x2f_column_major_contract)
{
	ktk::math::matrix2x2f mat(1.0f, 2.0f, 3.0f, 4.0f);
	const glm::mat2 expected(1.0f, 2.0f, 3.0f, 4.0f);

	// e(column, row) must match glm's [column][row]
	expect_near_mat2(mat, expected);

	// c(column) is a contiguous view over the column's rows
	ktk::math::vectornf_view_t column_1 = mat.c(1);
	EXPECT_EQ(column_1.get_row_count(), 2u);
	EXPECT_NEAR(column_1[0], 3.0f, k_tolerance);
	EXPECT_NEAR(column_1[1], 4.0f, k_tolerance);

	ktk::math::vectornf_view_t column_0 = mat[0];
	EXPECT_NEAR(column_0[0], 1.0f, k_tolerance);
	EXPECT_NEAR(column_0[1], 2.0f, k_tolerance);

	// e() is an lvalue: writes must land in the same (column, row) slot
	mat.e(1, 0) = 42.0f;
	EXPECT_NEAR(mat.e(1, 0), 42.0f, k_tolerance);
	EXPECT_NEAR(mat.c(1)[0], 42.0f, k_tolerance);
}

TEST(MathBackend, matrix3x3f_column_major_contract)
{
	ktk::math::matrix3x3f mat(
		1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
	const glm::mat3 expected(
		1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

	expect_near_mat3(mat, expected);

	ktk::math::vectornf_view_t column_2 = mat.c(2);
	EXPECT_EQ(column_2.get_row_count(), 3u);
	EXPECT_NEAR(column_2[0], 7.0f, k_tolerance);
	EXPECT_NEAR(column_2[2], 9.0f, k_tolerance);

	// data() is the raw column-major blob, identical layout to glm
	const float* kotek_data = mat.data();
	const float* glm_data = glm::value_ptr(expected);
	for (int i = 0; i < 9; ++i)
	{
		EXPECT_NEAR(kotek_data[i], glm_data[i], k_tolerance);
	}
}

TEST(MathBackend, matrix4x4f_column_major_contract)
{
	ktk::math::matrix4x4f mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	const glm::mat4 expected(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
		8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	expect_near_mat4(mat, expected);

	ktk::math::vectornf_view_t column_3 = mat.c(3);
	EXPECT_EQ(column_3.get_row_count(), 4u);
	EXPECT_NEAR(column_3[0], 13.0f, k_tolerance);
	EXPECT_NEAR(column_3[3], 16.0f, k_tolerance);

	const float* kotek_data = mat.data();
	const float* glm_data = glm::value_ptr(expected);
	for (int i = 0; i < 16; ++i)
	{
		EXPECT_NEAR(kotek_data[i], glm_data[i], k_tolerance);
	}
}

TEST(MathBackend, matrix2x2f_arithmetic_matches_glm)
{
	ktk::math::matrix2x2f a(1.0f, 2.0f, 3.0f, 4.0f);
	ktk::math::matrix2x2f b(5.0f, 1.0f, 2.0f, 3.0f);

	const glm::mat2 ga(1.0f, 2.0f, 3.0f, 4.0f);
	const glm::mat2 gb(5.0f, 1.0f, 2.0f, 3.0f);

	expect_near_mat2(a + b, ga + gb);
	expect_near_mat2(a - b, ga - gb);
	expect_near_mat2(a * b, ga * gb);
	expect_near_mat2(b * a, gb * ga);
	expect_near_mat2(a * 2.5f, ga * 2.5f);
	expect_near_mat2(a / 2.0f, ga / 2.0f);

	ktk::math::matrix2x2f accumulated = a;
	accumulated *= b;
	expect_near_mat2(accumulated, ga * gb);

	ktk::math::matrix2x2f added = a;
	added += b;
	expect_near_mat2(added, ga + gb);

	EXPECT_TRUE(a == ktk::math::matrix2x2f(1.0f, 2.0f, 3.0f, 4.0f));
	EXPECT_TRUE(a != b);
}

TEST(MathBackend, matrix3x3f_arithmetic_matches_glm)
{
	ktk::math::matrix3x3f a(
		1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f);
	ktk::math::matrix3x3f b(
		2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f, 2.0f, 1.0f);

	const glm::mat3 ga(
		1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f);
	const glm::mat3 gb(
		2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f, 2.0f, 1.0f);

	expect_near_mat3(a + b, ga + gb);
	expect_near_mat3(a - b, ga - gb);
	expect_near_mat3(a * b, ga * gb);
	expect_near_mat3(b * a, gb * ga);
	expect_near_mat3(a * 1.5f, ga * 1.5f);
	expect_near_mat3(a / 2.0f, ga / 2.0f);

	ktk::math::matrix3x3f accumulated = a;
	accumulated *= b;
	expect_near_mat3(accumulated, ga * gb);

	EXPECT_TRUE(a == ktk::math::matrix3x3f(
						1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f));
	EXPECT_TRUE(a != b);
}

TEST(MathBackend, matrix4x4f_arithmetic_matches_glm)
{
	ktk::math::matrix4x4f a(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f);
	ktk::math::matrix4x4f b(1.0f, 0.0f, 2.0f, 1.0f, 0.0f, 3.0f, 1.0f,
		1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f);

	const glm::mat4 ga(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f);
	const glm::mat4 gb(1.0f, 0.0f, 2.0f, 1.0f, 0.0f, 3.0f, 1.0f, 1.0f,
		2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f);

	expect_near_mat4(a + b, ga + gb);
	expect_near_mat4(a - b, ga - gb);
	expect_near_mat4(a * b, ga * gb);
	expect_near_mat4(b * a, gb * ga);
	expect_near_mat4(a * 0.25f, ga * 0.25f);
	expect_near_mat4(a / 4.0f, ga / 4.0f);

	ktk::math::matrix4x4f accumulated = a;
	accumulated *= b;
	expect_near_mat4(accumulated, ga * gb);

	EXPECT_TRUE(a == ktk::math::matrix4x4f(2.0f, 1.0f, 0.0f, 0.0f, 1.0f,
						2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f,
						1.0f, 2.0f));
	EXPECT_TRUE(a != b);
}

TEST(MathBackend, matrix_vector_multiplication_matches_glm)
{
	// 2x2
	{
		ktk::math::matrix2x2f m(1.0f, 2.0f, 3.0f, 4.0f);
		ktk::math::vector2f v(5.0f, -1.0f);

		const glm::mat2 gm(1.0f, 2.0f, 3.0f, 4.0f);
		const glm::vec2 gv(5.0f, -1.0f);

		expect_near_vec2(m * v, gm * gv);
		expect_near_vec2(v * m, gv * gm);
	}

	// 3x3
	{
		ktk::math::matrix3x3f m(
			1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f);
		ktk::math::vector3f v(2.0f, -1.0f, 3.0f);

		const glm::mat3 gm(
			1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f);
		const glm::vec3 gv(2.0f, -1.0f, 3.0f);

		expect_near_vec3(m * v, gm * gv);
		expect_near_vec3(v * m, gv * gm);
	}

	// 4x4
	{
		ktk::math::matrix4x4f m(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f);
		ktk::math::vector4f v(1.0f, 2.0f, -1.0f, 0.5f);

		const glm::mat4 gm(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f);
		const glm::vec4 gv(1.0f, 2.0f, -1.0f, 0.5f);

		expect_near_vec4(m * v, gm * gv);
		expect_near_vec4(v * m, gv * gm);
	}
}

TEST(MathBackend, matrix_transpose_determinant_inverse_match_glm)
{
	// 2x2 (det == -2)
	{
		ktk::math::matrix2x2f m(1.0f, 2.0f, 3.0f, 4.0f);
		const glm::mat2 gm(1.0f, 2.0f, 3.0f, 4.0f);

		expect_near_mat2(ktk::math::transpose(m), glm::transpose(gm));
		EXPECT_NEAR(ktk::math::get_math_determinant(m),
			glm::determinant(gm), k_tolerance);
		expect_near_mat2(
			ktk::math::get_math_inverse(m), glm::inverse(gm));

		// M * M^-1 == identity
		ktk::math::matrix2x2f identity =
			m * ktk::math::get_math_inverse(m);
		expect_near_mat2(identity, glm::mat2(1.0f));
	}

	// 3x3 (det == -7)
	{
		ktk::math::matrix3x3f m(
			1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f);
		const glm::mat3 gm(
			1.0f, 2.0f, 0.0f, 3.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f);

		expect_near_mat3(ktk::math::transpose(m), glm::transpose(gm));
		EXPECT_NEAR(ktk::math::get_math_determinant(m),
			glm::determinant(gm), k_tolerance);
		expect_near_mat3(
			ktk::math::get_math_inverse(m), glm::inverse(gm));

		ktk::math::matrix3x3f identity =
			m * ktk::math::get_math_inverse(m);
		expect_near_mat3(identity, glm::mat3(1.0f));
	}

	// 4x4 (tridiagonal, well conditioned)
	{
		ktk::math::matrix4x4f m(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f);
		const glm::mat4 gm(2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f);

		expect_near_mat4(ktk::math::transpose(m), glm::transpose(gm));
		EXPECT_NEAR(ktk::math::get_math_determinant(m),
			glm::determinant(gm), k_tolerance);
		expect_near_mat4(
			ktk::math::get_math_inverse(m), glm::inverse(gm));

		ktk::math::matrix4x4f identity =
			m * ktk::math::get_math_inverse(m);
		expect_near_mat4(identity, glm::mat4(1.0f));
	}
}

TEST(MathBackend, quaternion_component_contract)
{
	ktk::math::quaternionf quat(0.1f, 0.2f, 0.3f, 0.4f);

	// kotek's ctor contract is (x, y, z, w) and the accessors must
	// read back the same components in the same slots
	EXPECT_NEAR(quat.x(), 0.1f, k_tolerance);
	EXPECT_NEAR(quat.y(), 0.2f, k_tolerance);
	EXPECT_NEAR(quat.z(), 0.3f, k_tolerance);
	EXPECT_NEAR(quat.w(), 0.4f, k_tolerance);
}

TEST(MathBackend, quaternion_multiply_normalize_slerp_match_glm)
{
	// two unit quaternions with a positive dot product (short slerp path)
	constexpr float q1x = 0.18257419f;
	constexpr float q1y = 0.36514837f;
	constexpr float q1z = 0.54772256f;
	constexpr float q1w = 0.73029674f;

	ktk::math::quaternionf a(q1x, q1y, q1z, q1w);
	ktk::math::quaternionf b(-0.5f, 0.5f, -0.5f, 0.5f);

	const glm::quat ga(q1w, q1x, q1y, q1z);
	const glm::quat gb(0.5f, -0.5f, 0.5f, -0.5f);

	// hamilton product: a * b applies b's rotation first, like glm
	expect_near_quat(a * b, ga * gb);
	expect_near_quat(b * a, gb * ga);

	ktk::math::quaternionf accumulated = a;
	accumulated *= b;
	expect_near_quat(accumulated, ga * gb);

	// normalize of a non-unit quaternion
	ktk::math::quaternionf non_unit(1.0f, 2.0f, 3.0f, 4.0f);
	const glm::quat g_non_unit(4.0f, 1.0f, 2.0f, 3.0f);
	expect_near_quat(
		ktk::math::get_math_normalize(non_unit), glm::normalize(g_non_unit));

	// slerp endpoints and interior points
	for (float t : {0.0f, 0.25f, 0.5f, 0.75f, 1.0f})
	{
		expect_near_quat(
			ktk::math::get_math_slerp(a, b, t), glm::slerp(ga, gb, t));
	}
}

TEST(MathBackend, matrix_views_keep_column_major_layout)
{
	float storage[16];
	for (int i = 0; i < 16; ++i)
	{
		storage[i] = static_cast<float>(i + 1);
	}

	ktk::math::matrixnf_view_t view(storage, 4, 4);

	// e(column, row) reads storage[column * row_count + row]
	for (ktk::math::math_id_t column = 0; column < 4; ++column)
	{
		for (ktk::math::math_id_t row = 0; row < 4; ++row)
		{
			EXPECT_NEAR(view.e(column, row),
				storage[column * 4 + row], k_tolerance);
		}
	}

	// column view aliases the same memory
	ktk::math::vectornf_view_t column_2 = view.c(2);
	EXPECT_NEAR(column_2[1], storage[2 * 4 + 1], k_tolerance);

	// writes through the view land in the storage
	view.e(1, 2) = -5.0f;
	EXPECT_NEAR(storage[1 * 4 + 2], -5.0f, k_tolerance);
	view.e(1, 2) = 7.0f;

	// a matrix built from the view sees the same elements
	ktk::math::matrix4x4f mat(view);
	for (ktk::math::math_id_t column = 0; column < 4; ++column)
	{
		for (ktk::math::math_id_t row = 0; row < 4; ++row)
		{
			EXPECT_NEAR(mat.e(column, row),
				static_cast<float>(column * 4 + row + 1), k_tolerance);
		}
	}

	// vector view over the same blob
	ktk::math::vectornf_view_t vector_view(storage, 4);
	EXPECT_NEAR(vector_view[0], 1.0f, k_tolerance);
	EXPECT_NEAR(vector_view[3], 4.0f, k_tolerance);
	EXPECT_NEAR(vector_view.e(0, 2), 3.0f, k_tolerance);
}

TEST(MathBackend, matrix_constructors_from_views_match_glm)
{
	float storage2[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	ktk::math::matrixnf_view_t view2(storage2, 2, 2);
	ktk::math::matrix2x2f mat2(view2);
	expect_near_mat2(mat2, glm::mat2(1.0f, 2.0f, 3.0f, 4.0f));

	float storage3[9] = {
		1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
	ktk::math::matrixnf_view_t view3(storage3, 3, 3);
	ktk::math::matrix3x3f mat3(view3);
	expect_near_mat3(mat3,
		glm::mat3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
}

#endif

// link anchor (always defined, external linkage on purpose): gtest TUs in a
// static lib are unreferenced archive members, so the linker drops their obj
// and the tests never register — /INCREMENTAL then preserves that state
// forever. RegisterAllTests in main_core_dll.cpp references every registrar,
// and main_core_dll.obj is always linked (it defines InitializeModule_Core),
// which pulls this TU's obj out of kotek.core.lib — the established idiom of
// this module's runtime tests.
void RegisterTests_MathBackends_ForModule_Core(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
