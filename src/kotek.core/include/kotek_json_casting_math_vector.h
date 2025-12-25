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
	const vector1f& data
)
{
	json::array result = {data.x()};

	write_to = result;
}

inline vector1f tag_invoke(
	const json::value_to_tag<vector1f>&,
	const json::value& read_from
)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());

	vector1f result(x);

	return result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const vector2f& data
)
{
	json::array result = {data.x(), data.y()};

	write_to = result;
}

inline vector2f tag_invoke(
	const json::value_to_tag<vector2f>&,
	const json::value& read_from
)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());

	vector2f result(x, y);

	return result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const vector3f& data
)
{
	json::array result = {data.x(), data.y(), data.z()};

	write_to = result;
}

inline vector3f tag_invoke(
	const json::value_to_tag<vector3f>&,
	const json::value& read_from
)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());
	float z = static_cast<float>(vec[2].as_double());

	vector3f result(x, y, z);

	return result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const vector4f& data
)
{
	json::array result = {
		data.x(), data.y(), data.z(), data.w()
	};

	write_to = result;
}

inline vector4f tag_invoke(
	const json::value_to_tag<vector4f>&,
	const json::value& read_from
)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());
	float z = static_cast<float>(vec[2].as_double());
	float w = static_cast<float>(vec[3].as_double());

	vector4f result(x, y, z, w);

	return result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const quaternionf& data
)
{
	json::array result = {
		data.x(), data.y(), data.z(), data.w()
	};

	write_to = result;
}

inline quaternionf tag_invoke(
	const json::value_to_tag<quaternionf>&,
	const json::value& read_from
)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());
	float z = static_cast<float>(vec[2].as_double());
	float w = static_cast<float>(vec[3].as_double());

	quaternionf result(x, y, z, w);

	return result;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#endif