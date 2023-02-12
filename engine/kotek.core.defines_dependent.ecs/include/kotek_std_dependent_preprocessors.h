#pragma once

#define KOTEK_COMPONENT(YourClass)                                          \
public:                                                                     \
    static const Kotek::ktk::cstring& GetComponentName(void) noexcept       \
	{                                                                       \
		return m_component_name;                                            \
	}                                                                       \
	static Kotek::ktk::size_t GetHashCode(void) noexcept                    \
	{                                                                       \
		return typeid(YourClass).hash_code();                               \
	}                                                                       \
	void SetEnabled(bool status) noexcept                                   \
	{                                                                       \
		this->m_is_enabled = status;                                        \
	}                                                                       \
                                                                            \
	bool IsEnabled(void) const noexcept                                     \
	{                                                                       \
		return this->m_is_enabled;                                          \
	}                                                                       \
                                                                            \
	Kotek::ktk::json::value Serialize(void) noexcept override               \
	{                                                                       \
		return Kotek::ktk::json::value_from(*this);                         \
	}                                                                       \
	void Deserialize(const Kotek::ktk::json::value& data) noexcept override \
	{                                                                       \
		*this = Kotek::ktk::json::value_to<YourClass>(data);                \
	}                                                                       \
                                                                            \
private:                                                                    \
    inline static Kotek::ktk::cstring m_component_name = #YourClass;        \
	bool m_is_enabled = true;
