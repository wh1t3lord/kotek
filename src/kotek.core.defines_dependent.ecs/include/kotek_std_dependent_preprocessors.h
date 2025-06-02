#pragma once

// add here only static methods and fields!!!
// because field generator will fail
#define KOTEK_COMPONENT(YourClass, StringType)               \
public:                                                      \
	static const StringType& GetComponentName(void) noexcept \
	{                                                        \
		return m_component_name;                             \
	}                                                        \
	static kotek::size_t GetComponentNameHash(void) noexcept \
	{                                                        \
		return m_component_name_hash;                        \
	}                                                        \
	static kotek::size_t GetHashCode(void) noexcept          \
	{                                                        \
		return typeid(YourClass).hash_code();                \
	}                                                        \
                                                             \
private:                                                     \
	inline static StringType m_component_name = #YourClass;  \
	inline static kotek::size_t m_component_name_hash =      \
		kotek::hash_t<StringType>{}(m_component_name);
