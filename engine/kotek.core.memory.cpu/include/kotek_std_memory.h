#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_MEMORY_LEAK_DETECTION_VLD
	#include <kotek.core.memory.vld/include/kotek_core_memory_vld.h>
#endif

#include <cstring>

#include <mimalloc.h>

// TODO: add feature in order to disable mimalloc and use regular std::allocator
#define KOTEK_USE_MEMORY_ALLOCATOR_CLASS mi_stl_allocator

namespace Kotek
{
	namespace ktk
	{
		namespace memory
		{
			void free(void* pointer);
			void* malloc(ktk::size_t size);
			void* calloc(ktk::size_t count, ktk::size_t size);
			void* realloc(void* pointer, ktk::size_t newsize);
			void* expand(void* pointer, ktk::size_t newsize);
			char* strdup(const char* str);
			char* strndup(const char* str, size_t n);
			void* memcpy(void* p_dest, void* p_src, ktk::size_t count);

		} // namespace memory
	}     // namespace ktk
} // namespace Kotek
