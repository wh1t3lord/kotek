#pragma once

#define KOTEK_COMPONENT(YourClass)                                   \
public:                                                              \
	static const Kotek::ktk::string& GetComponentName(void) noexcept \
	{                                                                \
		return m_component_name;                                     \
	}                                                                \
                                                                     \
private:                                                             \
	inline static Kotek::ktk::string m_component_name = #YourClass;