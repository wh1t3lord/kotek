#include "../include/kotek_std_string.h"

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

    std::size_t hash_value(const ktk::string& instance)
    {
		ktk::hash<ktk::string> result;
        return result(instance);
    }

#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

