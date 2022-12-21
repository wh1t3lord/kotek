#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktk::string tag_invoke(const ktk::json::value_to_tag<ktk::string>&, const ktk::json::value& read_from) 
{
	const ktk::json::array& array = read_from.as_array();

	ktk::vector<ktk::tchar> casted;	

	for (const auto& value : array)
	{
		casted.push_back(static_cast<ktk::tchar>(value.as_int64()));
	}

	return ktk::string(casted.data());
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif