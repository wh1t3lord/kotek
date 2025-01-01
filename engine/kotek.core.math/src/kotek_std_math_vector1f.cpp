#include "../include/kotek_std_math_vector1f.h"

#include "../include/kotek_std_math_matrix1f_view.h"
#include "../include/kotek_std_math_matrix2f_view.h"
#include "../include/kotek_std_math_matrix3f_view.h"
#include "../include/kotek_std_math_matrix4f_view.h"
#include "../include/kotek_std_math_matrix1f_const_view.h"
#include "../include/kotek_std_math_matrix2f_const_view.h"
#include "../include/kotek_std_math_matrix3f_const_view.h"
#include "../include/kotek_std_math_matrix4f_const_view.h"

#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

vector1f::vector1f(void) : m_base(0.0f) {}
vector1f::vector1f(float x) : m_base(x) {}

vector1f::vector1f(float x, float y) : m_base(x) {}
vector1f::vector1f(float x, float y, float z) : m_base(x) {}
vector1f::vector1f(float x, float y, float z, float w) : m_base(x) {}

vector1f::vector1f(float* p_arr1, unsigned char size) : m_base(p_arr1[0]) {}
vector1f::vector1f(const float* p_arr1, unsigned char size) :
	m_base(p_arr1[0])
{
}

vector1f::vector1f(const matrix4f_view_t& view) : m_base(view.x()) {}
vector1f::vector1f(const matrix3f_view_t& view) : m_base(view.x()) {}
vector1f::vector1f(const matrix2f_view_t& view) : m_base(view.x()) {}
vector1f::vector1f(const matrix1f_view_t& view) : m_base(view.x()) {}

vector1f::vector1f(const matrix4f_const_view_t& view) : m_base(view.x()) {}
vector1f::vector1f(const matrix3f_const_view_t& view) : m_base(view.x()) {}
vector1f::vector1f(const matrix2f_const_view_t& view) : m_base(view.x()) {}
vector1f::vector1f(const matrix1f_const_view_t& view) : m_base(view.x()) {}

vector1f::vector1f(const vector2f& data) : m_base(data.x()) {}

vector1f::vector1f(const vector3f& data) : m_base(data.x()) {}

vector1f::vector1f(const vector4f& data) : m_base(data.x()) {}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f::vector1f(const base_vec1_t& data) : m_base(data) {}
#endif
vector1f::vector1f(const vector1f& data) : m_base(data.m_base) {}

vector1f& vector1f::operator=(const vector1f& data)
{
	this->m_base = data.m_base;
	return *this;
}

vector1f& vector1f::operator+=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto v1 = DirectX::XMLoadFloat(&this->m_base);
	auto v2 = DirectX::XMLoadFloat(&value);
	auto result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += value;
#endif
	return *this;
}

vector1f& vector1f::operator+=(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	this->operator+=(data.m_base);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data.m_base;
#endif
	return *this;
}

vector1f& vector1f::operator+=(const matrix4f_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix3f_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix2f_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix1f_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix4f_const_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix3f_const_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix2f_const_view_t& view)
{
	return this->operator+=(view.x());
}

vector1f& vector1f::operator+=(const matrix1f_const_view_t& view)
{
	return this->operator+=(view.x());
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& operator+=(const base_vec1_t& data)
{
	this->m_base += data;
	return *this;
}
#endif

vector1f& vector1f::operator-=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&value);
	auto result = DirectX::XMVectorSubtract(casted_original, casted_argument);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= value;
#endif
	return *this;
}

vector1f& vector1f::operator-=(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	this->operator-=(data.m_base);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data.m_base;
#endif
	return *this;
}

vector1f& vector1f::operator-=(const matrix4f_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix3f_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix2f_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix1f_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix4f_const_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix3f_const_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix2f_const_view_t& view)
{
	return this->operator-=(view.x());
}

vector1f& vector1f::operator-=(const matrix1f_const_view_t& view)
{
	return this->operator-=(view.x());
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& operator-=(const base_vec1_t& data)
{
	this->m_base -= data;
	return *this;
}
#endif

vector1f& vector1f::operator*=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto result = DirectX::XMVectorScale(casted_original, value);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif
	return *this;
}

vector1f& vector1f::operator*=(const matrix4f_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix3f_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix2f_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix1f_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix4f_const_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix3f_const_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix2f_const_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const matrix1f_const_view_t& view)
{
	return this->operator*=(view.x());
}

vector1f& vector1f::operator*=(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);
	auto result = DirectX::XMVectorMultiply(casted_original, casted_argument);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif
	return *this;
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& operator*=(const base_vec1_t& data)
{
	this->m_base *= data;
	return *this;
}
#endif

vector1f& vector1f::operator/=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	KOTEK_ASSERT(value != 0.0f, "you can't divide if you have zero!!!");

	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto result = DirectX::XMVectorScale(casted_original, 1.f / value);
	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= value;
#endif
	return *this;
}

vector1f& vector1f::operator/=(const matrix4f_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix3f_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix2f_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix1f_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix4f_const_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix3f_const_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix2f_const_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const matrix1f_const_view_t& view)
{
	return this->operator/=(view.x());
}

vector1f& vector1f::operator/=(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);
	auto result = DirectX::XMVectorDivide(casted_original, casted_argument);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data.m_base;
#endif
	return *this;
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& vector1f::operator/=(const base_vec1_t& data)
{
	this->m_base /= data;
	return *this;
}
#endif

vector1f& vector1f::operator%=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	this->m_base = std::fmod(this->m_base, value);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base.x = std::fmod(this->m_base.x, value);
#endif

	return *this;
}

vector1f& vector1f::operator%=(const vector1f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	this->m_base = std::fmod(this->m_base, data.m_base);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base.x = std::fmod(this->m_base.x, data.m_base.x);
#endif
	return *this;
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& vector1f::operator%=(const base_vec1_t& data) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, data.x);
	return *this;
}
#endif

vector1f vector1f::operator+() const noexcept
{
	return (*this);
}

vector1f vector1f::operator-() const noexcept
{
	return vector1f(-this->m_base);
}

bool vector1f::operator==(const vector1f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

	return DirectX::XMVector2Equal(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#endif
}

bool vector1f::operator!=(const vector1f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

	return DirectX::XMVector2NotEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#endif
}

float vector1f::operator[](unsigned int index) const
{
	KOTEK_ASSERT(index == 0, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float const* p_array = reinterpret_cast<float const*>(&this->m_base);

	return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	#error provide implementation
#endif
}

float& vector1f::operator[](unsigned int index)
{
	KOTEK_ASSERT(index == 0, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float* p_array = reinterpret_cast<float*>(&this->m_base);
	return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	#error provide implementation
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
vector1f::operator DirectX::XMVECTOR() const noexcept
{
	return DirectX::XMLoadFloat(&this->m_base);
}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

float vector1f::x(void) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return this->m_base;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base.x;
#endif
}

float& vector1f::x(void) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return this->m_base;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base.x;
#endif
}

const float* vector1f::data(void) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &this->m_base;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return &this->m_base.x;
#endif
}

float* vector1f::data(void) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &this->m_base;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return &this->m_base.x;
#endif
}

vector1f& vector1f::Set_Base(const base_vec1_t& data) noexcept
{
	this->m_base = data;
	return *this;
}

base_vec1_t& vector1f::Get_Base(void) noexcept
{
	return this->m_base;
}
const base_vec1_t& vector1f::Get_Base(void) const noexcept
{
	return this->m_base;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK