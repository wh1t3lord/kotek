#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/unordered/unordered_map.hpp>
	#include <unordered_map>
	#include <memory_resource>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <unordered_map>
	#include <span>
	#include <memory_resource>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY

namespace _kotek_hum_container_namespace = ::boost;
namespace _kotek_hum_container_namespace_pmr = ::std::pmr;
namespace _kotek_hum_container_namespace_swap = ::std;
namespace _kotek_hum_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hum_il_t = ::std::initializer_list<Type>;

template <typename Key, typename Value>
using _kotek_hum_value_type = _kotek_hum_container_namespace::
	unordered::unordered_map<Key, Value>::value_type;

template <typename Key, typename Value>
using _kotek_hum_polymorphic_allocator =
	_kotek_hum_container_namespace_pmr::polymorphic_allocator<
		_kotek_hum_value_type<Key, Value>>;

template <typename Key, typename Value>
using _kotek_humm_value_type = _kotek_hum_container_namespace::
	unordered::unordered_multimap<Key, Value>::value_type;

template <typename Key, typename Value>
using _kotek_humm_polymorphic_allocator =
	_kotek_hum_container_namespace_pmr::polymorphic_allocator<
		_kotek_humm_value_type<Key, Value>>;

template <typename Key, typename Value>
using hybrid_unordered_map_container =
	_kotek_hum_container_namespace::unordered::unordered_map<
		Key,
		Value,
		_kotek_hum_container_namespace::hash<Key>,
		std::equal_to<Key>,
		_kotek_hum_polymorphic_allocator<Key, Value>>;

#elif defined(KOTEK_USE_STD_LIBRARY)

namespace _kotek_hum_container_namespace = ::std;
namespace _kotek_hum_container_namespace_pmr = ::std::pmr;
namespace _kotek_hum_container_namespace_swap = ::std;
namespace _kotek_hum_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hum_il_t = ::std::initializer_list<Type>;

template <typename Key, typename Value>
using _kotek_hum_value_type = _kotek_hum_container_namespace::
	pmr::unordered_map<Key, Value>::value_type;

template <typename Key, typename Value>
using _kotek_hum_polymorphic_allocator =
	_kotek_hum_container_namespace_pmr::polymorphic_allocator<
		_kotek_hum_value_type<Key, Value>>;

template <typename Key, typename Value>
using _kotek_humm_value_type = _kotek_hum_container_namespace::
	pmr::unordered_multimap<Key, Value>::value_type;

template <typename Key, typename Value>
using _kotek_humm_polymorphic_allocator =
	_kotek_hum_container_namespace_pmr::polymorphic_allocator<
		_kotek_humm_value_type<Key, Value>>;

template <typename Key, typename Value>
using hybrid_unordered_map_container =
	_kotek_hum_container_namespace_pmr::
		unordered_map<Key, Value>;

#else
#endif

// Helper function for linear interpolation
constexpr size_t _kotek_pmr_hybrid_unordered_map_interpolate(
	size_t x0, size_t y0, size_t x1, size_t y1, size_t x
)
{
	if (x <= x0)
		return y0;
	if (x >= x1)
		return y1;
	return y0 + ((y1 - y0) * (x - x0)) / (x1 - x0);
}

// Helper function to find next prime number (for bucket count
// estimation)
constexpr bool _kotek_pmr_hybrid_unordered_map_is_prime(size_t n
)
{
	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	for (size_t i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

constexpr size_t
_kotek_pmr_hybrid_unordered_map_next_prime(size_t n)
{
	if (n <= 1)
		return 2;
	size_t candidate = n | 1; // Start with next odd number
	while (!_kotek_pmr_hybrid_unordered_map_is_prime(candidate))
		candidate += 2;
	return candidate;
}

// Returns buffer size for std::pmr::unordered_map
constexpr size_t
_kotek_pmr_hybrid_unordered_map_buffer_size(size_t N)
{
	if (N == 0)
		return 0;

#ifdef _MSC_VER
	// MSVC: Piecewise interpolation based on empirical data
	if (N <= 10)
		return _kotek_pmr_hybrid_unordered_map_interpolate(
			1, 179, 10, 1792, N
		);
	if (N <= 100)
		return _kotek_pmr_hybrid_unordered_map_interpolate(
			10, 1792, 100, 14656, N
		);
	if (N <= 1000)
		return _kotek_pmr_hybrid_unordered_map_interpolate(
			100, 14656, 1000, 80448, N
		);

	// For N > 1000: 80.4 bytes per element + bucket overhead
	const size_t node_size = 80;
	const size_t bucket_count =
		_kotek_pmr_hybrid_unordered_map_next_prime(N);
	return 80 * N + bucket_count * sizeof(void*);

#elif defined(__clang__) || defined(__GNUC__)
	// Clang/GCC: Piecewise interpolation based on empirical
	// data
	if (N <= 10)
		return _kotek_pmr_hybrid_unordered_map_interpolate(
			1, 66, 10, 664, N
		);
	if (N <= 100)
		return _kotek_pmr_hybrid_unordered_map_interpolate(
			10, 664, 100, 6616, N
		);
	if (N <= 1000)
		return _kotek_pmr_hybrid_unordered_map_interpolate(
			100, 6616, 1000, 64872, N
		);

	// For N > 1000: 64.9 bytes per element + bucket overhead
	const size_t node_size =
		56; // 8 (pointer) + 8 (hash) + 40 (pair)
	const size_t bucket_count =
		_kotek_pmr_hybrid_unordered_map_next_prime(N);
	return node_size * N + bucket_count * sizeof(void*);

#else
	// Conservative default for other compilers
	return 100 * N + 4096;
#endif
}

template <
	typename Key,
	typename Value,
	std::size_t ElementCount,
	bool Realloc,
	std::size_t _kotek_hum_Size =
		_kotek_pmr_hybrid_unordered_map_buffer_size(ElementCount
        )>
class hybrid_unordered_map
{
	//	static_assert(is_safe_for_buffer_v<Value>,
	//		"Value type must be fundamental, trivial, PMR
	// container, or
	// fixed-size " 		"container");

	static_assert(
		ElementCount == 0 ? Realloc : true,
		"if you specified ElementCount as 0 it means that it "
		"doesn't use stack "
		"memory at all and it means that container is forced "
		"to support "
		"reallocation!"
	);

	template <
		typename _K,
		typename _T,
		typename H2,
		typename KQ2>
#ifdef KOTEK_USE_BOOST_LIBRARY
	using base_type = _kotek_hum_container_namespace::
		unordered::unordered_map<
			_K,
			_T,
			H2,
			KQ2,
			_kotek_hum_polymorphic_allocator<_K, _T>>;
#elif defined(KOTEK_USE_STD_LIBRARY)
	using base_type =
		_kotek_hum_container_namespace::unordered_map<
			_K,
			_T,
			H2,
			KQ2,
			_kotek_hum_polymorphic_allocator<_K, _T>>;
#endif

	template <
		typename _K,
		typename _T,
		typename H2,
		typename KQ2>
#ifdef KOTEK_USE_BOOST_LIBRARY
	using base_multimap_type = _kotek_hum_container_namespace::
		unordered::unordered_multimap<
			_K,
			_T,
			H2,
			KQ2,
			_kotek_humm_polymorphic_allocator<_K, _T>>;
#elif defined(KOTEK_USE_STD_LIBRARY)
	using base_multimap_type =
		_kotek_hum_container_namespace::unordered_multimap<
			_K,
			_T,
			H2,
			KQ2,
			_kotek_humm_polymorphic_allocator<_K, _T>>;
#endif

	using container_type =
		hybrid_unordered_map_container<Key, Value>;

public:
	using key_type = typename container_type::key_type;
	using key_compare = typename container_type::key_compare;
	using value_compare =
		typename container_type::value_compare;
	using mapped_type = typename container_type::mapped_type;

	using reverse_iterator =
		typename container_type::reverse_iterator;
	using const_reverse_iterator =
		typename container_type::const_reverse_iterator;

	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using difference_type =
		typename container_type::difference_type;
	using reference = typename container_type::reference;
	using const_reference =
		typename container_type::const_reference;
	using pointer = typename container_type::pointer;
	using const_pointer =
		typename container_type::const_pointer;
	using iterator = typename container_type::iterator;
	using const_iterator =
		typename container_type::const_iterator;
	using allocator_type =
		typename container_type::allocator_type;
	using hasher = typename container_type::hasher;
	using node_type = typename container_type::node_type;
	using insert_return_type =
		typename container_type::insert_return_type;
	using key_equal = typename container_type::key_equal;

public:
	hybrid_unordered_map() : mem() {}

	explicit hybrid_unordered_map(
		size_type bucket_count,
		const hasher& hash = hasher(),
		const key_equal& equal = key_equal()
	) : mem(bucket_count, hash, equal)
	{
	}

	hybrid_unordered_map(size_type bucket_count) :
		mem(bucket_count)
	{
	}

	hybrid_unordered_map(
		size_type bucket_count, const hasher& hash
	) : mem(bucket_count, hash)
	{
	}

	template <class InputIt>
	hybrid_unordered_map(
		InputIt first,
		InputIt last,
		size_type bucket_count,
		const hasher& hash = hasher(),
		const key_equal& equal = key_equal()
	) : mem(first, last, bucket_count, hash, equal)
	{
	}

	template <class InputIt>
	hybrid_unordered_map(
		InputIt first, InputIt last, size_type bucket_count
	) : mem(first, last, bucket_count)
	{
	}

	template <class InputIt>
	hybrid_unordered_map(
		InputIt first,
		InputIt last,
		size_type bucket_count,
		const hasher& hash
	) : mem(first, last, bucket_count, hash)
	{
	}

	template <
		typename Key2,
		typename Value2,
		std::size_t ElementCount2,
		bool Realloc2,
		typename = std::enable_if_t<
			(ElementCount >= ElementCount2 || Realloc == true
	        ) &&
			std::is_same_v<Key, Key2> &&
			std::is_same_v<Value, Value2>>>
	hybrid_unordered_map(const hybrid_unordered_map<
						 Key2,
						 Value2,
						 ElementCount2,
						 Realloc2>& other) : mem(other)
	{
	}

	hybrid_unordered_map(const hybrid_unordered_map& other) :
		mem(other)
	{
	}

	template <
		typename Key2,
		typename Value2,
		std::size_t ElementCount2,
		bool Realloc2,
		typename = std::enable_if_t<
			(ElementCount >= ElementCount2 || Realloc == true
	        ) &&
			std::is_same_v<Key, Key2> &&
			std::is_same_v<Value, Value2>>>
	hybrid_unordered_map(hybrid_unordered_map<
						 Key2,
						 Value2,
						 ElementCount2,
						 Realloc2>&& other) : mem(other)
	{
	}

	hybrid_unordered_map(hybrid_unordered_map&& other) :
		mem(other)
	{
	}

	hybrid_unordered_map(
		std::initializer_list<value_type> init,
		size_type bucket_count
	) : mem(init, bucket_count)
	{
	}

	hybrid_unordered_map(
		std::initializer_list<value_type> init,
		size_type bucket_count,
		const hasher& hash
	) : mem(init, bucket_count, hash)
	{
	}

	~hybrid_unordered_map() {}

public:
	Value& at(const Key& key) { return mem.con.at(key); }
	const Value& at(const Key& key) const
	{
		return mem.con.at(key);
	}

	Value& operator[](const Key& key)
	{
		return mem.con.operator[](key);
	}

	Value& operator[](Key&& key)
	{
		return mem.con.operator[](std::move(key));
	}

public:
	iterator begin() { return mem.con.begin(); }

	const_iterator begin() const { return mem.con.begin(); }

	const_iterator cbegin() const noexcept
	{
		return mem.con.cbegin();
	}

	iterator end() { return mem.con.end(); }

	const_iterator end() const { return mem.con.end(); }

	const_iterator cend() const noexcept
	{
		return mem.con.cend();
	}

public:
	bool empty() const { return mem.con.empty(); }

	size_type size() const { return mem.con.size(); }

	size_type max_size() const { return mem.con.max_size(); }

public:
	void clear() { mem.con.clear(); }

	std::pair<iterator, bool> insert(const value_type& value)
	{
		return mem.con.insert(value);
	}

	template <class P>
	std::pair<iterator, bool> insert(P&& value)
	{
		return mem.con.insert<P>(std::move(value));
	}

	std::pair<iterator, bool> insert(value_type&& value)
	{
		return mem.con.insert(std::move(value));
	}

	iterator insert(iterator pos, const value_type& value)
	{
		return mem.con.insert(pos, value);
	}

	iterator insert(const_iterator pos, const value_type& value)
	{
		return mem.con.insert(pos, value);
	}

	template <class P>
	iterator insert(const_iterator pos, P&& value)
	{
		return mem.con.insert<P>(pos, value);
	}

	iterator insert(const_iterator pos, value_type&& value)
	{
		return mem.con.insert(pos, std::move(value));
	}

	template <class InputIt>
	void insert(InputIt first, InputIt last)
	{
		return mem.con.insert<InputIt>(first, last);
	}

	void insert(std::initializer_list<value_type> ilist)
	{
		return mem.con.insert(ilist);
	}

	insert_return_type insert(node_type&& nh)
	{
		return mem.con.insert(std::move(nh));
	}

	iterator insert(const_iterator pos, node_type&& nh)
	{
		return mem.con.insert(pos, std::move(nh));
	}

	template <class M>
	std::pair<iterator, bool>
	insert_or_assign(const Key& k, M&& obj)
	{
		return mem.con.insert_or_assign<M>(k, obj);
	}

	template <class M>
	std::pair<iterator, bool> insert_or_assign(Key&& k, M&& obj)
	{
		return mem.con.insert_or_assign<M>(std::move(k), obj);
	}

	template <class K, class M>
	std::pair<iterator, bool> insert_or_assign(K&& k, M&& obj)
	{
		return mem.con.insert_or_assign<K, M>(
			std::move(k), std::move(obj)
		);
	}

	template <class M>
	iterator
	insert_or_assign(const_iterator hint, const Key& k, M&& obj)
	{
		return mem.con.insert_or_assign<M>(hint, k, obj);
	}

	template <class M>
	iterator
	insert_or_assign(const_iterator hint, Key&& k, M&& obj)
	{
		return mem.con.insert_or_assign<M>(hint, k, obj);
	}

	template <class... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return mem.con.emplace(std::forward<Args>(args)...);
	}

	template <class... Args>
	iterator emplace_hint(const_iterator hint, Args&&... args)
	{
		return mem.con.emplace(std::forward<Args>(args)...);
	}

	template <class... Args>
	std::pair<iterator, bool>
	try_emplace(const Key& k, Args&&... args)
	{
		return mem.con.try_emplace<Args>(
			k, std::forward<Args>(args)...
		);
	}

	template <class... Args>
	std::pair<iterator, bool>
	try_emplace(Key&& k, Args&&... args)
	{
		return mem.con.try_emplace<Args>(
			std::move(k), std::forward<Args>(args)...
		);
	}

	template <class... Args>
	iterator try_emplace(
		const_iterator hint, const Key& k, Args&&... args
	)
	{
		return mem.con.try_emplace<Args>(
			hint, k, std::forward<Args>(args)...
		);
	}

	template <class... Args>
	iterator
	try_emplace(const_iterator hint, Key&& k, Args&&... args)
	{
		return mem.con.try_emplace(
			hint, std::move(k), std::forward<Args>(args)...
		);
	}

	iterator erase(iterator pos) { return mem.con.erase(pos); }

	iterator erase(const_iterator pos)
	{
		return mem.con.erase(pos);
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		return mem.con.erase(first, last);
	}

	size_type erase(const Key& key)
	{
		return mem.con.erase(key);
	}

	void swap(hybrid_unordered_map& other) noexcept
	{
		mem.con.swap(other);
	}

	node_type extract(const_iterator pos)
	{
		return mem.con.extract(pos);
	}

	node_type extract(const Key& k)
	{
		return mem.con.extract(k);
	}

	template <class Hasher2, class KeyEqual2>
	void merge(base_type<Key, Value, Hasher2, KeyEqual2>& source
	)
	{
		mem.con.merge<Hasher2, KeyEqual2>(source);
	}

	template <class Hasher2, class KeyEqual2>
	void
	merge(base_type<Key, Value, Hasher2, KeyEqual2>&& source)
	{
		mem.con.merge<Hasher2, KeyEqual2>(std::move(source));
	}

	template <class Hasher2, class KeyEqual2>
	void
	merge(base_multimap_type<Key, Value, Hasher2, KeyEqual2>&
	          source)
	{
		mem.con.merge<Hasher2, KeyEqual2>(source);
	}

	template <class Hasher2, class KeyEqual2>
	void
	merge(base_multimap_type<Key, Value, Hasher2, KeyEqual2>&&
	          source)
	{
		mem.con.merge<Hasher2, KeyEqual2>(std::move(source));
	}

public:
	size_type count(const Key& key) const
	{
		return mem.con.count(key);
	}

	template <class K>
	size_type count(const K& x) const
	{
		return mem.con.count<K>(x);
	}

	iterator find(const Key& key) { return mem.con.find(key); }

	const_iterator find(const Key& key) const
	{
		return mem.con.find(key);
	}

	template <class K>
	iterator find(const K& x)
	{
		return mem.con.find<K>(x);
	}

	template <class K>
	const_iterator find(const K& x) const
	{
		return mem.con.find<K>(x);
	}

	std::pair<iterator, iterator> equal_range(const Key& key)
	{
		return mem.con.equal_range(key);
	}

	std::pair<const_iterator, const_iterator>
	equal_range(const Key& key) const
	{
		return mem.con.equal_range(key);
	}

	template <class K>
	std::pair<iterator, iterator> equal_range(const K& x)
	{
		return mem.con.equal_range(x);
	}

	template <class K>
	std::pair<const_iterator, const_iterator>
	equal_range(const K& x) const
	{
		return mem.con.equal_range(x);
	}

	iterator lower_bound(const Key& key)
	{
		return mem.con.lower_bound(key);
	}

	const_iterator lower_bound(const Key& key) const
	{
		return mem.con.lower_bound(key);
	}

	template <class K>
	iterator lower_bound(const K& x)
	{
		return mem.con.lower_bound<K>(x);
	}

	template <class K>
	const_iterator lower_bound(const K& x) const
	{
		return mem.con.lower_bound<K>(x);
	}

	iterator upper_bound(const Key& key)
	{
		return mem.con.upper_bound(key);
	}

	const_iterator upper_bound(const Key& key) const
	{
		return mem.con.upper_bound(key);
	}

	template <class K>
	iterator upper_bound(const K& x)
	{
		return mem.con.upper_bound<K>(x);
	}

	template <class K>
	const_iterator upper_bound(const K& x) const
	{
		return mem.con.upper_bound<K>(x);
	}

public:
	key_compare key_comp() const { return mem.con.key_comp(); }

	value_compare value_comp() const
	{
		return mem.con.value_comp();
	}

public:
	constexpr std::size_t
	preallocated_memory_size() const noexcept
	{
		return _kotek_hum_Size;
	}
	constexpr std::size_t preallocated_size() const noexcept
	{
		return ElementCount;
	}
	constexpr bool is_reallocation_supported() const noexcept
	{
		return Realloc;
	}

	const container_type& container() const noexcept
	{
		return mem.con;
	}
	container_type& container() noexcept { return mem.con; }
	container_type&& container_move_out() noexcept
	{
		return std::move(mem.con);
	}

private:
	struct layout_prealloc_t
	{
		layout_prealloc_t() :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{&pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		explicit layout_prealloc_t(
			size_type bucket_count,
			const hasher& hash = hasher(),
			const key_equal& equal = key_equal()
		) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{bucket_count, hash, equal, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(size_type bucket_count) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{bucket_count, hasher(), key_equal(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(
			size_type bucket_count, const hasher& hash
		) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{bucket_count, hash, key_equal(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class InputIt>
		layout_prealloc_t(
			InputIt first,
			InputIt last,
			size_type bucket_count,
			const hasher& hash = hasher(),
			const key_equal& equal = key_equal()
		) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{first, last, bucket_count, hash, equal, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <typename InputIt>
		layout_prealloc_t(
			InputIt first, InputIt last, size_type bucket_count
		) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{first,
		        last,
		        bucket_count,
		        hasher(),
		        key_equal(),
		        &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <
			typename Key2,
			typename Value2,
			std::size_t ElementCount2,
			bool Realloc2,
			typename = std::enable_if_t<
				(ElementCount >= ElementCount2 ||
		         Realloc == true) &&
				std::is_same_v<Key, Key2> &&
				std::is_same_v<Value, Value2>>>
		layout_prealloc_t(const hybrid_unordered_map<
						  Key2,
						  Value2,
						  ElementCount2,
						  Realloc2>& other) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{other.container(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(const hybrid_unordered_map& other) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{other.container(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <
			typename Key2,
			typename Value2,
			std::size_t ElementCount2,
			bool Realloc2,
			typename = std::enable_if_t<
				(ElementCount >= ElementCount2 ||
		         Realloc == true) &&
				std::is_same_v<Key, Key2> &&
				std::is_same_v<Value, Value2>>>
		layout_prealloc_t(hybrid_unordered_map<
						  Key2,
						  Value2,
						  ElementCount2,
						  Realloc2>&& other) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{std::move(other.container_move_out()), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(hybrid_unordered_map&& other) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{std::move(other.container_move_out()), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(
			std::initializer_list<value_type> init,
			size_type bucket_count
		) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con{init, bucket_count, hasher(), key_equal(), &pool
		    }
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(
			std::initializer_list<value_type> init,
			size_type bucket_count,
			const hasher& hash
		) :
			pool{
				(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hum_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()
			},
			con(init, bucket_count, hash, key_equal(), &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		unsigned char buf[_kotek_hum_Size];
		_kotek_hum_container_namespace_pmr::
			monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		layout_no_prealloc_t() : con{} {}

		explicit layout_no_prealloc_t(
			size_type bucket_count,
			const hasher& hash = hasher(),
			const key_equal& equal = key_equal()
		) : con{bucket_count, hash, equal}
		{
		}

		layout_no_prealloc_t(size_type bucket_count) :
			con{bucket_count, hasher(), key_equal()}
		{
		}

		layout_no_prealloc_t(
			size_type bucket_count, const hasher& hash
		) : con{bucket_count, hash, key_equal()}
		{
		}

		template <class InputIt>
		layout_no_prealloc_t(
			InputIt first,
			InputIt last,
			size_type bucket_count,
			const hasher& hash = hasher(),
			const key_equal& equal = key_equal()
		) : con{first, last, bucket_count, hash, equal}
		{
		}

		template <typename InputIt>
		layout_no_prealloc_t(
			InputIt first, InputIt last, size_type bucket_count
		) :
			con{first, last, bucket_count, hasher(), key_equal()
		    }
		{
		}

		template <
			typename Key2,
			typename Value2,
			std::size_t ElementCount2,
			bool Realloc2,
			typename = std::enable_if_t<
				(ElementCount >= ElementCount2 ||
		         Realloc == true) &&
				std::is_same_v<Key, Key2> &&
				std::is_same_v<Value, Value2>>>
		layout_no_prealloc_t(const hybrid_unordered_map<
							 Key2,
							 Value2,
							 ElementCount2,
							 Realloc2>& other) :
			con{other.container()}
		{
		}

		layout_no_prealloc_t(const hybrid_unordered_map& other
		) : con{other.container()}
		{
		}

		template <
			typename Key2,
			typename Value2,
			std::size_t ElementCount2,
			bool Realloc2,
			typename = std::enable_if_t<
				(ElementCount >= ElementCount2 ||
		         Realloc == true) &&
				std::is_same_v<Key, Key2> &&
				std::is_same_v<Value, Value2>>>
		layout_no_prealloc_t(hybrid_unordered_map<
							 Key2,
							 Value2,
							 ElementCount2,
							 Realloc2>&& other) :
			con{std::move(other.container_move_out())}
		{
		}

		layout_no_prealloc_t(hybrid_unordered_map&& other) :
			con{std::move(other.container_move_out())}
		{
		}

		layout_no_prealloc_t(
			std::initializer_list<value_type> init,
			size_type bucket_count
		) : con{init, bucket_count, hasher(), key_equal()}
		{
		}

		layout_no_prealloc_t(
			std::initializer_list<value_type> init,
			size_type bucket_count,
			const hasher& hash
		) : con(init, bucket_count, hash, key_equal())
		{
		}

		container_type con;
	};

	using layout_t =
		_kotek_hum_container_namespace_conditional::
			conditional_t<
				ElementCount == 0,
				layout_no_prealloc_t,
				layout_prealloc_t>;

	layout_t mem;
};

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK