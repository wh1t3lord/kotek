#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#include <wrl.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_PLATFORM_WINDOWS
template <typename T>
using comptr_t = Microsoft::WRL::ComPtr<T>;
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK