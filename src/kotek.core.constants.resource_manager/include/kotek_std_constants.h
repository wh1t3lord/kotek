#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK

namespace ktkResourceTextFileHeader
{
	/// @brief \~english reduced and optimized field names for json
	/// serialization
	constexpr const char kField_JsonRequiredSizeForConstruction[] = "k_jsfc";
	constexpr const char kField_ChunkIterationsCount[] = "k_cic";
	constexpr const char kField_ChunkSize[] = "k_cs";

} // namespace ktkResourceTextFileHeader

static_assert(sizeof(ktkResourceTextFileHeader::kField_ChunkIterationsCount) /
			sizeof(ktkResourceTextFileHeader::kField_ChunkIterationsCount[0]) <
		8,
	"too long field name");
static_assert(sizeof(ktkResourceTextFileHeader::kField_ChunkSize) /
			sizeof(ktkResourceTextFileHeader::kField_ChunkSize[0]) <
		8,
	"too long field name");
static_assert(
	sizeof(ktkResourceTextFileHeader::kField_JsonRequiredSizeForConstruction) /
			sizeof(ktkResourceTextFileHeader::
					kField_JsonRequiredSizeForConstruction[0]) <
		8,
	"too long field name");

KOTEK_END_NAMESPACE_KOTEK
