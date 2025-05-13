#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#include <cstring>

#ifdef KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
	#ifdef KOTEK_PLATFORM_WINDOWS
		#define _CRTDBG_MAP_ALLOC
		#define _CRTDBG_MAP_ALLOC_NEW
		#include <crtdbg.h>
		#include <assert.h>
	#endif
#endif

#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
	#include <mimalloc.h>
#endif

#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
	#define KOTEK_USE_MEMORY_ALLOCATOR_CLASS mi_stl_allocator
#else
	#define KOTEK_USE_MEMORY_ALLOCATOR_CLASS std::allocator
#endif

#include "offsetAllocator.hpp"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
namespace memory
{
#ifndef KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
	void free(void* pointer);
	void* malloc(kun_ktk size_t size);
	void* calloc(kun_ktk size_t count, kun_ktk size_t size);
	void* realloc(void* pointer, kun_ktk size_t newsize);
	char* strdup(const char* str);
#endif

	void* expand(void* pointer, kun_ktk size_t newsize);
	char* strndup(const char* str, size_t n);
	void* memcpy(void* p_dest, void* p_src, kun_ktk size_t count);
	void* memcpy(void* p_dest, const void* p_src, kun_ktk size_t count);
	void* memset(void* p_dest, int value, kun_ktk size_t bytes);

	struct ktkMemoryAllocationCounter
	{
		ktkMemoryAllocationCounter() {}
		~ktkMemoryAllocationCounter() {}

		std::atomic<uint32_t> new_count = 0;
		std::atomic<uint32_t> new_brackets_count = 0;
		std::atomic<uint32_t> delete_count = 0;
		std::atomic<uint32_t> delete_brackets_count = 0;
		std::atomic<uint32_t> allocation_count = 0;
	};

	ktkMemoryAllocationCounter* get_counter();

} // namespace memory

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
