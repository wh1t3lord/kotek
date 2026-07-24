#include "../include/kotek_profiler.h"

#ifdef KOTEK_USE_CPU_PROFILER

#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkProfiler::ktkProfiler(void) {}

ktkProfiler::~ktkProfiler(void) {}

void ktkProfiler::Initialize(void)
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

void ktkProfiler::FrameMark(void)
{
#ifdef KOTEK_CPU_PROFILER
	FrameMark;
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
