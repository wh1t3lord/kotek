#pragma once

#include <kotek.core.defines.static.os.linux/include/kotek_core_defines_static_os_linux.h>
#include <kotek.core.defines.static.os.win32/include/kotek_core_defines_static_os_win32.h>

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED

	#ifdef KOTEK_PLATFORM_WINDOWS

		#ifndef KOTEK_MODULE_GAME
			#define KOTEK_MODULE_EXPORT __declspec(dllexport)
		#else
			#define KOTEK_MODULE_EXPORT __declspec(dllimport)
		#endif
	#elif KOTEK_PLATFORM_LINUX
		#ifdef KOTEK_MODULE_GAME
			#define KOTEK_MODULE_EXPORT
		#else
			#define KOTEK_MODULE_EXPORT
		#endif
	#endif

	#define KOTEK_MODULE_EXTERN_C extern "C"
#elif defined(KOTEK_USE_DEVELOPMENT_TYPE_STATIC)
	#define KOTEK_MODULE_EXPORT
#else
	#error engine supports only STATIC or SHARED. See what you passed to your CMake generation
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines_Static_OS(ktkMainManager*);
bool ShutdownModule_Core_Defines_Static_OS(ktkMainManager*);
bool SerializeModule_Core_Defines_Static_OS(ktkMainManager*);
bool DeserializeModule_Core_Defines_Static_OS(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
