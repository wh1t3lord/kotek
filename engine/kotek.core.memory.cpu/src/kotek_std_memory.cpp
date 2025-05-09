#include "../include/kotek_std_memory.h"
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#include <stdlib.h>

#ifdef KOTEK_DEBUG

	#ifdef KOTEK_PLATFORM_WINDOWS
		#include <Windows.h>
		#include <DbgHelp.h>
		#pragma comment(lib, "DbgHelp")
	#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
namespace memory
{
	ktkMemoryAllocationCounter ___counter_debug;
}
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
#endif

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		#include <mimalloc-new-delete.h>
	#else

		#ifdef KOTEK_DEBUG
void* operator new(std::size_t n) throw(std::bad_alloc)
{
	kun_kotek kun_ktk memory::___counter_debug.new_count++;
	kun_kotek kun_ktk memory::___counter_debug.allocation_count++;

			#ifdef KOTEK_PLATFORM_WINDOWS

	// TODO: implement stacktrace and detailed memory leak system
	STACKFRAME64 fm;
	CONTEXT ctxt;
	RtlCaptureContext(&ctxt);
	std::memset(&fm, 0, sizeof(STACKFRAME64));

	BOOL status = StackWalk64(IMAGE_FILE_MACHINE_AMD64, GetCurrentProcess(),
		GetCurrentThread(), &fm, &ctxt, NULL, SymFunctionTableAccess64,
		SymGetModuleBase64, NULL);

	if (status == TRUE)
	{
		char buffer_name[2048];
		IMAGEHLP_SYMBOL64 symbol;
		symbol.SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
		symbol.MaxNameLength = 2048;
		DWORD64 displacement = 0;
		SymGetSymFromAddr64(GetCurrentProcess(), (ULONG64)fm.AddrPC.Offset,
			&displacement, &symbol);
		UnDecorateSymbolName(
			symbol.Name, buffer_name, symbol.MaxNameLength, UNDNAME_COMPLETE);

		float a = 0; 
	}

			#endif

	return std::malloc(n);
}

void operator delete(void* p) throw()
{
	kun_kotek kun_ktk memory::___counter_debug.delete_count++;
	kun_kotek kun_ktk memory::___counter_debug.allocation_count--;

	std::free(p);
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
