#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_std_string.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <filesystem>
#else
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS
// todo: provide overriding through cmake this length
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 260
	#define KOTEK_DEF_OS_PATH_SEPARATOR "\\"
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
	#define KOTEK_DEF_OS_PATH_SEPARATOR "/"
#elif defined(KOTEK_USE_PLATFORM_MAC)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
	#define KOTEK_DEF_OS_PATH_SEPARATOR "/"
#else
	#error undefined platform
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#ifdef KOTEK_USE_PLATFORM_WINDOWS
		#include <Windows.h>
	#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
	#else
		#error unknown platform please report to developers or community for implementation request ^_^
	#endif
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

public:
	/* Member functions */
	static_path();
	~static_path();

	static_path<Size>& operator=(const static_path<Size>& path);
	static_path<Size>& operator=(static_path<Size>&& path) noexcept;
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
	int compare(static_cstring_view str) const;
	int compare(static_wstring_view str) const;
	int compare(static_u8string_view str) const;
	int compare(static_u16string_view str) const;
	int compare(static_u32string_view str) const;

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
inline static_path<Size>& static_path<Size>::operator=(
	const static_path<Size>& path)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::operator=(
	static_path<Size>&& path) noexcept
{
	assert(false && "todo");
	return *this;
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
	assert(false && "todo");
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
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::remove_filename()
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::replace_filename(
	const static_path<Size>& replacement)
{
	assert(false && "todo");
	return *this;
}

template <size_t Size>
inline static_path<Size>& static_path<Size>::replace_extension(
	const static_path<Size>& replacement)
{
	assert(false && "doto");
	return *this;
}

template <size_t Size>
inline void static_path<Size>::swap(static_path<Size>& other) noexcept
{
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
	assert(false && "doto");
	return static_cstring<Size>();
}

template <size_t Size>
inline static_u8string<Size> static_path<Size>::u8string() const
{
	assert(false && "doto");
	return static_u8string<Size>();
}

template <size_t Size>
inline static_u16string<Size> static_path<Size>::u16string() const
{
	assert(false && "doto");
	return static_u16string<Size>();
}

template <size_t Size>
inline static_u32string<Size> static_path<Size>::u32string() const
{
	assert(false && "doto");
	return static_u32string<Size>();
}

template <size_t Size>
inline static_wstring<Size> static_path<Size>::wstring() const
{
	assert(false && "doto");
	return static_wstring<Size>();
}

template <size_t Size>
inline static_cstring<Size> static_path<Size>::generic_string() const
{
	assert(false && "doto");
	return static_cstring<Size>();
}

template <size_t Size>
inline static_u8string<Size> static_path<Size>::generic_u8string() const
{
	assert(false && "doto");
	return static_u8string<Size>();
}

template <size_t Size>
inline static_u16string<Size> static_path<Size>::generic_u16string() const
{
	assert(false && "doto");
	return static_u16string<Size>();
}

template <size_t Size>
inline static_u32string<Size> static_path<Size>::generic_u32string() const
{
	assert(false && "doto");
	return static_u32string<Size>();
}

template <size_t Size>
inline static_wstring<Size> static_path<Size>::generic_wstring() const
{
	assert(false && "doto");
	return static_wstring<Size>();
}

template <size_t Size>
inline int static_path<Size>::compare(
	const static_path<Size>& path) const noexcept
{
	assert(false && "doto");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(static_cstring_view str) const
{
	assert(false && "doto");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(static_wstring_view str) const
{
	assert(false && "doto");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(static_u8string_view str) const
{
	assert(false && "doto");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(static_u16string_view str) const
{
	assert(false && "doto");
	return 0;
}

template <size_t Size>
inline int static_path<Size>::compare(static_u32string_view str) const
{
	assert(false && "doto");
	return 0;
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_normal() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_relative(
	const static_path<Size>& base) const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::lexically_proximate(
	const static_path<Size>& base) const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::root_name() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::root_directory() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::root_path() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::relative_path() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::parent_path() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::filename() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::stem() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline static_path<Size> static_path<Size>::extension() const
{
	assert(false && "doto");
	return static_path<Size>();
}

template <size_t Size>
inline bool static_path<Size>::empty() const noexcept
{
	return this->m_buffer.empty();
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
