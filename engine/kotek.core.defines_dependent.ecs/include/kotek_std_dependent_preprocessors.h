#pragma once

#define KOTEK_COMPONENT(YourClass)                                           \
public:                                                                      \
	static const kotek::static_cstring_t<zircon_DEF_MAX_COMPONENT_NAME_SIZE>& GetComponentName(void) noexcept        \
	{                                                                        \
		return m_component_name;                                             \
	}                                                                        \
	static kotek::size_t GetComponentNameHash(void) noexcept            \
	{                                                                        \
		return m_component_name_hash;                                        \
	}                                                                        \
	static kotek::size_t GetHashCode(void) noexcept                     \
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
	kotek::ktk::json::value Serialize(void) noexcept override                \
	{                                                                        \
		return kotek::ktk::json::value_from(*this);                          \
	}                                                                        \
	void Deserialize(const Kotek::ktk::json::value& data) noexcept override  \
	{                                                                        \
		*this = Kotek::ktk::json::value_to<YourClass>(data);                 \
	}                                                                        \
                                                                             \
	kotek::ktk::json::value Serialize(                                       \
		unsigned char* p_raw_memory, Kotek::ktk::size_t size) override       \
	{                                                                        \
		KOTEK_ASSERT(p_raw_memory, "you passed an invalid part of memory!"); \
		kotek::ktk::json::static_resource res(p_raw_memory, size);           \
		kotek::ktk::json::storage_ptr ptr(&res);                             \
		return Kotek::ktk::json::value_from(*this, ptr);                     \
	}                                                                        \
                                                                             \
private:                                                                     \
	inline static kotek::static_cstring_t<zircon_DEF_MAX_COMPONENT_NAME_SIZE> m_component_name = #YourClass;         \
	inline static kotek::size_t m_component_name_hash =                 \
		kotek::hash_t<kotek::static_cstring_t<zircon_DEF_MAX_COMPONENT_NAME_SIZE>>{}(m_component_name);           \
	inline static kotek::uint8_t m_component_type =                     \
		kComponentType##YourClass;                                           \
	bool m_is_enabled = true;
