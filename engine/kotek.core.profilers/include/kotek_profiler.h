#pragma once

#include <kotek.core.defines.static.profilers/include/kotek_core_defines_static_profilers.h>
#include <kotek.core.api/include/kotek_api.h>

#include <chrono>

#ifdef KOTEK_USE_CPU_PROFILER
	#include "./tracy/Tracy.hpp"

	#ifdef KOTEK_USE_GPU_PROFILER
		#include "./tracy/TracyVulkan.hpp"
	#endif

#endif

namespace Kotek
{
	namespace Core
	{
		class ktkProfiler : public ktkIProfiler
		{
		public:
			ktkProfiler(void);
			~ktkProfiler(void);

			/// <summary>
			/// You need to pass two arguments and the first argument you must
			/// pass without format
			/// </summary>
			/// <param name="your_test_name"></param>
			/// <param name="path_where_to_save"></param>
			void Initialize(void) override;
			void Shutdown(void) override;
		};
	} // namespace Core
} // namespace Kotek

#ifdef KOTEK_USE_CPU_PROFILER
	#define KOTEK_CPU_PROFILE() ZoneScoped;
#else
	#define KOTEK_CPU_PROFILE()
#endif