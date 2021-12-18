#include "kotek_profiler.h"

#ifdef KOTEK_USE_CPU_PROFILER

#endif

namespace Kotek
{
	namespace Core
	{
		ktkProfiler::ktkProfiler(void) {}

		ktkProfiler::~ktkProfiler(void)
		{
#ifdef KOTEK_USE_CPU_PROFILER

#endif
		}

		void ktkProfiler::Initialize(const ktk::string& your_test_name,
			const ktk::string& path_where_to_save)
		{
#ifdef KOTEK_USE_CPU_PROFILER
			tracy::StartupProfiler();
#endif
		}

		void ktkProfiler::Shutdown(void)
		{
#ifdef KOTEK_CPU_PROFILER
			tracy::ShutdownProfiler();
#endif
		}

	} // namespace Core
} // namespace Kotek
