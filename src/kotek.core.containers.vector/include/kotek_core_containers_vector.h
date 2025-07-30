#pragma once

#include "kotek_std_alias_vector.h"
#include "kotek_std_alias_hybrid_vector.h"
#include "kotek_std_alias_static_vector.h"

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_vector \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_vector
	#define KTK_VECTOR \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_vector
	#define ktkVector \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_vector
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
	#define ktk_vector KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK vector
	#define KTK_VECTOR KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK vector
	#define ktkVector KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK vector
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
// todo: provide implementation for hybrid vector container
#else
	#error unknown configuration, kotek supports static (EMB), dynamic (DYN) and hybrid (HYB) configurations
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(std::is_same_v<kun_kotek kun_ktk static_vector<bool, 1>,
				  ktk_vector<bool, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this vector "
	"container is expected as static_vector implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk vector<bool, 1>, ktk_vector<bool, 1>>,
	"if library type was defined as DYN (aka dynamic) it means that all "
	"containers that kotek framework provides to user ARE WITHOUT static_ and "
	"hybrid_ prefixes it means that this vector container is expected as "
	"vector "
	"implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(std::is_same_v<kun_kotek kun_ktk hybrid_vector<bool, 1>,
				  ktk_vector<bool, 1>>,
	"if library type was defined as HYB (hybrid) it means that all containers "
	"that kotek framework provides to user ARE with hybrid_ prefix that means "
	"that this vector container is expected as hybrid_vector implementation");
#else
	#error unknown configuration, kotek supports static (EMB), dynamic (DYN) and hybrid (HYB) configuration
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_Vector(ktkMainManager* p_manager);
bool SerializeModule_Core_Containers_Vector(ktkMainManager* p_manager);
bool DeserializeModule_Core_Containers_Vector(ktkMainManager* p_manager);
bool ShutdownModule_Core_Containers_Vector(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK