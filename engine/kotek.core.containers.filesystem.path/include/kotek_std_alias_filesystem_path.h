#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_std_string.h>
#include <kotek.core.utility/include/kotek_core_utility.h>

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

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS

template <size_t Size>
class static_path
{
public:
	using string_type = static_cstring<Size>;
	using value_type = tchar;

	static constexpr value_type preferred_separator =
		KOTEK_DEF_OS_PATH_SEPARATOR;
	static constexpr auto npos = static_cstring<Size>::npos;

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

	~static_path();

	static_path<Size>& operator=(const static_path<Size>& path) = default;
	static_path<Size>& operator=(static_path<Size>&& path) noexcept = default;
	static_path<Size>& operator=(string_type&& source);

	static_path<Size>& assign(string_type&& source);
	static_path<Size>& assign(const static_path<Size>& path);
	static_path<Size>& assign(const static_cstring_view& path);
	static_path<Size>& assign(const static_wstring_view& path);
	static_path<Size>& assign(const static_u8string_view& path);
	static_path<Size>& assign(const static_u16string_view& path);
	static_path<Size>& assign(const static_u32string_view& path);

	/* todo:
	template< class InputIt >
path& assign( InputIt first, InputIt last );
	*/

	/* Concatenation */

	static_path<Size>& operator/=(const static_path<Size>& path);
	static_path<Size>& operator/=(const static_cstring_view& path);
	static_path<Size>& operator/=(const static_wstring_view& path);
	static_path<Size>& operator/=(const static_u8string_view& path);
	static_path<Size>& operator/=(const static_u16string_view& path);
	static_path<Size>& operator/=(const static_u32string_view& path);

	static_path<Size>& append(const static_path<Size>& path);
	static_path<Size>& append(const static_cstring_view& path);
	static_path<Size>& append(const static_wstring_view& path);
	static_path<Size>& append(const static_u8string_view& path);
	static_path<Size>& append(const static_u16string_view& path);
	static_path<Size>& append(const static_u32string_view& path);

	/* todo
	template< class InputIt >
path& append( InputIt first, InputIt last )
	*/

	static_path<Size>& operator+=(const static_path<Size>& path);
	static_path<Size>& operator+=(const static_cstring_view& str);
	static_path<Size>& operator+=(const static_wstring_view& str);
	static_path<Size>& operator+=(const static_u8string_view& str);
	static_path<Size>& operator+=(const static_u16string_view& str);
	static_path<Size>& operator+=(const static_u32string_view& str);

	/* todo
	template< class InputIt >
path& concat( InputIt first, InputIt last );
	*/

	/* Modifiers */

	/// @brief erases the contents
	void clear() noexcept;

	/// @brief converts directory separators to preferred directory separator
	/// @return *this
	static_path<Size>& make_preferred();

	/// @brief Removes a single generic-format filename component (as returned
	/// by filename) from the given generic-format path. After this function
	/// completes, has_filename returns false.
	/// @return *this
	static_path<Size>& remove_filename();

	/// @brief Replaces a single filename component with replacement.Equivalent
	/// to: remove_filename(); return operator/=(replacement);.
	/// @param replacement	-	path used for replacing the filename component
	/// @return *this
	static_path<Size>& replace_filename(const static_path<Size>& replacement);

	static_path<Size>& replace_extension(
		const static_path<Size>& replacement = static_path<Size>());

	void swap(static_path<Size>& other) noexcept;

	/* Format observers */

	/// @brief Accesses the native path name as a character string.
	/// @return .c_str() that has size of KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
	const value_type* c_str() const noexcept;
	/// @brief Returns current static_string based on tchar type
	/// @return returns static_string that has size of
	/// KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
	const string_type& native() const noexcept;
	/// @brief casting implicit operation to static_string based on tchar type
	/// and has size of KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
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
	static_path<Size> lexically_relative(const static_path<Size>& base) const;
	static_path<Size> lexically_proximate(const static_path<Size>& base) const;

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
	/// @return filename without the final extension (if it has filename or its
	/// name is empty but extension is presented)
	bool has_stem() const;
	bool has_extension() const;

	bool is_absolute() const;
	bool is_relative() const;

	/* Iterators */

private:
	// todo: provide support of switching strings what user wants
	static_cstring<Size> m_buffer;
};
	#endif
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_filesystem_path                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
	#define ktkFileSystemPath                             \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
	#define KTK_FILESYSTEM_PATH                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
#else
	#define ktk_array \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK filesystem::path
	#define ktkFileSystemPath \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK filesystem::path
	#define KTK_FILESYSTEM_PATH \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK filesystem::path
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <size_t Size>
inline static_path<Size>::static_path()
{
}

template <size_t Size>
inline static_path<Size>::~static_path()
{
}

template <size_t Size>
inline static_path<Size>::static_path(const char* str) : m_buffer{str}
{
}

template <size_t Size>
inline static_path<Size>::static_path(const wchar_t* str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(const char8_t* str)
{
	assert(false && "todo");
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
inline static_path<Size>::static_path(const static_cstring_view& str) :
	m_buffer{str}
{
}

template <size_t Size>
inline static_path<Size>::static_path(const static_wstring_view& str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(const static_u8string_view& str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(const static_u16string_view& str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(const static_u32string_view& str)
{
	assert(false && "todo");
}

template <size_t Size>
inline static_path<Size>::static_path(const static_path<Size>& path) :
	m_buffer{path.m_buffer}
{
}

template <size_t Size>
inline static_path<Size>::static_path(static_path<Size>&& path) :
	m_buffer{etl::move(path.m_buffer)}
{
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator=(string_type&& source)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(string_type&& source)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(
	const static_path<Size>& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(
	const static_cstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(
	const static_wstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(
	const static_u8string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(
	const static_u16string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::assign(
	const static_u32string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(
	const static_path<Size>& path)
{
	assert(false && "todo");

	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(
	const static_cstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(
	const static_wstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(
	const static_u8string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(
	const static_u16string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator/=(
	const static_u32string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(
	const static_path<Size>& path)
{
	if (path.empty())
		return *this;

	this->m_buffer.append(path.m_buffer);

	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(
	const static_cstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(
	const static_wstring_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(
	const static_u8string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(
	const static_u16string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::append(
	const static_u32string_view& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(
	const static_path<Size>& path)
{
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(
	const static_cstring_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(
	const static_wstring_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(
	const static_u8string_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(
	const static_u16string_view& str)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator+=(
	const static_u32string_view& str)
{
	assert(false && "todo");
	return *this;
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
		etl::replace(this->m_buffer.begin(), this->m_buffer.end(),
			fs_give_opposite_to_preferred_separator(preferred_separator),
			preferred_separator);
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
	const static_path<Size>& replacement)
{
	this->remove_filename().append(replacement);
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::replace_extension(
	const static_path<Size>& replacement)
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
				extension_dot + 1, this->m_buffer.size() - extension_dot);

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
					this->m_buffer.append(1, preferred_separator);

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
				extension_dot, this->m_buffer.size() - extension_dot);
		}
	}

	return *this;
}

template <size_t Size>
inline void static_path<Size>::swap(static_path<Size>& other) noexcept
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
	assert(false && "todo");
	return static_u8string<Size>();
}

template <size_t Size>
inline static_u16string<Size> static_path<Size>::u16string() const
{
	assert(false && "todo");
	return static_u16string<Size>();
}

template <size_t Size>
inline static_u32string<Size> static_path<Size>::u32string() const
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
inline static_cstring<Size> static_path<Size>::generic_string() const
{
	assert(false && "todo");
	return static_cstring<Size>();
}

template <size_t Size>
inline static_u8string<Size> static_path<Size>::generic_u8string() const
{
	assert(false && "todo");
	return static_u8string<Size>();
}

template <size_t Size>
inline static_u16string<Size> static_path<Size>::generic_u16string() const
{
	assert(false && "todo");
	return static_u16string<Size>();
}

template <size_t Size>
inline static_u32string<Size> static_path<Size>::generic_u32string() const
{
	assert(false && "todo");
	return static_u32string<Size>();
}

template <size_t Size>
inline static_wstring<Size> static_path<Size>::generic_wstring() const
{
	assert(false && "todo");
	return static_wstring<Size>();
}

template <size_t Size>
inline int static_path<Size>::compare(
	const static_path<Size>& path) const noexcept
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
inline int static_path<Size>::compare(const static_cstring_view& str) const
{
	return this->compare(static_path<Size>(str));
}

template <size_t Size>
inline int static_path<Size>::compare(const static_wstring_view& str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const static_u8string_view& str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const static_u16string_view& str) const
{
	assert(false && "todo");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(const static_u32string_view& str) const
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
inline static_path<Size> static_path<Size>::lexically_normal() const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_relative(
	const static_path<Size>& base) const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_proximate(
	const static_path<Size>& base) const
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
			if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
				(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
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
inline static_path<Size> static_path<Size>::root_directory() const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::root_path() const
{
	assert(false && "todo");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::relative_path() const
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_buffer.empty() == false)
	{
		if (this->m_buffer.size() > 3)
		{
			if (this->m_buffer[0] == '/' || this->m_buffer[0] == '\\')
			{
				return this->m_buffer.substr(1).c_str();
			}
			else
			{
				if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
					(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
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
									return this->m_buffer.substr(3).c_str();
								}
								else
								{
									return this->m_buffer.substr(2).c_str();
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
			if (this->m_buffer[0] == '/' || this->m_buffer[0] == '\\')
			{
				return this->m_buffer.substr(1).c_str();
			}
			else
			{
				if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
					(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
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
									return this->m_buffer.substr(2).c_str();
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
				return this->m_buffer.substr(0, index_forward).c_str();
			}
			else
			{
				return this->m_buffer.substr(0, index_backward).c_str();
			}
		}
		else if (index_forward != npos)
		{
			return this->m_buffer.substr(0, index_forward).c_str();
		}
		else if (index_backward != npos)
		{
			return this->m_buffer.substr(0, index_backward).c_str();
		}
		else
		{
#ifdef KOTEK_USE_PLATFORM_WINDOWS

			if (this->m_buffer.size() > 1)
			{
				auto index_double_dots = this->m_buffer.rfind(':');

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
	assert(false && "todo");
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
				if (this->m_buffer[index_previous_to_dot] != '.')
				{
					return this->m_buffer.substr(index_dot).c_str();
				}
				else
				{
					auto valid_last_symbol_index = this->m_buffer.size() - 1;

					if (this->m_buffer.size() >= 3)
					{
						auto before_previous_index = index_previous_to_dot - 1;
						if (((this->m_buffer[before_previous_index] != '/' &&
									this->m_buffer[before_previous_index] !=
										'\\')))
						{
							return this->m_buffer.substr(index_dot).c_str();
						}
						else
						{
							if (((this->m_buffer[valid_last_symbol_index] !=
										 '/' &&
									 this->m_buffer[valid_last_symbol_index] !=
										 '\\') &&
									index_dot != valid_last_symbol_index))
							{
								return this->m_buffer.substr(index_dot).c_str();
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
			if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
				(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
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
				if (this->m_buffer[0] == '/' || this->m_buffer[0] == '\\')
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
			if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
				(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
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
				// invalid disk and path so we think it is not root directory
				// because of invalid path nothing applies to result variable
			}
			else
			{
				if (this->m_buffer[0] == '/' || this->m_buffer[0] == '\\')
				{
					result = true;
				}
				else
				{
					if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
						(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
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
			if (this->m_buffer[0] == '/' || this->m_buffer[0] == '\\')
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

	if (index_forward_slash != npos && index_backward_slash != npos)
	{
		// '/' is the last symbol from end
		if (index_forward_slash > index_backward_slash)
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
		// otherwise it is '\\' from end
		else
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
					if (index_forward != this->m_buffer.size() - 1)
					{
						result = true;
					}
				}
				else
				{
					if (index_backward != this->m_buffer.size() - 1)
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
					if (this->m_buffer[this->m_buffer.size() - 1] != ':')
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
						this->m_buffer[this->m_buffer.size() - 1] != ':')
						result = true;
				}
				else
				{
					if (this->m_buffer.size() > 1)
					{
						if ((this->m_buffer[1] != ':' &&
								this->m_buffer[this->m_buffer.size() - 1] !=
									':') &&
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
				// we might have a name of file as '.' and it has some
				// extension...

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
			if ((this->m_buffer[0] >= 65 && this->m_buffer[0] <= 90) ||
				(this->m_buffer[0] >= 97 && this->m_buffer[0] <= 122))
			{
				if (this->m_buffer[1] == ':')
				{
					if (this->m_buffer[2] == '/' || this->m_buffer[2] == '\\')
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

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
