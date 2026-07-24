#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

template <typename Type>
void tag_invoke(const KUN_KTK json::value_from_tag&, KUN_KTK json::value& write_to,
	const KUN_KTK vector<Type>& data)
{
	KUN_KTK json::array temp;

	for (const auto& element : data)
	{
		temp.push_back(element);
	}

	write_to = temp;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif