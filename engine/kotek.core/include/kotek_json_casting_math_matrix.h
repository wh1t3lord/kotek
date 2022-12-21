#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

void tag_invoke(const ktk::json::value_from_tag&, ktk::json::value& write_to,
	const ktk::math::matrix2x2f& data)
{
	write_to = {data.Get_00(), data.Get_01(), data.Get_10(), data.Get_11()};
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif