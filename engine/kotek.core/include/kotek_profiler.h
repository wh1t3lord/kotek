#pragma once

#include "kotek_std.h"
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
		class ktkProfiler
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
			void Initialize(const ktk::string& your_test_name,
				const ktk::string& path_where_to_save);

			void Shutdown(void);
		};
	} // namespace Core
} // namespace Kotek

#ifdef KOTEK_USE_CPU_PROFILER
	#define KOTEK_CPU_PROFILE() ZoneScoped;
#else
	#define KOTEK_CPU_PROFILE()
#endif