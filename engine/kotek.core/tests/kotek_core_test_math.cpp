#include "../kotek_std.h"
#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Core
	{
		void RegisterTests_Math_ForModule_Core(void)
		{
#ifdef KOTEK_USE_TESTS
			KOTEK_MESSAGE("Registered!");
#endif
		}

#ifdef KOTEK_USE_TESTS
	#ifdef KOTEK_DEBUG
		BOOST_AUTO_TEST_CASE(vector1f_testing_constructor_default) 
		{ 
			Kotek::ktk::math::vector1f vec;

			BOOST_REQUIRE(vec.Get_X() == 0.0f);
		}
	#endif
#endif

	} // namespace Core
} // namespace Kotek