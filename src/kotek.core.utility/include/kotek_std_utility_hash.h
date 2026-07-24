#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

inline constexpr size_t fnv1a_32(std::string_view str)
{
	size_t hash = 2166136261u;
	for (char c : str)
	{
		hash ^= static_cast<size_t>(c);
		hash *= 16777619u;
	}
	return hash;
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK