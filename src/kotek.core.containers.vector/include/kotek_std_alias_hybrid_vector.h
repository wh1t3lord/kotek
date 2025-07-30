#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/pmr/vector.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <vector>
	#include <memory_resource>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY

namespace __hv_container_namespace = ::boost;

namespace __hv_container_namespace_pmr = ::boost::container::pmr;

namespace __hv_container_namespace_swap = ::std;

namespace __hv_container_namespace_conditional = ::std;

/// @brief \~english notice that some libraries are not supposed to have some
/// implementations and for that you can use from standard as boost library did
/// or provide own implementation but you have to specify the aliases all
/// @tparam Type
template <class Type>
using __hv_il_t = ::std::initializer_list<Type>;

template <typename Type>
using hybrid_vector_container = __hv_container_namespace_pmr::vector<Type>;

#elif defined(KOTEK_USE_STD_LIBRARY)

namespace __hv_container_namespace = ::std;

namespace __hv_container_namespace_pmr = ::std::pmr;

namespace __hv_container_namespace_swap = ::std;

namespace __hv_container_namespace_conditional = ::std;

/// @brief \~english notice that some libraries are not supposed to have some
/// implementations and for that you can use from standard as boost library did
/// or provide own implementation but you have to specify the aliases all
/// @tparam Type
template <class Type>
using __hv_il_t = ::std::initializer_list<Type>;

template <typename Type>
using hybrid_vector_container = __hv_container_namespace_pmr::vector<Type>;

#else
#endif

template <typename Type, kun_ktk size_t ElementCount, bool Realloc,
	kun_ktk size_t __hv_Size
#ifdef KOTEK_DEBUG
	= sizeof(Type) * ElementCount * 2
#else
	= sizeof(Type) * ElementCount
#endif
	>
class hybrid_vector_impl
{
	static_assert(ElementCount == 0 ? Realloc : true,
		"you must set Realloc=true if you passed ElementCount==0");

public:
	using container_type = typename hybrid_vector_container<Type>;

	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using difference_type = typename container_type::difference_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using pointer = typename container_type::pointer;
	using const_pointer = typename container_type::const_pointer;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;
	using reverse_iterator = typename container_type::reverse_iterator;
	using const_reverse_iterator =
		typename container_type::const_reverse_iterator;
	using allocator_type = typename container_type::allocator_type;

public:
	hybrid_vector_impl() : mem() {}

	explicit hybrid_vector_impl(size_type count) : mem(count) {}

	hybrid_vector_impl(size_type count, const Type& value) : mem(count, value)
	{
	}

	template <class InputIt>
	hybrid_vector_impl(InputIt first, InputIt last) : mem<InputIt>(first, last)
	{
	}

	template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
		typename = __hv_container_namespace::enable_if_t<
			(ElementCount >= ElementCount2 || Realloc == true) &&
			__hv_container_namespace::is_same_v<Type, Type2>>>
	hybrid_vector_impl(
		const hybrid_vector_impl<Type2, ElementCount2, Realloc2>& other) :
		mem<Type2, ElementCount2, Realloc2>(other)
	{
	}

	hybrid_vector_impl(const hybrid_vector_impl& other) : mem(other)
	{
	}

	template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
		typename = __hv_container_namespace::enable_if_t<
			(ElementCount >= ElementCount2 || Realloc == true) &&
			__hv_container_namespace::is_same_v<Type, Type2>>>
	hybrid_vector_impl(
		hybrid_vector_impl<Type2, ElementCount2, Realloc2>&& other) :
		pool{memory, __hv_Size,
			Realloc ? __hv_container_namespace_pmr::get_default_resource()
					: __hv_container_namespace_pmr::null_memory_resource()},
		con{__hv_container_namespace::move(other.container_move()), &pool}
	{
		if constexpr (ElementCount > 0)
		{
			con.reserve(ElementCount);
		}
	}

	hybrid_vector_impl(hybrid_vector_impl&& other) noexcept :
		pool{(ElementCount == 0) ? nullptr : buf,
			(ElementCount == 0) ? 0 : __hv_Size,
			Realloc ? __hv_container_namespace_pmr::get_default_resource()
					: __hv_container_namespace_pmr::null_memory_resource()},
		con{__hv_container_namespace::move(other.vec), &pool}
	{
		if constexpr (ElementCount > 0)
		{
			con.reserve(ElementCount);
		}
	}

	hybrid_vector_impl(__hv_il_t<Type> init) :
		pool{(ElementCount == 0) ? nullptr : buf,
			(ElementCount == 0) ? 0 : __hv_Size,
			Realloc ? __hv_container_namespace_pmr::get_default_resource()
					: __hv_container_namespace_pmr::null_memory_resource()},
		con{init, &pool}
	{
		if constexpr (ElementCount > 0)
		{
			con.reserve(ElementCount);
		}
	}

	~hybrid_vector_impl() {}

public:
	reference at(size_type pos) { return con.at(pos); }
	const_reference at(size_type pos) const { return con.at(pos); }
	reference operator[](size_type pos) { return con[pos]; }
	const_reference operator[](size_type pos) const { return con[pos]; }
	reference front() { return con.front(); }
	const_reference front() const { return con.front(); }
	reference back() { return con.back(); }
	const_reference back() const { return con.back(); }
	pointer data() noexcept { return con.data(); }
	const_pointer data() const noexcept { return con.data(); }

	iterator begin() noexcept { return con.begin(); }
	const_iterator begin() const noexcept { return con.begin(); }
	const_iterator cbegin() const noexcept { return con.cbegin(); }

	iterator end() noexcept { return con.end(); }
	const_iterator end() const noexcept { return con.end(); }
	const_iterator cend() const noexcept { return con.cend(); }

	reverse_iterator rbegin() noexcept { return con.rbegin(); }
	const_reverse_iterator rbegin() const noexcept { return con.rbegin(); }
	const_reverse_iterator crbegin() const noexcept { return con.crbegin(); }

	reverse_iterator rend() noexcept { return con.rend(); }
	const_reverse_iterator rend() const noexcept { return con.rend(); }
	const_reverse_iterator crend() const noexcept { return con.crend(); }

	bool empty() const noexcept { return con.empty(); }
	size_type size() const noexcept { return con.size(); }
	size_type max_size() const noexcept { return con.max_size(); }
	void reserve(size_type new_cap) { con.reserve(new_cap); }
	size_type capacity() const noexcept { return con.capacity(); }
	void shrink_to_fit() { con.shrink_to_fit(); }

	void clear() noexcept { con.clear(); }

	template <typename... Args>
	reference emplace_back(Args&&... args)
	{
		return con.emplace_back(
			__hv_container_namespace::forward<Args>(args)...);
	}

	template <class... Args>
	iterator emplace(const_iterator pos, Args&&... args)
	{
		return con.emplace(__hv_container_namespace::forward<Args>(args)...);
	}

	iterator insert(const_iterator pos, const Type& value)
	{
		return con.insert(pos, value);
	}
	iterator insert(const_iterator pos, Type&& value)
	{
		return con.insert(pos, __hv_container_namespace::move(value));
	}
	iterator insert(const_iterator pos, size_type count, const Type& value)
	{
		return con.insert(pos, count, value);
	}

	template <class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last)
	{
		return con.insert<InputIt>(pos, first, last);
	}

	iterator insert(const_iterator pos, __hv_il_t<Type> ilist)
	{
		return con.insert(pos, ilist);
	}

	void push_back(const Type& value) { con.push_back(value); }
	void push_back(Type&& value)
	{
		con.push_back(__hv_container_namespace::move(value));
	}
	void pop_back() { con.pop_back(); }

	void resize(size_type count) { con.resize(count); }
	void resize(size_type count, const Type& value)
	{
		con.resize(count, value);
	}

	void swap(hybrid_vector_impl& other) noexcept
	{
		__hv_container_namespace_swap::swap(con, other.con);
	}

	iterator erase(iterator pos) { return con.erase(pos); }
	iterator erase(const_iterator pos) { return con.erase(pos); }
	iterator erase(iterator first, iterator last)
	{
		return con.erase(first, last);
	}
	iterator erase(const_iterator first, const_iterator last)
	{
		return con.erase(first, last);
	}

	void assign(size_type count, const Type& value)
	{
		return con.assign(count, value);
	}

	template <class InputIt>
	void assign(InputIt first, InputIt last)
	{
		return con.assign<InputIt>(first, last);
	}

	void assign(__hv_il_t<Type> ilist) { return con.assign(ilist); }

	allocator_type get_allocator() const { return con.get_allocator(); }

	hybrid_vector_impl& operator=(const hybrid_vector_impl& other)
	{
		con.operator=(other.con);
		return *this;
	}
	hybrid_vector_impl& operator=(const container_type& other)
	{
		con.operator=(other);
		return *this;
	}

	hybrid_vector_impl& operator=(hybrid_vector_impl&& other)
	{
		con.operator=(__hv_container_namespace::move(other.con));
		return *this;
	}

	hybrid_vector_impl& operator=(container_type&& other)
	{
		con.operator=(__hv_container_namespace::move(other));
		return *this;
	}

	hybrid_vector_impl& operator=(__hv_il_t<value_type> ilist)
	{
		con.operator=(ilist);
		return *this;
	}

public:
	const container_type& container(void) const noexcept { return con; }
	container_type& container(void) noexcept { return con; }
	container_type&& container_move(void) noexcept
	{
		return __hv_container_namespace::move(con);
	}

	constexpr kun_ktk size_t size_preallocated(void) const noexcept
	{
		return ElementCount;
	}

	constexpr kun_ktk size_t size_preallocated_memory(
		void) const KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		return __hv_Size;
	}

	constexpr bool is_static(void) const noexcept { return Realloc; }

private:
	struct layout_prealloc_t
	{
		layout_prealloc_t() :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hv_Size,
				Realloc ? __hv_container_namespace_pmr::get_default_resource()
						: __hv_container_namespace_pmr::null_memory_resource()},
			con{&pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		explicit layout_prealloc_t(size_type count) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hv_Size,
				Realloc ? __hv_container_namespace_pmr::get_default_resource()
						: __hv_container_namespace_pmr::null_memory_resource()},
			con{count, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(size_type count, const Type& value) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hv_Size,
				Realloc ? __hv_container_namespace_pmr::get_default_resource()
						: __hv_container_namespace_pmr::null_memory_resource()},
			con{count, value, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class InputIt>
		layout_prealloc_t(InputIt first, InputIt last) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hv_Size,
				Realloc ? __hv_container_namespace_pmr::get_default_resource()
						: __hv_container_namespace_pmr::null_memory_resource()},
			con{first, last, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
			typename = __hv_container_namespace::enable_if_t<
				(ElementCount >= ElementCount2 || Realloc == true) &&
				__hv_container_namespace::is_same_v<Type, Type2>>>
		layout_prealloc_t(
			const hybrid_vector_impl<Type2, ElementCount2, Realloc2>& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : __hv_Size,
				Realloc ? __hv_container_namespace_pmr::get_default_resource()
						: __hv_container_namespace_pmr::null_memory_resource()},
			con{other.container(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(const hybrid_vector_impl& other) pool{
			(ElementCount == 0) ? nullptr : buf,
			(ElementCount == 0) ? 0 : __hv_Size,
			Realloc ? __hv_container_namespace_pmr::get_default_resource()
					: __hv_container_namespace_pmr::null_memory_resource()},
			con{other.container(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		unsigned char buf[__hv_Size == 0 ? 1 : __hv_Size];
		__hv_container_namespace_pmr::monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		layout_no_prealloc_t() : con() {}

		container_type con;
	};

	using layout_t =
		__hv_container_namespace_conditional::conditional_t<ElementCount == 0,
			layout_no_prealloc_t, layout_prealloc_t>;

	layout_t mem;
};

template <typename Type, kun_ktk size_t NotInUsed = 0>
using hybrid_std_vector = hybrid_vector_impl<Type, 0, true>;

template <typename Type, kun_ktk size_t ElementCount>
using hybrid_vector = hybrid_vector_impl<Type, ElementCount, true>;

template <typename Type, kun_ktk size_t ElementCount>
using static_hybrid_vector = hybrid_vector_impl<Type, ElementCount, false>;

KOTEK_END_NAMESPACE_KTK

template <typename Type, kun_ktk size_t NotInUsed = 0>
using hybrid_std_vector_t = kun_ktk hybrid_std_vector<Type, NotInUsed>;

template <typename Type, kun_ktk size_t ElementCount>
using hybrid_vector_t = kun_ktk hybrid_vector<Type, ElementCount>;

template <typename Type, kun_ktk size_t ElementCount>
using static_hybrid_vector_t = kun_ktk static_hybrid_vector<Type, ElementCount>;

KOTEK_END_NAMESPACE_KOTEK