#pragma once

#include <kotek.core.types.string/include/kotek_core_types_string.h>
#include <kotek.core.casting.string/include/kotek_core_casting_string.h>
#include <kotek.core.casting.lexical/include/kotek_core_casting_lexical.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

// TODO: use ICU library for converting things warning STL4017
#include <codecvt>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
// TODO: remove warning warning C4244: 'argument': conversion from
// 'const wchar_t' to 'const _Elem', possible loss of data
class string
{
public:
	string(void) = default;
	~string(void) = default;

	#ifdef KOTEK_USE_UNICODE
	template <typename T,
		std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
	string(T number) :
		m_data(ktk::cast::to_string(std::to_string(number).c_str()))
	{
	}
	#else
	template <typename T,
		std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
	string(T number) :
		m_data(ktk::cast::to_legacy_string(std::to_string(number).c_str()))
	{
	}
	#endif

	#ifdef KOTEK_USE_UNICODE
	string(string_unicode::iterator begin, string_unicode::iterator end) :
		m_data(begin, end)
	{
	}

	string(string_unicode::const_iterator cbegin,
		string_unicode::const_iterator cend) :
		m_data(cbegin, cend)
	{
	}
	#endif

	string(string_legacy::iterator begin, string_legacy::iterator end) :
		m_data(begin, end)
	{
	}

	string(string_legacy::const_iterator cbegin,
		string_legacy::const_iterator cend) :
		m_data(cbegin, cend)
	{
	}

	string(const char* p_data)
	{
		if (p_data != nullptr)
		{
	#ifdef KOTEK_USE_UNICODE
			this->m_data = ktk::cast::to_string(p_data);
	#else
			this->m_data = p_data;
	#endif
		}
	}

	#ifdef KOTEK_USE_UNICODE
		#if defined(KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC)
	string(const ktk::string_legacy& data) : m_data(ktk::cast::to_string(data))
	{
	}
		#endif
	#else
	string(const ktk::string_legacy& data) : m_data(data) {}
	#endif

	string(const std::string& data) : m_data(ktk::cast::to_string(data.c_str()))
	{
	}

	#ifdef KOTEK_USE_UNICODE
	string(const uchar* p_data)
	{
		if (p_data != nullptr)
		{
			this->m_data = p_data;
		}
	}

		#if defined(KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC)
	string(const ktk::string_unicode& str) : m_data(str) {}
		#endif

	string(const std::wstring& data) : m_data(data.begin(), data.end()) {}
	#endif

	#ifdef KOTEK_USE_UNICODE
	string& operator=(const string_unicode& data)
	{
		this->m_data = data;

		return *this;
	}
	#endif

	string& operator=(const string_legacy& data)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data = ktk::cast::to_string(data);
	#else
		this->m_data = data;
	#endif

		return *this;
	}

	string& operator=(const char* p_data)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data = ktk::cast::to_string(p_data);
	#else
		this->m_data = p_data;
	#endif

		return *this;
	}

	template <typename Type,
		std::enable_if_t<std::is_arithmetic<Type>::value, bool> = true>
	string& operator=(Type number)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data = ktk::cast::to_string(std::to_string(number).c_str());
	#else
		this->m_data = std::to_string(number).c_str();
	#endif

		return *this;
	}

	#ifdef KOTEK_USE_UNICODE
	string& operator=(const tchar* p_data)
	{
		this->m_data = p_data;

		return *this;
	}

	string& operator=(const char32_t* p_data)
	{
		std::wstring_convert<std::codecvt<char32_t, char, std::mbstate_t>,
			char32_t, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char32_t>,
			KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char>>
			converter;

		auto bytes = converter.to_bytes(p_data);
		this->m_data = string_unicode(bytes.begin(), bytes.end());

		return *this;
	}

	string& operator=(const char16_t* p_data)
	{
		std::wstring_convert<std::codecvt<char16_t, char, std::mbstate_t>,
			char16_t, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char16_t>,
			KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char>>
			converter;

		auto bytes = converter.to_bytes(p_data);

		this->m_data = string_unicode(bytes.begin(), bytes.end());

		return *this;
	}

	string& operator=(const char8_t* p_data)
	{
		std::wstring_convert<std::codecvt<char8_t, char, std::mbstate_t>,
			char8_t, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char8_t>,
			KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char>>
			converter;

		auto bytes = converter.to_bytes(p_data);

		this->m_data = string_unicode(bytes.begin(), bytes.end());

		return *this;
	}

	#endif

	bool operator==(const string& data) const
	{
		return this->get_as_is() == data.get_as_is();
	}

	#ifdef KOTEK_USE_UNICODE
	bool operator==(const tchar* p_data) { return this->m_data == p_data; }
	#endif

	bool operator==(const char* p_data)
	{
	#ifdef KOTEK_USE_UNICODE
		return this->m_data == ktk::cast::to_string(p_data);
	#else
		return this->m_data == p_data;
	#endif
	}

	#pragma region += operators
	string& operator+=(const string& data)
	{
		this->m_data += data.get_as_is();

		return *this;
	}

	string& operator+=(const char symbol)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data += ktk::cast::to_string(string_legacy(1, symbol));
	#else
		this->m_data += symbol;
	#endif

		return *this;
	}

	#ifdef KOTEK_USE_UNICODE
	string& operator+=(const tchar symbol)
	{
		this->m_data += symbol;

		return *this;
	}

	string& operator+=(const string_unicode& data)
	{
		this->m_data += data;

		return *this;
	}
	#endif

	string& operator+=(const string_legacy& data)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data += ktk::cast::to_string(data);
	#else
		this->m_data += data;
	#endif

		return *this;
	}

	#ifdef KOTEK_USE_UNICODE
	string& operator+=(const tchar* p_data)
	{
		this->m_data += p_data;

		return *this;
	}
	#endif

	string& operator+=(const char* p_data)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data += ktk::cast::to_string(p_data);
	#else
		this->m_data += p_data;
	#endif

		return *this;
	}

	template <typename Type,
		std::enable_if_t<std::is_arithmetic<Type>::value, bool> = true>
	string& operator+=(Type number)
	{
	#ifdef KOTEK_USE_UNICODE
		this->m_data += ktk::cast::to_string(std::to_string(number).c_str());
	#else
		this->m_data += std::to_string(number).c_str();
	#endif

		return *this;
	}
	#pragma endregion

	string_legacy get_as_legacy() const noexcept
	{
		// TODO: if we are use unicode and uchar != char so we must convert to
		// u8 and obtain casted const char* otherwise information will be lost!
	#ifdef KOTEK_USE_UNICODE
		return reinterpret_cast<const char*>(ktk::cast::to_utf8(this->m_data).c_str());
	#else
		return this->m_data;
	#endif
	}

	#ifdef KOTEK_USE_UNICODE
	const string_unicode& get_as_is() const noexcept { return this->m_data; }

	string_unicode& get_as_is() noexcept { return this->m_data; }
	#else
	const string_legacy& get_as_is() const noexcept { return this->m_data; }

	string_legacy& get_as_is() noexcept { return this->m_data; }
	#endif

	ktk::size_t get_hash(void) const noexcept;

	bool empty(void) const noexcept { return this->m_data.empty(); }

	#ifdef KOTEK_USE_UNICODE
	string_unicode::iterator begin(void) noexcept
	{
		return this->m_data.begin();
	}

	string_unicode::iterator end(void) noexcept { return this->m_data.end(); }

	string_unicode::const_iterator cbegin(void) const noexcept
	{
		return this->m_data.cbegin();
	}

	string_unicode::const_iterator cend(void) const noexcept
	{
		return this->m_data.cend();
	}
	#else
	string_legacy::iterator begin(void) noexcept
	{
		return this->m_data.begin();
	}

	string_legacy::iterator end(void) noexcept { return this->m_data.end(); }

	string_legacy::const_iterator cbegin(void) const noexcept
	{
		return this->m_data.cbegin();
	}

	string_legacy::const_iterator cend(void) const noexcept
	{
		return this->m_data.cend();
	}

	#endif

	template <class _Iter>
	void assign(_Iter begin, _Iter end)
	{
		this->m_data.assign(begin, end);
	}

	#ifdef KOTEK_USE_UNICODE
	operator std::wstring() const
	{
		return std::wstring(this->m_data.begin(), this->m_data.end());
	}

		#if defined(KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC)
	operator string_unicode() const { return this->m_data; }
		#endif
	#endif

	operator std::string() const
	{
	#ifdef KOTEK_USE_UNICODE
		return std::string(this->m_data.begin(), this->m_data.end());
	#else
		return this->m_data;
	#endif
	}

	#if defined(KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC)
	operator string_legacy() const
	{
		#ifdef KOTEK_USE_UNICODE
		return ktk::cast::to_legacy_string(this->m_data);
		#else
		return this->m_data;
		#endif
	}
	#endif

	template <typename Type,
		std::enable_if_t<std::is_arithmetic<Type>::value, bool> = true>
	operator Type() const
	{
		return ktk::lexical_cast<Type>(this->m_data);
	}

	#pragma region UTILITY
	void append_path(const ktk::string&
			your_folder_or_file_name_with_or_without_format) noexcept;
	#pragma endregion

	ktk::size_t size(void) const noexcept { return this->m_data.size(); }

public:
	#ifdef KOTEK_USE_UNICODE
	static constexpr auto npos = string_unicode::npos;

	#else
	static constexpr auto npos = string_legacy::npos;
	#endif

private:
	#ifdef KOTEK_USE_UNICODE
	string_unicode m_data;
	#else
	string_legacy m_data;
	#endif
};

std::size_t hash_value(const string& instance);

// Be careful this returns a copy, not a modified string if you want to
// modify existed string apply operator += not just +
ktk::string operator+(
	const ktk::string& data_left, const ktk::string& data_right) noexcept;
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK