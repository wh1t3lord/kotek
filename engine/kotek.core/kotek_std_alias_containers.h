#pragma once

#include <any>
#include <boost/algorithm/algorithm.hpp>
#include <boost/array.hpp>
#include <boost/container/deque.hpp>
#include <boost/container/map.hpp>
#include <boost/container/set.hpp>
#include <boost/container/vector.hpp>
#include <boost/container_hash/extensions.hpp>
#include <boost/json.hpp>
#include <boost/regex.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <cassert>
#include <deque>
#include <fstream>
#include <functional>
#include <queue>
#include <variant>
#include <filesystem>

#ifdef KOTEK_PLATFORM_WINDOWS
	#include <wrl.h>
#endif

namespace Kotek
{
	namespace ktk
	{
		using any = std::any;

		template <typename T>
		using hash = boost::hash<T>;

		template <class K, class V>
		using pair = std::pair<K, V>;

		template <typename K>
		using vector = boost::container::vector<K, mi_stl_allocator<K>>;

		template <class K, class V, class P = std::less<K>,
			typename allocator = mi_stl_allocator<std::pair<const K, V>>>
		using map = boost::container::map<K, V, P, allocator>;

		template <class K, class T, class H = boost::hash<K>,
			class P = std::equal_to<K>,
			class A = mi_stl_allocator<std::pair<const K, T>>>
		using unordered_map = boost::unordered::unordered_map<K, T, H, P, A>;

		template <class Key, class Hash = boost::hash<Key>,
			class Predicate = std::equal_to<Key>,
			class Allocator = mi_stl_allocator<Key>>
		using unordered_set =
			boost::unordered_set<Key, Hash, Predicate, Allocator>;

		template <typename Type, typename Allocator = mi_stl_allocator<Type>>
		using deque = std::deque<Type, Allocator>;

		template <typename T>
		using unique_ptr = std::unique_ptr<T>;

		template <typename T>
		using shared_ptr = std::shared_ptr<T>;

		template <class T>
		using function = std::function<T>;

		template <class T, std::size_t N>
		using array = boost::array<T, N>;

		template <typename... Args>
		using variant = std::variant<Args...>;

#ifdef KOTEK_PLATFORM_WINDOWS
		template <typename T>
		using comptr_t = Microsoft::WRL::ComPtr<T>;
#endif

		template <typename Type>
		using queue = std::queue<Type, deque<Type>>;

		using path = std::filesystem::path;

		namespace json = boost::json;
	} // namespace ktk
} // namespace Kotek
