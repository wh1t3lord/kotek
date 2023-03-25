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

enum class eRenderStatistics : ktk::enum_base_t
{
	kStat_Buffer_SSBO_Matrix,
	kStat_Buffer_Vertex,
	kStat_Buffer_Index,
	kStat_Buffer_Uniform,
	kEndOfEnum,
	kStat_Unknown = -1
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
