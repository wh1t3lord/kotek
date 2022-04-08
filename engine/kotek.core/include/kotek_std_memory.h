#pragma once

#include "kotek_std_alias_numerics.h"
#include <cstring>
#include <mimalloc.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_DEBUG
		#include <vld.h>
	#endif
#endif

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
