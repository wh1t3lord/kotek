#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_vectornf_view.h"
#include "../include/kotek_std_math_vectornf_const_view.h"
#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"

#include "../include/kotek_std_math_functions_vector.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

vector4f::vector4f(float x, float y, float z, float w) :
	m_base(x, y, z, w)
{
}
vector4f::vector4f(float* p_arr4, math_id_t size)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	#error todo: impl
#else
	if (p_arr4)
	{
		KOTEK_ASSERT(size == 4, "wrong dimension");

		if (size == 4)
		{
			this->m_base.x = p_arr4[0];
			this->m_base.y = p_arr4[1];
			this->m_base.z = p_arr4[2];
			this->m_base.w = p_arr4[3];
		}
		else
		{
			this->m_base.x = 0.0f;
			this->m_base.y = 0.0f;
			this->m_base.z = 0.0f;
			this->m_base.w = 0.0f;
		}
	}
	else
	{
		this->m_base.x = 0.0f;
		this->m_base.y = 0.0f;
		this->m_base.z = 0.0f;
		this->m_base.w = 0.0f;
	}
#endif
}
vector4f::vector4f(const float* p_arr4, math_id_t size)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING

#else
	if (p_arr4)
	{
		KOTEK_ASSERT(size == 4, "wrong dimension");

		if (size == 4)
		{
			this->m_base.x = p_arr4[0];
			this->m_base.y = p_arr4[1];
			this->m_base.z = p_arr4[2];
			this->m_base.w = p_arr4[3];
		}
		else
		{
			this->m_base.x = 0.0f;
			this->m_base.y = 0.0f;
			this->m_base.z = 0.0f;
			this->m_base.w = 0.0f;
		}
	}
	else
	{
		this->m_base.x = 0.0f;
		this->m_base.y = 0.0f;
		this->m_base.z = 0.0f;
		this->m_base.w = 0.0f;
	}
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector4f::vector4f(float x) : m_base(x, 0.0f, 0.0f, 0.0f) {}
vector4f::vector4f(float x, float y) : m_base(x, y, 0.0f, 0.0f)
{
}
vector4f::vector4f(float x, float y, float z) :
	m_base(x, y, z, 0.0f)
{
}

vector4f::vector4f(const vector1f& data) :
	m_base(get_math_component_x(data), 0.0f, 0.0f, 0.0f)
{
}

vector4f::vector4f(const vector1f& data, float y) :
	m_base(get_math_component_x(data), y, 0.0f, 0.0f)
{
}

vector4f::vector4f(const vector1f& data, float y, float z) :
	m_base(get_math_component_x(data), y, z, 0.0f)
{
}

vector4f::vector4f(
	const vector1f& data, float y, float z, float w
) : m_base(get_math_component_x(data), y, z, w)
{
}

vector4f::vector4f(const vector2f& data) :
	m_base(
		get_math_component_x(data),
		get_math_component_y(data),
		0.0f,
		0.0f
	)
{
}

vector4f::vector4f(const vector2f& data, float z) :
	m_base(
		get_math_component_x(data),
		get_math_component_y(data),
		z,
		0.0f
	)
{
}

vector4f::vector4f(const vector2f& data, float z, float w) :
	m_base(
		get_math_component_x(data),
		get_math_component_y(data),
		z,
		w
	)
{
}

vector4f::vector4f(const vector3f& data) :
	m_base(
		get_math_component_x(data),
		get_math_component_y(data),
		get_math_component_z(data),
		0.0f
	)
{
}

vector4f::vector4f(const vector3f& data, float w) :
	m_base(
		get_math_component_x(data),
		get_math_component_y(data),
		get_math_component_z(data),
		w
	)
{
}
#endif

vector4f::vector4f(const base_vec4_t& data) : m_base(data) {}
vector4f::vector4f(const vector4f& data) : m_base(data.m_base)
{
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
vector4f::vector4f(const DirectX::XMVECTOR& vec)
{
	DirectX::XMStoreFloat4(&this->m_base, vec);
}
#endif

vector4f::vector4f(void) : m_base(0.0f, 0.0f, 0.0f, 0.0f) {}

vector4f& vector4f::operator=(const vector4f& data) noexcept
{
	this->m_base = data.m_base;
	return *this;
}

vector4f& vector4f::operator+=(const vector4f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	DirectX::XMVECTOR v2 = data;
	auto result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data.m_base;
#endif
	return *this;
}

vector4f& vector4f::operator+=(const base_vec4_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	DirectX::XMVECTOR v2 = DirectX::XMLoadFloat4(&data);
	auto result = DirectX::XMVectorAdd(v1, v2);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data;
#endif
	return *this;
}

vector4f& vector4f::operator-=(const vector4f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	auto result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data.m_base;
#endif
	return *this;
}

vector4f& vector4f::operator-=(const base_vec4_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat4(&data);
	auto result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data;
#endif
	return *this;
}

vector4f& vector4f::operator*=(const vector4f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	auto result = DirectX::XMVectorMultiply(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif
	return *this;
}

vector4f& vector4f::operator*=(const base_vec4_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat4(&data);
	auto result = DirectX::XMVectorMultiply(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data;
#endif
	return *this;
}

vector4f& vector4f::operator*=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = *this;
	auto result = DirectX::XMVectorScale(v1, value);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif
	return *this;
}

vector4f& vector4f::operator/=(const vector4f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;
	auto result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data.m_base;
#endif
	return *this;
}

vector4f& vector4f::operator/=(const base_vec4_t& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument =
		DirectX::XMLoadFloat4(&data);
	auto result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data;
#endif
	return *this;
}

vector4f& vector4f::operator/=(float value) noexcept
{
	return this->operator*=(1.f / value);
}

vector4f& vector4f::operator%=(float value) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, value);
	this->m_base.y = std::fmod(this->m_base.y, value);
	this->m_base.z = std::fmod(this->m_base.z, value);
	this->m_base.w = std::fmod(this->m_base.w, value);

	return *this;
}

vector4f& vector4f::operator%=(const vector4f& data) noexcept
{
	this->m_base.x = std::fmod(this->m_base.x, data.x());
	this->m_base.y = std::fmod(this->m_base.y, data.y());
	this->m_base.z = std::fmod(this->m_base.z, data.z());
	this->m_base.w = std::fmod(this->m_base.w, data.w());

	return *this;
}

vector4f vector4f::operator+() const noexcept
{
	return *this;
}

vector4f vector4f::operator-() const noexcept
{
	return vector4f(
		-this->m_base.x,
		-this->m_base.y,
		-this->m_base.z,
		-this->m_base.w
	);
}

bool vector4f::operator==(const vector4f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;

	return DirectX::XMVector4Equal(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#endif
}

bool vector4f::operator!=(const vector4f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_original = *this;
	DirectX::XMVECTOR casted_argument = data;

	return DirectX::XMVector4NotEqual(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#endif
}

float vector4f::operator[](unsigned char index) const
{
	KOTEK_ASSERT(
		index != unsigned char(-1),
		"out of range (probably you passed a negative value)"
	);
	KOTEK_ASSERT(index <= 3, "out of range");

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

float& vector4f::operator[](unsigned char index)
{
	KOTEK_ASSERT(
		index != unsigned char(-1),
		"out of range (probably you passed a negative value)"
	);
	KOTEK_ASSERT(index <= 3, "out of range");

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
vector4f::operator DirectX::XMVECTOR() const noexcept
{
	return DirectX::XMLoadFloat4(&this->m_base);
}
#endif

const float* vector4f::data(void) const noexcept
{
	return &this->m_base.x;
}
float* vector4f::data(void) noexcept
{
	return &this->m_base.x;
}

void vector4f::set(float x, float y, float z, float w)
{
	this->m_base.x = x;
	this->m_base.y = y;
	this->m_base.z = z;
	this->m_base.w = w;
}

vector4f& vector4f::Set_Base(const base_vec4_t& data) noexcept
{
	this->m_base = data;
	return *this;
}

base_vec4_t& vector4f::Get_Base(void) noexcept
{
	return this->m_base;
}

const base_vec4_t& vector4f::Get_Base(void) const noexcept
{
	return this->m_base;
}

float vector4f::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->operator[](row_id);
}

float&
vector4f::e(math_id_t column_id, math_id_t row_id) noexcept
{
	return this->operator[](row_id);
}

vectornf_view_t vector4f::c(math_id_t column_id) noexcept
{
	return vectornf_view_t(this->data(), 4);
}

vectornf_const_view_t vector4f::c(math_id_t column_id
) const noexcept
{
	return vectornf_const_view_t(this->data(), 4);
}

constexpr math_id_t vector4f::size_of(void) noexcept
{
	static_assert(
		sizeof(float[4]) == sizeof(m_base),
		"gurantee that your class will be equal to float[4]"
	);

	return static_cast<math_id_t>(sizeof(float[4]));
}

constexpr math_id_t vector4f::get_column_count(void
) const noexcept
{
	return 1;
}

constexpr math_id_t vector4f::get_row_count(void) const noexcept
{
	return 4;
}

float vector4f::x(void) const noexcept
{
	return this->m_base.x;
}

float& vector4f::x(void) noexcept
{
	return this->m_base.x;
}

float vector4f::y(void) const noexcept
{
	return this->m_base.y;
}

float& vector4f::y(void) noexcept
{
	return this->m_base.y;
}

float vector4f::z(void) const noexcept
{
	return this->m_base.z;
}

float& vector4f::z(void) noexcept
{
	return this->m_base.z;
}

float vector4f::w(void) const noexcept
{
	return this->m_base.w;
}

float& vector4f::w(void) noexcept
{
	return this->m_base.w;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK