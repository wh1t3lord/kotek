#pragma once

	#ifdef KOTEK_MATH_LIBRARY_GLM
		#define KOTEK_USE_MATH_LIBRARY_GLM
	#elif defined(KOTEK_MATH_LIBRARY_DXM)
		#define KOTEK_USE_MATH_LIBRARY_DXM
	#else
		#error undefined math library. So it doesn't support by engine now
	#endif
	