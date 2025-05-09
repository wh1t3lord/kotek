#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::vector1f& data)
{
	ktk::json::array result = {data.x()};

	write_to = result;
}

inline ktk::math::vector1f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::vector1f>&,
	const ktk::json::value& read_from)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());

	ktk::math::vector1f result(x);

	return result;
}

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::vector2f& data)
{
	ktk::json::array result = {data.x(), data.y()};

	write_to = result;
}

inline ktk::math::vector2f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::vector2f>&,
	const ktk::json::value& read_from)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());

	ktk::math::vector2f result(x, y);

	return result;
}

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::vector3f& data)
{
	ktk::json::array result = {data.x(), data.y(), data.z()};

	write_to = result;
}

inline ktk::math::vector3f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::vector3f>&,
	const ktk::json::value& read_from)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());
	float z = static_cast<float>(vec[2].as_double());

	ktk::math::vector3f result(x, y, z);

	return result;
}

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::vector4f& data)
{
	ktk::json::array result = {
		data.x(), data.y(), data.z(), data.w()};

	write_to = result;
}

inline ktk::math::vector4f tag_invoke(
	const ktk::json::value_to_tag<ktk::math::vector4f>&,
	const ktk::json::value& read_from)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());
	float z = static_cast<float>(vec[2].as_double());
	float w = static_cast<float>(vec[3].as_double());

	ktk::math::vector4f result(x, y, z, w);

	return result;
}

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::math::quaternionf& data)
{
	ktk::json::array result = {
		data.x(), data.y(), data.z(), data.w()};

	write_to = result;
}

inline ktk::math::quaternionf tag_invoke(
	const ktk::json::value_to_tag<ktk::math::quaternionf>&,
	const ktk::json::value& read_from)
{
	const auto& vec = read_from.as_array();

	float x = static_cast<float>(vec[0].as_double());
	float y = static_cast<float>(vec[1].as_double());
	float z = static_cast<float>(vec[2].as_double());
	float w = static_cast<float>(vec[3].as_double());

	ktk::math::quaternionf result(x, y, z, w);

	return result;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#endif