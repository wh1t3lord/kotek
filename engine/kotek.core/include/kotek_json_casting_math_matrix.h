#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::matrix2x2f& data)
{
	ktk::json::array row_1;
	ktk::json::array row_2;

	ktk::json::array result;

	row_1 = {data.Get_00(), data.Get_01()};
	row_2 = {data.Get_10(), data.Get_11()};

	result.push_back(row_1);
	result.push_back(row_2);

	write_to = result;
}

inline ktk::math::matrix2x2f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::matrix2x2f>&,
	const ktk::json::value& read_from)
{
	const auto& two_rows = read_from.as_array();

	const auto& row_1 = two_rows[0].as_array();
	const auto& row_2 = two_rows[1].as_array();

	float m00 = static_cast<float>(row_1[0].as_double());
	float m01 = static_cast<float>(row_1[1].as_double());

	float m10 = static_cast<float>(row_2[0].as_double());
	float m11 = static_cast<float>(row_2[1].as_double());

	ktk::math::matrix2x2f result(m00, m01, m10, m11);

	return result;
}

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::matrix3x3f& matrix)
{
	ktk::json::array row_1;
	ktk::json::array row_2;
	ktk::json::array row_3;

	ktk::json::array result;

	row_1 = {matrix.Get_00(), matrix.Get_01(), matrix.Get_02()};
	row_2 = {matrix.Get_10(), matrix.Get_11(), matrix.Get_12()};
	row_3 = {matrix.Get_20(), matrix.Get_21(), matrix.Get_22()};

	result.push_back(row_1);
	result.push_back(row_2);
	result.push_back(row_3);

	write_to = result;
}

inline ktk::math::matrix3x3f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::matrix3x3f>&,
	const ktk::json::value& read_from)
{
	const auto& three_rows = read_from.as_array();

	const auto& row_1 = three_rows[0].as_array();
	const auto& row_2 = three_rows[1].as_array();
	const auto& row_3 = three_rows[2].as_array();

	float m00 = static_cast<float>(row_1[0].as_double());
	float m01 = static_cast<float>(row_1[1].as_double());
	float m02 = static_cast<float>(row_2[2].as_double());

	float m10 = static_cast<float>(row_2[0].as_double());
	float m11 = static_cast<float>(row_2[1].as_double());
	float m12 = static_cast<float>(row_2[2].as_double());

	float m20 = static_cast<float>(row_3[0].as_double());
	float m21 = static_cast<float>(row_3[1].as_double());
	float m22 = static_cast<float>(row_3[2].as_double());

	ktk::math::matrix3x3f result(m00, m01, m02, m10, m11, m12, m20, m21, m22);

	return result;
}

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::matrix4x4f& matrix)
{
	ktk::json::array row_1;
	ktk::json::array row_2;
	ktk::json::array row_3;
	ktk::json::array row_4;

	ktk::json::array result;

	row_1 = {
		matrix.Get_00(), matrix.Get_01(), matrix.Get_02(), matrix.Get_03()};
	row_2 = {
		matrix.Get_10(), matrix.Get_11(), matrix.Get_12(), matrix.Get_13()};
	row_3 = {
		matrix.Get_20(), matrix.Get_21(), matrix.Get_22(), matrix.Get_23()};
	row_4 = {
		matrix.Get_30(), matrix.Get_31(), matrix.Get_32(), matrix.Get_33()};

	result.push_back(row_1);
	result.push_back(row_2);
	result.push_back(row_3);
	result.push_back(row_4);

	write_to = result;
}

inline ktk::math::matrix4x4f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::matrix4x4f>&,
	const ktk::json::value& read_from)
{
	const auto& four_rows = read_from.as_array();

	const auto& row_1 = four_rows[0].as_array();
	const auto& row_2 = four_rows[1].as_array();
	const auto& row_3 = four_rows[2].as_array();
	const auto& row_4 = four_rows[3].as_array();

	float m00 = static_cast<float>(row_1[0].as_double());
	float m01 = static_cast<float>(row_1[1].as_double());
	float m02 = static_cast<float>(row_2[2].as_double());
	float m03 = static_cast<float>(row_2[3].as_double());

	float m10 = static_cast<float>(row_2[0].as_double());
	float m11 = static_cast<float>(row_2[1].as_double());
	float m12 = static_cast<float>(row_2[2].as_double());
	float m13 = static_cast<float>(row_2[3].as_double());

	float m20 = static_cast<float>(row_3[0].as_double());
	float m21 = static_cast<float>(row_3[1].as_double());
	float m22 = static_cast<float>(row_3[2].as_double());
	float m23 = static_cast<float>(row_3[3].as_double());

	float m30 = static_cast<float>(row_4[0].as_double());
	float m31 = static_cast<float>(row_4[1].as_double());
	float m32 = static_cast<float>(row_4[2].as_double());
	float m33 = static_cast<float>(row_4[3].as_double());

	ktk::math::matrix4x4f result(m00, m01, m02, m03, m10, m11, m12, m13, m20,
		m21, m22, m23, m30, m31, m32, m33);

	return result;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif