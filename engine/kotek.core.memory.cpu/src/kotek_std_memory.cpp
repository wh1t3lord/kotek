#include "../include/kotek_std_memory.h"
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#include <stdlib.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
		#include <mimalloc-new-delete.h>
	#else

		#ifdef KOTEK_DEBUG
			#define __PLACEMENT_NEW_INLINE
			#include <unordered_map>
			#include <vector>
			#include <mutex>
			#include <filesystem>
			#include <fstream>
			#include <Windows.h>
			#include <DbgHelp.h>
			#include <iostream>
			#pragma comment(lib, "Dbghelp.lib")

struct AllocInfo
{
	static constexpr int MAX_FRAMES = 62;
	void* frames[MAX_FRAMES];
	USHORT frameCount;
};

static std::unordered_map<void*, AllocInfo>& g_allocMap()
{
	static std::unordered_map<void*, AllocInfo>* map =
		new std::unordered_map<void*, AllocInfo>;
	return *map;
}

static std::mutex& g_allocMutex()
{
	static std::mutex* m = new std::mutex;
	return *m;
}

static std::recursive_mutex g_mcounter;

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
namespace memory
{
	ktkMemoryAllocationCounter* get_counter()
	{
		static wchar_t names_mapping[256][256]{};
		static char names_modules[256][512]{};
		static HANDLE handles[256]{};

		static bool first = true;

		std::lock_guard<std::recursive_mutex> guard(g_mcounter);

		char module_name[sizeof(ktkMemoryAllocationCounter::module_name)];

		HMODULE hMod = nullptr;
		if (!::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
					GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
				reinterpret_cast<LPCSTR>(&get_counter), &hMod))
		{
			throw std::runtime_error("GetModuleHandleEx failed");
		}

		DWORD len = ::GetModuleFileNameA(hMod, module_name,
			static_cast<DWORD>(sizeof(ktkMemoryAllocationCounter::module_name) /
				sizeof(decltype(ktkMemoryAllocationCounter::module_name[0]))));

		constexpr auto _kModulesSize =
			sizeof(names_modules) / sizeof(names_modules[0]);

		wchar_t* p_mapping_name{};
		char* p_module_name{};
		int index{-1};
		for (int i = 0; i < _kModulesSize; ++i)
		{
			if (!strcmp(module_name, names_modules[i]))
			{
				p_mapping_name = names_mapping[i];
				p_module_name = names_modules[i];
				index = i;
				break;
			}
			else
			{
				if (index == -1 && handles[i] == nullptr)
				{
					index = i;
				}
			}
		}

		HANDLE hMap = NULL;
		if (!p_mapping_name && index != -1)
		{
			const char* last_slash = strrchr(module_name, '\\');
			if (!last_slash)
				last_slash = strrchr(module_name, '/');
			const char* fname_start = last_slash ? last_slash + 1 : module_name;

			// 3) Copy into a fixed-size char buffer
			char filename[128] = {0};
			size_t fname_len = strlen(fname_start);
			if (fname_len >= sizeof(filename))
				throw std::runtime_error("Filename too long");
			memcpy(filename, fname_start, fname_len + 1); // +1 to copy the '\0'

			// 4) Convert to wide-char
			wchar_t wFilename[128] = {0};
			size_t converted = 0;
			errno_t err =
				mbstowcs_s(&converted, wFilename, filename, _TRUNCATE);
			if (err != 0 || converted == 0)
				throw std::runtime_error("Filename conversion failed");

			// 5) Build your final string
			wchar_t p_temp[256] = {0};
			wsprintf(p_temp, L"Local\\ktkMemoryAllocationCounter_%s_%d",
				wFilename, index);

			handles[index] = ::CreateFileMapping(INVALID_HANDLE_VALUE, nullptr,
				PAGE_READWRITE, 0, sizeof(ktkMemoryAllocationCounter), p_temp);
			std::memcpy(names_mapping[index], p_temp, sizeof(p_temp));
			std::memcpy(names_modules[index], module_name, sizeof(module_name));
		}

		hMap = handles[index];
		assert(hMap && "can't be invalid here");

		auto ptr =
			reinterpret_cast<ktkMemoryAllocationCounter*>(::MapViewOfFile(hMap,
				FILE_MAP_WRITE, 0, 0, sizeof(ktkMemoryAllocationCounter)));

		if (first)
		{
			// zero-initialize only once
			new (ptr) ktkMemoryAllocationCounter;
			ptr->current_process =
				reinterpret_cast<size_t>(GetCurrentProcess());
			std::memcpy(ptr->module_name, module_name, sizeof(module_name));
			first = false;
		}

		return ptr;
	}

	int registerLeakPrinter()
	{
		std::atexit(printLeaks);
		return 0;
	}
	// force it to run at startup
	static int _leakPrinterReg = registerLeakPrinter();

	void printLeaks()
	{
		// std::lock_guard<std::mutex> lk(g_allocMutex());
		SymInitialize(GetCurrentProcess(), nullptr, TRUE);
		const auto& map = g_allocMap();
		auto* ptr = get_counter();

		bool is_memory_leaks = false;
		auto count = ptr->allocation_count.load();
		if (count < 0)
		{
			count += (ptr->delete_count - ptr->new_count);

			if (count != 0)
			{
				count += (ptr->delete_brackets_count - ptr->new_brackets_count);
			}

			is_memory_leaks = count != 0;
		}
		else
		{
			is_memory_leaks = count != 0;
		}

		if (is_memory_leaks)
		{
			std::printf("[%s]: allocation_count == %d "
						"new == %d "
						"delete == %d new[] == %d delete[] == %d | %s \n",
				ptr->module_name, ptr->allocation_count.load(),
				ptr->new_count.load(), ptr->delete_count.load(),
				ptr->new_brackets_count.load(),
				ptr->delete_brackets_count.load(), "MEMORY LEAKS EXIST!");
		}
		else
		{
			std::printf("[%s]: %s \n", ptr->module_name, "NO MEMORY LEAKS :)");
		}

		{
			if (is_memory_leaks)
			{
				std::filesystem::path temp(ptr->module_name);
				std::fstream log(
					("report_memleak_" + temp.filename().string() + ".txt"),
					std::ios::out | std::ios::trunc);
				assert(log.good() && "failed to create log file!");

				log << "stats: "
					<< "allocation_count=" << ptr->allocation_count.load()
					<< " new=" << ptr->new_count.load()
					<< " new[]=" << ptr->new_brackets_count.load()
					<< " delete=" << ptr->delete_count.load()
					<< " delete[]=" << ptr->delete_brackets_count.load();

				for (auto const& [ptr, info] : map)
				{
					log << "LEAK at " << ptr << ", allocated from:\n";

					std::cerr << "LEAK at " << ptr << ", allocated from:\n";
					USHORT framecount = info.frameCount;

					for (USHORT i = 0; i < framecount; ++i)
					{
						DWORD64 addr = (DWORD64)info.frames[i];
						char nameBuf[sizeof(SYMBOL_INFO) + 256] = {};
						auto sym = reinterpret_cast<SYMBOL_INFO*>(nameBuf);
						sym->SizeOfStruct = sizeof(SYMBOL_INFO);
						sym->MaxNameLen = 255;
						DWORD64 displacement = 0;
						if (SymFromAddr(
								GetCurrentProcess(), addr, &displacement, sym))
						{
							if (i < 4 ||
								(i > info.frameCount - 10 &&
									i < info.frameCount - 6))
							{
								std::cerr << "  " << sym->Name << " + 0x"
										  << std::hex << displacement
										  << std::dec << "\n";
							}
							log << "  " << sym->Name << " + 0x" << std::hex
								<< displacement << std::dec << "\n";
						}
						else
						{
							if (i < 4 ||
								(i > info.frameCount - 10 &&
									i < info.frameCount - 6))
							{
								std::cerr << "  [0x" << std::hex << addr
										  << std::dec << "]\n";
							}

							log << "  [0x" << std::hex << addr << std::dec
								<< "]\n";
						}
					}
				}
				log.close();
			}
		}
		assert(!is_memory_leaks && map.empty() && "memory leak detected!");
	}
} // namespace memory

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

static thread_local bool s_inNew = false;

// no inline, required by [replacement.functions]/3
void* operator new(std::size_t sz)
{
	if (sz == 0)
		++sz; // avoid std::malloc(0) which may return nullptr on success

	if (void* ptr = std::malloc(sz))
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (!s_inNew)
		{
			if (p_counter)
			{
				p_counter->new_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);
			}

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				AllocInfo info;
				info.frameCount =
					CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
						reinterpret_cast<PVOID*>(info.frames), nullptr);
				g_allocMap()[ptr] = info;
			}
			s_inNew = false;
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
			if (!s_inNew)
			{
				p_counter->new_brackets_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);

				s_inNew = true;
				{
					std::lock_guard<std::mutex> lock(g_allocMutex());
					AllocInfo info;
					info.frameCount =
						CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
							reinterpret_cast<PVOID*>(info.frames), nullptr);
					g_allocMap()[ptr] = info;
				}
				s_inNew = false;
			}
		}

		return ptr;
	}

	throw std::bad_alloc{}; // required by [new.delete.single]/3
}

void* operator new(std::size_t size, std::align_val_t align)
{
	auto ptr = _aligned_malloc(size, static_cast<std::size_t>(align));

	if (ptr)
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (!s_inNew)
		{
			if (p_counter)
			{
				p_counter->new_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);
			}

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				AllocInfo info;
				info.frameCount =
					CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
						reinterpret_cast<PVOID*>(info.frames), nullptr);
				g_allocMap()[ptr] = info;
			}
			s_inNew = false;
		}

		return ptr;
	}

	throw std::bad_alloc{};
}

void* operator new[](std::size_t size, std::align_val_t align)
{
	auto ptr = _aligned_malloc(size, static_cast<std::size_t>(align));

	if (ptr)
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (!s_inNew)
		{
			if (p_counter)
			{
				p_counter->new_brackets_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);
			}

			s_inNew = true;

			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				AllocInfo info;
				info.frameCount =
					CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
						reinterpret_cast<PVOID*>(info.frames), nullptr);
				g_allocMap()[ptr] = info;
			}

			s_inNew = false;
		}

		return ptr;
	}

	throw std::bad_alloc{};
}

void* operator new(std::size_t sz, const std::nothrow_t& tag)
{
	if (sz == 0)
		++sz; // avoid std::malloc(0) which may return nullptr on success

	if (void* ptr = std::malloc(sz))
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (!s_inNew)
		{
			if (p_counter)
			{
				p_counter->new_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);
			}

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				AllocInfo info;
				info.frameCount =
					CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
						reinterpret_cast<PVOID*>(info.frames), nullptr);
				g_allocMap()[ptr] = info;
			}
			s_inNew = false;
		}

		return ptr;
	}

	return nullptr;
}

void* operator new[](std::size_t sz, const std::nothrow_t& tag)
{
	if (sz == 0)
		++sz; // avoid std::malloc(0) which may return nullptr on success

	if (void* ptr = std::malloc(sz))
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (p_counter)
		{
			if (!s_inNew)
			{
				p_counter->new_brackets_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);

				s_inNew = true;
				{
					std::lock_guard<std::mutex> lock(g_allocMutex());
					AllocInfo info;
					info.frameCount =
						CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
							reinterpret_cast<PVOID*>(info.frames), nullptr);
					g_allocMap()[ptr] = info;
				}
				s_inNew = false;
			}
		}

		return ptr;
	}

	return nullptr;
}

void* operator new(std::size_t size, std::align_val_t align,
	const std::nothrow_t& tag) noexcept
{
	auto ptr = _aligned_malloc(size, static_cast<std::size_t>(align));

	if (ptr)
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (!s_inNew)
		{
			if (p_counter)
			{
				p_counter->new_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);
			}

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				AllocInfo info;
				info.frameCount =
					CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
						reinterpret_cast<PVOID*>(info.frames), nullptr);
				g_allocMap()[ptr] = info;
			}
			s_inNew = false;
		}

		return ptr;
	}

	return nullptr;
}

void* operator new[](std::size_t size, std::align_val_t align,
	const std::nothrow_t& tag) noexcept
{
	auto ptr = _aligned_malloc(size, static_cast<std::size_t>(align));

	if (ptr)
	{
		auto* p_counter = kun_kotek kun_ktk memory::get_counter();

		if (!s_inNew)
		{
			if (p_counter)
			{
				p_counter->new_brackets_count.fetch_add(1);
				p_counter->allocation_count.fetch_add(1);
			}

			s_inNew = true;

			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				AllocInfo info;
				info.frameCount =
					CaptureStackBackTrace(0, AllocInfo::MAX_FRAMES,
						reinterpret_cast<PVOID*>(info.frames), nullptr);
				g_allocMap()[ptr] = info;
			}

			s_inNew = false;
		}

		return ptr;
	}

	return nullptr;
}

void operator delete(void* ptr) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		if (!s_inNew)
		{
			p_counter->delete_count.fetch_add(1);
			p_counter->allocation_count.fetch_sub(1);

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				//	auto it = g_allocMap().find(ptr);
				//	if (it != g_allocMap().end())
				//	{
				g_allocMap().erase(ptr);
				//	}
			}
			s_inNew = false;
		}
	}

	std::free(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		if (!s_inNew)
		{
			p_counter->delete_count.fetch_add(1);
			p_counter->allocation_count.fetch_sub(1);

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				auto& map = g_allocMap();
				//	auto it = map.find(ptr);
				//	if (it != g_allocMap().end())
				//	{
				g_allocMap().erase(ptr);
				//	}
			}
			s_inNew = false;
		}
	}

	std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		if (!s_inNew)
		{
			p_counter->delete_brackets_count.fetch_add(1);
			p_counter->allocation_count.fetch_sub(1);

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				//	auto it = g_allocMap().find(ptr);
				//	if (it != g_allocMap().end())
				//	{
				g_allocMap().erase(ptr);
				//}
			}
			s_inNew = false;
		}
	}

	std::free(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept
{
	auto* p_counter = kun_kotek kun_ktk memory::get_counter();

	if (p_counter)
	{
		if (!s_inNew)
		{
			p_counter->delete_brackets_count.fetch_add(1);
			p_counter->allocation_count.fetch_sub(1);

			s_inNew = true;
			{
				std::lock_guard<std::mutex> lock(g_allocMutex());
				//	auto it = g_allocMap().find(ptr);
				//	if (it != g_allocMap().end())
				//	{
				g_allocMap().erase(ptr);
				//}
			}
			s_inNew = false;
		}
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
