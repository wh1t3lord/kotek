#include "../include/kotek_std_json.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkJson::ktkJson(void) : m_json{} {}

#ifdef KOTEK_USE_BOOST_LIBRARY
ktkJson::ktkJson(const ktk::json::object& text) : m_json{text} {}
#endif

ktkJson::ktkJson(const ktkJson& instance) : m_json{instance.m_json} {}

ktkJson& ktkJson::operator=(const ktkJson& instance)
{
	this->m_json = instance.m_json;
	return *this;
}

ktkJson::~ktkJson(void) {}

const ktk::json::object& ktkJson::Get_Object(void) const noexcept
{
	return this->m_json;
}

ktkJson& ktkJson::operator=(const ktk::json::object& instance)
{
	this->m_json = instance;
	return *this;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK