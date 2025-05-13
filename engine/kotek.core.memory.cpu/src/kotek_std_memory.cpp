#include "../include/kotek_std_memory.h"
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#include <stdlib.h>

#ifdef KOTEK_DEBUG

	#ifdef KOTEK_PLATFORM_WINDOWS
		#include <Windows.h>
	#endif
#endif

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		#include <mimalloc-new-delete.h>
	#else

		#ifdef KOTEK_DEBUG

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
namespace memory
{
	ktkMemoryAllocationCounter* get_counter()
	{
		static HANDLE hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, nullptr,
			PAGE_READWRITE, 0, sizeof(ktkMemoryAllocationCounter),
			L"Local\\MyMemoryCounter");
		static bool first = true;
		auto ptr =
			reinterpret_cast<ktkMemoryAllocationCounter*>(::MapViewOfFile(hMap,
				FILE_MAP_WRITE, 0, 0, sizeof(ktkMemoryAllocationCounter)));
		if (first)
		{
			// zero-initialize only once
			new (ptr) ktkMemoryAllocationCounter;
			first = false;
		}
		return ptr;
	}
} // namespace memory

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

// no inline, required by [replacement.functions]/3
void* operator new(std::size_t sz)
{
	if (sz == 0)
		++sz; // avoid std::malloc(0) which may return nullptr on success

	if (void* ptr = std::malloc(sz))
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (p_counter)
		{
			p_counter->new_count.fetch_add(1);
			p_counter->allocation_count.fetch_add(1);
		}

		return ptr;
	}

	throw std::bad_alloc{}; // required by [new.delete.single]/3
}

// no inline, required by [replacement.functions]/3
void* operator new[](std::size_t sz)
{
	if (sz == 0)
		++sz; // avoid std::malloc(0) which may return nullptr on success

	if (void* ptr = std::malloc(sz))
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (p_counter)
		{
			p_counter->new_brackets_count.fetch_add(1);
			p_counter->allocation_count.fetch_add(1);
		}

		return ptr;
	}

	throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void operator delete(void* ptr) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		p_counter->delete_count.fetch_add(1);
		p_counter->allocation_count.fetch_sub(1);
	}

	std::free(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		p_counter->delete_count.fetch_add(1);
		p_counter->allocation_count.fetch_sub(1);
	}

	std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		p_counter->delete_brackets_count.fetch_add(1);
		p_counter->allocation_count.fetch_sub(1);
	}

	std::free(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		p_counter->delete_brackets_count.fetch_add(1);
		p_counter->allocation_count.fetch_sub(1);
	}

	std::free(ptr);
}

		#endif

	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace memory
{
#ifndef KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
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

	char* strdup(const char* str)
	{
	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		return mi_strdup(str);
	#else
		return ::strdup(str);
	#endif
	}
#endif

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

	void* memcpy(void* p_dest, const void* p_src, kun_ktk size_t count)
	{
		return std::memcpy(p_dest, p_src, count);
	}

	void* memset(void* p_dest, int value, kun_ktk size_t bytes)
	{
		return std::memset(p_dest, value, bytes);
	}
} // namespace memory

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
