#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/unordered/unordered_set.hpp>
	#include <memory_resource>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <unordered_set>
	#include <memory_resource>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY

namespace __hus_container_namespace = ::boost;
namespace __hus_container_namespace_pmr = ::std::pmr;
namespace __hus_container_namespace_swap = ::std;
namespace __hus_container_namespace_conditional = ::std;

template <class Type>
using __hv_il_t = ::std::initializer_list<Type>;

template <typename Type>
using hybrid_unordered_set_container =
	__hus_container_namespace::unordered::unordered_set<Type,
		__hus_container_namespace::hash<Type>, std::equal_to<Type>,
		__hus_container_namespace_pmr::polymorphic_allocator<Type>>;

#elif defined(KOTEK_USE_STD_LIBRARY)

namespace __hus_container_namespace = ::std;
namespace __hus_container_namespace_pmr = ::std::pmr;
namespace __hus_container_namespace_swap = ::std;
namespace __hus_container_namespace_conditional = ::std;

template <class Type>
using __hv_il_t = ::std::initializer_list<Type>;

template <typename Type>
using hybrid_unordered_set_container = std::pmr::unordered_set<Type>;

#else
#endif

inline constexpr size_t __next_power_of_two(size_t n) noexcept
{
	if (n == 0)
		return 1;
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	if constexpr (sizeof(size_t) > 4)
	{
		n |= n >> 32;
	}
	return n + 1;
}

// Main buffer size calculation
inline constexpr size_t __calculate_unordered_set_size(
	size_t element_count) noexcept
{
	// Minimum buffer size for empty container
	if (element_count == 0)
		return 64;

	// Worst-case node size (MSVC: 24 bytes)
	constexpr size_t node_size = 24;

	// Worst-case bucket array calculation
	size_t bucket_array_size{};
	if (element_count < 8)
	{
		// Small collection case (matches MSVC minimum)
		bucket_array_size = 128;
	}
	else
	{
		// MSVC-style bucket array (power-of-two * sizeof(void*))
		const size_t min_buckets = element_count * 2;
		const size_t bucket_count = __next_power_of_two(min_buckets);
		bucket_array_size = bucket_count * sizeof(void*);
	}

	// Base memory requirements
	const size_t total_base = bucket_array_size + (element_count * node_size);

	// Safety margin: 30% extra + 64 bytes padding
	return total_base + (total_base * 3 + 9) / 10 + 64; // Ceiling division
}

template <typename Type, typename H, typename P, std::size_t ElementCount,
	bool Realloc,
	std::size_t __hus_Size = __calculate_unordered_set_size(ElementCount)>
class hybrid_unordered_set
{
	static_assert(ElementCount == 0 ? Realloc : true,
		"if you specified ElementCount as 0 it means that it doesn't use stack "
		"memory at all and it means that container is forced to support "
		"reallocation!");

public:
	using container_type = hybrid_unordered_set_container<Type>;
	using key_type = typename container_type::key_type;
	using hasher = typename container_type::hasher;
	using key_equal = typename container_type::key_equal;

	using local_iterator = typename container_type::local_iterator;
	using const_local_iterator = typename container_type::const_local_iterator;

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
	hybrid_unordered_set() : mem() {}

	hybrid_unordered_set(size_type bucket_count) : mem(bucket_count) {}

	hybrid_unordered_set(size_type bucket_count, const H& hash) :
		mem(bucket_count, hash)
	{
	}

	// explicit unordered_set(const allocator_type& alloc);

	template <class InputIt>
	hybrid_unordered_set(InputIt first, InputIt last, size_type bucket_count,
		const H& hash = H(), const key_equal& equal = key_equal()) :
		mem(first, last, bucket_count, hash, equal)
	{
	}

	template <class InputIt>
	hybrid_unordered_set(InputIt first, InputIt last, size_type bucket_count) :
		mem(first, last, bucket_count)
	{
	}

	template <class InputIt>
	hybrid_unordered_set(InputIt first, InputIt last, size_type bucket_count,
		const H& hash) : mem(first, last, bucket_count, hash)
	{
	}

	/*
	template<typename Type2, typename H2, typename P2, std::size_t Count, bool
	Realloc, typename = std::enable_if_t<(ElementCount < Count) && (Realloc ==
	false)>> hybrid_unordered_set(const hybrid_unordered_set<Type2, H2, P2,
	Count, Realloc>&) = delete;

	template<typename Type2, typename H2, typename P2, std::size_t Count, bool
	Realloc, typename = std::enable_if_t<(ElementCount < Count) && (Realloc ==
	false)>> hybrid_unordered_set(hybrid_unordered_set<Type2, H2, P2, Count,
	Realloc>&&) = delete;*/

	template <typename Type2, typename H2, typename P2,
		std::size_t ElementCount2, bool Realloc2,
		typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
										Realloc == true) &&
			std::is_same_v<Type, Type2>>>
	hybrid_unordered_set(
		const hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&
			other) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set{other.container(), &m_pool}
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	hybrid_unordered_set(const hybrid_unordered_set& other) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set{other.set, &m_pool}
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	hybrid_unordered_set(hybrid_unordered_set&& other) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set{std::move(other.set), &m_pool}
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	template <typename Type2, typename H2, typename P2,
		std::size_t ElementCount2, bool Realloc2,
		typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
										Realloc == true) &&
			std::is_same_v<Type, Type2>>>
	hybrid_unordered_set(
		hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&& other) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set{std::move(other.container_move_out()), &m_pool}
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	hybrid_unordered_set(std::initializer_list<value_type> init,
		size_type bucket_count, const H& hash = H(),
		const key_equal& equal = key_equal()) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set{init, bucket_count, hash, equal, &m_pool}
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	hybrid_unordered_set(
		std::initializer_list<value_type> init, size_type bucket_count) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set(init, bucket_count, H(), key_equal(), &m_pool)
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	hybrid_unordered_set(std::initializer_list<value_type> init,
		size_type bucket_count, const H& hash) :
		m_pool{(ElementCount == 0) ? nullptr : m_memory,
			(ElementCount == 0) ? 0 : __hus_Size,
			Realloc ? std::pmr::get_default_resource()
					: std::pmr::null_memory_resource()},
		set(init, bucket_count, hash, key_equal(), &m_pool)
	{
		if constexpr (ElementCount > 0)
		{
			set.reserve(ElementCount);
		}
	}

	~hybrid_unordered_set() {}

public:
	hybrid_unordered_set& operator=(const hybrid_unordered_set& other)
	{
		set.operator=(other.set);
		return *this;
	}

	hybrid_unordered_set& operator=(const container_type& other)
	{
		set.operator=(other);
		return *this;
	}

	hybrid_unordered_set& operator=(hybrid_unordered_set&& other) noexcept
	{
		set.operator=(std::move(other.set));
		return *this;
	}

	hybrid_unordered_set& operator=(container_type&& other)
	{
		set.operator=(std::move(other));
		return *this;
	}

	hybrid_unordered_set& operator=(std::initializer_list<value_type> ilist);

	allocator_type get_allocator() const noexcept
	{
		return set.get_allocator();
	}

	iterator begin() noexcept { return set.begin(); }

	const_iterator begin() const noexcept { return set.begin(); }

	const_iterator cbegin() const noexcept { return set.cbegin(); }

	iterator end() noexcept { return set.end(); }

	const_iterator end() const noexcept { return set.end(); }

	const_iterator cend() const noexcept { return set.cend(); }

	bool empty() const noexcept { return set.empty(); }

	size_type size() const noexcept { return set.size(); }

	size_type max_size() const noexcept { return set.max_size(); }

	void clear() noexcept { return set.clear(); }

	std::pair<iterator, bool> insert(const value_type& value)
	{
		return set.insert(value);
	}

	std::pair<iterator, bool> insert(value_type&& value)
	{
		return set.insert(std::move(value));
	}

	iterator insert(const_iterator hint, const value_type& value)
	{
		return set.insert(hint, value);
	}

	iterator insert(const_iterator hint, value_type&& value)
	{
		return set.insert(hint, std::move(value));
	}

	template <class InputIt>
	void insert(InputIt first, InputIt last)
	{
		set.insert<InputIt>(first, last);
	}

	void insert(std::initializer_list<value_type> ilist) { set.insert(ilist); }

	insert_return_type insert(node_type&& nh) { return set.insert(nh); }

	iterator insert(const_iterator hint, node_type&& nh)
	{
		return set.insert(hint, nh);
	}

	template <class... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return set.emplace(std::forward<Args>(args)...);
	}

	template <class... Args>
	iterator emplace_hint(const_iterator hint, Args&&... args)
	{
		return set.emplace_hint(hint, std::forward<Args>(args)...);
	}

	/*
	iterator erase(iterator pos)
	{
	    return set.erase(pos);
	}
	*/

	iterator erase(const_iterator pos) { return set.erase(pos); }

	iterator erase(const_iterator first, const_iterator last)
	{
		return set.erase(first, last);
	}

	size_type erase(const Type& key) { return set.erase(key); }

	void swap(hybrid_unordered_set& other) noexcept { set.swap(other.set); }

	void swap(container_type& other) noexcept { set.swap(other); }

	node_type extract(const_iterator pos) { return set.extract(pos); }

	node_type extract(const Type& k) { return set.extract(k); }

	template <class H2, class P2>
	void merge(
		hybrid_unordered_set<Type, H2, P2, ElementCount, Realloc>& source)
	{
		set.merge(source.set);
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_set<Type, H2, P2>& source)
	{
		set.merge(source);
	}

	template <class H2, class P2>
	void merge(
		hybrid_unordered_set<Type, H2, P2, ElementCount, Realloc>&& source)
	{
		set.merge(std::move(source.set));
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_set<Type, H2, P2>&& source)
	{
		set.merge(std::move(source));
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_multiset<Type, H2, P2>& source)
	{
		set.merge(source);
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_multiset<Type, H2, P2>&& source)
	{
		set.merge(std::move(source));
	}

	size_type count(const Type& key) const { return set.count(key); }

	iterator find(const Type& key) { return set.find(key); }

	const_iterator find(const Type& key) const { return set.find(key); }

	std::pair<iterator, iterator> equal_range(const Type& key)
	{
		return set.equal_range(key);
	}

	std::pair<const_iterator, const_iterator> equal_range(const Type& key) const
	{
		return set.equal_range(key);
	}

	local_iterator begin(size_type n) { return set.begin(n); }

	const_local_iterator begin(size_type n) const { return set.begin(n); }

	const_local_iterator cbegin(size_type n) const { return set.cbegin(n); }

	local_iterator end(size_type n) { return set.end(n); }

	const_local_iterator end(size_type n) const { return set.end(n); }
	const_local_iterator cend(size_type n) const { return set.cend(n); }

	size_type bucket_count() const { return set.bucket_count(); }

	size_type max_bucket_count() const { return set.max_bucket_count(); }

	size_type bucket_size(size_type n) const { return set.bucket_size(n); }

	size_type bucket(const Type& key) const { return set.bucket(key); }

	float load_factor() const { return set.load_factor(); }

	float max_load_factor() const { return set.max_load_factor(); }

	void max_load_factor(float ml) { return set.max_load_factor(ml); }

	void rehash(size_type count) { return set.rehash(count); }

	void reserve(size_type count) { return set.reserve(count); }

	hasher hash_function() const { return set.hash_function(); }

	key_equal key_eq() const { return set.key_eq(); }

public:
	constexpr std::size_t preallocated_memory_size() const noexcept
	{
		return __hus_Size;
	}
	constexpr std::size_t preallocated_size() const noexcept
	{
		return ElementCount;
	}
	constexpr bool is_reallocation_supported() const noexcept
	{
		return Realloc;
	}

	const container_type& container() const noexcept { return set; }
	container_type& container() noexcept { return set; }
	container_type&& container_move_out() noexcept { return std::move(str); }

private:
	struct layout_prealloc_t
	{
		layout_prealloc_t() :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{&pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(size_type bucket_count) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(bucket_count, H(), P(), &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(size_type bucket_count, const H& hash) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(bucket_count, hash, P(), &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class InputIt>
		layout_prealloc_t(InputIt first, InputIt last, size_type bucket_count,
			const H& hash = H(), const key_equal& equal = key_equal()) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(first, last, bucket_count, hash, equal, &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class InputIt>
		layout_prealloc_t(InputIt first, InputIt last, size_type bucket_count) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(first, last, bucket_count, H(), key_equal(), &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class InputIt>
		layout_prealloc_t(InputIt first, InputIt last, size_type bucket_count,
			const H& hash) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(first, last, bucket_count, hash, key_equal(), &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		unsigned char buf[__hus_Size];
		__hv_container_namespace_pmr::monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		container_type con;
	};

	using layout_t =
		__hv_container_namespace_conditional::conditional_t<ElementCount == 0,
			layout_no_prealloc_t, layout_prealloc_t>;

	layout_t mem;
};

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK