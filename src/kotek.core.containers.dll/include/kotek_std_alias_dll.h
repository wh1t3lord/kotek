#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/dll.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
namespace dll
{
	struct shared_library
	{
		shared_library();
		shared_library(const char* p_path);
		~shared_library();

		bool load(const char* p_path);
		bool unload();

		void* get(const char* p_func_name);

		void* p_lib;
	};
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