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


KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
namespace memory
{
#ifndef KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
	void free(void* pointer);
	void* malloc(ktk::size_t size);
	void* calloc(ktk::size_t count, ktk::size_t size);
	void* realloc(void* pointer, ktk::size_t newsize);
	char* strdup(const char* str);
#endif

	void* expand(void* pointer, ktk::size_t newsize);
	char* strndup(const char* str, size_t n);
	void* memcpy(void* p_dest, void* p_src, ktk::size_t count);
	void* memcpy(void* p_dest, const void* p_src, ktk::size_t count);

} // namespace memory

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
