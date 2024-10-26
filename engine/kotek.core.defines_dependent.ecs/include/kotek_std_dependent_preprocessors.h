#pragma once

#define KOTEK_COMPONENT(YourClass)                                           \
public:                                                                      \
	static const Kotek::ktk::cstring& GetComponentName(void) noexcept        \
	{                                                                        \
		return m_component_name;                                             \
	}                                                                        \
	static Kotek::ktk::size_t GetComponentNameHash(void) noexcept            \
	{                                                                        \
		return m_component_name_hash;                                        \
	}                                                                        \
	static Kotek::ktk::size_t GetHashCode(void) noexcept                     \
	{                                                                        \
		return typeid(YourClass).hash_code();                                \
	}                                                                        \
	void SetEnabled(bool status) noexcept                                    \
	{                                                                        \
		this->m_is_enabled = status;                                         \
	}                                                                        \
                                                                             \
	bool IsEnabled(void) const noexcept                                      \
	{                                                                        \
		return this->m_is_enabled;                                           \
	}                                                                        \
                                                                             \
	Kotek::ktk::json::value Serialize(void) noexcept override                \
	{                                                                        \
		return Kotek::ktk::json::value_from(*this);                          \
	}                                                                        \
	void Deserialize(const Kotek::ktk::json::value& data) noexcept override  \
	{                                                                        \
		*this = Kotek::ktk::json::value_to<YourClass>(data);                 \
	}                                                                        \
                                                                             \
	Kotek::ktk::json::value Serialize(                                       \
		unsigned char* p_raw_memory, Kotek::ktk::size_t size) override       \
	{                                                                        \
		KOTEK_ASSERT(p_raw_memory, "you passed an invalid part of memory!"); \
		Kotek::ktk::json::static_resource res(p_raw_memory, size);           \
		Kotek::ktk::json::storage_ptr ptr(&res);                             \
		return Kotek::ktk::json::value_from(*this, ptr);                     \
	}                                                                        \
                                                                             \
private:                                                                     \
	inline static Kotek::ktk::cstring m_component_name = #YourClass;         \
	inline static Kotek::ktk::size_t m_component_name_hash =                 \
		Kotek::ktk::hash<Kotek::ktk::cstring>{}(m_component_name);           \
	inline static Kotek::ktk::uint8_t m_component_type =                     \
		kComponentType##YourClass;                                           \
	bool m_is_enabled = true;
