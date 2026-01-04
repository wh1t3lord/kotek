#include "../include/kotek_std_math_vector1f.h"

#include "../include/kotek_std_math_vectornf_view.h"
#include "../include/kotek_std_math_vectornf_const_view.h"
#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_functions_vector.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

vector1f::vector1f(void) : m_base(0.0f) {}
vector1f::vector1f(float x) : m_base(x) {}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f::vector1f(float x, float y) : m_base(x) {}
vector1f::vector1f(float x, float y, float z) : m_base(x) {}
vector1f::vector1f(float x, float y, float z, float w) :
	m_base(x)
{
}
#endif

vector1f::vector1f(float* p_arr1, math_id_t element_count) :
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	m_base(p_arr1 ? p_arr1[0] : 0.0f)
#else
	m_base(
		p_arr1 ? element_count == 1 ? p_arr1[0] : 0.0f : 0.0f
	)
#endif
{
#ifndef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	KOTEK_ASSERT(
		element_count == 1,
		"implicit casting is not enabled it means you must "
		"provide same dimension math objects!"
	);
#endif
}

vector1f::vector1f(
	const float* p_arr1, math_id_t element_count
) :
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	m_base(p_arr1 ? p_arr1[0] : 0.0f)
#else
	m_base(
		p_arr1 ? element_count == 1 ? p_arr1[0] : 0.0f : 0.0f
	)
#endif
{
#ifndef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	KOTEK_ASSERT(
		element_count == 1,
		"implicit casting is not enabled it means you must "
		"provide same dimension math objects!"
	);
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f::vector1f(const vector2f& data) :
	m_base(get_math_component_x(data))
{
}

vector1f::vector1f(const vector3f& data) :
	m_base(get_math_component_x(data))
{
}

vector1f::vector1f(const vector4f& data) :
	m_base(get_math_component_x(data))
{
}
#endif

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f::vector1f(const base_vec1_t& data) : m_base(data) {}
#endif

vector1f::vector1f(const vector1f& data) : m_base(data.m_base)
{
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f::vector1f(const matrixnf_view_t& view) {}

vector1f::vector1f(const matrixnf_const_view_t& view) {}
#endif

vector1f::vector1f(const vectornf_view_t& view)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	#error todo: impl
#else

	KOTEK_ASSERT(view.data(), "not initialized or corrupted");
	KOTEK_ASSERT(
		view.get_row_count() == get_row_count(),
		"wrong dimension"
	);

	if (view.data())
	{
		if (view.get_row_count() == get_row_count())
		{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			this->m_base = view.x();
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base.x = view.x();
	#endif
		}
	}
#endif
}

vector1f::vector1f(const vectornf_const_view_t& view)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	#error todo: impl
#else

	KOTEK_ASSERT(view.data(), "not initialized or corrupted");
	KOTEK_ASSERT(
		view.get_row_count() == get_row_count(),
		"wrong dimension"
	);

	if (view.data())
	{
		if (view.get_row_count() == get_row_count())
		{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			this->m_base = view.x();
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base.x = view.x();
	#endif
		}
	}
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f::vector1f(const matrix2x2f& data) {}

vector1f::vector1f(const matrix3x3f& data) {}

vector1f::vector1f(const matrix4x4f& data) {}
#endif

vector1f& vector1f::operator=(const vector1f& data)
{
	this->m_base = data.m_base;
	return *this;
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator=(const matrixnf_view_t& data)
{
	return this->operator=(
		vector1f(get_math_component_x(data.c(0)))
	);
}

vector1f& vector1f::operator=(const matrixnf_const_view_t& data)
{
	return this->operator=(
		vector1f(get_math_component_x(data.c(0)))
	);
}
#endif

vector1f& vector1f::operator=(const vectornf_view_t& data)
{
	return this->operator=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator=(const vectornf_const_view_t& data)
{
	return this->operator=(vector1f(get_math_component_x(data))
	);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator=(const vector2f& data)
{
	return this->operator=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator=(const vector3f& data)
{
	return this->operator=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator=(const vector4f& data)
{
	return this->operator=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator=(const matrix2x2f& data) {}

vector1f& vector1f::operator=(const matrix3x3f& data) {}

vector1f& vector1f::operator=(const matrix4x4f& data) {}
#endif

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

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& vector1f::operator+=(const base_vec1_t& data)
{
	this->m_base += data;
	return *this;
}

#endif

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator+=(const matrixnf_view_t& view)
{
	return this->operator+=(
		vector1f(get_math_component_x(view.c(0)))
	);
}

vector1f& vector1f::operator+=(const matrixnf_const_view_t& view
)
{
	return this->operator+=(
		vector1f(get_math_component_x(view.c(0)))
	);
}
#endif

vector1f& vector1f::operator+=(const vectornf_view_t& view)
{
	return this->operator+=(vector1f(get_math_component_x(view))
	);
}

vector1f& vector1f::operator+=(const vectornf_const_view_t& view
)
{
	return this->operator+=(vector1f(get_math_component_x(view))
	);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator+=(const vector2f& data)
{
	return this->operator+=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator+=(const vector3f& data)
{
	return this->operator+=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator+=(const vector4f& data)
{
	return this->operator+=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator+=(const matrix2x2f& data) {}

vector1f& vector1f::operator+=(const matrix3x3f& data) {}

vector1f& vector1f::operator+=(const matrix4x4f& data) {}
#endif

vector1f& vector1f::operator-=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&value);
	auto result = DirectX::XMVectorSubtract(
		casted_original, casted_argument
	);

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

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& vector1f::operator-=(const base_vec1_t& data)
{
	this->m_base -= data;
	return *this;
}
#endif

vector1f& vector1f::operator*=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto result =
		DirectX::XMVectorScale(casted_original, value);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif
	return *this;
}

vector1f& vector1f::operator*=(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);
	auto result = DirectX::XMVectorMultiply(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif
	return *this;
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator*=(const matrixnf_view_t& view)
{
	return this->operator*=(
		vector1f(get_math_component_x(view.c(0)))
	);
}

vector1f& vector1f::operator*=(const matrixnf_const_view_t& view
)
{
	return this->operator*=(
		vector1f(get_math_component_x(view.c(0)))
	);
}
#endif

vector1f& vector1f::operator*=(const vectornf_view_t& view)
{
	return this->operator*=(vector1f(get_math_component_x(view))
	);
}

vector1f& vector1f::operator*=(const vectornf_const_view_t& view
)
{
	return this->operator*=(vector1f(get_math_component_x(view))
	);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator*=(const vector2f& data)
{
	return this->operator*=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator*=(const vector3f& data)
{
	return this->operator*=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator*=(const vector4f& data)
{
	return this->operator*=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator*=(const matrix3x3f& data) {}

vector1f& vector1f::operator*=(const matrix2x2f& data) {}

vector1f& vector1f::operator*=(const matrix4x4f& data) {}

#endif

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
vector1f& vector1f::operator*=(const base_vec1_t& data)
{
	this->m_base *= data;
	return *this;
}
#endif

vector1f& vector1f::operator/=(float value)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	KOTEK_ASSERT(
		value != 0.0f, "you can't divide if you have zero!!!"
	);

	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto result =
		DirectX::XMVectorScale(casted_original, 1.f / value);
	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= value;
#endif
	return *this;
}

vector1f& vector1f::operator/=(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);
	auto result = DirectX::XMVectorDivide(
		casted_original, casted_argument
	);

	DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= data.m_base;
#endif
	return *this;
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator/=(const matrixnf_view_t& view)
{
	return this->operator/=(
		vector1f(get_math_component_x(view.c(0)))
	);
}

vector1f& vector1f::operator/=(const matrixnf_const_view_t& view
)
{
	return this->operator/=(
		vector1f(get_math_component_x(view.c(0)))
	);
}
#endif

vector1f& vector1f::operator/=(const vectornf_const_view_t& view
)
{
	return this->operator/=(vector1f(get_math_component_x(view))
	);
}

vector1f& vector1f::operator/=(const vectornf_view_t& view)
{
	return this->operator/=(vector1f(get_math_component_x(view))
	);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator/=(const matrix2x2f& data) {}

vector1f& vector1f::operator/=(const matrix3x3f& data) {}

vector1f& vector1f::operator/=(const matrix4x4f& data) {}

vector1f& vector1f::operator/=(const vector2f& data)
{
	return this->operator/=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator/=(const vector3f& data)
{
	return this->operator/=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator/=(const vector4f& data)
{
	return this->operator/=(vector1f(get_math_component_x(data))
	);
}
#endif

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

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator%=(const vector2f& data) noexcept
{
	return this->operator%=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator%=(const vector3f& data) noexcept
{
	return this->operator%=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator%=(const vector4f& data) noexcept
{
	return this->operator%=(vector1f(get_math_component_x(data))
	);
}
#endif

vector1f& vector1f::operator%=(const vectornf_view_t& view
) noexcept
{
	return this->operator%=(vector1f(get_math_component_x(view))
	);
}

vector1f& vector1f::operator%=(const vectornf_const_view_t& view
) noexcept
{
	return this->operator%=(vector1f(get_math_component_x(view))
	);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator%=(const matrixnf_view_t& view
) noexcept
{
	return this->operator%=(
		vector1f(get_math_component_x(view.c(0)))
	);
}

vector1f& vector1f::operator%=(const matrixnf_const_view_t& view
) noexcept
{
	return this->operator%=(
		vector1f(get_math_component_x(view.c(0)))
	);
}

vector1f& vector1f::operator%=(const matrix2x2f& data) noexcept
{
}

vector1f& vector1f::operator%=(const matrix3x3f& data) noexcept
{
}

vector1f& vector1f::operator%=(const matrix4x4f& data) noexcept
{
}
#endif

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

	return DirectX::XMVector2Equal(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
bool vector1f::operator==(const vector2f& data) const noexcept
{
}

bool vector1f::operator==(const vector3f& data) const noexcept
{
}

bool vector1f::operator==(const vector4f& data) const noexcept
{
}
#endif

bool vector1f::operator==(const vectornf_view_t& view
) const noexcept
{
}

bool vector1f::operator==(const vectornf_const_view_t& view
) const noexcept
{
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
bool vector1f::operator==(const matrixnf_view_t& view
) const noexcept
{
}

bool vector1f::operator==(const matrixnf_const_view_t& view
) const noexcept
{
}

bool vector1f::operator==(const matrix2x2f& data) const noexcept
{
}

bool vector1f::operator==(const matrix3x3f& data) const noexcept
{
}

bool vector1f::operator==(const matrix4x4f& data) const noexcept
{
}
#endif

bool vector1f::operator!=(const vector1f& data) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto casted_original = DirectX::XMLoadFloat(&this->m_base);
	auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

	return DirectX::XMVector2NotEqual(
		casted_original, casted_argument
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
bool vector1f::operator!=(const vector2f& data) const noexcept
{
}

bool vector1f::operator!=(const vector3f& data) const noexcept
{
}

bool vector1f::operator!=(const vector4f& data) const noexcept
{
}
#endif

bool vector1f::operator!=(const vectornf_view_t& view
) const noexcept
{
}

bool vector1f::operator!=(const vectornf_const_view_t& view
) const noexcept
{
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
bool vector1f::operator!=(const matrixnf_view_t& view
) const noexcept
{
}

bool vector1f::operator!=(const matrixnf_const_view_t& view
) const noexcept
{
}

bool vector1f::operator!=(const matrix2x2f& data) const noexcept
{
}

bool vector1f::operator!=(const matrix3x3f& data) const noexcept
{
}

bool vector1f::operator!=(const matrix4x4f& data) const noexcept
{
}
#endif

float vector1f::operator[](math_id_t index) const
{
	KOTEK_ASSERT(index == 0, "out of range");

	if (index > 0)
		index = 0;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float const* p_array =
		reinterpret_cast<float const*>(&this->m_base);

	return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base[index];
#endif
}

float& vector1f::operator[](math_id_t index)
{
	KOTEK_ASSERT(index == 0, "out of range");

	if (index > 0)
		index = 0;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float* p_array = reinterpret_cast<float*>(&this->m_base);
	return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base[index];
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
vector1f::operator DirectX::XMVECTOR() const noexcept
{
	return DirectX::XMLoadFloat(&this->m_base);
}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

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

void vector1f::set(float x) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	this->m_base = x;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base.x = x;
#else
	#error todo: provide implementation
#endif
}

constexpr math_id_t vector1f::size_of(void) noexcept
{
	static_assert(
		sizeof(float[1]) == sizeof(m_base) &&
		"we gurantee that base type is float[1] by size"
	);
	return sizeof(float[1]);
}

constexpr math_id_t vector1f::get_column_count(void
) const noexcept
{
	return 1;
}

constexpr math_id_t vector1f::get_row_count(void) const noexcept
{
	return 1;
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

float vector1f::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->operator[](row_id);
}

float&
vector1f::e(math_id_t column_id, math_id_t row_id) noexcept
{
	return this->operator[](row_id);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator-=(const matrixnf_const_view_t& view
)
{
	return this->operator-=(
		vector1f(get_math_component_x(view.c(0)))
	);
}

vector1f& vector1f::operator-=(const matrixnf_view_t& view)
{
	return this->operator-=(
		vector1f(get_math_component_x(view.c(0)))
	);
}
#endif

vectornf_view_t vector1f::c(math_id_t column_id) noexcept
{
	return vectornf_view_t(this->data(), 1);
}

vectornf_const_view_t vector1f::c(math_id_t column_id
) const noexcept
{
	return vectornf_const_view_t(this->data(), 1);
}

vector1f& vector1f::operator-=(const vectornf_view_t& view)
{
	return this->operator-=(vector1f(get_math_component_x(view))
	);
}

vector1f& vector1f::operator-=(const vectornf_const_view_t& view
)
{
	return this->operator-=(vector1f(get_math_component_x(view))
	);
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
vector1f& vector1f::operator-=(const vector2f& data)
{
	return this->operator-=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator-=(const vector3f& data)
{
	return this->operator-=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator-=(const vector4f& data)
{
	return this->operator-=(vector1f(get_math_component_x(data))
	);
}

vector1f& vector1f::operator-=(const matrix2x2f& data) {}

vector1f& vector1f::operator-=(const matrix3x3f& data) {}

vector1f& vector1f::operator-=(const matrix4x4f& data) {}

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

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK KOTEK_END_NAMESPACE_KOTEK