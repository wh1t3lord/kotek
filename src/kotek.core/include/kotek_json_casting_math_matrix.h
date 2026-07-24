#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const matrix2x2f& data
)
{
	json::array row_1;
	json::array row_2;

	json::array result;

	row_1 = {data.e(0, 0), data.e(0, 1)};
	row_2 = {data.e(1, 0), data.e(1, 1)};

	result.push_back(row_1);
	result.push_back(row_2);

	write_to = result;
}

inline matrix2x2f tag_invoke(
	const json::value_to_tag<matrix2x2f>&,
	const json::value& read_from
)
{
	const auto& two_rows = read_from.as_array();

	const auto& row_1 = two_rows[0].as_array();
	const auto& row_2 = two_rows[1].as_array();

	float m00 = static_cast<float>(row_1[0].to_number<float>());
	float m01 = static_cast<float>(row_1[1].to_number<float>());

	float m10 = static_cast<float>(row_2[0].to_number<float>());
	float m11 = static_cast<float>(row_2[1].to_number<float>());

	matrix2x2f result(m00, m01, m10, m11);

	return result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const matrix3x3f& matrix
)
{
	json::array row_1;
	json::array row_2;
	json::array row_3;

	json::array result;

	row_1 = {matrix[0][0], matrix[0][1], matrix[0][2]};
	row_2 = {matrix[1][0], matrix[1][1], matrix[1][2]};
	row_3 = {matrix[2][0], matrix[2][1], matrix[2][2]};

	result.push_back(row_1);
	result.push_back(row_2);
	result.push_back(row_3);

	write_to = result;
}

inline matrix3x3f tag_invoke(
	const json::value_to_tag<matrix3x3f>&,
	const json::value& read_from
)
{
	const auto& three_rows = read_from.as_array();

	const auto& row_1 = three_rows[0].as_array();
	const auto& row_2 = three_rows[1].as_array();
	const auto& row_3 = three_rows[2].as_array();

	float m00 = static_cast<float>(row_1[0].to_number<float>());
	float m01 = static_cast<float>(row_1[1].to_number<float>());
	float m02 = static_cast<float>(row_1[2].to_number<float>());

	float m10 = static_cast<float>(row_2[0].to_number<float>());
	float m11 = static_cast<float>(row_2[1].to_number<float>());
	float m12 = static_cast<float>(row_2[2].to_number<float>());

	float m20 = static_cast<float>(row_3[0].to_number<float>());
	float m21 = static_cast<float>(row_3[1].to_number<float>());
	float m22 = static_cast<float>(row_3[2].to_number<float>());

	matrix3x3f result(
		m00, m01, m02, m10, m11, m12, m20, m21, m22
	);

	return result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const matrix4x4f& matrix
)
{
	json::array row_1;
	json::array row_2;
	json::array row_3;
	json::array row_4;

	json::array result;

	row_1 = {
		matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]
	};
	row_2 = {
		matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]
	};
	row_3 = {
		matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]
	};
	row_4 = {
		matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]
	};

	result.push_back(row_1);
	result.push_back(row_2);
	result.push_back(row_3);
	result.push_back(row_4);

	write_to = result;
}

inline matrix4x4f tag_invoke(
	const json::value_to_tag<matrix4x4f>&,
	const json::value& read_from
)
{
	const auto& four_rows = read_from.as_array();

	const auto& row_1 = four_rows[0].as_array();
	const auto& row_2 = four_rows[1].as_array();
	const auto& row_3 = four_rows[2].as_array();
	const auto& row_4 = four_rows[3].as_array();

	float m00 = static_cast<float>(row_1[0].to_number<float>());
	float m01 = static_cast<float>(row_1[1].to_number<float>());
	float m02 = static_cast<float>(row_1[2].to_number<float>());
	float m03 = static_cast<float>(row_1[3].to_number<float>());

	float m10 = static_cast<float>(row_2[0].to_number<float>());
	float m11 = static_cast<float>(row_2[1].to_number<float>());
	float m12 = static_cast<float>(row_2[2].to_number<float>());
	float m13 = static_cast<float>(row_2[3].to_number<float>());

	float m20 = static_cast<float>(row_3[0].to_number<float>());
	float m21 = static_cast<float>(row_3[1].to_number<float>());
	float m22 = static_cast<float>(row_3[2].to_number<float>());
	float m23 = static_cast<float>(row_3[3].to_number<float>());

	float m30 = static_cast<float>(row_4[0].to_number<float>());
	float m31 = static_cast<float>(row_4[1].to_number<float>());
	float m32 = static_cast<float>(row_4[2].to_number<float>());
	float m33 = static_cast<float>(row_4[3].to_number<float>());

	matrix4x4f result(
		m00,
		m01,
		m02,
		m03,
		m10,
		m11,
		m12,
		m13,
		m20,
		m21,
		m22,
		m23,
		m30,
		m31,
		m32,
		m33
	);

	return result;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#else
	#error provide implementation if it is needed
#endif