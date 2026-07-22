#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/dll.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
#include <filesystem>
namespace dll
{
	struct shared_library
	{
		shared_library();
		shared_library(const char* p_path);
		~shared_library();

		// owning handle: non-copyable, movable (the temporary in
		// `x = shared_library(path)` must not FreeLibrary the handle
		// it just transferred)
		shared_library(const shared_library&) = delete;
		shared_library& operator=(const shared_library&) = delete;
		shared_library(shared_library&& other) noexcept;
		shared_library& operator=(shared_library&& other) noexcept;

		bool load(const char* p_path);
		bool unload();

		void* get(const char* p_func_name);

		void* p_lib;
	};

	/// @brief \~english full path of the running executable (mirrors
	/// boost::dll::program_location so both library configurations share the
	/// same call site)
	std::filesystem::path program_location();
}
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
namespace dll = boost::dll;
#elif defined(KOTEK_USE_STD_LIBRARY)
namespace dll = ::dll;
#else
#endif

KOTEK_END_NAMESPACE_KTK

namespace dll = KUN_KOTEK KUN_KTK dll;

KOTEK_END_NAMESPACE_KOTEK

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
#define ktk_dll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define ktkDll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define KTK_DLL KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
#define ktk_dll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define ktkDll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define KTK_DLL KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#endif