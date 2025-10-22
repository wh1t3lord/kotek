#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <filesystem>
#else
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS
// todo: provide overriding through cmake this length
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 260
	#define KOTEK_DEF_OS_PATH_SEPARATOR '\\'
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
	#define KOTEK_DEF_OS_PATH_SEPARATOR '/'
#elif defined(KOTEK_USE_PLATFORM_MAC)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
	#define KOTEK_DEF_OS_PATH_SEPARATOR '/'
#else
	#error undefined platform
#endif

// TODO: add namespace filesystem for the following std design
// TODO: also add KOTEK_USE_NAMESPACE_FILESYSTEM after ktk in
// places where KOTEK_USE_NAMESPACE_KTK is used
KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

/// @brief returns OPPOSITE separator depends on OS. For
/// example, if your OS is windows and you pass a '\\' separator
/// it will return a '/' separator because
/// '\\' is preferred separator on WindowsNT platforms and thus
/// opposite separator for Windows will be '/'.
/// @param separator '/' and '\\' as accepted argument values
/// for function
/// @return depends on platform and passed separator. Function
/// CHECKS the value of separator and if it is not preferred
/// value that expected than function returns passed argument
char fs_give_opposite_to_preferred_separator(char separator);

KOTEK_BEGIN_NAMESPACE_FILESYSTEM

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS

template <std::size_t Size>
class static_path
{
public:
	using string_type = static_cstring<Size>;
	using value_type = tchar;

	static constexpr value_type preferred_separator =
		KOTEK_DEF_OS_PATH_SEPARATOR;
	static constexpr auto npos = static_cstring<Size>::npos;

public:
	/// @brief implementation of iterator (not the whole
	/// static_path class) based on this iterator
	/// implementation, maikyie (Microsoft) uses
	/// input_iterator... so let it be bidirectional
	/// https://github.com/gulrak/filesystem/blob/master/include/ghc/filesystem.hpp
	/// Author: Copyright (c) 2018, Steffen Schümann
	/// <s.schuemann@pobox.com> (MIT license)
	class path_iterator
	{
	public:
		using iterator_category =
			std::bidirectional_iterator_tag;
		using value_type = const static_path<Size>;
		using different_type = std::ptrdiff_t;
		using pointer = const static_path<Size>*;
		using reference = const static_path<Size>&;
		using base_iterator =
			static_path<Size>::string_type::const_iterator;

		path_iterator() = default;

		/*
		path_iterator(const path_iterator&) = default;
		path_iterator(path_iterator&&) = default;
		path_iterator& operator=(const path_iterator&) =
		default; path_iterator& operator=(path_iterator&&) =
		default;
		*/

		path_iterator(
			const static_path<Size>& path,
			const base_iterator& pos
		) :
			m_first{path.m_buffer.begin()},
			m_last{path.m_buffer.end()},
			m_prefix{
				m_first +
				static_cast<string_type::difference_type>(
					path.get_prefix_length()
				)
			},
			m_root{
				path.has_root_directory()
					? this->m_first +
						static_cast<
							string_type::difference_type>(
							path.get_prefix_length() +
							path.get_root_name_length()
						)
					: this->m_last
			},
			m_iter{pos}
		{
			if (pos != this->m_last)
			{
				this->update_current();
			}
		}

		path_iterator& operator++()
		{
			this->m_iter = this->increment(this->m_iter);
			while (this->m_iter != this->m_last &&
			       this->m_iter != this->m_root &&
			       (*this->m_iter == '\\' ||
			        *this->m_iter == '/') &&
			       (this->m_iter + 1) != this->m_last)
			{
				++this->m_iter;
			}

			this->update_current();

			return *this;
		}

		path_iterator operator++(int i)
		{
			path_iterator i{*this};
			++(*this);
			return i;
		}

		path_iterator& operator--()
		{
			this->m_iter = this->decrement(this->m_iter);
			this->update_current();
			return *this;
		}

		path_iterator operator--(int i)
		{
			auto i = *this;
			--(*this);
			return i;
		}

		bool operator==(const path_iterator& other) const
		{
			return this->m_iter == other.m_iter;
		}

		bool operator!=(const path_iterator& other) const
		{
			return this->m_iter != other.m_iter;
		}

		reference operator*() const { return this->m_current; }
		pointer operator->() const { return &this->m_current; }

	private:
		friend class static_path<Size>;

	private:
		base_iterator increment(const base_iterator& pos) const
		{
			base_iterator i = pos;

			bool fromStart =
				i == this->m_first || i == this->m_prefix;

			if (i != this->m_last)
			{
				if (fromStart && i == this->m_first &&
				    this->m_prefix > this->m_first)
				{
					i = this->m_prefix;
				}
				else if (auto extracted_symbol = *i++;
				         (extracted_symbol == '/' ||
				          extracted_symbol == '\\'))
				{
					if (i != this->m_last &&
					    (*i == '/' || *i == '\\'))
					{
						if (fromStart &&
						    !(i + 1 != this->m_last &&
						      (*(i + 1) == '/' ||
						       *(i + 1) == '\\')))
						{
							auto cur_forward = std::find(
								++i, this->m_last, '/'
							);
							auto cur_backward = std::find(
								i, this->m_last, '\\'
							);

							i = cur_forward;
							if (cur_forward > cur_backward)
								i = cur_backward;
						}
						else
						{
							while (i != this->m_last &&
							       (*i == '/' || *i == '\\'))
							{
								++i;
							}
						}
					}
				}
				else
				{
					if (fromStart && i != this->m_last &&
					    *i == ':')
					{
						++i;
					}
					else
					{
						auto cur_forward =
							std::find(i, this->m_last, '/');
						auto cur_backward =
							std::find(i, this->m_last, '\\');

						i = cur_forward;

						if (cur_forward > cur_backward)
							i = cur_backward;
					}
				}
			}

			return i;
		}

		base_iterator decrement(const base_iterator& pos) const
		{
			base_iterator i = pos;

			if (i != this->m_first)
			{
				--i;

				if (i != this->m_root &&
				    (pos != this->m_last ||
				     (*i != '/' || *i == '\\')))
				{
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
					static_cstring<3> seps = "\\:";

					i = std::find_first_of(
							std::reverse_iterator<
								base_iterator>(i),
							std::reverse_iterator<
								base_iterator>(this->m_first),
							seps.begin(),
							seps.end()
					)
							.base();
					if (i > this->m_first && *i == ':')
					{
						i++;
					}
		#else
					auto cur_forward =
						std::find(
							std::reverse_iterator<
								base_iterator>(i),
							std::reverse_iterator<
								base_iterator>(this->m_first),
							'/'
						)
							.base();
					auto cur_backward =
						std::find(
							std::reverse_iterator<
								base_iterator>(i),
							std::reverse_iterator<
								base_iterator>(this->m_first),
							'\\'
						)
							.base();

					i = cur_forward;

					if (cur_forward > cur_backward)
						i = cur_backward;
		#endif
					// Now we have to check if this is a network
					// name
					if (i - this->m_first == 2 &&
					    (*this->m_first == '/' ||
					     *this->m_first == '\\') &&
					    (*(this->m_first + 1) == '/' ||
					     *(this->m_first + 1) == '\\'))
					{
						i -= 2;
					}
				}
			}

			return i;
		}

		void update_current()
		{
			if ((this->m_iter == this->m_last) ||
			    (this->m_iter != this->m_first &&
			     this->m_iter != this->m_last &&
			     ((*this->m_iter == '/' || *this->m_iter == '\\'
			      ) &&
			      this->m_iter != this->m_root)) &&
			        (this->m_iter + 1 == this->m_last))
			{
				this->m_current.clear();
			}
			else
			{
				this->m_current.assign(
					this->m_iter, this->increment(this->m_iter)
				);
			}
		}

	private:
		base_iterator m_first;
		base_iterator m_last;
		base_iterator m_prefix;
		base_iterator m_root;
		base_iterator m_iter;
		static_path<Size> m_current;
	};

public:
	/* Member functions */
	static_path();
	static_path(const static_path<Size>& path);
	static_path(static_path<Size>&& path);
	static_path(const char* str);
	static_path(const wchar_t* str);
	static_path(const char8_t* str);
	static_path(const char16_t* str);
	static_path(const char32_t* str);
	static_path(const static_cstring_view& str);
	static_path(const static_wstring_view& str);
	static_path(const static_u8string_view& str);
	static_path(const static_u16string_view& str);
	static_path(const static_u32string_view& str);
	static_path(const cstring& str);
	static_path(char symbol);

	template <class InputIteratorType>
	static_path(
		InputIteratorType first, InputIteratorType last
	);

	~static_path();

	static_path<Size>& operator=(const static_path<Size>& path
	) = default;
	static_path<Size>& operator=(const string_type& source);
	static_path<Size>& operator=(const char* str);
	static_path<Size>& operator=(const char8_t* str);
	static_path<Size>& operator=(const wchar_t* str);
	static_path<Size>& operator=(char str);
	static_path<Size>& operator=(char8_t str);
	static_path<Size>& operator=(const static_cstring_view& view
	);
	static_path<Size>&
	operator=(const static_u8string_view& view);
	static_path<Size>& operator=(const std::string_view& view);

	static_path<Size>& assign(string_type&& source);
	static_path<Size>& assign(const static_path<Size>& path);
	static_path<Size>& assign(const static_cstring_view& path);
	static_path<Size>& assign(const static_wstring_view& path);
	static_path<Size>& assign(const static_u8string_view& path);
	static_path<Size>& assign(const static_u16string_view& path
	);
	static_path<Size>& assign(const static_u32string_view& path
	);
	static_path<Size>& assign(const char* str);
	static_path<Size>& assign(const char8_t* str);
	static_path<Size>& assign(char symbol);
	static_path<Size>& assign(char8_t symbol);

	template <class InputIterator>
	static_path<Size>&
	assign(InputIterator first, InputIterator last);

	/* todo:
	template< class InputIt >
path& assign( InputIt first, InputIt last );
	*/

	/* Concatenation */

	static_path<Size>& operator/=(const static_path<Size>& path
	);
	static_path<Size>&
	operator/=(const static_cstring_view& path);
	static_path<Size>&
	operator/=(const static_wstring_view& path);
	static_path<Size>&
	operator/=(const static_u8string_view& path);
	static_path<Size>&
	operator/=(const static_u16string_view& path);
	static_path<Size>&
	operator/=(const static_u32string_view& path);
	static_path<Size>& operator/=(const char* str);
	static_path<Size>& operator/=(const char8_t* str);
	static_path<Size>& operator/=(char str);
	static_path<Size>& operator/=(char8_t str);

	static_path<Size>& append(const static_path<Size>& path);
	static_path<Size>& append(const static_cstring_view& path);
	static_path<Size>& append(const static_wstring_view& path);
	static_path<Size>& append(const static_u8string_view& path);
	static_path<Size>& append(const static_u16string_view& path
	);
	static_path<Size>& append(const static_u32string_view& path
	);
	static_path<Size>& append(const char* str);
	static_path<Size>& append(const char8_t* str);
	static_path<Size>& append(char str);
	static_path<Size>& append(char8_t str);

	/* todo
	template< class InputIt >
path& append( InputIt first, InputIt last )
	*/

	static_path<Size>& operator+=(const static_path<Size>& path
	);
	static_path<Size>& operator+=(const static_cstring_view& str
	);
	static_path<Size>& operator+=(const static_wstring_view& str
	);
	static_path<Size>&
	operator+=(const static_u8string_view& str);
	static_path<Size>&
	operator+=(const static_u16string_view& str);
	static_path<Size>&
	operator+=(const static_u32string_view& str);
	static_path<Size>& operator+=(const char* str);
	static_path<Size>& operator+=(const char8_t* str);
	static_path<Size>& operator+=(char str);
	static_path<Size>& operator+=(char8_t str);

	static_path<Size>& concat(const static_path<Size>& path);
	static_path<Size>& concat(const static_cstring_view& str);
	static_path<Size>& concat(const static_u8string_view& str);
	static_path<Size>& concat(const char* str);
	static_path<Size>& concat(const char8_t* str);
	static_path<Size>& concat(char symbol);
	static_path<Size>& concat(char8_t symbol);

	inline friend static_path<Size> operator/(
		const static_path<Size>& left,
		const static_path<Size>& right
	)
	{
		auto tmp = left;
		tmp /= right;
		return tmp;
	}

	inline friend bool operator==(
		const static_path<Size>& left,
		const static_path<Size>& right
	) noexcept
	{
		return left.native() == right.native();
	}

	inline friend bool operator!=(
		const static_path<Size>& left,
		const static_path<Size>& right
	) noexcept
	{
		return !(left == right);
	}

	inline friend bool operator<(
		const static_path<Size>& left,
		const static_path<Size>& right
	) noexcept
	{
		return (left.compare(right) < 0);
	}

	inline friend bool operator<=(
		const static_path<Size>& left,
		const static_path<Size>& right
	) noexcept
	{
		return !(right < left);
	}

	inline friend bool operator>(
		const static_path<Size>& left,
		const static_path<Size>& right
	) noexcept
	{
		return (right < left);
	}

	inline friend bool operator>=(
		const static_path<Size>& left,
		const static_path<Size>& right
	) noexcept
	{
		return !(left < right);
	}

	template <class CharT, class Traits>
	inline friend std::basic_ostream<CharT, Traits>& operator<<(
		std::basic_ostream<CharT, Traits>& os,
		const static_path<Size>& path
	)
	{
		os << std::quoted<CharT, Traits>(path.m_buffer.c_str());
		return os;
	}

	template <class CharT, class Traits>
	inline friend std::basic_istream<CharT, Traits>& operator>>(
		std::basic_istream<CharT, Traits>& is,
		static_path<Size>& path
	)
	{
		std::basic_string<CharT, Traits> t;
		is >> std::quoted(t);

		path.m_buffer = t.c_str();

		return is;
	}

	/* todo
	template< class InputIt >
path& concat( InputIt first, InputIt last );
	*/

	/* Modifiers */

	/// @brief erases the contents
	void clear() noexcept;

	/// @brief converts directory separators to preferred
	/// directory separator
	/// @return *this
	static_path<Size>& make_preferred();

	/// @brief Removes a single generic-format filename
	/// component (as returned by filename) from the given
	/// generic-format path. After this function completes,
	/// has_filename returns false.
	/// @return *this
	static_path<Size>& remove_filename();

	/// @brief Replaces a single filename component with
	/// replacement.Equivalent to: remove_filename(); return
	/// operator/=(replacement);.
	/// @param replacement	-	path used for replacing the
	/// filename component
	/// @return *this
	static_path<Size>&
	replace_filename(const static_path<Size>& replacement);

	static_path<Size>& replace_extension(
		const static_path<Size>& replacement =
			static_path<Size>()
	);

	void swap(static_path<Size>& other) noexcept;

	/* Format observers */

	/// @brief Accesses the native path name as a character
	/// string.
	/// @return .c_str() that has size of
	/// KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
	const value_type* c_str() const noexcept;
	/// @brief Returns current static_string based on tchar type
	/// @return returns static_string that has size of
	/// KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
	const string_type& native() const noexcept;
	/// @brief casting implicit operation to static_string based
	/// on tchar type and has size of
	/// KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
	operator string_type() const;

	static_cstring<Size> string() const;
	static_u8string<Size> u8string() const;
	static_u16string<Size> u16string() const;
	static_u32string<Size> u32string() const;
	static_wstring<Size> wstring() const;

	static_cstring<Size> generic_string() const;
	static_u8string<Size> generic_u8string() const;
	static_u16string<Size> generic_u16string() const;
	static_u32string<Size> generic_u32string() const;
	static_wstring<Size> generic_wstring() const;

	/* Compare */

	int compare(const static_path<Size>& path) const noexcept;
	int compare(const static_cstring_view& str) const;
	int compare(const static_wstring_view& str) const;
	int compare(const static_u8string_view& str) const;
	int compare(const static_u16string_view& str) const;
	int compare(const static_u32string_view& str) const;
	int compare(const char* str) const;
	int compare(const char8_t* str) const;
	int compare(const char16_t* str) const;
	int compare(const char32_t* str) const;
	int compare(const wchar_t* str) const;

	/* Generation */

	static_path<Size> lexically_normal() const;
	static_path<Size>
	lexically_relative(const static_path<Size>& base) const;
	static_path<Size>
	lexically_proximate(const static_path<Size>& base) const;

	/* Decomposition */

	static_path<Size> root_name() const;
	static_path<Size> root_directory() const;
	static_path<Size> root_path() const;
	static_path<Size> relative_path() const;
	static_path<Size> parent_path() const;
	static_path<Size> filename() const;
	static_path<Size> stem() const;
	static_path<Size> extension() const;

	/* Queries */

	bool empty() const noexcept;

	bool has_root_path() const;
	bool has_root_name() const;
	bool has_root_directory() const;
	bool has_relative_path() const;
	bool has_parent_path() const;
	bool has_filename() const;

	/// @brief filename without the final extension
	/// @return filename without the final extension (if it has
	/// filename or its name is empty but extension is
	/// presented)
	bool has_stem() const;
	bool has_extension() const;

	bool is_absolute() const;
	bool is_relative() const;

	/* Iterators */

	inline path_iterator begin() const
	{
		return path_iterator(*this, this->m_buffer.begin());
	}

	inline path_iterator end() const
	{
		return path_iterator(*this, this->m_buffer.end());
	}

private:
	inline size_t get_prefix_length() const
	{
		size_t result{};

		#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_buffer.empty() == false)
		{
			if (this->m_buffer.size() >= 6)
			{
				if (this->m_buffer[2] == '?' &&
				    ((this->m_buffer[4] >= 65 &&
				      this->m_buffer[4] <= 90) ||
				     (this->m_buffer[4] >= 97 &&
				      this->m_buffer[4] <= 122)) &&
				    this->m_buffer[5] == ':')
				{
					// validating '\\?\' and '\??\' strings if
					// they don't present in buffer we can't say
					// anything about 'prefix'
					if (((this->m_buffer[0] == '\\' ||
					      this->m_buffer[0] == '/') &&
					     (this->m_buffer[1] == '\\' ||
					      this->m_buffer[1] == '/') &&
					     (this->m_buffer[2] == '?') &&
					     (this->m_buffer[3] == '\\' ||
					      this->m_buffer[3] == '/')) ||
					    ((this->m_buffer[0] == '/' ||
					      this->m_buffer[0] == '\\') &&
					     (this->m_buffer[1] == '?') &&
					     (this->m_buffer[2] == '?') &&
					     (this->m_buffer[3] == '/' ||
					      this->m_buffer[3] == '\\')))
					{
						result = 4;
					}
				}
			}
		}
		#else
		#endif

		return result;
	}

	inline size_t get_root_name_length() const
	{
		auto prefix_length = this->get_prefix_length();
		size_t result{};

		#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_buffer.length() >= prefix_length + 2 &&
		    ((this->m_buffer[prefix_length] >= 65 &&
		      this->m_buffer[prefix_length] <= 90) ||
		     (this->m_buffer[prefix_length] >= 97 &&
		      this->m_buffer[prefix_length] <= 122)) &&
		    this->m_buffer[prefix_length + 1] == ':')
		{
			result = 2;
		}
		#endif

		if (this->m_buffer.length() > prefix_length + 2 &&
		    (this->m_buffer[prefix_length] == '/' ||
		     this->m_buffer[prefix_length == '\\']) &&
		    (this->m_buffer[prefix_length + 1] == '/' ||
		     this->m_buffer[prefix_length + 1] == '\\') &&
		    (this->m_buffer[prefix_length + 2] != '/' ||
		     this->m_buffer[prefix_length + 2] != '\\'))
		{
			auto pos_forward =
				this->m_buffer.find('/', prefix_length + 3);
			auto pos_backward =
				this->m_buffer.find('\\', prefix_length + 3);

			if (pos_forward == npos && pos_backward == npos)
			{
				result = this->m_buffer.length();
			}
			else if (pos_forward != npos &&
			         pos_backward == npos)
			{
				result = pos_forward;
			}
			else if (pos_backward != npos &&
			         pos_forward == npos)
			{
				result = pos_backward;
			}
			else
			{
				result = pos_backward;
				if (pos_backward > pos_forward)
				{
					result = pos_forward;
				}
			}
		}

		return result;
	}

private:
	// todo: provide support of switching strings what user
	// wants
	static_cstring<Size> m_buffer;
};

class directory_iterator;

enum class eFileType
{
	kNone,
	kNotFound,
	kRegular,
	kDirectory,
	kSymLink,
	kBlock,
	kCharacter,
	kFifo,
	kSocket,
	kUnknown
};

enum class perms : uint16_t
{
	none = 0,

	owner_read = 0400,
	owner_write = 0200,
	owner_exec = 0100,
	owner_all = 0700,

	group_read = 040,
	group_write = 020,
	group_exec = 010,
	group_all = 070,

	others_read = 04,
	others_write = 02,
	others_exec = 01,
	others_all = 07,

	all = 0777,
	set_uid = 04000,
	set_gid = 02000,
	sticky_bit = 01000,

	mask = 07777,
	unknown = 0xffff
};

enum class directory_options : uint16_t
{
	none = 0,
	follow_directory_symlink = 1,
	skip_permission_denied = 2,
};

inline directory_options operator&(
	const directory_options& left,
	const directory_options& right
)
{
	return static_cast<directory_options>(
		static_cast<uint16_t>(left) &
		static_cast<uint16_t>(right)
	);
}

inline perms operator|(const perms& left, const perms& right)
{
	return static_cast<perms>(
		static_cast<uint16_t>(left) |
		static_cast<uint16_t>(right)
	);
}

inline perms operator&(const perms& left, const perms& right)
{
	return static_cast<perms>(
		static_cast<uint16_t>(left) &
		static_cast<uint16_t>(right)
	);
}

class file_status
{
public:
	file_status() noexcept;
	explicit file_status(
		eFileType ft, perms prms = perms::unknown
	) noexcept;
	file_status(const file_status&) noexcept;
	file_status(file_status&&) noexcept;
	~file_status();
	// assignments:
	file_status& operator=(const file_status&) noexcept;
	file_status& operator=(file_status&&) noexcept;
	// [fs.file_status.mods] modifiers
	void type(eFileType ft) noexcept;
	void permissions(perms prms) noexcept;
	// [fs.file_status.obs] observers
	eFileType type() const noexcept;
	perms permissions() const noexcept;
	friend bool operator==(
		const file_status& lhs, const file_status& rhs
	) noexcept
	{
		return lhs.type() == rhs.type() &&
			lhs.permissions() == rhs.permissions();
	}

private:
	eFileType _type;
	perms _perms;
};

inline file_status::file_status() noexcept :
	file_status(eFileType::kNone)
{
}

inline file_status::file_status(
	eFileType ft, perms prms
) noexcept : _type(ft), _perms(prms)
{
}

inline file_status::file_status(const file_status& other
) noexcept : _type(other._type), _perms(other._perms)
{
}

inline file_status::file_status(file_status&& other) noexcept :
	_type(other._type), _perms(other._perms)
{
}

inline file_status::~file_status() {}

// assignments:
inline file_status&
file_status::operator=(const file_status& rhs) noexcept
{
	_type = rhs._type;
	_perms = rhs._perms;
	return *this;
}

inline file_status& file_status::operator=(file_status&& rhs
) noexcept
{
	_type = rhs._type;
	_perms = rhs._perms;
	return *this;
}

// [fs.file_status.mods] modifiers
inline void file_status::type(eFileType ft) noexcept
{
	_type = ft;
}

inline void file_status::permissions(perms prms) noexcept
{
	_perms = prms;
}

// [fs.file_status.obs] observers
inline eFileType file_status::type() const noexcept
{
	return _type;
}

inline perms file_status::permissions() const noexcept
{
	return _perms;
}

		#ifdef KOTEK_USE_PLATFORM_WINDOWS
inline std::error_code make_system_error(uint32_t err = 0)
{
	return std::error_code(
		err ? static_cast<int>(err)
			: static_cast<int>(::GetLastError()),
		std::system_category()
	);
}

typedef struct _REPARSE_DATA_BUFFER
{
	ULONG ReparseTag{};
	USHORT ReparseDataLength{};
	USHORT Reserved{};

	inline bool is_initialized(void) const
	{
		return ReparseTag != ULONG(0) &&
			ReparseDataLength != USHORT(0) &&
			Reserved != USHORT(0);
	}

	inline operator bool() const { return is_initialized(); }

	union
	{
		struct
		{
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			ULONG Flags;
			WCHAR PathBuffer[1];
		} SymbolicLinkReparseBuffer;
		struct
		{
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			WCHAR PathBuffer[1];
		} MountPointReparseBuffer;
		struct
		{
			UCHAR DataBuffer[1];
		} GenericReparseBuffer;
	} DUMMYUNIONNAME;
} REPARSE_DATA_BUFFER;

inline REPARSE_DATA_BUFFER getReparseData(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
)
{
	HANDLE file(CreateFileA(
		p.c_str(),
		0,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		0,
		OPEN_EXISTING,
		FILE_FLAG_OPEN_REPARSE_POINT |
			FILE_FLAG_BACKUP_SEMANTICS,
		0
	));
	if (file == INVALID_HANDLE_VALUE)
	{
		ec = make_system_error();
		return REPARSE_DATA_BUFFER();
	}

	REPARSE_DATA_BUFFER reparseData;
	ULONG bufferUsed;
	if (DeviceIoControl(
			file,
			FSCTL_GET_REPARSE_POINT,
			0,
			0,
			&reparseData,
			MAXIMUM_REPARSE_DATA_BUFFER_SIZE,
			&bufferUsed,
			0
		))
	{
		return reparseData;
	}
	else
	{
		ec = make_system_error();
	}
	return REPARSE_DATA_BUFFER();
}

inline bool endsWith(
	const static_wstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
		what,
	const static_wstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& with
)
{
	return with.length() <= what.length() &&
		what.compare(
			what.length() - with.length(), with.size(), with
		) == 0;
}

inline bool startsWith(
	const static_wstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
		what,
	const static_wstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& with
)
{
	return with.length() <= what.length() &&
		what.compare(
			what.length() - with.length(), with.size(), with
		) == 0;
}

inline static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
getFullPathName(const char* p, std::error_code& ec)
{
	ULONG size = ::GetFullPathNameA(p, 0, 0, 0);
	if (size)
	{
		assert(
			size <= KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH &&
			"your path is too big for us!"
		);

		char buf[KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH];
		ULONG s2 = GetFullPathNameA(p, size, buf, nullptr);
		if (s2 && s2 < size)
		{
			return static_path<
				KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>(buf);
		}
	}
	ec = make_system_error();
	return static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>();
}

template <typename INFO>
inline bool is_symlink_from_INFO(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	const INFO* info,
	std::error_code& ec
)
{
	if ((info->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
	{
		auto reparseData = getReparseData(p, ec);
		if (!ec && reparseData.is_initialized() &&
		    IsReparseTagMicrosoft(reparseData.ReparseTag) &&
		    reparseData.ReparseTag == IO_REPARSE_TAG_SYMLINK)
		{
			return true;
		}
	}
	return false;
}

template <>
inline bool
is_symlink_from_INFO(const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&, const WIN32_FIND_DATAW* info, std::error_code&)
{
	// dwReserved0 is undefined unless dwFileAttributes includes
	// the FILE_ATTRIBUTE_REPARSE_POINT attribute according to
	// microsoft documentation. In practice, dwReserved0 is not
	// reset which causes it to report the incorrect symlink
	// status. Note that microsoft documentation does not say
	// whether there is a null value for dwReserved0, so we test
	// for symlink directly instead of returning the tag which
	// requires returning a null value for non-reparse-point
	// files.
	return (info->dwFileAttributes &
	        FILE_ATTRIBUTE_REPARSE_POINT) &&
		info->dwReserved0 == IO_REPARSE_TAG_SYMLINK;
}

inline time_t timeFromFILETIME(const FILETIME& ft)
{
	ULARGE_INTEGER ull;
	ull.LowPart = ft.dwLowDateTime;
	ull.HighPart = ft.dwHighDateTime;
	return static_cast<time_t>(
		ull.QuadPart / 10000000ULL - 11644473600ULL
	);
}

inline bool equals_simple_insensitive(
	const static_path<
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>::value_type* str1,
	const static_path<
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>::value_type* str2
)
{
	while (::tolower((unsigned char)*str1) ==
	       ::tolower((unsigned char)*str2++))
	{
		if (*str1++ == 0)
			return true;
	}
	return false;
}

inline bool has_executable_extension(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	if (p.has_relative_path())
	{
		auto iter = p.end();
		const auto& fn = *--iter;
		auto pos = fn.string().find_last_of('.');
		if (pos == std::string::npos || pos == 0 ||
		    fn.string().length() - pos != 3)
		{
			return false;
		}
		const static_path<
			KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>::value_type* ext =
			fn.c_str() + pos + 1;
		if (equals_simple_insensitive(ext, "exe") ||
		    equals_simple_insensitive(ext, "cmd") ||
		    equals_simple_insensitive(ext, "bat") ||
		    equals_simple_insensitive(ext, "com"))
		{
			return true;
		}
	}
	return false;
}

template <typename INFO>
inline file_status status_from_INFO(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	const INFO* info,
	std::error_code& ec,
	uintmax_t* sz = nullptr,
	time_t* lwt = nullptr
)
{
	auto ft = eFileType::kUnknown;
	if (is_symlink_from_INFO(p, info, ec))
	{
		ft = eFileType::kSymLink;
	}
	else if ((info->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
	         ))
	{
		ft = eFileType::kDirectory;
	}
	else
	{
		ft = eFileType::kRegular;
	}
	perms prms = perms::owner_read | perms::group_read |
		perms::others_read;
	if (!(info->dwFileAttributes & FILE_ATTRIBUTE_READONLY))
	{
		prms = prms | perms::owner_write | perms::group_write |
			perms::others_write;
	}
	if (has_executable_extension(p))
	{
		prms = prms | perms::owner_exec | perms::group_exec |
			perms::others_exec;
	}
	if (sz)
	{
		*sz = static_cast<uintmax_t>(info->nFileSizeHigh)
				<< (sizeof(info->nFileSizeHigh) * 8) |
			info->nFileSizeLow;
	}
	if (lwt)
	{
		*lwt = timeFromFILETIME(info->ftLastWriteTime);
	}
	return file_status(ft, prms);
}

		#endif // KOTEK_PLATFORM_WINDOWS

inline static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
resolveSymlink(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
)
{
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH> result;
	auto reparseData = getReparseData(p, ec);
	if (!ec)
	{
		if (reparseData &&
		    IsReparseTagMicrosoft(reparseData.ReparseTag))
		{
			switch (reparseData.ReparseTag)
			{
			case IO_REPARSE_TAG_SYMLINK:
			{
				static_wstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
					printName(
						&reparseData.SymbolicLinkReparseBuffer
							 .PathBuffer
								 [reparseData
				                      .SymbolicLinkReparseBuffer
				                      .PrintNameOffset /
				                  sizeof(WCHAR)],
						reparseData.SymbolicLinkReparseBuffer
								.PrintNameLength /
							sizeof(WCHAR)
					);

				static_wstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
					substituteName(
						&reparseData.SymbolicLinkReparseBuffer
							 .PathBuffer
								 [reparseData
				                      .SymbolicLinkReparseBuffer
				                      .SubstituteNameOffset /
				                  sizeof(WCHAR)],
						reparseData.SymbolicLinkReparseBuffer
								.SubstituteNameLength /
							sizeof(WCHAR)
					);
				/*
				auto printName = std::wstring(
				    &reparseData.SymbolicLinkReparseBuffer
				         .PathBuffer[reparseData.SymbolicLinkReparseBuffer
				                         .PrintNameOffset /
				             sizeof(WCHAR)],
				    reparseData.SymbolicLinkReparseBuffer.PrintNameLength
				/ sizeof(WCHAR)); auto substituteName =
				std::wstring(
				    &reparseData.SymbolicLinkReparseBuffer
				         .PathBuffer[reparseData.SymbolicLinkReparseBuffer
				                         .SubstituteNameOffset /
				             sizeof(WCHAR)],
				    reparseData.SymbolicLinkReparseBuffer
				            .SubstituteNameLength /
				        sizeof(WCHAR));
				*/

				if (endsWith(substituteName, printName) &&
				    startsWith(
						substituteName,
						static_wstring<
							KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>(
							L"\\??\\"
						)
					))
				{
					result = printName.c_str();
				}
				else
				{
					result = substituteName.c_str();
				}
				if (reparseData.SymbolicLinkReparseBuffer
				        .Flags &
				    0x1 /*SYMLINK_FLAG_RELATIVE*/)
				{
					result = p.parent_path() / result;
				}
				break;
			}
			case IO_REPARSE_TAG_MOUNT_POINT:
				result = getFullPathName(p.c_str(), ec);
				// result =
				// std::wstring(&reparseData->MountPointReparseBuffer.PathBuffer[reparseData->MountPointReparseBuffer.SubstituteNameOffset
				// / sizeof(WCHAR)],
				// reparseData->MountPointReparseBuffer.SubstituteNameLength
				// / sizeof(WCHAR));
				break;
			default:
				break;
			}
		}
	}
	return result;
		#else
	size_t bufferSize = 256;
	while (true)
	{
		std::vector<char> buffer(
			bufferSize, static_cast<char>(0)
		);
		auto rc =
			::readlink(p.c_str(), buffer.data(), buffer.size());
		if (rc < 0)
		{
			ec = detail::make_system_error();
			return path();
		}
		else if (rc < static_cast<int>(bufferSize))
		{
			return path(std::string(
				buffer.data(),
				static_cast<std::string::size_type>(rc)
			));
		}
		bufferSize *= 2;
	}
	return path();
		#endif
}

inline bool is_not_found_error(std::error_code& ec)
{
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	return ec.value() == ERROR_FILE_NOT_FOUND ||
		ec.value() == ERROR_PATH_NOT_FOUND ||
		ec.value() == ERROR_INVALID_NAME;
		#else
	return ec.value() == ENOENT || ec.value() == ENOTDIR;
		#endif
}

inline file_status status_ex(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec,
	file_status* sls = nullptr,
	uintmax_t* sz = nullptr,
	uintmax_t* nhl = nullptr,
	time_t* lwt = nullptr,
	int recurse_count = 0
) noexcept
{
	ec.clear();
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (recurse_count > 16)
	{
		ec =
			make_system_error(0x2A9 /*ERROR_STOPPED_ON_SYMLINK*/
		    );
		return file_status(eFileType::kUnknown);
	}
	WIN32_FILE_ATTRIBUTE_DATA attr;
	if (!::GetFileAttributesExA(
			p.c_str(), GetFileExInfoStandard, &attr
		))
	{
		ec = make_system_error();
	}
	else if (attr.dwFileAttributes &
	         FILE_ATTRIBUTE_REPARSE_POINT)
	{
		auto reparseData = getReparseData(p, ec);
		if (!ec && reparseData &&
		    IsReparseTagMicrosoft(reparseData.ReparseTag) &&
		    reparseData.ReparseTag == IO_REPARSE_TAG_SYMLINK)
		{
			auto target = resolveSymlink(p, ec);
			file_status result;
			if (!ec && !target.empty())
			{
				if (sls)
				{
					*sls = status_from_INFO(p, &attr, ec);
				}
				return status_ex(
					target,
					ec,
					nullptr,
					sz,
					nhl,
					lwt,
					recurse_count + 1
				);
			}
			return file_status(eFileType::kUnknown);
		}
	}
	if (ec)
	{
		if (is_not_found_error(ec))
		{
			return file_status(eFileType::kNotFound);
		}
		return file_status(eFileType::kNone);
	}
	if (nhl)
	{
		*nhl = 0;
	}
	return status_from_INFO(p, &attr, ec, sz, lwt);
		#else
			#error todo: implement
		#endif
}

inline file_status symlink_status_ex(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec,
	uintmax_t* sz = nullptr,
	uintmax_t* nhl = nullptr,
	time_t* lwt = nullptr
) noexcept
{
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	file_status fs;
	WIN32_FILE_ATTRIBUTE_DATA attr;
	if (!GetFileAttributesExA(
			p.c_str(), GetFileExInfoStandard, &attr
		))
	{
		ec = make_system_error();
	}
	else
	{
		ec.clear();
		fs = status_from_INFO(p, &attr, ec, sz, lwt);
		if (nhl)
		{
			*nhl = 0;
		}
	}
	if (is_not_found_error(ec))
	{
		return file_status(eFileType::kNotFound);
	}
	return ec ? file_status(eFileType::kNone) : fs;
		#else
			#error todo: implement
		#endif
}

inline file_status
status(const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p)
{
	std::error_code ec;
	auto result = status_ex(p, ec);
	if (result.type() == eFileType::kNone)
	{
		assert(false && "error!");
	}
	return result;
}

inline bool is_symlink(file_status s) noexcept
{
	return s.type() == eFileType::kSymLink;
}

inline uintmax_t file_size(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
) noexcept
{
	ec.clear();
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	WIN32_FILE_ATTRIBUTE_DATA attr;
	if (!GetFileAttributesExA(
			p.c_str(), GetFileExInfoStandard, &attr
		))
	{
		ec = make_system_error();
		return static_cast<uintmax_t>(-1);
	}
	return static_cast<uintmax_t>(attr.nFileSizeHigh)
		<< (sizeof(attr.nFileSizeHigh) * 8) |
		attr.nFileSizeLow;
		#else
			#error todo: implement
		#endif
}

inline uintmax_t
file_size(const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	std::error_code ec;
	auto result = file_size(p, ec);
	if (ec)
	{
		assert(false && "erro!");
	}
	return result;
}

inline uintmax_t hard_link_count(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
) noexcept
{
	ec.clear();
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	uintmax_t result = static_cast<uintmax_t>(-1);
	auto file(::CreateFileA(
		p.c_str(),
		0,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		0,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		0
	));
	BY_HANDLE_FILE_INFORMATION inf;
	if (file == INVALID_HANDLE_VALUE)
	{
		ec = make_system_error();
	}
	else
	{
		if (!::GetFileInformationByHandle(file, &inf))
		{
			ec = make_system_error();
		}
		else
		{
			result = inf.nNumberOfLinks;
		}
	}
	return result;
		#else
			#error todo: implement
		#endif
}

inline uintmax_t hard_link_count(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	std::error_code ec;
	auto result = hard_link_count(p, ec);
	if (ec)
	{
		assert(false && "error!");
	}
	return result;
}

inline std::chrono::time_point<std::chrono::system_clock>
last_write_time(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
) noexcept
{
	time_t result = 0;
	ec.clear();
	file_status fs =
		status_ex(p, ec, nullptr, nullptr, nullptr, &result);
	return ec ? (std::chrono::time_point<
					std::chrono::system_clock>::min)()
			  : std::chrono::system_clock::from_time_t(result);
}

inline std::chrono::time_point<std::chrono::system_clock>
last_write_time(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	std::error_code ec;
	auto result = last_write_time(p, ec);
	if (ec)
	{
		assert(false && "error!");
	}
	return result;
}

inline file_status symlink_status(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
) noexcept
{
	return symlink_status_ex(p, ec);
}

inline file_status symlink_status(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	std::error_code ec;
	auto result = symlink_status(p, ec);
	if (result.type() == eFileType::kNone)
	{
		assert(false && "error");
	}
	return result;
}

class directory_entry
{
public:
	directory_entry() noexcept {}
	directory_entry(const directory_entry& de) :
		_status{de._status},
		_symlink_status{de._symlink_status},
		_file_size{de._file_size},
		#ifndef KOTEK_USE_PLATFORM_WINDOWS
		_hard_link_count{de._hard_link_count},
		#endif
		_last_write_time{de._last_write_time}, _path{de._path}

	{
	}
	directory_entry(directory_entry&&) noexcept = default;
	explicit directory_entry(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
	);
	~directory_entry();

	directory_entry&
	operator=(const directory_entry&) = default;
	directory_entry&
	operator=(directory_entry&&) noexcept = default;

	void assign(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
	);
	void replace_filename(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
	);
	void refresh();

	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
	path() const noexcept;
	operator const static_path<
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&() const noexcept;

	bool exists() const;
	bool is_block_file() const;
	bool is_character_file() const;
	bool is_directory() const;
	bool is_fifo() const;
	bool is_other() const;
	bool is_regular_file() const;
	bool is_socket() const;
	bool is_symlink() const;
	uintmax_t file_size() const;
	std::chrono::time_point<std::chrono::system_clock>
	last_write_time() const;
	file_status status() const;
	file_status symlink_status() const;

	uintmax_t hard_link_count() const;

	bool operator<(const directory_entry& rhs) const noexcept;
	bool operator==(const directory_entry& rhs) const noexcept;
	bool operator!=(const directory_entry& rhs) const noexcept;
	bool operator<=(const directory_entry& rhs) const noexcept;
	bool operator>(const directory_entry& rhs) const noexcept;
	bool operator>=(const directory_entry& rhs) const noexcept;

private:
	friend class directory_iterator;

private:
	eFileType status_file_type() const;

private:
	file_status _status;
	file_status _symlink_status;
	uintmax_t _file_size = static_cast<uintmax_t>(-1);

		#ifndef KOTEK_USE_PLATFORM_WINDOWS
	uintmax_t _hard_link_count = static_cast<uintmax_t>(-1);
		#endif
	time_t _last_write_time = 0;
	static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH> _path;
};

inline directory_entry::directory_entry(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
) :
	_path(p), _file_size(static_cast<uintmax_t>(-1))
		#ifndef KOTEK_USE_PLATFORM_WINDOWS
	,
	_hard_link_count(static_cast<uintmax_t>(-1))
		#endif
	,
	_last_write_time(0)
{
	refresh();
}

inline directory_entry::~directory_entry() {}

inline void directory_entry::assign(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	_path = p;
	refresh();
}

inline void directory_entry::replace_filename(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
)
{
	_path.replace_filename(p);
	refresh();
}

inline void directory_entry::refresh()
{
	std::error_code ec;

		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	_status = status_ex(
		_path,
		ec,
		&_symlink_status,
		&_file_size,
		nullptr,
		&_last_write_time
	);
		#else
	_status = detail::status_ex(
		_path,
		ec,
		&_symlink_status,
		&_file_size,
		&_hard_link_count,
		&_last_write_time
	);
		#endif

	if (ec &&
	    (_status.type() == eFileType::kNone ||
	     _symlink_status.type() != eFileType::kSymLink))
	{
		assert(false && "check values under debugger please!");
	}
}

inline const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
directory_entry::path() const noexcept
{
	return _path;
}

inline directory_entry::operator const static_path<
	KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&() const noexcept
{
	return _path;
}

inline eFileType directory_entry::status_file_type() const
{
	return _status.type() != eFileType::kNone
		? _status.type()
		: KOTEK_USE_NAMESPACE_KTK KOTEK_USE_NAMESPACE_FILESYSTEM
			  status(path())
				  .type();
}

inline bool directory_entry::exists() const
{
	return status_file_type() != eFileType::kNotFound;
}

inline bool directory_entry::is_block_file() const
{
	return status_file_type() == eFileType::kBlock;
}

inline bool directory_entry::is_character_file() const
{
	return status_file_type() == eFileType::kCharacter;
}

inline bool directory_entry::is_directory() const
{
	return status_file_type() == eFileType::kDirectory;
}

inline bool directory_entry::is_fifo() const
{
	return status_file_type() == eFileType::kFifo;
}

inline bool directory_entry::is_other() const
{
	auto ft = status_file_type();
	return ft != eFileType::kNone &&
		ft != eFileType::kNotFound &&
		ft != eFileType::kRegular &&
		ft != eFileType::kDirectory && !is_symlink();
}

inline bool directory_entry::is_regular_file() const
{
	return status_file_type() == eFileType::kRegular;
}

inline bool directory_entry::is_socket() const
{
	return status_file_type() == eFileType::kSocket;
}

inline bool directory_entry::is_symlink() const
{
	return _symlink_status.type() != eFileType::kNone
		? _symlink_status.type() == eFileType::kSymLink
		: KOTEK_USE_NAMESPACE_KTK KOTEK_USE_NAMESPACE_FILESYSTEM
			  is_symlink(symlink_status());
}

inline uintmax_t directory_entry::file_size() const
{
	if (_file_size != static_cast<uintmax_t>(-1))
	{
		return _file_size;
	}
	return KOTEK_USE_NAMESPACE_KTK
		KOTEK_USE_NAMESPACE_FILESYSTEM file_size(path());
}

inline uintmax_t directory_entry::hard_link_count() const
{
		#ifndef KOTEK_USE_PLATFORM_WINDOWS
	if (_hard_link_count != static_cast<uintmax_t>(-1))
	{
		return _hard_link_count;
	}
		#endif

	return KOTEK_USE_NAMESPACE_KTK
		KOTEK_USE_NAMESPACE_FILESYSTEM hard_link_count(path());
}

inline std::chrono::time_point<std::chrono::system_clock>
directory_entry::last_write_time() const
{
	if (_last_write_time != 0)
	{
		return std::chrono::system_clock::from_time_t(
			_last_write_time
		);
	}
	return KOTEK_USE_NAMESPACE_KTK
		KOTEK_USE_NAMESPACE_FILESYSTEM last_write_time(path());
}

inline file_status directory_entry::status() const
{
	if (_status.type() != eFileType::kNone &&
	    _status.permissions() != perms::unknown)
	{
		return _status;
	}
	return KOTEK_USE_NAMESPACE_KTK
		KOTEK_USE_NAMESPACE_FILESYSTEM status(path());
}

inline file_status directory_entry::symlink_status() const
{
	if (_symlink_status.type() != eFileType::kNone &&
	    _symlink_status.permissions() != perms::unknown)
	{
		return _symlink_status;
	}
	return KOTEK_USE_NAMESPACE_KTK
		KOTEK_USE_NAMESPACE_FILESYSTEM symlink_status(path());
}

inline bool
directory_entry::operator<(const directory_entry& rhs
) const noexcept
{
	return _path < rhs._path;
}

inline bool
directory_entry::operator==(const directory_entry& rhs
) const noexcept
{
	return _path == rhs._path;
}

inline bool
directory_entry::operator!=(const directory_entry& rhs
) const noexcept
{
	return _path != rhs._path;
}

inline bool
directory_entry::operator<=(const directory_entry& rhs
) const noexcept
{
	return _path <= rhs._path;
}

inline bool
directory_entry::operator>(const directory_entry& rhs
) const noexcept
{
	return _path > rhs._path;
}

inline bool
directory_entry::operator>=(const directory_entry& rhs
) const noexcept
{
	return _path >= rhs._path;
}

class directory_iterator
{
public:
	class proxy
	{
	public:
		const directory_entry& operator*() const& noexcept
		{
			return _dir_entry;
		}

		directory_entry operator*() && noexcept
		{
			return std::move(_dir_entry);
		}

	private:
		explicit proxy(const directory_entry& dir_entry) :
			_dir_entry(dir_entry)
		{
		}
		friend class directory_iterator;
		directory_entry _dir_entry;
	};

public:
	using iterator_category = std::input_iterator_tag;
	using value_type = directory_entry;
	using difference_type = std::ptrdiff_t;
	using pointer = const directory_entry*;
	using reference = const directory_entry&;

public:
	directory_iterator() noexcept;
	explicit directory_iterator(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
	);
	directory_iterator(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
		directory_options options
	);
	directory_iterator(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
		std::error_code& ec
	) noexcept;
	directory_iterator(
		const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
		directory_options options,
		std::error_code& ec
	) noexcept;
	directory_iterator(const directory_iterator& rhs);
	directory_iterator(directory_iterator&& rhs) noexcept;
	~directory_iterator();
	directory_iterator& operator=(const directory_iterator& rhs
	);
	directory_iterator& operator=(directory_iterator&& rhs
	) noexcept;
	const directory_entry& operator*() const;
	const directory_entry* operator->() const;
	directory_iterator& operator++();
	directory_iterator& increment(std::error_code& ec) noexcept;
	proxy operator++(int)
	{
		proxy p{**this};
		++*this;
		return p;
	}

	bool operator==(const directory_iterator& rhs) const;
	bool operator!=(const directory_iterator& rhs) const;

private:
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	class impl
	{
	public:
		impl(
			const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
				p,
			directory_options options
		) :
			_base(p), _options(options),
			_dirHandle(INVALID_HANDLE_VALUE)
		{
			if (!_base.empty())
			{
				ZeroMemory(&_findData, sizeof(_findData));
				if ((_dirHandle = FindFirstFileA(
						 (_base / "*").c_str(), &_findData
					 )) != INVALID_HANDLE_VALUE)
				{
					if (strcmp(_findData.cFileName, ".") == 0 ||
					    strcmp(_findData.cFileName, "..") == 0)
					{
						increment(_ec);
					}
					else
					{
						_dir_entry._path =
							_base / (_findData.cFileName);
						copyToDirEntry(_ec);
					}
				}
				else
				{
					auto error = ::GetLastError();
					_base = static_path<
						KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>();
					if (error != ERROR_ACCESS_DENIED ||
					    (options &
					     directory_options::
					         skip_permission_denied) ==
					        directory_options::none)
					{
						_ec = make_system_error();
					}
				}
			}
		}
		impl(const impl& other) = delete;
		~impl()
		{
			if (_dirHandle != INVALID_HANDLE_VALUE)
			{
				FindClose(_dirHandle);
				_dirHandle = INVALID_HANDLE_VALUE;
			}
		}
		void increment(std::error_code& ec)
		{
			if (_dirHandle != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (FindNextFileA(_dirHandle, &_findData))
					{
						_dir_entry._path = _base;
						//	_dir_entry._path.append_name(_findData.cFileName);

						copyToDirEntry(ec);
					}
					else
					{
						auto err = ::GetLastError();
						if (err != ERROR_NO_MORE_FILES)
						{
							_ec = ec = make_system_error(err);
						}
						FindClose(_dirHandle);
						_dirHandle = INVALID_HANDLE_VALUE;
						_dir_entry._path.clear();
						break;
					}
				} while (
					strcmp(_findData.cFileName, ".") == 0 ||
					strcmp(_findData.cFileName, "..") == 0
				);
			}
			else
			{
				ec = _ec;
			}
		}
		void copyToDirEntry(std::error_code& ec)
		{
			if (_findData.dwFileAttributes &
			    FILE_ATTRIBUTE_REPARSE_POINT)
			{
				_dir_entry._status = status_ex(
					_dir_entry._path,
					ec,
					&_dir_entry._symlink_status,
					&_dir_entry._file_size,
					nullptr,
					&_dir_entry._last_write_time
				);
			}
			else
			{
				_dir_entry._status = status_from_INFO(
					_dir_entry._path,
					&_findData,
					ec,
					&_dir_entry._file_size,
					&_dir_entry._last_write_time
				);
				_dir_entry._symlink_status = _dir_entry._status;
			}
			if (ec)
			{
				if (_dir_entry._status.type() !=
				        eFileType::kNone &&
				    _dir_entry._symlink_status.type() !=
				        eFileType::kNone)
				{
					ec.clear();
				}
				else
				{
					_dir_entry._file_size =
						static_cast<uintmax_t>(-1);
					_dir_entry._last_write_time = 0;
				}
			}
		}

		static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH> _base;
		directory_options _options;
		WIN32_FIND_DATAA _findData;
		HANDLE _dirHandle;
		directory_entry _dir_entry;
		std::error_code _ec;
	};
		#else
			#error todo: implement
		#endif
	std::shared_ptr<impl> _impl;
};

inline directory_iterator::directory_iterator() noexcept :
	_impl(new impl(
		static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>(),
		directory_options::none
	))
{
}

inline directory_iterator::directory_iterator(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p
) : _impl(new impl(p, directory_options::none))
{
	if (_impl->_ec)
	{
		assert(
			false && "check value of error code _ec variable"
		);
	}

	_impl->_ec.clear();
}

inline directory_iterator::directory_iterator(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	directory_options options
) : _impl(new impl(p, options))
{
}

inline directory_iterator::directory_iterator(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	std::error_code& ec
) noexcept : _impl(new impl(p, directory_options::none))
{
	if (_impl->_ec)
	{
		ec = _impl->_ec;
	}
}

inline directory_iterator::directory_iterator(
	const static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& p,
	directory_options options,
	std::error_code& ec
) noexcept : _impl(new impl(p, options))
{
	if (_impl->_ec)
	{
		ec = _impl->_ec;
	}
}

inline directory_iterator::directory_iterator(
	const directory_iterator& rhs
) : _impl(rhs._impl)
{
}

inline directory_iterator::directory_iterator(
	directory_iterator&& rhs
) noexcept : _impl(std::move(rhs._impl))
{
}

inline directory_iterator::~directory_iterator() {}

inline directory_iterator&
directory_iterator::operator=(const directory_iterator& rhs)
{
	_impl = rhs._impl;
	return *this;
}

inline directory_iterator&
directory_iterator::operator=(directory_iterator&& rhs) noexcept
{
	_impl = std::move(rhs._impl);
	return *this;
}

inline const directory_entry&
directory_iterator::operator*() const
{
	return _impl->_dir_entry;
}

inline const directory_entry*
directory_iterator::operator->() const
{
	return &_impl->_dir_entry;
}

inline directory_iterator& directory_iterator::operator++()
{
	std::error_code ec;
	_impl->increment(ec);
	if (ec)
	{
		assert(
			false && "something is wrong, check error code!"
		);
	}
	return *this;
}

inline directory_iterator&
directory_iterator::increment(std::error_code& ec) noexcept
{
	_impl->increment(ec);
	return *this;
}

inline bool
directory_iterator::operator==(const directory_iterator& rhs
) const
{
	return _impl->_dir_entry._path ==
		rhs._impl->_dir_entry._path;
}

inline bool
directory_iterator::operator!=(const directory_iterator& rhs
) const
{
	return _impl->_dir_entry._path !=
		rhs._impl->_dir_entry._path;
}

inline directory_iterator begin(directory_iterator& iter
) noexcept
{
	return iter;
}

inline directory_iterator end(const directory_iterator& iter
) noexcept
{
	return directory_iterator();
}
	#endif
#else
	#error todo: implement
#endif // KOTEK_USE_NOT_CUSTOM_LIBRARY

using path = std::filesystem::path;

KOTEK_END_NAMESPACE_FILESYSTEM
KOTEK_END_NAMESPACE_KTK

using static_path_t = KUN_KOTEK KUN_KTK KUN_FILESYSTEM
	static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>;

KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_filesystem_path                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			KOTEK_USE_NAMESPACE_FILESYSTEM                \
				static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
	#define ktkFileSystemPath                             \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			KOTEK_USE_NAMESPACE_FILESYSTEM                \
				static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
	#define KTK_FILESYSTEM_PATH                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			KOTEK_USE_NAMESPACE_FILESYSTEM                \
				static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
#else
	#define ktk_array                                     \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			std::filesystem::path
	#define ktkFileSystemPath                             \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			std::filesystem::path
	#define KTK_FILESYSTEM_PATH                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			std::filesystem::path
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<
		kun_kotek kun_ktk kun_filesystem
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		ktk_filesystem_path>,
	"If library type was defined as EMB (aka static) it means "
	"that all "
	"containers that "
	"kotek framework provides to use ARE with static_ postfix "
	"it means that "
	"this path "
	"container is expected as static_path implementation"
);
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<
		kun_kotek kun_ktk kun_filesystem path,
		ktk_filesystem_path>,
	"If library type was defined as DYN (aka dynamic) it means "
	"that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ "
	"postfix and dynamic_ "
	"postfix it means that "
	"this path "
	"container is expected as path implementation"
);
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<
		kun_kotek kun_ktk kun_filesystem hybrid_path,
		ktk_filesystem_path>,
	"If library type was defined as HYB (aka hybrid) it means "
	"that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ postfix "
	"it means that "
	"this path "
	"container is expected as hybrid_path implementation"
);
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_FILESYSTEM

template <size_t Size>
inline static_path<Size>::static_path()
{
}

template <size_t Size>
inline static_path<Size>::~static_path()
{
}

template <size_t Size>
inline static_path<Size>::static_path(const char* str) :
	m_buffer{str}
{
}

template <size_t Size>
inline static_path<Size>::static_path(const wchar_t* str) :
	m_buffer{convert_wchar_to_char<Size>(str)}
{
}

template <size_t Size>
inline static_path<Size>::static_path(const char8_t* str) :
	m_buffer{
		static_u8string_view(str).begin(),
		static_u8string_view(str).end()
	}
{
}

template <size_t Size>
inline static_path<Size>::static_path(const char16_t* str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(const char32_t* str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(
	const static_cstring_view& str
) : m_buffer{str}
{
}

template <size_t Size>
inline static_path<Size>::static_path(
	const static_wstring_view& str
) : m_buffer{convert_wchar_to_char<Size>(str.data())}
{
}

template <size_t Size>
inline static_path<Size>::static_path(
	const static_u8string_view& str
)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(
	const static_u16string_view& str
)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(
	const static_u32string_view& str
)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(char symbol) :
	m_buffer{symbol}
{
}

template <size_t Size>
inline static_path<Size>::static_path(
	const static_path<Size>& path
) : m_buffer{path.m_buffer}
{
}

template <size_t Size>
inline static_path<Size>::static_path(static_path<Size>&& path
) : m_buffer{etl::move(path.m_buffer)}
{
}

template <size_t Size>
inline static_path<Size>::static_path(const cstring& str) :
	m_buffer{str.c_str()}
{
}

template <size_t Size>
template <class InputIteratorType>
inline static_path<Size>::static_path(
	InputIteratorType first, InputIteratorType last
) : m_buffer(first, last)
{
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const string_type& source)
{
	this->m_buffer = source;
	return *this;
}
template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const char* str)
{
	this->m_buffer = str;
	return *this;
}
template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const char8_t* str)
{
	return this->operator=(reinterpret_cast<const char*>(str));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const wchar_t* str)
{
	this->m_buffer = convert_wchar_to_char<Size>(str);
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator=(char str)
{
	return this->operator=(&str);
}
template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(char8_t str)
{
	return this->operator=(reinterpret_cast<const char*>(&str));
}
template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const static_cstring_view& view)
{
	return this->operator=(view.data());
}
template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const static_u8string_view& view)
{
	return this->operator=(
		reinterpret_cast<const char*>(view.data())
	);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator=(const std::string_view& view)
{
	return this->operator=(view.data());
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(string_type&& source)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const static_path<Size>& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const static_cstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const static_wstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const static_u8string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const static_u16string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const static_u32string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const char* str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(const char8_t* str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(char symbol)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::assign(char8_t symbol)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
template <class InputIterator>
inline static_path<Size>& static_path<Size>::assign(
	InputIterator first, InputIterator last
)
{
	this->m_buffer.assign(first, last);
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const static_path<Size>& path)
{
	return this->append(path);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const static_cstring_view& path)
{
	return this->append(path);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const static_wstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const static_u8string_view& path)
{
	return this->append(path);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const static_u16string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const static_u32string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const char* str)
{
	return this->operator/=(static_cstring_view(str));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(const char8_t* str)
{
	return this->operator/=(static_u8string_view(str));
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(char str
)
{
	return this->operator/=(&str);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator/=(char8_t str)
{
	return this->operator/=(&str);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const static_path<Size>& p)
{
	/* todo: delete obsolete
	if (path.is_absolute() ||
	    (path.has_root_name() && path.root_name() !=
	root_name()))
	{
	    this->m_buffer = path.m_buffer;
	}
	else if (path.has_root_directory())
	{
	    if (this->m_buffer.size() >= 2)
	    {
	        if (this->m_buffer[1] == ':')
	        {
	            this->m_buffer.replace(
	                2, this->m_buffer.size(),
	path.m_buffer.c_str());
	        }
	        else
	        {
	            this->m_buffer = path.m_buffer;
	        }
	    }
	    else
	    {
	        this->m_buffer = path.m_buffer;
	    }
	}
	else if (this->has_filename() ||
	    (!this->has_root_directory() && this->is_absolute()))
	{
	    this->m_buffer.append(1, preferred_separator);
	}

	this->m_buffer.append(path.m_buffer);
	*/

	 // Case 1: p is absolute OR has different root name
	if (p.is_absolute() ||
	    (p.has_root_name() && p.root_name() != root_name()))
	{
		m_buffer = p.m_buffer;
		return *this;
	}

	// Store current state before modifications
	bool current_has_root_name = has_root_name();
	bool current_has_root_dir = has_root_directory();
	auto current_root = root_name();

	// Case 2: p has root directory
	if (p.has_root_directory())
	{
		if (current_has_root_name)
		{
			if (current_has_root_dir)
			{
				// Remove everything after root directory
				// Find the end of root directory
				size_t root_dir_end =
					m_buffer.find_last_of(preferred_separator);
				if (root_dir_end != decltype(m_buffer)::npos)
				{
					m_buffer.resize(root_dir_end + 1);
				}
				else
				{
					// Should not happen if has_root_directory()
					// is true
					m_buffer = current_root.native();
					m_buffer += preferred_separator;
				}
			}
			else
			{
				// Current has root name but no root directory:
				// "C:" -> "C:/"
				m_buffer =
					current_root.native();
				m_buffer += preferred_separator;
			}
		}
		else
		{
			// No root name - clear everything
			m_buffer.clear();
		}
		m_buffer.append(p.m_buffer);
		return *this;
	}

	// Case 3 & 4: Normal append
	if (m_buffer.empty())
	{
		// Empty current path - just assign
		m_buffer = p.m_buffer;
	}
	else if (has_filename() ||
	         (!has_root_directory() && is_absolute()))
	{
		// Need separator
		if ((m_buffer.back() != '/' && m_buffer.back() != '\\') &&
		    !p.m_buffer.empty() && p.m_buffer.front() != '/' &&
		    p.m_buffer.front() != '\\')
		{
			// Special case: drive-relative paths ("C:" +
			// "Windows")
			if (!(current_has_root_name &&
			      !current_has_root_dir &&
			      m_buffer.size() ==
			          current_root.native().size()))
			{
				m_buffer += preferred_separator;
			}
		}
		m_buffer.append(p.m_buffer);
	}
	else
	{
		// No separator needed
		m_buffer.append(p.m_buffer);
	}

	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const static_cstring_view& p)
{
	static_path<Size> path(p);

	this->append(path);

	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const static_wstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const static_u8string_view& path)
{
	const static_cstring_view& casted = static_cstring_view(
		reinterpret_cast<const char*>(path.data())
	);

	static_path<Size> p(casted);

	this->append(p);

	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const static_u16string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const static_u32string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const char* str)
{
	if (str)
	{
		static_cstring_view view(str);
		this->append(view);
	}

	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::append(const char8_t* str)
{
	if (str)
	{
		static_u8string_view view(str);
		this->append(view);
	}

	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(char str)
{
	const char* p_str = &str;
	return this->append(p_str);
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(char8_t str)
{
	const char* p_str = reinterpret_cast<const char*>(&str);
	return this->append(p_str);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const static_path<Size>& path)
{
	return this->concat(path);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const static_cstring_view& str)
{
	return this->operator+=(static_path<Size>(str));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const static_wstring_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const static_u8string_view& str)
{
	return this->operator+=(
		reinterpret_cast<const char*>(str.data())
	);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const static_u16string_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const static_u32string_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const char* str)
{
	return this->operator+=(static_cstring_view(str));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(const char8_t* str)
{
	return this->operator+=(static_u8string_view(str));
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(char str
)
{
	return this->operator+=(&str);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::operator+=(char8_t str)
{
	return this->operator+=(&str);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::concat(const static_path<Size>& path)
{
	if (path.empty() == false)
	{
		this->m_buffer.append(path.m_buffer);
	}

	return *this;
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::concat(const static_cstring_view& str)
{
	return this->concat(static_path<Size>(str));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::concat(const static_u8string_view& str)
{
	return this->concat(reinterpret_cast<const char*>(str.data()
	));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::concat(const char* str)
{
	return this->concat(static_cstring_view(str));
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::concat(const char8_t* str)
{
	return this->concat(reinterpret_cast<const char*>(str));
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::concat(char symbol)
{
	return this->concat(&symbol);
}

template <size_t Size>
inline static_path<Size>&
static_path<Size>::concat(char8_t symbol)
{
	return this->concat(&symbol);
}

template <size_t Size>
inline void static_path<Size>::clear() noexcept
{
	this->m_buffer.clear();
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::make_preferred()
{
	if (this->m_buffer.empty() == false)
	{
		etl::replace(
			this->m_buffer.begin(),
			this->m_buffer.end(),
			fs_give_opposite_to_preferred_separator(
				preferred_separator
			),
			preferred_separator
		);
	}

	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::remove_filename()
{
	if (this->m_buffer.empty() == false)
	{
		auto index_forward = this->m_buffer.rfind('/');
		auto index_back = this->m_buffer.rfind('\\');

		if (index_forward != npos || index_back != npos)
		{
			if (this->m_buffer.size() > 1)
			{
				if (index_forward == npos)
				{
					this->m_buffer.erase(index_back + 1);
				}
				else if (index_back == npos)
				{
					this->m_buffer.erase(index_forward + 1);
				}
				else
				{
					// forward is the last symbol as separator
					if (index_forward > index_back)
					{
						this->m_buffer.erase(index_forward + 1);
					}
					// otherwise it is a backslash
					else
					{
						this->m_buffer.erase(index_back + 1);
					}
				}
			}
		}
		else
		{
			this->m_buffer.clear();
		}
	}

	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::replace_filename(
	const static_path<Size>& replacement
)
{
	this->remove_filename().append(replacement);
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::replace_extension(
	const static_path<Size>& replacement
)
{
	if (replacement.empty() == false)
	{
		const auto& str_native = replacement.native();
		bool has_dot_in_replacement = str_native[0] == '.';
		const auto* p_c_str = str_native.c_str();

		if (this->has_extension())
		{
			auto extension_dot = this->m_buffer.rfind('.');
			this->m_buffer.erase(
				extension_dot + 1,
				this->m_buffer.size() - extension_dot
			);

			if (has_dot_in_replacement)
			{
				this->m_buffer.append(p_c_str + 1);
			}
			else
			{
				this->m_buffer.append(str_native);
			}
		}
		else
		{
			if (this->has_filename())
			{
				if (has_dot_in_replacement)
				{
					this->m_buffer.append(str_native);
				}
				else
				{
					this->m_buffer.append(1, '.');
					this->m_buffer.append(str_native);
				}
			}
			else
			{
				if (this->m_buffer.back() == '/' ||
				    this->m_buffer.back() == '\\')
				{
					if (has_dot_in_replacement)
					{
						this->m_buffer.append(str_native);
					}
					else
					{
						this->m_buffer.append(1, '.');
						this->m_buffer.append(str_native);
					}
				}
				else
				{
					this->m_buffer.append(
						1, preferred_separator
					);

					if (has_dot_in_replacement)
					{
						this->m_buffer.append(str_native);
					}
					else
					{
						this->m_buffer.append(1, '.');
						this->m_buffer.append(str_native);
					}
				}
			}
		}
	}
	else
	{
		if (this->has_extension())
		{
			auto extension_dot = this->m_buffer.rfind('.');
			this->m_buffer.erase(
				extension_dot,
				this->m_buffer.size() - extension_dot
			);
		}
	}

	return *this;
}

template <size_t Size>
inline void static_path<Size>::swap(static_path<Size>& other
) noexcept
{
	auto copy = other.m_buffer;
	other.m_buffer = this->m_buffer;
	this->m_buffer = copy;
}

template <size_t Size>
inline const static_path<Size>::value_type*
static_path<Size>::c_str() const noexcept
{
	return this->m_buffer.c_str();
}

template <size_t Size>
inline const static_path<Size>::string_type&
static_path<Size>::native() const noexcept
{
	return this->m_buffer;
}

template <size_t Size>
inline static_path<Size>::operator string_type() const
{
	return this->m_buffer;
}

template <size_t Size>
inline static_cstring<Size> static_path<Size>::string() const
{
	return this->m_buffer;
}

template <size_t Size>
inline static_u8string<Size> static_path<Size>::u8string() const
{
	return static_u8string<Size>(
		this->m_buffer.begin(), this->m_buffer.end()
	);
}

template <size_t Size>
inline static_u16string<Size>
static_path<Size>::u16string() const
{
	assert(false && "todo");
	return static_u16string<Size>();
}

template <size_t Size>
inline static_u32string<Size>
static_path<Size>::u32string() const
{
	assert(false && "todo");
	return static_u32string<Size>();
}

template <size_t Size>
inline static_wstring<Size> static_path<Size>::wstring() const
{
	assert(false && "todo");
	return static_wstring<Size>();
}

template <size_t Size>
inline static_cstring<Size>
static_path<Size>::generic_string() const
{
	assert(false && "todo");
	return static_cstring<Size>();
}

template <size_t Size>
inline static_u8string<Size>
static_path<Size>::generic_u8string() const
{
	assert(false && "todo");
	return static_u8string<Size>();
}

template <size_t Size>
inline static_u16string<Size>
static_path<Size>::generic_u16string() const
{
	assert(false && "todo");
	return static_u16string<Size>();
}

template <size_t Size>
inline static_u32string<Size>
static_path<Size>::generic_u32string() const
{
	assert(false && "todo");
	return static_u32string<Size>();
}

template <size_t Size>
inline static_wstring<Size>
static_path<Size>::generic_wstring() const
{
	assert(false && "todo");
	return static_wstring<Size>();
}

template <size_t Size>
inline int
static_path<Size>::compare(const static_path<Size>& path
) const noexcept
{
	int result{this->m_buffer.compare(path.m_buffer)};
	if (this->has_root_directory())
	{
		if (path.has_root_directory() == false)
		{
			if (result < 0)
				result = -result;
		}
	}
	else
	{
		if (result > 0)
			result = -result;
	}

	return result;
}

template <size_t Size>
inline int
static_path<Size>::compare(const static_cstring_view& str) const
{
	return this->compare(static_path<Size>(str));
}

template <size_t Size>
inline int
static_path<Size>::compare(const static_wstring_view& str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int
static_path<Size>::compare(const static_u8string_view& str
) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int
static_path<Size>::compare(const static_u16string_view& str
) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int
static_path<Size>::compare(const static_u32string_view& str
) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const char* str) const
{
	return this->compare(static_path<Size>(str));
}

template <size_t Size>
inline int static_path<Size>::compare(const char8_t* str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const char16_t* str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const char32_t* str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const wchar_t* str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline static_path<Size>
static_path<Size>::lexically_normal() const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_relative(
	const static_path<Size>& base
) const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_proximate(
	const static_path<Size>& base
) const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::root_name() const
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() >= 2)
		{
			if ((this->m_buffer[0] >= 65 &&
			     this->m_buffer[0] <= 90) ||
			    (this->m_buffer[0] >= 97 &&
			     this->m_buffer[0] <= 122))
			{
				if (this->m_buffer[1] == ':')
				{
					return this->m_buffer.substr(0, 2).c_str();
				}
			}
		}
	}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif

	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size>
static_path<Size>::root_directory() const
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer[0] == '/' ||
		    this->m_buffer[0] == '\\')
		{
			return this->m_buffer[0];
		}
		else
		{
			if (this->m_buffer.size() >= 3)
			{
				if ((this->m_buffer[0] >= 65 &&
				     this->m_buffer[0] <= 90) ||
				    (this->m_buffer[0] >= 97 &&
				     this->m_buffer[0] <= 122))
				{
					if (this->m_buffer[1] == ':')
					{
						if (this->m_buffer[2] == '/' ||
						    this->m_buffer[2] == '\\')
						{
							return this->m_buffer[2];
						}
					}
				}
			}
		}
	}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif

	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::root_path() const
{
	return (this->root_name() / this->root_directory());
}

template <size_t Size>
inline static_path<Size>
static_path<Size>::relative_path() const
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() > 3)
		{
			if (this->m_buffer[0] == '/' ||
			    this->m_buffer[0] == '\\')
			{
				return this->m_buffer.substr(1).c_str();
			}
			else
			{
				if ((this->m_buffer[0] >= 65 &&
				     this->m_buffer[0] <= 90) ||
				    (this->m_buffer[0] >= 97 &&
				     this->m_buffer[0] <= 122))
				{
					if (this->m_buffer.size() > 1)
					{
						if (this->m_buffer[1] == ':')
						{
							if (this->m_buffer.size() > 2)
							{
								if (this->m_buffer[2] == '/' ||
								    this->m_buffer[2] == '\\')
								{
									return this->m_buffer
										.substr(3)
										.c_str();
								}
								else
								{
									return this->m_buffer
										.substr(2)
										.c_str();
								}
							}
							else
							{
								// nothing here
							}
						}
						else
						{
							return this->m_buffer.c_str();
						}
					}
					else
					{
						return this->m_buffer.c_str();
					}
				}
				else
				{
					return this->m_buffer.c_str();
				}
			}
		}
		else
		{
			if (this->m_buffer[0] == '/' ||
			    this->m_buffer[0] == '\\')
			{
				return this->m_buffer.substr(1).c_str();
			}
			else
			{
				if ((this->m_buffer[0] >= 65 &&
				     this->m_buffer[0] <= 90) ||
				    (this->m_buffer[0] >= 97 &&
				     this->m_buffer[0] <= 122))
				{
					if (this->m_buffer.size() > 1)
					{
						if (this->m_buffer[1] == ':')
						{
							if (this->m_buffer.size() > 2)
							{
								if (this->m_buffer[2] == '/' ||
								    this->m_buffer[2] == '\\')
								{
									// nothing
								}
								else
								{
									return this->m_buffer
										.substr(2)
										.c_str();
								}
							}
							else
							{
								// nothing here
							}
						}
						else
						{
							return this->m_buffer.c_str();
						}
					}
					else
					{
						return this->m_buffer.c_str();
					}
				}
				else
				{
					return this->m_buffer.c_str();
				}
			}
		}
	}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif

	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::parent_path() const
{
	if (this->has_relative_path() == false)
		return *this;
	else
	{
		auto index_forward = this->m_buffer.rfind('/');
		auto index_backward = this->m_buffer.rfind('\\');

		if (index_forward != npos && index_backward != npos)
		{
			if (index_forward > index_backward)
			{
				return this->m_buffer.substr(0, index_forward)
					.c_str();
			}
			else
			{
				return this->m_buffer.substr(0, index_backward)
					.c_str();
			}
		}
		else if (index_forward != npos)
		{
			return this->m_buffer.substr(0, index_forward)
				.c_str();
		}
		else if (index_backward != npos)
		{
			return this->m_buffer.substr(0, index_backward)
				.c_str();
		}
		else
		{
#ifdef KOTEK_USE_PLATFORM_WINDOWS

			if (this->m_buffer.size() > 1)
			{
				auto index_double_dots =
					this->m_buffer.rfind(':');

				if (index_double_dots != npos)
				{
					if (index_double_dots == 0)
					{
						return "";
					}
					else
					{
						return this->m_buffer.c_str();
					}
				}
				else
				{
					return "";
				}
			}
			else
			{
				if (this->m_buffer[0] == ':')
					return this->m_buffer.c_str();
				else
					return "";
			}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif
		}
	}

	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::filename() const
{
	if (this->m_buffer.empty() == false)
	{
		auto index_forward = this->m_buffer.rfind('/');
		auto index_backward = this->m_buffer.rfind('\\');
		auto index_last_symbol = this->m_buffer.size() - 1;

		if (index_forward != npos && index_backward != npos)
		{
			if (index_forward > index_backward)
			{
				if (index_forward != index_last_symbol)
				{
					return this->m_buffer
						.substr(index_forward + 1)
						.c_str();
				}
			}
			else
			{
				if (index_backward != index_last_symbol)
				{
					return this->m_buffer
						.substr(index_backward + 1)
						.c_str();
				}
			}
		}
		else if (index_backward != npos)
		{
			if (index_backward != index_last_symbol)
			{
				return this->m_buffer.substr(index_backward + 1)
					.c_str();
			}
		}
		else if (index_forward != npos)
		{
			if (index_forward != index_last_symbol)
			{
				return this->m_buffer.substr(index_forward + 1)
					.c_str();
			}
		}
		else
		{
			return this->m_buffer.c_str();
		}
	}

	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::stem() const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::extension() const
{
	if (this->m_buffer.empty() == false)
	{
		auto index_dot = this->m_buffer.rfind('.');

		if (index_dot != npos)
		{
			auto index_previous_to_dot = index_dot - 1;
			if (this->m_buffer[index_previous_to_dot] != '/' &&
			    this->m_buffer[index_previous_to_dot] != '\\')
			{
				if (this->m_buffer[index_previous_to_dot] !=
				    '.')
				{
					return this->m_buffer.substr(index_dot)
						.c_str();
				}
				else
				{
					auto valid_last_symbol_index =
						this->m_buffer.size() - 1;

					if (this->m_buffer.size() >= 3)
					{
						auto before_previous_index =
							index_previous_to_dot - 1;
						if (((this->m_buffer
						              [before_previous_index] !=
						          '/' &&
						      this->m_buffer
						              [before_previous_index] !=
						          '\\')))
						{
							return this->m_buffer
								.substr(index_dot)
								.c_str();
						}
						else
						{
							if (((this->m_buffer
							              [valid_last_symbol_index] !=
							          '/' &&
							      this->m_buffer
							              [valid_last_symbol_index] !=
							          '\\') &&
							     index_dot !=
							         valid_last_symbol_index))
							{
								return this->m_buffer
									.substr(index_dot)
									.c_str();
							}
						}
					}
				}
			}
		}
	}

	return static_path<Size>();
}

template <size_t Size>
inline bool static_path<Size>::empty() const noexcept
{
	return this->m_buffer.empty();
}

template <size_t Size>
inline bool static_path<Size>::has_root_path() const
{
	bool result{};

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() >= 1)
		{
			if ((this->m_buffer[0] >= 65 &&
			     this->m_buffer[0] <= 90) ||
			    (this->m_buffer[0] >= 97 &&
			     this->m_buffer[0] <= 122))
			{
				if (this->m_buffer.size() >= 2)
				{
					if (this->m_buffer[1] == ':')
					{
						result = true;
					}
				}
			}
			else
			{
				if (this->m_buffer[0] == '/' ||
				    this->m_buffer[0] == '\\')
				{
					result = true;
				}
			}
		}
	}

#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif

	return result;
}

template <size_t Size>
inline bool static_path<Size>::has_root_name() const
{
	bool result{};

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() >= 1)
		{
			if ((this->m_buffer[0] >= 65 &&
			     this->m_buffer[0] <= 90) ||
			    (this->m_buffer[0] >= 97 &&
			     this->m_buffer[0] <= 122))
			{
				if (this->m_buffer.size() >= 2)
				{
					if (this->m_buffer[1] == ':')
					{
						result = true;
					}
				}
			}
		}
	}

#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif

	return result;
}

template <size_t Size>
inline bool static_path<Size>::has_root_directory() const
{
	bool result{};

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() >= 3)
		{
			if (this->m_buffer[0] == ':')
			{
				// invalid disk and path so we think it is not
				// root directory because of invalid path
				// nothing applies to result variable
			}
			else
			{
				if (this->m_buffer[0] == '/' ||
				    this->m_buffer[0] == '\\')
				{
					result = true;
				}
				else
				{
					if ((this->m_buffer[0] >= 65 &&
					     this->m_buffer[0] <= 90) ||
					    (this->m_buffer[0] >= 97 &&
					     this->m_buffer[0] <= 122))
					{
						if (this->m_buffer[1] == ':')
						{
							if (this->m_buffer[2] == '/' ||
							    this->m_buffer[2] == '\\')
							{
								result = true;
							}
						}
					}
				}
			}
		}
		else
		{
			if (this->m_buffer[0] == '/' ||
			    this->m_buffer[0] == '\\')
			{
				result = true;
			}
		}
	}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#elif defined(KOTEK_USE_PLATFORM_MACOS)
	#error not implemented
#endif

	return result;
}

template <size_t Size>
inline bool static_path<Size>::has_relative_path() const
{
	return !relative_path().empty();
}

template <size_t Size>
inline bool static_path<Size>::has_parent_path() const
{
	return !parent_path().empty();
}

template <size_t Size>
inline bool static_path<Size>::has_filename() const
{
	bool result{};

	auto index_forward_slash = this->m_buffer.rfind('/');
	auto index_backward_slash = this->m_buffer.rfind('\\');

	if (index_forward_slash != npos &&
	    index_backward_slash != npos)
	{
		// '/' is the last symbol from end
		if (index_forward_slash > index_backward_slash)
		{
			if (index_forward_slash ==
			    this->m_buffer.size() - 1)
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
		// otherwise it is '\\' from end
		else
		{
			if (index_backward_slash ==
			    this->m_buffer.size() - 1)
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
	}
	else if (index_forward_slash != npos)
	{
		if (index_forward_slash == this->m_buffer.size() - 1)
		{
			result = false;
		}
		else
		{
			result = true;
		}
	}
	else if (index_backward_slash != npos)
	{
		if (index_backward_slash == this->m_buffer.size() - 1)
		{
			result = false;
		}
		else
		{
			result = true;
		}
	}

	return result;
}

template <size_t Size>
inline bool static_path<Size>::has_stem() const
{
	bool result{};

	if (this->m_buffer.empty() == false)
	{
		auto last_dot = this->m_buffer.rfind('.');
		auto index_forward = this->m_buffer.rfind('/');
		auto index_backward = this->m_buffer.rfind('\\');

		if (last_dot != npos)
		{
			result = true;
		}
		else
		{
			if (index_forward != npos && index_backward != npos)
			{
				if (index_forward > index_backward)
				{
					if (index_forward !=
					    this->m_buffer.size() - 1)
					{
						result = true;
					}
				}
				else
				{
					if (index_backward !=
					    this->m_buffer.size() - 1)
					{
						result = true;
					}
				}
			}
			else if (index_forward != npos)
			{
				if (index_forward != this->m_buffer.size() - 1)
				{
					result = true;
				}
			}
			else if (index_backward != npos)
			{
				if (index_backward != this->m_buffer.size() - 1)
				{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
					if (this->m_buffer
					        [this->m_buffer.size() - 1] != ':')
					{
						result = true;
					}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif
				}
			}
			else
			{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
				if (this->m_buffer.size() > 2)
				{
					if (this->m_buffer[0] == ':' ||
					    this->m_buffer
					            [this->m_buffer.size() - 1] !=
					        ':')
						result = true;
				}
				else
				{
					if (this->m_buffer.size() > 1)
					{
						if ((this->m_buffer[1] != ':' &&
						     this->m_buffer
						             [this->m_buffer.size() -
						              1] != ':') &&
						    this->m_buffer[0] != ':')
						{
							result = true;
						}
					}
					else
					{
						if (this->m_buffer[0] != ':')
						{
							result = true;
						}
					}
				}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif
			}
		}
	}

	return result;
}

template <size_t Size>
inline bool static_path<Size>::has_extension() const
{
	bool result{};

	auto index = this->m_buffer.rfind('.');

	if (index != static_cstring<Size>::npos && index > 0)
	{
		// imagine like cat/ab/..
		if (index == this->m_buffer.size() - 1)
		{
			auto previous_pos = index - 1;
			// we got ".." string
			if (this->m_buffer[previous_pos] == '.')
			{
				auto previous_pos2 = previous_pos - 1;

				if (this->m_buffer[previous_pos2] == '/' ||
				    this->m_buffer[previous_pos2] == '\\')
					result = false;
				else
					result = true;
			}
			else
			{
				if (this->m_buffer[previous_pos] == '/' ||
				    this->m_buffer[previous_pos] == '\\')
				{
					result = false;
				}
				else
				{
					result = true;
				}
			}
		}
		else
		{
			auto previous_pos = index - 1;

			if (this->m_buffer[previous_pos] == '.')
			{
				// we might have a name of file as '.' and it
				// has some extension...

				auto next_pos = index + 1;

				if (this->m_buffer[next_pos] != '/' ||
				    this->m_buffer[next_pos] != '\\')
					result = true;
				else
					result = false;
			}
			else
			{
				if (this->m_buffer[previous_pos] == '/' ||
				    this->m_buffer[previous_pos] == '\\')
				{
					result = false;
				}
				else
				{
					result = true;
				}
			}
		}
	}

	return result;
}

template <size_t Size>
inline bool static_path<Size>::is_absolute() const
{
	bool result{};

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() >= 3)
		{
			if ((this->m_buffer[0] >= 65 &&
			     this->m_buffer[0] <= 90) ||
			    (this->m_buffer[0] >= 97 &&
			     this->m_buffer[0] <= 122))
			{
				if (this->m_buffer[1] == ':')
				{
					if (this->m_buffer[2] == '/' ||
					    this->m_buffer[2] == '\\')
					{
						result = true;
					}
				}
			}
		}
	}

#elif defined(KOTEK_USE_PLATFORM_LINUX)
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#endif
	return result;
}

template <size_t Size>
inline bool static_path<Size>::is_relative() const
{
	return !(this->is_absolute());
}

KOTEK_END_NAMESPACE_FILESYSTEM
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#include <format>
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#include <fmt/core.h>
	#include <fmt/format.h>
	#include <fmt/xchar.h>
#else
	#error Unknown platform we cant know status about your format library
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS

	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
template <>
struct std::formatter<ktk_filesystem_path, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	inline auto
	format(ktk_filesystem_path const& str, auto& ctx) const
	{
		return std::format_to(
			ctx.out(),
			"{}",
			reinterpret_cast<const char*>(str.u8string().c_str()
		    )
		);
	}
};
	#endif

#elif defined(KOTEK_USE_PLATFORM_LINUX)
template <>
struct fmt::formatter<kun_kotek kun_ktk filesystem::path, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(
		kun_kotek kun_ktk filesystem::path const& str,
		FormatContext& ctx
	)
	{
		return fmt::format_to(
			ctx.out(),
			u8"{}",
			kun_kotek kun_ktk ustring(str.u8string().c_str())
		);
	}
};
#endif