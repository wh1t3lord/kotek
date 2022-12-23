#pragma once

#define KOTEK_COMPONENT(YourClass)                                   \
public:                                                              \
	static const Kotek::ktk::string& GetComponentName(void) noexcept \
	{                                                                \
		return m_component_name;                                     \
	}                                                                \
	static Kotek::ktk::size_t GetHashCode(void) noexcept             \
	{                                                                \
		return typeid(YourClass).hash_code();                        \
	}                                                                \
                                                                     \
private:                                                             \
	inline static Kotek::ktk::string m_component_name = #YourClass;