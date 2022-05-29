#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.memory.vld/include/kotek_core_memory_vld.h>
#include <cstring>
#include <mimalloc.h>

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
