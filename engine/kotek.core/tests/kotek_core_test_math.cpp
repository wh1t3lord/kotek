#include "../kotek_std.h"
#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Core
	{
		void RegisterTests_Math_ForModuleCore(void)
		{
#ifdef KOTEK_USE_TESTS
			KOTEK_MESSAGE("Registered!");
#endif
		}

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG

	#endif
#endif

	} // namespace Core
} // namespace Kotek