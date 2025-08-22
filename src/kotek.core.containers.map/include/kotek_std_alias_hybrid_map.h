#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/pmr/map.hpp>
	#include <span>
	#include <memory_resource>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <map>
	#include <span>
	#include <memory_resource>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY

namespace _kotek_hm_container_namespace = ::boost;
namespace _kotek_hm_container_namespace_pmr = ::boost::container::pmr;
namespace _kotek_hm_container_namespace_swap = ::std;
namespace _kotek_hm_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hm_il_t = ::std::initializer_list<Type>;

template <typename Key, typename Value>
using hybrid_map_container = _kotek_hm_container_namespace_pmr::map<Key, Value>;

#elif defined(KOTEK_USE_STD_LIBRARY)

namespace _kotek_hm_container_namespace = ::std;
namespace _kotek_hm_container_namespace_pmr = ::std::pmr;
namespace _kotek_hm_container_namespace_swap = ::std;
namespace _kotek_hm_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hm_il_t = ::std::initializer_list<Type>;

template <typename Key, typename Value>
using hybrid_map_container = _kotek_hm_container_namespace_pmr::map<Key, Value>;

#else
#endif

// Helper function for linear interpolation
constexpr size_t _kotek_pmr_hybrid_map_interpolate(
	size_t x0, size_t y0, size_t x1, size_t y1, size_t x)
{
	if (x <= x0)
		return y0;
	if (x >= x1)
		return y1;
	return y0 + ((y1 - y0) * (x - x0)) / (x1 - x0);
}

// Helper function to find next prime number (for bucket count estimation)
constexpr bool _kotek_pmr_hybrid_map_is_prime(size_t n)
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

constexpr size_t _kotek_pmr_hybrid_map_next_prime(size_t n)
{
	if (n <= 1)
		return 2;
	size_t candidate = n | 1; // Start with next odd number
	while (!_kotek_pmr_hybrid_map_is_prime(candidate))
		candidate += 2;
	return candidate;
}

// Returns buffer size for std::pmr::map
constexpr size_t _kotek_pmr_hybrid_map_map_buffer_size(size_t N)
{
	if (N == 0)
		return 0;

#ifdef _MSC_VER
	// MSVC: 80 bytes per node + 80 byte base
	return 80 + 80 * N;
#else
	// Clang/GCC: 80 bytes per node
	return 80 * N;
#endif
}

template <typename T>
struct is_fundamental_or_void
	: std::bool_constant<std::is_fundamental_v<T> || std::is_void_v<T>>
{
};

template <typename T>
struct is_trivial_no_alloc : std::bool_constant<std::is_trivial_v<T> &&
								 std::is_trivially_copyable_v<T>>
{
};

template <typename T>
struct is_pmr_container : std::false_type
{
};

template <typename T>
struct is_pmr_container<std::pmr::vector<T>> : std::true_type
{
};
template <typename T>
struct is_pmr_container<std::pmr::basic_string<T>> : std::true_type
{
};
template <typename T>
struct is_pmr_container<std::pmr::list<T>> : std::true_type
{
};

template <typename T>
struct is_fixed_size_container : std::false_type
{
};

template <typename T, std::size_t N>
struct is_fixed_size_container<std::array<T, N>> : std::true_type
{
};

template <typename T>
struct is_fixed_size_container<std::span<T>> : std::true_type
{
};

template <typename T>
struct is_safe_for_buffer
	: std::bool_constant<is_fundamental_or_void<T>::value ||
		  is_trivial_no_alloc<T>::value || is_pmr_container<T>::value ||
		  is_fixed_size_container<T>::value>
{
};

template <typename T>
inline constexpr bool is_safe_for_buffer_v = is_safe_for_buffer<T>::value;

template <typename Key, typename Value, std::size_t ElementCount, bool Realloc,
	std::size_t _kotek_hm_Size =
		_kotek_pmr_hybrid_map_map_buffer_size(ElementCount)>
class hybrid_map
{
	static_assert(is_safe_for_buffer_v<Value>,
		"Value type must be fundamental, trivial, PMR container, or fixed-size "
		"container");

	static_assert(ElementCount == 0 ? Realloc : true,
		"if you specified ElementCount as 0 it means that it doesn't use stack "
		"memory at all and it means that container is forced to support "
		"reallocation!");

	template <typename _K, typename _T, typename _C>
	using base_type = _kotek_hm_container_namespace_pmr::map<_K, _T, _C>;

	template <typename _K, typename _T, typename _C>
	using base_multimap_type =
		_kotek_hm_container_namespace_pmr::multimap<_K, _T, _C>;

	using container_type = hybrid_map_container<Key, Value>;

public:
	using key_type = typename container_type::key_type;
	using key_compare = typename container_type::key_compare;
	using value_compare = typename container_type::value_compare;
	using mapped_type = typename container_type::mapped_type;

	using reverse_iterator = typename container_type::reverse_iterator;
	using const_reverse_iterator =
		typename container_type::const_reverse_iterator;

	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using difference_type = typename container_type::difference_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using pointer = typename container_type::pointer;
	using const_pointer = typename container_type::const_pointer;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;
	using allocator_type = typename container_type::allocator_type;

	using node_type = typename container_type::node_type;
	using insert_return_type = typename container_type::insert_return_type;

public:
	hybrid_map() : mem() {}

	explicit hybrid_map(const key_compare& comp) : mem(comp) {}

	template <class InputIt>
	hybrid_map(InputIt first, InputIt last,
		const key_compare& comp = key_compare()) : mem(first, last, comp)
	{
	}

	template <class InputIt>
	hybrid_map(InputIt first, InputIt last) : mem(first, last)
	{
	}

	hybrid_map(const hybrid_map& other) : mem(other) {}

	hybrid_map(hybrid_map&& other) : mem(other) {}

	hybrid_map(std::initializer_list<value_type> init,
		const key_compare& comp = key_compare()) : mem(init, comp)
	{
	}

	hybrid_map(std::initializer_list<value_type> init) : mem(init) {}

	~hybrid_map() {}

public:
	Value& at(const Key& key) { return mem.con.at(key); }
	const Value& at(const Key& key) const { return mem.con.at(key); }

	Value& operator[](const Key& key) { return mem.con.operator[](key); }

	Value& operator[](Key&& key) { return mem.con.operator[](std::move(key)); }

public:
	iterator begin() { return mem.con.begin(); }

	const_iterator begin() const { return mem.con.begin(); }

	const_iterator cbegin() const noexcept { return mem.con.cbegin(); }

	iterator end() { return mem.con.end(); }

	const_iterator end() const { return mem.con.end(); }

	const_iterator cend() const noexcept { return mem.con.cend(); }

	reverse_iterator rbegin() { return mem.con.rbegin(); }

	const_reverse_iterator rbegin() const { return mem.con.rbegin(); }

	const_reverse_iterator crbegin() const noexcept
	{
		return mem.con.crbegin();
	}

	reverse_iterator rend() { return mem.con.rend(); }

	const_reverse_iterator rend() const { return mem.con.rend(); }

	const_reverse_iterator crend() const noexcept { return mem.con.crend(); }

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
	std::pair<iterator, bool> insert_or_assign(const Key& k, M&& obj)
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
		return mem.con.insert_or_assign<K, M>(std::move(k), std::move(obj));
	}

	template <class M>
	iterator insert_or_assign(const_iterator hint, const Key& k, M&& obj)
	{
		return mem.con.insert_or_assign<M>(hint, k, obj);
	}

	template <class M>
	iterator insert_or_assign(const_iterator hint, Key&& k, M&& obj)
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
	std::pair<iterator, bool> try_emplace(const Key& k, Args&&... args)
	{
		return mem.con.try_emplace<Args>(k, std::forward<Args>(args)...);
	}

	template <class... Args>
	std::pair<iterator, bool> try_emplace(Key&& k, Args&&... args)
	{
		return mem.con.try_emplace<Args>(
			std::move(k), std::forward<Args>(args)...);
	}

	template <class... Args>
	iterator try_emplace(const_iterator hint, const Key& k, Args&&... args)
	{
		return mem.con.try_emplace<Args>(hint, k, std::forward<Args>(args)...);
	}

	template <class... Args>
	iterator try_emplace(const_iterator hint, Key&& k, Args&&... args)
	{
		return mem.con.try_emplace(
			hint, std::move(k), std::forward<Args>(args)...);
	}

	iterator erase(iterator pos) { return mem.con.erase(pos); }

	iterator erase(const_iterator pos) { return mem.con.erase(pos); }

	iterator erase(const_iterator first, const_iterator last)
	{
		return mem.con.erase(first, last);
	}

	size_type erase(const Key& key) { return mem.con.erase(key); }

	void swap(hybrid_map& other) noexcept { mem.con.swap(other); }

	node_type extract(const_iterator pos) { return mem.con.extract(pos); }

	node_type extract(const Key& k) { return mem.con.extract(k); }

	template <class C2>
	void merge(base_type<Key, Value, C2>& source)
	{
		mem.con.merge<C2>(source);
	}

	template <class C2>
	void merge(base_type<Key, Value, C2>&& source)
	{
		mem.con.merge<C2>(std::move(source));
	}

	template <class C2>
	void merge(base_multimap_type<Key, Value, C2>& source)
	{
		mem.con.merge<C2>(source);
	}

	template <class C2>
	void merge(base_multimap_type<Key, Value, C2>&& source)
	{
		mem.con.merge<C2>(std::move(source));
	}

public:
	size_type count(const Key& key) const { return mem.con.count(key); }

	template <class K>
	size_type count(const K& x) const
	{
		return mem.con.count<K>(x);
	}

	iterator find(const Key& key) { return mem.con.find(key); }

	const_iterator find(const Key& key) const { return mem.con.find(key); }

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

	std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		return mem.con.equal_range(key);
	}

	template <class K>
	std::pair<iterator, iterator> equal_range(const K& x)
	{
		return mem.con.equal_range(x);
	}

	template <class K>
	std::pair<const_iterator, const_iterator> equal_range(const K& x) const
	{
		return mem.con.equal_range(x);
	}

	iterator lower_bound(const Key& key) { return mem.con.lower_bound(key); }

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

	iterator upper_bound(const Key& key) { return mem.con.upper_bound(key); }

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

	value_compare value_comp() const { return mem.con.value_comp(); }

public:
	constexpr std::size_t preallocated_memory_size() const noexcept
	{
		return _kotek_hm_Size;
	}
	constexpr std::size_t preallocated_size() const noexcept
	{
		return ElementCount;
	}
	constexpr bool is_reallocation_supported() const noexcept
	{
		return Realloc;
	}

	const container_type& container() const noexcept { return mem.con; }
	container_type& container() noexcept { return mem.con; }
	container_type&& container_move_out() noexcept
	{
		return std::move(mem.con);
	}

private:
	struct layout_prealloc_t
	{
		layout_prealloc_t() :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{&pool}
		{
		}

		explicit layout_prealloc_t(const key_compare& comp) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{comp, &pool}
		{
		}

		template <class InputIt>
		layout_prealloc_t(InputIt first, InputIt last,
			const key_compare& comp = key_compare()) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{first, last, comp, &pool}
		{
		}

		template <typename InputIt>
		layout_prealloc_t(InputIt first, InputIt last) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(first, last, key_compare(), &pool)
		{
		}

		layout_prealloc_t(const hybrid_map& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{other.container(), &pool}
		{
		}

		layout_prealloc_t(hybrid_map&& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{std::move(other.container_move_out()), &pool}
		{
		}

		layout_prealloc_t(std::initializer_list<value_type> init,
			const key_compare& comp = key_compare()) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{init, comp, &pool}
		{
		}

		layout_prealloc_t(std::initializer_list<value_type> init) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hm_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(init, key_compare(), &pool)
		{
		}

		unsigned char buf[_kotek_hm_Size];
		_kotek_hm_container_namespace_pmr::monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		layout_no_prealloc_t() : con{} {}

		explicit layout_no_prealloc_t(const key_compare& comp) : con{comp} {}

		template <class InputIt>
		layout_no_prealloc_t(InputIt first, InputIt last,
			const key_compare& comp = key_compare()) : con{first, last, comp}
		{
		}

		template <typename InputIt>
		layout_no_prealloc_t(InputIt first, InputIt last) :
			con(first, last, key_compare())
		{
		}

		layout_no_prealloc_t(const hybrid_map& other) : con{other.container()}
		{
		}

		layout_no_prealloc_t(hybrid_map&& other) :
			con{std::move(other.container_move_out())}
		{
		}

		layout_no_prealloc_t(std::initializer_list<value_type> init,
			const key_compare& comp = key_compare()) : con{init, comp}
		{
		}

		layout_no_prealloc_t(std::initializer_list<value_type> init) :
			con(init, key_compare())
		{
		}

		container_type con;
	};

	using layout_t = _kotek_hm_container_namespace_conditional::conditional_t<
		ElementCount == 0, layout_no_prealloc_t, layout_prealloc_t>;

	layout_t mem;
};

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK