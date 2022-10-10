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

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkProfiler : public ktkIProfiler
{
public:
	ktkProfiler(void);
	~ktkProfiler(void);

	void Initialize(void) override;
	void Shutdown(void) override;

	void FrameMark(void) override;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#ifdef KOTEK_USE_CPU_PROFILER
	#define KOTEK_CPU_PROFILE() ZoneScoped;
#else
	#define KOTEK_CPU_PROFILE()
#endif