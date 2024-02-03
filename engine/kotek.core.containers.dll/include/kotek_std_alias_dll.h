#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/dll.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#error add replacement for boost::dll
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
namespace dll = boost::dll;
#elif defined(KOTEK_USE_STD_LIBRARY)
	#error add replacement for boost::dll
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KTK

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
#define ktk_dll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define ktkDll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define KTK_DLL KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
#define ktk_dll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define ktkDll KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#define KTK_DLL KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK dll
#endif