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
			ktk::string build_path = path_where_to_save;
			ktk::string build_filename = your_test_name;

			build_filename += ".pltraw";
			build_path.appendPath(build_filename);

			KOTEK_ASSERT(build_path.get_as_legacy().size() <= 256,
				"you can't use string that contains more "
				"than 256 symbols!");

	
#endif
		}

		void ktkProfiler::Shutdown(void) {}

	} // namespace Core
} // namespace Kotek
