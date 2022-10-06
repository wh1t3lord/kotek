#pragma once

#include "kotek_std_constants.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
	KOTEK_BEGIN_NAMESPACE_CORE
		class ktkMainManager;
	KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
	KOTEK_BEGIN_NAMESPACE_CORE
		bool InitializeModule_Core_Constants_Window(ktkMainManager*);
		bool ShutdownModule_Core_Constants_Window(ktkMainManager*);
		bool SerializeModule_Core_Constants_Window(ktkMainManager*);
		bool DeserializeModule_Core_Constants_Window(ktkMainManager*);
	KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK