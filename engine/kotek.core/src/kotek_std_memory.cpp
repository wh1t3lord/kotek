#include "../include/kotek_std_memory.h"

namespace Kotek
{
	namespace ktk
	{
		namespace memory
		{
			void free(void* pointer) { mi_free(pointer); }
			void* malloc(ktk::size_t size) { return mi_malloc(size); }
			void* calloc(ktk::size_t count, ktk::size_t size)
			{
				return mi_calloc(count, size);
			}
			void* realloc(void* pointer, ktk::size_t newsize)
			{
				return mi_realloc(pointer, newsize);
			}
			void* expand(void* pointer, ktk::size_t newsize)
			{
				return mi_expand(pointer, newsize);
			}
			char* strdup(const char* str) { return mi_strdup(str); }
			char* strndup(const char* str, size_t n)
			{
				return mi_strndup(str, n);
			}
			void* memcpy(void* p_dest, void* p_src, ktk::size_t count)
			{
				return std::memcpy(p_dest, p_src, count);
			}
		} // namespace memory
	}     // namespace ktk
} // namespace Kotek
