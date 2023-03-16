#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
	ktk::cstring Translate_StaticGeometryType(eStaticGeometryType type)
	{
		switch (type)
		{
		case eStaticGeometryType::kTriangle:
		{
			return "Triangle";
		}
		case eStaticGeometryType::kBox:
		{
			return "Box";
		}
		case eStaticGeometryType::kEndOfEnum:
		{
			return "EndOfEnum";
		}
		case eStaticGeometryType::kUnknown:
		{
			return "Unknown";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_STATIC_GEOMETRY_TYPE";
		}
		}
	}
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
