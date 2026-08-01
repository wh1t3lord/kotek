#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/pmr/deque.hpp>
	#include <queue>
	#include <memory_resource>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <deque>
	#include <queue>
	#include <memory_resource>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY

namespace _kotek_hq_container_namespace = ::boost;

namespace _kotek_hq_container_namespace_pmr = ::std::pmr;

namespace _kotek_hq_container_namespace_swap = ::std;

namespace _kotek_hq_container_namespace_conditional = ::std;

namespace _kotek_hq_container_namespace_enable_if = ::std;

namespace _kotek_hq_container_namespace_is_same_v = ::std;

namespace _kotek_hq_container_namespace_forward = ::std;

template <typename Type>
using hybrid_queue_underlying_container =
	_kotek_hq_container_namespace_pmr::deque<Type>;

/// @brief \~english std (and boost) provide no pmr queue because queue is a
/// container adaptor, not a container — the hybrid queue is therefore the
/// standard adaptor over the pmr deque fed by the bounded buffer
/// @tparam Type
template <typename Type>
using hybrid_queue_container =
	::std::queue<Type, hybrid_queue_underlying_container<Type>>;

#elif defined(KOTEK_USE_STD_LIBRARY)

namespace _kotek_hq_container_namespace = ::std;

namespace _kotek_hq_container_namespace_pmr = ::std::pmr;

namespace _kotek_hq_container_namespace_swap = ::std;

namespace _kotek_hq_container_namespace_conditional = ::std;

namespace _kotek_hq_container_namespace_enable_if = ::std;

namespace _kotek_hq_container_namespace_is_same_v = ::std;

namespace _kotek_hq_container_namespace_forward = ::std;

template <typename Type>
using hybrid_queue_underlying_container =
	_kotek_hq_container_namespace_pmr::deque<Type>;

/// @brief \~english std (and boost) provide no pmr queue because queue is a
/// container adaptor, not a container — the hybrid queue is therefore the
/// standard adaptor over the pmr deque fed by the bounded buffer
/// @tparam Type
template <typename Type>
using hybrid_queue_container =
	::std::queue<Type, hybrid_queue_underlying_container<Type>>;

#else
#endif

// Returns buffer size for the underlying std::pmr::deque of the queue
// adaptor (same block-based bookkeeping as hybrid_deque: element payload
// plus the block map).
template <typename Type>
constexpr kun_ktk size_t _kotek_hq_buffer_size(
	kun_ktk size_t element_count) noexcept
{
	if (element_count == 0)
		return 0;

#ifdef _MSC_VER
	// MSVC: blocks hold max(1, 16/sizeof(Type)) elements (16-byte minimum
	// block granularity), plus a pointer map with a 64-byte initial extent
	// and one pointer per block
	constexpr kun_ktk size_t elements_per_block =
		(16 / sizeof(Type)) > 1 ? (16 / sizeof(Type)) : 1;
	const kun_ktk size_t blocks =
		(element_count + elements_per_block - 1) / elements_per_block;
	return blocks * elements_per_block * sizeof(Type) +
		blocks * sizeof(void*) + 64;
#else
	// GCC/Clang: 512-byte blocks (512/sizeof(Type) elements per block), plus
	// a pointer map with a 64-byte initial extent and one pointer per block
	constexpr kun_ktk size_t block_size =
		sizeof(Type) < 512 ? 512 : sizeof(Type);
	const kun_ktk size_t blocks =
		(element_count * sizeof(Type) + block_size - 1) / block_size;
	return blocks * block_size + blocks * sizeof(void*) + 64;
#endif
}

template <typename Type, kun_ktk size_t ElementCount, bool Realloc,
	kun_ktk size_t _kotek_hq_Size
#ifdef KOTEK_DEBUG
	= _kotek_hq_buffer_size<Type>(ElementCount) * 2
#else
	= _kotek_hq_buffer_size<Type>(ElementCount)
#endif
	>
class hybrid_queue_impl
{
	static_assert(ElementCount == 0 ? Realloc : true,
		"you must set Realloc=true if you passed ElementCount==0");

public:
	using container_type = typename hybrid_queue_container<Type>;
	using underlying_container_type =
		typename hybrid_queue_underlying_container<Type>;

	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	// the standard adaptors (queue/stack) expose no allocator_type of their
	// own, so it is taken from the underlying container
	using allocator_type = typename underlying_container_type::allocator_type;

public:
	hybrid_queue_impl() : mem() {}

	explicit hybrid_queue_impl(const underlying_container_type& cont) :
		mem(cont)
	{
	}

	explicit hybrid_queue_impl(underlying_container_type&& cont) : mem(cont)
	{
	}

	template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
		typename = _kotek_hq_container_namespace_enable_if::enable_if_t<
			(ElementCount >= ElementCount2 || Realloc == true) &&
			_kotek_hq_container_namespace_is_same_v::is_same_v<Type, Type2>>>
	hybrid_queue_impl(
		const hybrid_queue_impl<Type2, ElementCount2, Realloc2>& other) :
		mem(other)
	{
	}

	hybrid_queue_impl(const hybrid_queue_impl& other) : mem(other) {}

	template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
		typename = _kotek_hq_container_namespace_enable_if::enable_if_t<
			(ElementCount >= ElementCount2 || Realloc == true) &&
			_kotek_hq_container_namespace_is_same_v::is_same_v<Type, Type2>>>
	hybrid_queue_impl(
		hybrid_queue_impl<Type2, ElementCount2, Realloc2>&& other) : mem(other)
	{
	}

	hybrid_queue_impl(hybrid_queue_impl&& other) noexcept : mem(other) {}

	~hybrid_queue_impl() {}

public:
	reference front() { return mem.con.front(); }
	const_reference front() const { return mem.con.front(); }
	reference back() { return mem.con.back(); }
	const_reference back() const { return mem.con.back(); }

	bool empty() const noexcept { return mem.con.empty(); }
	size_type size() const noexcept { return mem.con.size(); }

	void push(const Type& value) { mem.con.push(value); }
	void push(Type&& value)
	{
		mem.con.push(_kotek_hq_container_namespace::move(value));
	}

	template <class... Args>
	decltype(auto) emplace(Args&&... args)
	{
		return mem.con.emplace(
			_kotek_hq_container_namespace_forward::forward<Args>(args)...);
	}

	void pop() { mem.con.pop(); }

	void swap(hybrid_queue_impl& other) noexcept
	{
		// std doesn't support swapping polymorphic allocators (C++20);
		// no exceptions in this codebase — fail loudly instead
		KOTEK_ASSERT(false,
			"hybrid_queue_impl::swap is not supported with polymorphic "
			"allocators (C++20)");
		//	_kotek_hq_container_namespace_swap::swap(mem.con, other.mem.con);
	}

	hybrid_queue_impl& operator=(const hybrid_queue_impl& other)
	{
		mem.con.operator=(other.container());
		return *this;
	}

	hybrid_queue_impl& operator=(hybrid_queue_impl&& other)
	{
		mem.con.operator=(
			_kotek_hq_container_namespace::move(other.container_move()));
		return *this;
	}

public:
	const container_type& container(void) const noexcept { return mem.con; }
	container_type& container(void) noexcept { return mem.con; }
	container_type&& container_move(void) noexcept
	{
		return _kotek_hq_container_namespace::move(mem.con);
	}

	constexpr kun_ktk size_t size_preallocated(void) const noexcept
	{
		return ElementCount;
	}

	constexpr kun_ktk size_t size_preallocated_memory(
		void) const KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		return _kotek_hq_Size;
	}

	constexpr bool is_static(void) const noexcept { return !Realloc; }

private:
	struct layout_prealloc_t
	{
		layout_prealloc_t() :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{&pool}
		{
		}

		explicit layout_prealloc_t(const underlying_container_type& cont) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{cont, &pool}
		{
		}

		explicit layout_prealloc_t(underlying_container_type&& cont) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{_kotek_hq_container_namespace::move(cont), &pool}
		{
		}

		template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
			typename = _kotek_hq_container_namespace_enable_if::enable_if_t<
				(ElementCount >= ElementCount2 || Realloc == true) &&
				_kotek_hq_container_namespace_is_same_v::is_same_v<Type,
					Type2>>>
		layout_prealloc_t(
			const hybrid_queue_impl<Type2, ElementCount2, Realloc2>& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{other.container(), &pool}
		{
		}

		layout_prealloc_t(const hybrid_queue_impl<Type, ElementCount, Realloc,
			_kotek_hq_Size>& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{other.container(), &pool}
		{
		}

		template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
			typename = _kotek_hq_container_namespace_enable_if::enable_if_t<
				(ElementCount >= ElementCount2 || Realloc == true) &&
				_kotek_hq_container_namespace_is_same_v::is_same_v<Type,
					Type2>>>
		layout_prealloc_t(
			hybrid_queue_impl<Type2, ElementCount2, Realloc2>&& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{_kotek_hq_container_namespace::move(other.container_move()),
				&pool}
		{
		}

		layout_prealloc_t(
			hybrid_queue_impl<Type, ElementCount, Realloc, _kotek_hq_Size>&&
				other) noexcept :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hq_Size,
				Realloc
					? _kotek_hq_container_namespace_pmr::get_default_resource()
					: _kotek_hq_container_namespace_pmr::
						  null_memory_resource()},
			con{_kotek_hq_container_namespace::move(other.container_move()),
				&pool}
		{
		}

		unsigned char buf[_kotek_hq_Size == 0 ? 1 : _kotek_hq_Size];
		_kotek_hq_container_namespace_pmr::monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		layout_no_prealloc_t() : con{} {}

		explicit layout_no_prealloc_t(const underlying_container_type& cont) :
			con{cont}
		{
		}

		explicit layout_no_prealloc_t(underlying_container_type&& cont) :
			con{_kotek_hq_container_namespace::move(cont)}
		{
		}

		template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
			typename = _kotek_hq_container_namespace_enable_if::enable_if_t<
				(ElementCount >= ElementCount2 || Realloc == true) &&
				_kotek_hq_container_namespace_is_same_v::is_same_v<Type,
					Type2>>>
		layout_no_prealloc_t(
			const hybrid_queue_impl<Type2, ElementCount2, Realloc2>& other) :
			con{other.container()}
		{
		}

		layout_no_prealloc_t(const hybrid_queue_impl<Type, ElementCount,
			Realloc, _kotek_hq_Size>& other) : con{other.container()}
		{
		}

		template <typename Type2, kun_ktk size_t ElementCount2, bool Realloc2,
			typename = _kotek_hq_container_namespace_enable_if::enable_if_t<
				(ElementCount >= ElementCount2 || Realloc == true) &&
				_kotek_hq_container_namespace_is_same_v::is_same_v<Type,
					Type2>>>
		layout_no_prealloc_t(
			hybrid_queue_impl<Type2, ElementCount2, Realloc2>&& other) :
			con{_kotek_hq_container_namespace::move(other.container_move())}
		{
		}

		layout_no_prealloc_t(
			hybrid_queue_impl<Type, ElementCount, Realloc, _kotek_hq_Size>&&
				other) noexcept :
			con{_kotek_hq_container_namespace::move(other.container_move())}
		{
		}

		container_type con;
	};

	using layout_t = _kotek_hq_container_namespace_conditional::conditional_t<
		ElementCount == 0, layout_no_prealloc_t, layout_prealloc_t>;

	layout_t mem;
};

template <typename Type, kun_ktk size_t NotInUsed = 0>
using hybrid_std_queue = hybrid_queue_impl<Type, 0, true>;

template <typename Type, kun_ktk size_t ElementCount>
using hybrid_queue = hybrid_queue_impl<Type, ElementCount, true>;

template <typename Type, kun_ktk size_t ElementCount>
using static_hybrid_queue = hybrid_queue_impl<Type, ElementCount, false>;

KOTEK_END_NAMESPACE_KTK

template <typename Type, kun_ktk size_t NotInUsed = 0>
using hybrid_std_queue_t = kun_ktk hybrid_std_queue<Type, NotInUsed>;

template <typename Type, kun_ktk size_t ElementCount>
using hybrid_queue_t = kun_ktk hybrid_queue<Type, ElementCount>;

template <typename Type, kun_ktk size_t ElementCount>
using static_hybrid_queue_t = kun_ktk static_hybrid_queue<Type, ElementCount>;

KOTEK_END_NAMESPACE_KOTEK


// a hybrid container owns its bounded buffer and its memory resource, so an
// outer (pmr) container must not try to propagate its allocator into it:
// the wrapper has no allocator-extended constructors and the uses_allocator
// construction protocol is therefore disabled for it
namespace std
{
template <typename Type, size_t ElementCount, bool Realloc, size_t Size, typename Alloc>
struct uses_allocator<KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK
						  hybrid_queue_impl<Type, ElementCount, Realloc, Size>,
	Alloc> : false_type
{
};
} // namespace std
