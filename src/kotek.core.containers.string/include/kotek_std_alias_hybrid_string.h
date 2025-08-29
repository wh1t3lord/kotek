#pragma once

#include <kotek.core.types.string/include/kotek_core_types_string.h>
#include <kotek.core.casting.string/include/kotek_core_casting_string.h>
#include <kotek.core.casting.lexical/include/kotek_core_casting_lexical.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <string>
	#include <memory_resource>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <string>
	#include <memory_resource>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
namespace _kotek_hstr_container_namespace = ::std;
namespace _kotek_hstr_container_namespace_pmr = ::std::pmr;
namespace _kotek_hstr_container_namespace_swap = ::std;
namespace _kotek_hstr_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hstr_il_t = ::std::initializer_list<Type>;

template <typename CharType>
using hybrid_string_container =
	_kotek_hstr_container_namespace_pmr::basic_string<CharType>;

#elif defined(KOTEK_USE_STD_LIBRARY)
namespace _kotek_hstr_container_namespace = ::std;
namespace _kotek_hstr_container_namespace_pmr = ::std::pmr;
namespace _kotek_hstr_container_namespace_swap = ::std;
namespace _kotek_hstr_container_namespace_conditional = ::std;

template <class Type>
using _kotek_hstr_il_t = ::std::initializer_list<Type>;

template <typename CharType>
using hybrid_string_container =
	_kotek_hstr_container_namespace_pmr::basic_string<CharType>;
#else
#endif

template <typename T, std::size_t E, bool R, std::size_t B>
class hybrid_string;

// Type trait to detect hybrid_string
template <typename T>
struct _kotek_hstr_is_hybrid_string : std::false_type
{
};

template <typename Type, std::size_t EC, bool R, std::size_t BS>
struct _kotek_hstr_is_hybrid_string<hybrid_string<Type, EC, R, BS>>
	: std::true_type
{
};

template <typename T>
inline constexpr bool _kotek_hstr_is_hybrid_string_v =
	_kotek_hstr_is_hybrid_string<T>::value;

template <typename Type, std::size_t ElementCount, bool Realloc,
	std::size_t _kotek_hstr_Size
#ifdef _DEBUG
	= sizeof(Type) * ElementCount * 2
#else
	= sizeof(Type) * ElementCount
#endif

	>
class hybrid_string
{
	using container_type = std::pmr::basic_string<Type>;
	using container_view_type = std::basic_string_view<Type>;

	static_assert(ElementCount == 0 ? Realloc : true,
		"if you specified ElementCount as 0 it means that it doesn't use stack "
		"memory at all and it means that container is forced to support "
		"reallocation!");

public:
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

	template <class InputIt>
	hybrid_string(InputIt first, InputIt last) : mem{first, last}
	{
	}

	hybrid_string(const Type* s, size_type count) : mem{s, count} {}

	hybrid_string(const Type* s) : mem{s} {}

	template <class StringViewLike,
		typename = std::enable_if_t<
			!_kotek_hstr_is_hybrid_string_v<std::decay_t<StringViewLike>> &&
			std::is_convertible_v<const StringViewLike&, container_view_type>>>
	hybrid_string(const StringViewLike& t) : mem{t}
	{
	}

	template <class StringViewLike,
		typename = std::enable_if_t<
			!is_hybrid_string_v<std::decay_t<StringViewLike>> &&
			std::is_convertible_v<const StringViewLike&, container_view_type>>>
	hybrid_string(const StringViewLike& t, size_type pos, size_type count) :
		mem{t, pos, count}
	{
	}

	// hybrid_string(const hybrid_string& other);
	// hybrid_string(hybrid_string&& other) noexcept;

	template <typename TypeOther, std::size_t Size, bool Realloc,
		typename = std::enable_if_t<(ElementCount >= Size || Realloc == true) &&
			std::is_same_v<Type, TypeOther>>>
	hybrid_string(hybrid_string<TypeOther, Size, Realloc>&& other) noexcept :
		mem{other}
	{
	}

	hybrid_string(hybrid_string&& other) noexcept : mem{other} {}

	//	hybrid_string(const hybrid_string& other, const allocator_type& alloc);

	// Deleted constructor for invalid sizes

	template <typename TypeOther, std::size_t Size, bool Realloc,
		typename = std::enable_if_t<(ElementCount >= Size || Realloc == true) &&
			std::is_same_v<Type, TypeOther>>>
	hybrid_string(const hybrid_string<TypeOther, Size, Realloc>& other) :
		mem{other}
	{
	}

	hybrid_string(const hybrid_string& other) : mem{other} {}

	//	hybrid_string(hybrid_string&& other, const allocator_type& alloc);

	//	hybrid_string(const hybrid_string& other, size_type pos,
	//	const allocator_type& alloc = allocator_type());

	//	hybrid_string(const hybrid_string& other,
	//		size_type pos, size_type count,
	//		const allocator_type& alloc = allocator_type());

	hybrid_string(std::initializer_list<Type> ilist) : mem{ilist} {}

	hybrid_string() : mem{} {}

	~hybrid_string() {}

	inline const_iterator begin() const { return mem.con.begin(); }
	inline const_iterator end() const { return mem.con.end(); }

	inline const_iterator cbegin() const { return mem.con.cbegin(); }
	inline const_iterator cend() const { return mem.con.cend(); }

	inline reverse_iterator rbegin() { return mem.con.rbegin(); }
	inline reverse_iterator rend() { return mem.con.rend(); }

	inline const_reverse_iterator rbegin() const { return mem.con.rbegin(); }
	inline const_reverse_iterator rend() const { return mem.con.rend(); }

	inline const_reverse_iterator crbegin() const { return mem.con.crbegin(); }
	inline const_reverse_iterator crend() const { return mem.con.crend(); }

	inline const value_type* c_str(void) const { return mem.con.c_str(); }
	inline size_type max_size(void) const { return mem.con.max_size(); }
	inline bool empty(void) const { return mem.con.empty(); }
	inline reference at(size_type index) { return mem.con.at(index); }

	inline const_reference at(const size_type index) const
	{
		return mem.con.at(index);
	}

	hybrid_string substr(
		size_type pos = 0, size_type count = container_type::npos) const
	{
		return mem.con.substr(pos, count);
	}

	size_type copy(Type* dest, size_type count, size_type pos = 0) const
	{
		return mem.con.copy(dest, count, pos);
	}

	size_type find(const hybrid_string& istr, size_type pos = 0) const
	{
		return mem.con.find(istr.mem.con, pos);
	}

	size_type find(const container_type& istr, size_type pos = 0) const
	{
		return mem.con.find(istr, pos);
	}

	size_type find(const Type* s, size_type pos, size_type count) const
	{
		return mem.con.find(s, pos, count);
	}

	size_type find(const Type* s, size_type pos = 0) const
	{
		return mem.con.find(s, pos);
	}

	size_type find(Type ch, size_type pos = 0) const
	{
		return mem.con.find(ch, pos);
	}

	template <class StringViewLike>
	size_type find(const StringViewLike& t, size_type pos = 0) const noexcept
	{
		return mem.con.find<StringViewLike>(t, pos);
	}

	size_type rfind(
		const hybrid_string& istr, size_type pos = container_type::npos) const
	{
		return mem.con.rfind(istr.mem.con, pos);
	}

	size_type rfind(
		const container_type& str, size_type pos = container_type::npos) const
	{
		return mem.con.rfind(str, pos);
	}

	size_type rfind(const Type* s, size_type pos, size_type count) const
	{
		return mem.con.rfind(s, pos, count);
	}

	size_type rfind(const Type* s, size_type pos = container_type::npos) const
	{
		return mem.con.rfind(s, pos);
	}

	size_type rfind(Type ch, size_type pos = container_type::npos) const
	{
		return mem.con.rfind(ch, pos);
	}

	template <class StringViewLike>
	size_type rfind(const StringViewLike& t,
		size_type pos = container_type::npos) const noexcept
	{
		return mem.con.rfind<StringViewLike>(t, pos);
	}

	size_type find_first_of(const hybrid_string& istr, size_type pos = 0) const
	{
		return mem.con.find_first_of(istr.mem.con, pos);
	}

	size_type find_first_of(const container_type& str, size_type pos = 0) const
	{
		return mem.con.find_first_of(str, pos);
	}

	size_type find_first_of(const Type* s, size_type pos, size_type count) const
	{
		return mem.con.find_first_of(s, pos, count);
	}

	size_type find_first_of(const Type* s, size_type pos = 0) const
	{
		return mem.con.find_first_of(s, pos);
	}

	size_type find_first_of(Type ch, size_type pos = 0) const
	{
		return mem.con.find_first_of(ch, pos);
	}

	template <class StringViewLike>
	size_type find_first_of(
		const StringViewLike& t, size_type pos = 0) const noexcept
	{
		return mem.con.find_first_of<StringViewLike>(t, pos);
	}

	size_type find_first_not_of(
		const hybrid_string& istr, size_type pos = 0) const
	{
		return mem.con.find_first_not_of(istr.mem.con, pos);
	}

	size_type find_first_not_of(
		const container_type& str, size_type pos = 0) const
	{
		return mem.con.find_first_not_of(str, pos);
	}

	size_type find_first_not_of(
		const Type* s, size_type pos, size_type count) const
	{
		return mem.con.find_first_not_of(s, pos, count);
	}

	size_type find_first_not_of(const Type* s, size_type pos = 0) const
	{
		return mem.con.find_first_not_of(s, pos);
	}

	size_type find_first_not_of(Type ch, size_type pos = 0) const
	{
		return mem.con.find_first_not_of(ch, pos);
	}

	template <class StringViewLike>
	size_type find_first_not_of(
		const StringViewLike& t, size_type pos = 0) const noexcept
	{
		return mem.con.find_first_not_of<StringViewLike>(t, pos);
	}

	size_type find_last_of(
		const hybrid_string& istr, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_of(istr.mem.con, pos);
	}

	size_type find_last_of(
		const container_type& str, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_of(str, pos);
	}

	size_type find_last_of(const Type* s, size_type pos, size_type count) const
	{
		return mem.con.find_last_of(s, pos, count);
	}

	size_type find_last_of(
		const Type* s, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_of(s, pos);
	}

	size_type find_last_of(Type ch, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_of(ch, pos);
	}

	template <class StringViewLike>
	size_type find_last_of(const StringViewLike& t,
		size_type pos = container_type::npos) const noexcept
	{
		return mem.con.find_last_of<StringViewLike>(t, pos);
	}

	size_type find_last_not_of(
		const hybrid_string& istr, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_not_of(istr.mem.con, pos);
	}

	size_type find_last_not_of(
		const container_type& str, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_not_of(str, pos);
	}

	size_type find_last_not_of(
		const Type* s, size_type pos, size_type count) const
	{
		return mem.con.find_last_not_of(s, pos, count);
	}

	size_type find_last_not_of(
		const Type* s, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_not_of(s, pos);
	}

	size_type find_last_not_of(
		Type ch, size_type pos = container_type::npos) const
	{
		return mem.con.find_last_not_of(ch, pos);
	}

	template <class StringViewLike>
	size_type find_last_not_of(const StringViewLike& t,
		size_type pos = container_type::npos) const noexcept
	{
		return mem.con.find_last_not_of<StringViewLike>(t, pos);
	}

	// non-const
	inline iterator begin() { return mem.con.begin(); }
	inline iterator end() { return mem.con.end(); }

	inline void clear(void) { mem.con.clear(); }
	inline pointer data(void) { return mem.con.data(); }
	inline size_type size(void) const { return mem.con.size(); }

	size_type length() const { return mem.con.length(); }

	hybrid_string& append(size_type count, Type ch)
	{
		mem.con.append(count, ch);
		return *this;
	}

	hybrid_string& append(const Type* s, size_type count)
	{
		mem.con.append(s, count);
		return *this;
	}

	hybrid_string& append(const Type* s)
	{
		mem.con.append(s);
		return *this;
	}

	template <class SV>
	hybrid_string& append(const SV& t)
	{
		mem.con.append<SV>(t);
		return *this;
	}

	template <class SV>
	hybrid_string& append(
		const SV& t, size_type pos, size_type count = container_type::npos)
	{
		mem.con.append<SV>(t, pos, count);
		return *this;
	}

	hybrid_string& append(const hybrid_string& istr)
	{
		mem.con.append(istr.mem.con);
		return *this;
	}

	hybrid_string& append(const container_type& istr)
	{
		mem.con.append(istr);
		return *this;
	}

	hybrid_string& append(const hybrid_string& istr, size_type pos,
		size_type count = container_type::npos)
	{
		mem.con.append(istr.mem.con, pos, count);
		return *this;
	}

	hybrid_string& append(const container_type& istr, size_type pos,
		size_type count = container_type::npos)
	{
		mem.con.append(istr, pos, count);
		return *this;
	}

	template <class InputIt>
	hybrid_string& append(InputIt first, InputIt last)
	{
		mem.con.append<InputIt>(first, last);
		return *this;
	}

	hybrid_string& append(std::initializer_list<Type> ilist)
	{
		mem.con.append(ilist);
		return *this;
	}

	inline void swap(const hybrid_string& istr)
	{
		return mem.con.swap(istr.mem.con);
	}

	inline void swap(const container_type& istr) { return mem.con.swap(istr); }

	inline void push_back(Type c) { mem.con.push_back(c); }

	inline void pop_back() { mem.con.pop_back(); }

	hybrid_string& operator+=(const hybrid_string& istr)
	{
		mem.con.operator+=(istr.mem.con);
		return *this;
	}

	hybrid_string& operator+=(const container_type& istr)
	{
		mem.con.operator+=(istr);
		return *this;
	}

	hybrid_string& operator+=(Type ch)
	{
		mem.con.operator+=(ch);
		return *this;
	}

	hybrid_string& operator+=(const Type* s)
	{
		mem.con.operator+=(s);
		return *this;
	}

	hybrid_string& operator+=(std::initializer_list<Type> ilist)
	{
		mem.con.operator+=(ilist);
		return *this;
	}

	template <class StringViewLike>
	hybrid_string& operator+=(const StringViewLike& t)
	{
		mem.con.operator+=(t);
		return *this;
	}

	hybrid_string& operator=(const hybrid_string& istr)
	{
		mem.con.operator=(istr.mem.con);
		return *this;
	}

	hybrid_string& operator=(const container_type& istr)
	{
		mem.con.operator=(istr);
		return *this;
	}

	hybrid_string& operator=(hybrid_string&& istr) noexcept
	{
		mem.con.operator=(std::move(istr.mem.con));
		return *this;
	}
	hybrid_string& operator=(container_type&& istr) noexcept
	{
		mem.con.operator=(std::move(istr));
		return *this;
	}

	template <size_type Size>
	hybrid_string& operator=(const Type (&test)[Size])
	{
		this->operator=(static_cast<const Type*>(test));
		return *this;
	}

	hybrid_string& operator=(const Type* s)
	{
		mem.con.operator=(s);
		return *this;
	}

	hybrid_string& operator=(Type ch)
	{
		mem.con.operator=(ch);
		return *this;
	}

	hybrid_string& operator=(std::initializer_list<Type> ilist)
	{
		mem.con.operator=(ilist);
		return *this;
	}

	template <class StringViewLike>
	hybrid_string& operator=(const StringViewLike& t)
	{
		mem.con.operator= <StringViewLike>(t);
		return *this;
	}

	explicit operator container_view_type() const noexcept
	{
		return container_view_type(mem.con);
	}

	allocator_type get_allocator() const noexcept
	{
		return mem.con.get_allocator();
	}

	value_type& front() { return mem.con.front(); }
	const value_type& front() const { return mem.con.front(); }

	value_type& back() { return mem.con.back(); }
	const value_type& back() const { return mem.con.back(); }

	inline reference operator[](size_type pos) noexcept
	{
		return mem.con.operator[](pos);
	}
	inline const_reference operator[](size_type pos) const noexcept
	{
		return mem.con.operator[](pos);
	}

	container_type& container() noexcept { return mem.con; }
	container_type&& container_move_out() noexcept { return std::move(mem.con); }
	const container_type& container() const noexcept { return mem.con; }

	constexpr std::size_t preallocated_memory_size() const noexcept
	{
		return _kotek_hstr_Size;
	}
	constexpr std::size_t preallocated_size() const noexcept
	{
		return ElementCount;
	}
	constexpr bool is_reallocation_supported() const noexcept
	{
		return Realloc;
	}

private:
	struct layout_prealloc_t
	{
		template <class InputIt>
		layout_prealloc_t(InputIt first, InputIt last) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{first, last, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(const Type* s, size_type count) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{s, count, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(const Type* s) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{s, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class StringViewLike,
			typename = std::enable_if_t<
				!_kotek_hstr_is_hybrid_string_v<std::decay_t<StringViewLike>> &&
				std::is_convertible_v<const StringViewLike&,
					container_view_type>>>
		layout_prealloc_t(const StringViewLike& t) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{t, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <class StringViewLike,
			typename = std::enable_if_t<!+_kotek_hstr_is_hybrid_string_v<
											std::decay_t<StringViewLike>> &&
				std::is_convertible_v<const StringViewLike&,
					container_view_type>>>
		layout_prealloc_t(
			const StringViewLike& t, size_type pos, size_type count) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{t, pos, count, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <typename TypeOther, std::size_t Size, bool Realloc,
			typename =
				std::enable_if_t<(ElementCount >= Size || Realloc == true) &&
					std::is_same_v<Type, TypeOther>>>
		layout_prealloc_t(
			hybrid_string<TypeOther, Size, Realloc>&& other) noexcept :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{std::move(other.container_move_out()), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(hybrid_string&& other) noexcept :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{std::move(other.str), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		template <typename TypeOther, std::size_t Size, bool Realloc,
			typename =
				std::enable_if_t<(ElementCount >= Size || Realloc == true) &&
					std::is_same_v<Type, TypeOther>>>
		layout_prealloc_t(
			const hybrid_string<TypeOther, Size, Realloc>& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{other.container(), &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(const hybrid_string& other) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{other.str, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t(std::initializer_list<Type> ilist) :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{ilist, &pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		layout_prealloc_t() :
			pool{(ElementCount == 0) ? nullptr : buf,
				(ElementCount == 0) ? 0 : _kotek_hstr_Size,
				Realloc ? std::pmr::get_default_resource()
						: std::pmr::null_memory_resource()},
			con{&pool}
		{
			if constexpr (ElementCount > 0)
			{
				con.reserve(ElementCount);
			}
		}

		unsigned char buf[(ElementCount == 0) ? 1 : _kotek_hstr_Size];
		std::pmr::monotonic_buffer_resource pool;
		container_type con;
	};

	struct layout_no_prealloc_t
	{
		template <class InputIt>
		layout_no_prealloc_t(InputIt first, InputIt last) : con{first, last}
		{
		}

		layout_no_prealloc_t(const Type* s, size_type count) : con{s, count} {}

		layout_no_prealloc_t(const Type* s) : con{s} {}

		template <class StringViewLike,
			typename = std::enable_if_t<
				!_kotek_hstr_is_hybrid_string_v<std::decay_t<StringViewLike>> &&
				std::is_convertible_v<const StringViewLike&,
					container_view_type>>>
		layout_no_prealloc_t(const StringViewLike& t) : con{t}
		{
		}

		template <class StringViewLike,
			typename = std::enable_if_t<!+_kotek_hstr_is_hybrid_string_v<
											std::decay_t<StringViewLike>> &&
				std::is_convertible_v<const StringViewLike&,
					container_view_type>>>
		layout_no_prealloc_t(const StringViewLike& t, size_type pos,
			size_type count) : con{t, pos, count}
		{
		}

		template <typename TypeOther, std::size_t Size, bool Realloc,
			typename =
				std::enable_if_t<(ElementCount >= Size || Realloc == true) &&
					std::is_same_v<Type, TypeOther>>>
		layout_no_prealloc_t(
			hybrid_string<TypeOther, Size, Realloc>&& other) noexcept :
			con{std::move(other.container_move_out())}
		{
		}

		layout_no_prealloc_t(hybrid_string&& other) noexcept :
			con{std::move(other.str)}
		{
		}

		template <typename TypeOther, std::size_t Size, bool Realloc,
			typename =
				std::enable_if_t<(ElementCount >= Size || Realloc == true) &&
					std::is_same_v<Type, TypeOther>>>
		layout_no_prealloc_t(
			const hybrid_string<TypeOther, Size, Realloc>& other) :
			con{other.container()}
		{
		}

		layout_no_prealloc_t(const hybrid_string& other) : con{other.str} {}

		layout_no_prealloc_t(std::initializer_list<Type> ilist) : con{ilist} {}

		layout_no_prealloc_t() : con{} {}

		container_type con;
	};

	using layout_t = _kotek_hstr_container_namespace_conditional::conditional_t<
		ElementCount == 0, layout_no_prealloc_t, layout_prealloc_t>;

	layout_t mem;
};

KOTEK_END_NAMESPACE_KTK

KOTEK_END_NAMESPACE_KOTEK