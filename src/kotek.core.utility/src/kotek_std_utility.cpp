#include "../include/kotek_std_utility.h"
#include <cmath>
#include <utility>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

bool is_equal(float a, float b,
	float relative_difference_factor) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	auto difference = std::fabs(a - b);
	auto magnitude = std::max(std::abs(a), std::abs(b));
	auto factor = relative_difference_factor * magnitude;

	if (difference <= factor)
		return true;

	return false;
}

bool is_equal(double a, double b,
	double relative_difference_factor) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	auto difference = std::fabs(a - b);
	auto magnitude = std::max(std::abs(a), std::abs(b));
	auto factor = relative_difference_factor * magnitude;

	if (difference <= factor)
		return true;

	return false;
}

bool is_equal(long double a, long double b,
	long double relative_difference_factor) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	auto difference = std::fabs(a - b);
	auto magnitude = std::max(std::abs(a), std::abs(b));
	auto factor = relative_difference_factor * magnitude;

	if (difference <= factor)
		return true;

	return false;
}

void set_thread_name(const char* p_name)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	__set_thread_name(GetCurrentThreadId(), p_name);
#else
	#error provide implementation for linux and mac
#endif
}

void __set_thread_name(unsigned int id, const char* p_name)
{
#ifdef KOTEK_PLATFORM_WINDOWS

	constexpr DWORD _kVC_EXCEPTION = 0x406D1388;

	#pragma pack(push, 8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType;     // Must be 0x1000.
		LPCSTR szName;    // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags;    // Reserved for future use, must be zero.
	} THREADNAME_INFOA;
	#pragma pack(pop)

	#ifdef KOTEK_DEBUG
	THREADNAME_INFOA info;

	info.dwType = 0x1000;
	info.szName = p_name;
	info.dwThreadID = id;
	info.dwFlags = 0;

	__try
	{
		RaiseException(_kVC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR),
			(ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
	#endif

#else
	#error provide implementation for linux and mac
#endif
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK