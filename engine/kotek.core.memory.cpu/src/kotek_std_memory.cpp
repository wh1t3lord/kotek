#include "../include/kotek_std_memory.h"
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#include <stdlib.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		#include <mimalloc-new-delete.h>
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace memory
{
	void free(void* pointer)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		mi_free(pointer);
#else
		// TODO: provide a function here
		::free(pointer);
#endif
	}

	void* malloc(ktk::size_t size)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_malloc(size);
#else
		return ::malloc(size);
#endif
	}

	void* calloc(ktk::size_t count, ktk::size_t size)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_calloc(count, size);
#else
		return ::calloc(count, size);
#endif
	}

	void* realloc(void* pointer, ktk::size_t newsize)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_realloc(pointer, newsize);
#else
		return ::realloc(pointer, newsize);
#endif
	}

	void* expand(void* pointer, ktk::size_t newsize)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_expand(pointer, newsize);
#else
		// TODO: provide a function herer
		return nullptr;
	//	return ::expand(pointer, newsize);
#endif
	}

	char* strdup(const char* str)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_strdup(str);
#else
		return ::strdup(str);
#endif
	}

	char* strndup(const char* str, size_t n)
	{
#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_strndup(str, n);
#else
		// TODO: replace to function
		return nullptr;
#endif
	}

	void* memcpy(void* p_dest, void* p_src, ktk::size_t count)
	{
		return std::memcpy(p_dest, p_src, count);
	}
} // namespace memory

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
