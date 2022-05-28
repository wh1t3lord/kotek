#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#include <wrl.h>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_PLATFORM_WINDOWS
		template <typename T>
		using comptr_t = Microsoft::WRL::ComPtr<T>;
#endif
	} // namespace ktk
} // namespace Kotek