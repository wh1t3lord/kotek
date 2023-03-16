#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

enum class eStaticGeometryType : ktk::enum_base_t
{
	kTriangle,
	kBox,
	kEndOfEnum,
	kUnknown = -1
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
