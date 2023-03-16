#pragma once

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
enum class eStaticGeometryType;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK


KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
	ktk::cstring Translate_StaticGeometryType(eStaticGeometryType type);
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK