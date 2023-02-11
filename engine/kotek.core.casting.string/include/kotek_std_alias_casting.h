#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.types.string/include/kotek_core_types_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace cast
{
	// @ Converts from 1,0,yes,no,true,false into appropriate bool type
	// Register independent
	bool to_bool(const string& your_logical_string_written_in_text) noexcept;
} // namespace cast

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
