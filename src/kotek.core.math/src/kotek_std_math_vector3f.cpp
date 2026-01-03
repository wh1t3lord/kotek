#include "../include/kotek_std_math_vector3f.h"

#include "../include/kotek_std_math_vectornf_view.h"
#include "../include/kotek_std_math_vectornf_const_view.h"
#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_functions_vector.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

vector3f::vector3f(float x) : m_base(x, 0.0f, 0.0f) {}
vector3f::vector3f(float x, float y) : m_base(x, y, 0.0f) {}
vector3f::vector3f(float x, float y, float z) : m_base(x, y, z)
{
}
vector3f::vector3f(float x, float y, float z, float w) :
	m_base(x, y, z)
{
}

vector3f::vector3f(float* p_arr3, unsigned char size) :
	m_base(p_arr3[0], p_arr3[1], p_arr3[2])
{
	KOTEK_ASSERT(
		size > 0 && size <= 3, "needed to be as valid value!"
	);

	if (size == 2)
	{
		this->m_base.z = 0.0f;
	}
	else if (size == 1)
	{
		this->m_base.z = 0.0f;
		this->m_base.y = 0.0f;
	}
}

vector3f::vector3f(const float* p_arr3, unsigned char size) :
	m_base(p_arr3[0], p_arr3[1], p_arr3[2])
{
	KOTEK_ASSERT(
		size > 0 && size <= 3, "needed to be as valid value!"
	);

	if (size == 2)
	{
		this->m_base.z = 0.0f;
	}
	else if (size == 1)
	{
		this->m_base.z = 0.0f;
		this->m_base.y = 0.0f;
	}
}

vector3f::vector3f(const base_vec3_t& data) : m_base(data) {}
vector3f::vector3f(const vector3f& data) : m_base(data.m_base)
{
}

vector3f::vector3f(const vector1f& data) :
	m_base(get_component_x(data), 0.0f, 0.0f)
{
}

vector3f::vector3f(const vector2f& data) :
	m_base(get_component_x(data), get_component_y(data), 0.0f)
{
}

vector3f::vector3f(const vector4f& data) :
	m_base(data.x(), data.y(), data.z())
{
}

vector3f::vector3f(const vector1f& data, float y) :
	m_base(data.x(), y, 0.0f)
{
}

vector3f::vector3f(const vector1f& data, float y, float z) :
	m_base(data.x(), y, z)
{
}

vector3f::vector3f(const vector2f& data, float z) :
	m_base(data.x(), data.y(), z)
{
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
vector3f::vector3f(const DirectX::XMVECTOR& xmvec)
{
	DirectX::XMStoreFloat3(&this->m_base, xmvec);
}
#endif

vector3f::vector3f(void) : m_base(0.0f, 0.0f, 0.0f) {}

vector3f& vector3f::operator=(const vector3f& data) noexcept
{
	this->m_base = data.m_base;
	return *this;
}

vector3f& vector3f::operator+=(const vector3f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	DirectX::XMVECTOR v2 = data;
	const auto& result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data.m_base;
#endif
	return *this;
}

vector3f& vector3f::operator+=(const base_vec3_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	DirectX::XMVECTOR v2 = DirectX::XMLoadFloat3(&data);
	const auto& result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data;
#endif
	return *this;
}

vector3f& vector3f::operator-=(const vector3f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	const auto& result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data.m_base;
#endif
	return *this;
}

vector3f& vector3f::operator-=(const base_vec3_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat3(&data);
	const auto& result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data;
#endif
	return *this;
}

vector3f& vector3f::operator*=(const vector3f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	const auto& result = DirectX::XMVectorMultiply(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif
	return *this;
}

vector3f& vector3f::operator*=(const base_vec3_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat3(&data);
	auto result = DirectX::XMVectorMultiply(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data;
#endif
	return *this;
}

vector3f& vector3f::operator*=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	const auto& result = DirectX::XMVectorScale(v1, value);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif
	return *this;
}

vector3f& vector3f::operator/=(const vector3f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	const auto& result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data.m_base;
#endif
	return *this;
}

vector3f& vector3f::operator/=(const base_vec3_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat3(&data);
	const auto& result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data;
#endif
	return *this;
}

vector3f& vector3f::operator/=(float value) noexcept
{
	return this->operator*=(1.f / value);
}

vector3f& vector3f::operator%=(float value) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, value);
	this->m_base.y = std::fmod(this->m_base.y, value);
	this->m_base.z = std::fmod(this->m_base.z, value);

	return *this;
}

vector3f& vector3f::operator%=(const vector3f& data) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, data.x());
	this->m_base.y = std::fmod(this->m_base.y, data.y());
	this->m_base.z = std::fmod(this->m_base.z, data.z());

	return *this;
}

vector3f vector3f::operator+() const noexcept
{
	return *this;
}
vector3f vector3f::operator-() const noexcept
{
	return vector3f(
		-this->m_base.x, -this->m_base.y, -this->m_base.z
	);
}

bool vector3f::operator==(const vector3f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;

	return DirectX::XMVector3Equal(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#endif
}

bool vector3f::operator!=(const vector3f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;

	return DirectX::XMVector3NotEqual(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#endif
}

float vector3f::operator[](unsigned char index) const
{
	KOTEK_ASSERT(
		index != unsigned char(-1),
		"out of range (probably you passed a negative number)"
	);
	KOTEK_ASSERT(index <= 2, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float const* p_array =
		reinterpret_cast<float const*>(&this->m_base);

	return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base[index];
#else
	#error todo: provide implementation
#endif
}

float& vector3f::operator[](unsigned char index)
{
	KOTEK_ASSERT(
		index != unsigned char(-1),
		"out of range (probably you passed a negative number)"
	);
	KOTEK_ASSERT(index <= 2, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float* p_array = reinterpret_cast<float*>(&this->m_base);
	return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base[index];
#else
	#error todo: provide implementation
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
vector3f::operator DirectX::XMVECTOR() const noexcept
{
	return DirectX::XMLoadFloat3(&this->m_base);
}
#endif

const float* vector3f::data(void) const noexcept
{
	return &this->m_base.x;
}
float* vector3f::data(void) noexcept
{
	return &this->m_base.x;
}

void vector3f::set(float x, float y, float z) noexcept
{
	this->m_base.x = x;
	this->m_base.y = y;
	this->m_base.z = z;
}

vector3f& vector3f::Set_Base(const base_vec3_t& data) noexcept
{
	this->m_base = data;
	return *this;
}

base_vec3_t& vector3f::Get_Base(void) noexcept
{
	return this->m_base;
}

const base_vec3_t& vector3f::Get_Base(void) const noexcept
{
	return this->m_base;
}

float vector3f::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->operator[](row_id);
}

float&
vector3f::e(math_id_t column_id, math_id_t row_id) noexcept
{
	return this->operator[](row_id);
}

vectornf_view_t vector3f::c(math_id_t column_id) noexcept
{
	return vectornf_view_t(this->data(), 3);
}

vectornf_const_view_t vector3f::c(math_id_t column_id
) const noexcept
{
	return vectornf_const_view_t(this->data(), 3);
}

constexpr math_id_t vector3f::size_of(void) noexcept
{
	static_assert(
		sizeof(float[3]) == sizeof(m_base),
		"gurantee that your class will be equal to float[3]"
	);

	return static_cast<math_id_t>(sizeof(float[3]));
}

constexpr math_id_t vector3f::get_column_count(void
) const noexcept
{
	return 1;
}

constexpr math_id_t vector3f::get_row_count(void) const noexcept
{
	return 3;
}

float vector3f::x(void) const noexcept 
{
	return this->m_base.x;
}

float& vector3f::x(void) noexcept 
{
	return this->m_base.x;
}

float vector3f::y(void) const noexcept 
{
	return this->m_base.y;
}

float& vector3f::y(void) noexcept 
{
	return this->m_base.y;
}

float vector3f::z(void) const noexcept 
{
	return this->m_base.z;
}

float& vector3f::z(void) noexcept 
{
	return this->m_base.z;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK