#pragma once

#include "kotek_std_alias_unordered_map.h"
#include "kotek_std_alias_static_unordered_map.h"
#include "kotek_std_alias_hybrid_unordered_map.h"

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_unordered_map \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_map
	#define KTK_UNORDERED_MAP \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_map
	#define ktkUnorderedMap \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_map
#else
	#define ktk_unordered_map \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_map
	#define KTK_UNORDERED_MAP \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_map
	#define ktkUnorderedMap \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_mapkds
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_unordered_map<bool, int, 1>,
		ktk_unordered_map<bool, int, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this unordered_map "
	"container is expected as static_unordered_map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(std::is_same_v<kun_kotek kun_ktk unordered_map<bool, int, 1>,
				  ktk_unordered_map<bool, int, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this unordered_map "
	"container is expected as unordered_map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_unordered_map<bool, int, 1>,
		ktk_unordered_map<bool, int, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this hybrid_unordered_map "
	"container is expected as hybrid_unordered_map implementation");
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_Unordered_Map(ktkMainManager* p_manager);
bool SerializeModule_Core_Containers_Unordered_Map(ktkMainManager* p_manager);
bool DeserializeModule_Core_Containers_Unordered_Map(ktkMainManager* p_manager);
bool ShutdownModule_Core_Containers_Unordered_Map(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK