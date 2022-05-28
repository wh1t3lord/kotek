#pragma once

#include <boost/algorithm/algorithm.hpp>

#include <boost/container/set.hpp>
#include <boost/container/vector.hpp>

#include <boost/regex.hpp>
#include <boost/unordered_set.hpp>
#include <variant>



namespace Kotek
{
	namespace ktk
	{
		template <typename K>
		using vector = boost::container::vector<K, mi_stl_allocator<K>>;

		template <class Key, class Hash = boost::hash<Key>,
			class Predicate = std::equal_to<Key>,
			class Allocator = mi_stl_allocator<Key>>
		using unordered_set =
			boost::unordered_set<Key, Hash, Predicate, Allocator>;

		template <typename... Args>
		using variant = std::variant<Args...>;
	} // namespace ktk
} // namespace Kotek
