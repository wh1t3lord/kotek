#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to,
	const ktkJson& data)
{
	write_to = data.GetObject();
}

inline ktkJson tag_invoke(
	const ktk::json::value_to_tag<ktkJson>&, const ktk::json::value& read_from)
{
	const ktk::json::object& object = read_from.as_object();

	return ktkJson(object);
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif