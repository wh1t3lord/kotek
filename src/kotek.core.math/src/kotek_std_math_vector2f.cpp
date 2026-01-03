#include "../include/kotek_std_math_vector2f.h"

#include "../include/kotek_std_math_vectornf_view.h"
#include "../include/kotek_std_math_vectornf_const_view.h"
#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_functions_vector.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector2f::vector2f(float x) : m_base(x, 0.0f) {}
vector2f::vector2f(float x, float y, float z) : m_base(x, y) {}
vector2f::vector2f(float x, float y, float z, float w) :
	m_base(x, y)
{
}
#endif

vector2f::vector2f(float x, float y) : m_base(x, y) {}

vector2f::vector2f(float* p_arr2, math_id_t size)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	#error todo: impl

#else
	if (p_arr2)
	{
		KOTEK_ASSERT(size == 2, "wrong dimension");

		if (size == 2)
		{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		#error todo: impl
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base.x = p_arr2[0];
			this->m_base.y = p_arr2[1];
	#endif
		}
	}
#endif
}

vector2f::vector2f(const float* p_arr2, math_id_t size)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
#else
	if (p_arr2)
	{
		KOTEK_ASSERT(size == 2, "wrong dimension");

		if (size == 2)
		{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		#error todo: impl
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base.x = p_arr2[0];
			this->m_base.y = p_arr2[1];
	#endif
		}
		else
		{
			this->m_base.x = 0.0f;
			this->m_base.y = 0.0f;
		}
	}
	else
	{
		this->m_base.x = 0.0f;
		this->m_base.y = 0.0f;
	}
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector2f::vector2f(const vector1f& data) : m_base(x(data), 0.0f)
{
}

vector2f::vector2f(const vector1f& data, float y) :
	m_base(get_component_x(data), y)
{
}

vector2f::vector2f(const vector3f& data) :
	m_base(get_component_x(data), data.y())
{
}

vector2f::vector2f(const vector4f& data) :
	m_base(data.x(), data.y())
{
}
#endif

vector2f::vector2f(const base_vec2_t& data) : m_base(data) {}
vector2f::vector2f(const vector2f& data) : m_base(data.m_base)
{
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
vector2f::vector2f(const DirectX::XMVECTOR& vec)
{
	DirectX::XMStoreFloat2(&this->m_base, vec);
}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

vector2f::vector2f(void) : m_base(0.0f, 0.0f) {}

vector2f& vector2f::operator=(const vector2f& data) noexcept
{
	this->m_base = data.m_base;
	return *this;
}

vector2f& vector2f::operator+=(const vector2f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	DirectX::XMVECTOR v2 = data;
	auto result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data.m_base;
#endif
	return *this;
}

vector2f& vector2f::operator+=(const base_vec2_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	DirectX::XMVECTOR v2 = DirectX::XMLoadFloat2(&data);
	auto result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data;
#endif
	return *this;
}

vector2f& vector2f::operator-=(const vector2f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	auto result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data.m_base;
#endif
	return *this;
}

vector2f& vector2f::operator-=(const base_vec2_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat2(&data);
	auto result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data;
#endif
	return *this;
}

vector2f& vector2f::operator*=(const vector2f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	auto result = DirectX::XMVectorMultiply(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif
	return *this;
}

vector2f& vector2f::operator*=(const base_vec2_t& data) noexcept
{
	return this->operator*=(vector2f(data));
}

vector2f& vector2f::operator*=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	auto result = DirectX::XMVectorScale(v1, value);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif
	return *this;
}

vector2f& vector2f::operator/=(const vector2f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	auto result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data.m_base;
#endif
	return *this;
}

vector2f& vector2f::operator/=(const base_vec2_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat2(&data);
	auto result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data;
#endif
	return *this;
}

vector2f& vector2f::operator/=(float value) noexcept
{
	return this->operator*=(1.f / value);
}

vector2f& vector2f::operator%=(float value) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, value);
	this->m_base.y = std::fmod(this->m_base.y, value);
	return *this;
}

vector2f& vector2f::operator%=(const vector2f& data) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, data.x());
	this->m_base.y = std::fmod(this->m_base.y, data.y());
	return *this;
}

vector2f vector2f::operator+() const noexcept
{
	return *this;
}
vector2f vector2f::operator-() const noexcept
{
	return vector2f(-this->m_base.x, -this->m_base.y);
}

bool vector2f::operator==(const vector2f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;

	return DirectX::XMVector2Equal(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#endif
}

bool vector2f::operator!=(const vector2f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;

	return DirectX::XMVector2NotEqual(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#endif
}

float vector2f::operator[](unsigned char index) const
{
	KOTEK_ASSERT(
		index != unsigned char(-1),
		"out of range (probably you passed a negative number)"
	);
	KOTEK_ASSERT(index <= 1, "out of range");

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

float& vector2f::operator[](unsigned char index)
{
	KOTEK_ASSERT(
		index != unsigned char(-1),
		"out of range (probably you passed a negative number)"
	);
	KOTEK_ASSERT(index <= 1, "out of range");

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
vector2f::operator DirectX::XMVECTOR() const noexcept
{
	return DirectX::XMLoadFloat2(&this->m_base);
}
#endif

const float* vector2f::data(void) const noexcept
{
	return &this->m_base.x;
}
float* vector2f::data(void) noexcept
{
	return &this->m_base.x;
}

void vector2f::set(float x, float y)
{
	this->m_base.x = x;
	this->m_base.y = y;
}

vector2f& vector2f::Set_Base(const base_vec2_t& data) noexcept
{
	this->m_base = data;
	return *this;
}

base_vec2_t& vector2f::Get_Base(void) noexcept
{
	return this->m_base;
}

const base_vec2_t& vector2f::Get_Base(void) const noexcept
{
	return this->m_base;
}

float vector2f::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->operator[](row_id);
}

float&
vector2f::e(math_id_t column_id, math_id_t row_id) noexcept
{
	return this->operator[](row_id);
}

vectornf_view_t vector2f::c(math_id_t column_id) noexcept
{
	return vectornf_view_t(this->data(), 2);
}

vectornf_const_view_t vector2f::c(math_id_t column_id
) const noexcept
{
	return vectornf_const_view_t(this->data(), 2);
}

constexpr math_id_t vector2f::size_of(void) noexcept
{
	static_assert(
		sizeof(float[2]) == sizeof(m_base),
		"gurantee that float[2] will be your class"
	);

	return static_cast<math_id_t>(sizeof(float[2]));
}

constexpr math_id_t vector2f::get_column_count(void
) const noexcept
{
	return 1;
}

constexpr math_id_t vector2f::get_row_count(void) const noexcept
{
	return 2;
}

float vector2f::x(void) const noexcept
{
	return this->m_base.x;
}

float& vector2f::x(void) noexcept 
{
	return this->m_base.x;
}

float vector2f::y(void) const noexcept 
{
	return this->m_base.y;
}

float& vector2f::y(void) noexcept 
{
	return this->m_base.y;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK