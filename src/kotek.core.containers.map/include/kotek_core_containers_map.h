#pragma once

#include "kotek_std_alias_map.h"
#include "kotek_std_alias_static_map.h"
#include "kotek_std_alias_hybrid_map.h"

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_map KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_map
	#define ktkMap KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_map
	#define KTK_MAP KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_map
#else
	#define ktk_map KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK map
	#define ktkMap KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK map
	#define KTK_MAP KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK map
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(std::is_same_v<kun_kotek kun_ktk static_map<bool, int, 1>,
				  ktk_map<bool, int, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this map "
	"container is expected as static_map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk map<bool, int, 1>, ktk_map<bool, int, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this map "
	"container is expected as map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(std::is_same_v<kun_kotek kun_ktk hybrid_map<bool, int, 1>,
				  ktk_map<bool, int, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this map "
	"container is expected as hybrid_map implementation");
#else

#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_Map(ktkMainManager* p_manager);
bool SerializeModule_Core_Containers_Map(ktkMainManager* p_manager);
bool DeserializeModule_Core_Containers_Map(ktkMainManager* p_manager);
bool ShutdownModule_Core_Containers_Map(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK