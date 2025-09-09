#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

/* even for current 1.84-1.89 there's no support for unordered_set
* it means that unordered_set has undefined behaviour with polymorphic_allocator 
* for a trivial test sample you can test on just initialization of unordered_set with {1,2,3} and do .find(2); .erase(it); and you will get next as == to .end but it is expected as != because iterators that were increments are invalid!!
* So in such case we use std 
* You can use only when unordered_set header will be shown in boost/container/pmr folder otherwise for now and further versions of boost are treated as not compatible with polymorphic_allocator usage
namespace boost
{
	namespace unordered
	{
		namespace detail
		{

			// Provide a swap function for polymorphic_allocator that Boost can
			// find via ADL
			template <typename T>
			void swap(std::pmr::polymorphic_allocator<T>& a,
				std::pmr::polymorphic_allocator<T>& b) noexcept
			{
				// polymorphic_allocators are stateless, so swap is a no-op
			}

		} // namespace detail
	} // namespace unordered
} // namespace boost

	#include <boost/unordered/unordered_set.hpp>
	#include <unordered_set>
	#include <memory_resource>
*/

	#include <unordered_set>
	#include <memory_resource>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <unordered_set>
	#include <memory_resource>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY

/* rn boost doesn't provide implementation of pmr unordered_set
namespace _kotek_hus_container_namespace = ::boost;
namespace _kotek_hus_container_namespace_pmr = ::std::pmr;
namespace _kotek_hus_container_namespace_swap = ::std;
namespace _kotek_hus_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hus_il_t = ::std::initializer_list<Type>;

template <typename Type, typename Hasher, typename KeyEqual>
using hybrid_unordered_set_container =
	_kotek_hus_container_namespace::unordered::unordered_set<Type, Hasher,
		KeyEqual,
		_kotek_hus_container_namespace_pmr::polymorphic_allocator<Type>>;
*/

namespace _kotek_hus_container_namespace = ::std;
namespace _kotek_hus_container_namespace_pmr = ::std::pmr;
namespace _kotek_hus_container_namespace_swap = ::std;
namespace _kotek_hus_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hus_il_t = ::std::initializer_list<Type>;

template <typename Type, typename Hasher, typename KeyEqual>
using hybrid_unordered_set_container =
	std::pmr::unordered_set<Type, Hasher, KeyEqual>;

#elif defined(KOTEK_USE_STD_LIBRARY)

namespace _kotek_hus_container_namespace = ::std;
namespace _kotek_hus_container_namespace_pmr = ::std::pmr;
namespace _kotek_hus_container_namespace_swap = ::std;
namespace _kotek_hus_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hus_il_t = ::std::initializer_list<Type>;

template <typename Type, typename Hasher, typename KeyEqual>
using hybrid_unordered_set_container =
	std::pmr::unordered_set<Type, Hasher, KeyEqual>;

#else
#endif

constexpr size_t _kotek_hus_default_bucket_count = 0;

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
	std::size_t _kotek_hus_Size = __calculate_unordered_set_size(ElementCount)>
class hybrid_unordered_set
{
	static_assert(ElementCount == 0 ? Realloc : true,
		"if you specified ElementCount as 0 it means that it doesn't use stack "
		"memory at all and it means that container is forced to support "
		"reallocation!");

public:
	using container_type = hybrid_unordered_set_container<Type, H, P>;
	using key_type = typename container_type::key_type;
	using hasher = typename container_type::hasher;
	using key_equal = typename container_type::key_equal;
	using allocator_type = typename container_type::allocator_type;

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

	explicit hybrid_unordered_set(size_type bucket_count, const H& hash = H()) :
		mem(bucket_count, hash)
	{
	}

	// explicit unordered_set(const allocator_type& alloc);

	template <class InputIt>
	hybrid_unordered_set(InputIt first, InputIt last,
		size_type bucket_count = _kotek_hus_default_bucket_count,
		const H& hash = H(), const key_equal& equal = key_equal()) :
		mem(first, last, bucket_count, hash, equal)
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
			other) : mem(other)
	{
	}

	hybrid_unordered_set(const hybrid_unordered_set& other) : mem(other) {}

	hybrid_unordered_set(hybrid_unordered_set&& other) : mem(std::move(other))
	{
	}

	template <typename Type2, typename H2, typename P2,
		std::size_t ElementCount2, bool Realloc2,
		typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
										Realloc == true) &&
			std::is_same_v<Type, Type2>>>
	hybrid_unordered_set(
		hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&& other) :
		mem(other)
	{
	}

	hybrid_unordered_set(_kotek_hus_il_t<value_type> init,
		size_type bucket_count = _kotek_hus_default_bucket_count,
		const H& hash = H(), const key_equal& equal = key_equal()) :
		mem(init, bucket_count, hash, equal)
	{
	}

	~hybrid_unordered_set() {}

public:
	hybrid_unordered_set& operator=(const hybrid_unordered_set& other)
	{
		mem.con.operator=(other.mem.con);
		return *this;
	}

	hybrid_unordered_set& operator=(const container_type& other)
	{
		mem.con.operator=(other);
		return *this;
	}

	hybrid_unordered_set& operator=(hybrid_unordered_set&& other) noexcept
	{
		mem.con.operator=(std::move(other.mem.con));
		return *this;
	}

	hybrid_unordered_set& operator=(container_type&& other)
	{
		mem.con.operator=(std::move(other));
		return *this;
	}

	hybrid_unordered_set& operator=(_kotek_hus_il_t<value_type> ilist)
	{
		mem.con.operator=(ilist);
		return *this;
	}

	allocator_type get_allocator() const noexcept
	{
		return mem.con.get_allocator();
	}

	iterator begin() noexcept { return mem.con.begin(); }

	const_iterator begin() const noexcept { return mem.con.begin(); }

	const_iterator cbegin() const noexcept { return mem.con.cbegin(); }

	iterator end() noexcept { return mem.con.end(); }

	const_iterator end() const noexcept { return mem.con.end(); }

	const_iterator cend() const noexcept { return mem.con.cend(); }

	bool empty() const noexcept { return mem.con.empty(); }

	size_type size() const noexcept { return mem.con.size(); }

	size_type max_size() const noexcept { return mem.con.max_size(); }

	void clear() noexcept { return mem.con.clear(); }

	std::pair<iterator, bool> insert(const value_type& value)
	{
		return mem.con.insert(value);
	}

	std::pair<iterator, bool> insert(value_type&& value)
	{
		return mem.con.insert(std::move(value));
	}

	iterator insert(const_iterator hint, const value_type& value)
	{
		return mem.con.insert(hint, value);
	}

	iterator insert(const_iterator hint, value_type&& value)
	{
		return mem.con.insert(hint, std::move(value));
	}

	template <class InputIt>
	void insert(InputIt first, InputIt last)
	{
		mem.con.insert<InputIt>(first, last);
	}

	void insert(_kotek_hus_il_t<value_type> ilist) { mem.con.insert(ilist); }

	insert_return_type insert(node_type&& nh) { return mem.con.insert(nh); }

	iterator insert(const_iterator hint, node_type&& nh)
	{
		return mem.con.insert(hint, nh);
	}

	template <class... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return mem.con.emplace(std::forward<Args>(args)...);
	}

	template <class... Args>
	iterator emplace_hint(const_iterator hint, Args&&... args)
	{
		return mem.con.emplace_hint(hint, std::forward<Args>(args)...);
	}

	/*
	iterator erase(iterator pos)
	{
	    return set.erase(pos);
	}
	*/

	iterator erase(const_iterator pos) { return mem.con.erase(pos); }

	iterator erase(const_iterator first, const_iterator last)
	{
		return mem.con.erase(first, last);
	}

	size_type erase(const Type& key) { return mem.con.erase(key); }

	void swap(hybrid_unordered_set& other) 
	{
		throw "stl doesn't support swap operation";
	}

	void swap(container_type& other) noexcept { mem.con.swap(other); }

	node_type extract(const_iterator pos) { return mem.con.extract(pos); }

	node_type extract(const Type& k) { return mem.con.extract(k); }

	template <class H2, class P2>
	void merge(
		hybrid_unordered_set<Type, H2, P2, ElementCount, Realloc>& source)
	{
		throw "stl polymorphic_allocator doesn't support merge";
		//		mem.con.merge(source.mem.con);
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_set<Type, H2, P2>& source)
	{
		throw "stl polymorphic_allocator doesn't support merge";
	//	mem.con.merge(source);
	}

	template <class H2, class P2>
	void merge(
		hybrid_unordered_set<Type, H2, P2, ElementCount, Realloc>&& source)
	{
		throw "stl polymorphic_allocator doesn't support merge";
	//	mem.con.merge(std::move(source.mem.con));
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_set<Type, H2, P2>&& source)
	{
		throw "stl polymorphic_allocator doesn't support merge";
	//	mem.con.merge(std::move(source));
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_multiset<Type, H2, P2>& source)
	{
		throw "stl polymorphic_allocator doesn't support merge";
	//	mem.con.merge(source);
	}

	template <class H2, class P2>
	void merge(std::pmr::unordered_multiset<Type, H2, P2>&& source)
	{
		throw "stl polymorphic_allocator doesn't support merge";
	//	mem.con.merge(std::move(source));
	}

	size_type count(const Type& key) const { return mem.con.count(key); }

	iterator find(const Type& key) { return mem.con.find(key); }

	const_iterator find(const Type& key) const { return mem.con.find(key); }

	std::pair<iterator, iterator> equal_range(const Type& key)
	{
		return mem.con.equal_range(key);
	}

	std::pair<const_iterator, const_iterator> equal_range(const Type& key) const
	{
		return mem.con.equal_range(key);
	}

	local_iterator begin(size_type n) { return mem.con.begin(n); }

	const_local_iterator begin(size_type n) const { return mem.con.begin(n); }

	const_local_iterator cbegin(size_type n) const { return mem.con.cbegin(n); }

	local_iterator end(size_type n) { return mem.con.end(n); }

	const_local_iterator end(size_type n) const { return mem.con.end(n); }
	const_local_iterator cend(size_type n) const { return mem.con.cend(n); }

	size_type bucket_count() const { return mem.con.bucket_count(); }

	size_type max_bucket_count() const { return mem.con.max_bucket_count(); }

	size_type bucket_size(size_type n) const { return mem.con.bucket_size(n); }

	size_type bucket(const Type& key) const { return mem.con.bucket(key); }

	float load_factor() const { return mem.con.load_factor(); }

	float max_load_factor() const { return mem.con.max_load_factor(); }

	void max_load_factor(float ml) { return mem.con.max_load_factor(ml); }

	void rehash(size_type count) { return mem.con.rehash(count); }

	void reserve(size_type count) { return mem.con.reserve(count); }

	hasher hash_function() const { return mem.con.hash_function(); }

	key_equal key_eq() const { return mem.con.key_eq(); }

public:
	constexpr std::size_t preallocated_memory_size() const noexcept
	{
		return _kotek_hus_Size;
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
	container_type container_move_out() noexcept
	{
		container_type temp = std::move(mem.con);
		return std::move(temp);
	}

private:
	struct layout_prealloc_t
	{
		layout_prealloc_t() :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{&pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(size_type bucket_count, const H& hash) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
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
		layout_prealloc_t(InputIt first, InputIt last,
			size_type bucket_count = _kotek_hus_default_bucket_count,
			const H& hash = H(), const key_equal& equal = key_equal()) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con(first, last, bucket_count, hash, equal, &pool)
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <typename Type2, typename H2, typename P2,
			std::size_t ElementCount2, bool Realloc2,
			typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
											Realloc == true) &&
				std::is_same_v<Type, Type2>>>

		layout_prealloc_t(
			const hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&
				other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{other.container(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(const hybrid_unordered_set& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{other.mem.con, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(hybrid_unordered_set&& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{std::move(other.mem.con), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}

#ifdef KOTEK_USE_BOOST_LIBRARY
	#if BOOST_VERSION <= 108400
			// in some cases when we do move they compare resources
			// (std::pmr::memory_resource) that used by polymorphic_allocator so
			// they compare them on equality and by that time we have different
			// resources because of different resources, memory were allocated
			// differently and on con that being constructed here will have
			// different free amount of memory but that container what we move
			// will have different free amount of memory too and that might
			// cause their == expression as false and thus leads to not valid
			// move operation as we expect, but since it is reallocated
			// containers the clear is just for ensurance that behaviour would
			// be expected
			// so for example std::pmr::unordered_set with passed unsigned char
			// buf still after moving will set to 0 its content (like it was
			// really moved or just issued clear) but boost version doesn't do
			// it!
			other.mem.con.clear();
	#else
				// todo: test
				// test_container_hybrid_unordered_set_move_constructor will it
				// be same as std container behaviour?
	#endif
#endif
		}

		template <typename Type2, typename H2, typename P2,
			std::size_t ElementCount2, bool Realloc2,
			typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
											Realloc == true) &&
				std::is_same_v<Type, Type2>>>
		layout_prealloc_t(
			hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&&
				other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{std::move(other.container_move_out()), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(_kotek_hus_il_t<value_type> init,
			size_type bucket_count = _kotek_hus_default_bucket_count,
			const H& hash = H(), const key_equal& equal = key_equal()) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hus_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{init, bucket_count, hash, equal, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		unsigned char buf[_kotek_hus_Size];
		_kotek_hus_container_namespace_pmr::monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		layout_no_prealloc_t() : con{} {}

		layout_no_prealloc_t(size_type bucket_count, const H& hash) :
			con(bucket_count, hash, P())
		{
		}

		template <class InputIt>
		layout_no_prealloc_t(InputIt first, InputIt last,
			size_type bucket_count = _kotek_hus_default_bucket_count,
			const H& hash = H(), const key_equal& equal = key_equal()) :
			con(first, last, bucket_count, hash, equal)
		{
		}

		template <typename Type2, typename H2, typename P2,
			std::size_t ElementCount2, bool Realloc2,
			typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
											Realloc == true) &&
				std::is_same_v<Type, Type2>>>

		layout_no_prealloc_t(
			const hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&
				other) : con{other.container()}
		{
		}

		layout_no_prealloc_t(const hybrid_unordered_set& other) :
			con{other.mem.con}
		{
		}

		layout_no_prealloc_t(hybrid_unordered_set&& other) :
			con{std::move(other.mem.con)}
		{
		}

		template <typename Type2, typename H2, typename P2,
			std::size_t ElementCount2, bool Realloc2,
			typename = std::enable_if_t<(ElementCount >= ElementCount2 ||
											Realloc == true) &&
				std::is_same_v<Type, Type2>>>
		layout_no_prealloc_t(
			hybrid_unordered_set<Type2, H2, P2, ElementCount2, Realloc2>&&
				other) : con{std::move(other.container_move_out())}
		{
		}

		layout_no_prealloc_t(_kotek_hus_il_t<value_type> init,
			size_type bucket_count = _kotek_hus_default_bucket_count,
			const H& hash = H(), const key_equal& equal = key_equal()) :
			con{init, bucket_count, hash, equal}
		{
		}

		container_type con;
	};

	using layout_t = _kotek_hus_container_namespace_conditional::conditional_t<
		ElementCount == 0, layout_no_prealloc_t, layout_prealloc_t>;

	layout_t mem;
};

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK