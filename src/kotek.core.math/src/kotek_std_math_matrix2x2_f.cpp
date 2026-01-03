#include "../include/kotek_std_math_matrix_2x2_f.h"

#include "../include/kotek_std_math_matrix_3x3_f.h"
#include "../include/kotek_std_math_matrix_4x4_f.h"

#include "../include/kotek_std_math_vectornf_view.h"
#include "../include/kotek_std_math_vectornf_const_view.h"
#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_functions_vector.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
matrix2x2f::matrix2x2f(
	float c0r0, float c0r1, float c1r0, float c1r1
) : m_base{c0r0, c0r1, c1r0, c1r1}
{
}
#endif

matrix2x2f::matrix2x2f(const base_mat2x2_t& data) : m_base{data}
{
}

matrix2x2f::matrix2x2f(const matrix2x2f& data) :
	m_base{data.m_base}
{
}

matrix2x2f::matrix2x2f(void) : m_base{} {}

matrix2x2f& matrix2x2f::operator=(const matrix2x2f& data)
{
	this->m_base = data.m_base;
	return *this;
}

matrix2x2f& matrix2x2f::operator=(const base_mat2x2_t& data)
{
	this->m_base = data;
	return *this;
}

matrix2x2f& matrix2x2f::operator+=(const matrix2x2f& data
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._21
		)
	);

	row_original_0 =
		DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 =
		DirectX::XMVectorAdd(row_original_1, row_argument_1);

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
		row_original_1
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data.m_base;
#endif
	return *this;
}

matrix2x2f& matrix2x2f::operator+=(const base_mat2x2_t& data
) noexcept
{
	return this->operator+=(data);
}

matrix2x2f& matrix2x2f::operator-=(const matrix2x2f& data
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._21
		)
	);

	row_original_0 = DirectX::XMVectorSubtract(
		row_original_0, row_argument_0
	);
	row_original_1 = DirectX::XMVectorSubtract(
		row_original_1, row_argument_1
	);

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
		row_original_1
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data.m_base;
#endif
	return *this;
}

matrix2x2f& matrix2x2f::operator-=(const base_mat2x2_t& data
) noexcept
{
	return this->operator-=(data);
}

matrix2x2f& matrix2x2f::operator*=(const matrix2x2f& data
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX m1 = *this;
	DirectX::XMMATRIX m2 = data;

	auto result = DirectX::XMMatrixMultiply(m1, m2);

	DirectX::XMStoreFloat3x3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif

	return *this;
}

matrix2x2f& matrix2x2f::operator*=(const base_mat2x2_t& data
) noexcept
{
	return this->operator*=(data);
}

matrix2x2f& matrix2x2f::operator*=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, value);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, value);

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
		row_original_1
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif

	return *this;
}

matrix2x2f& matrix2x2f::operator/=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);

	float factor = 1.f / value;

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, factor);

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
		row_original_1
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= value;
#endif

	return *this;
}

// TODO: provide preprocessor for user implementation here
// like
// KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
matrix2x2f& matrix2x2f::operator/=(const matrix2x2f& data) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix2x2f&
matrix2x2f::operator/=(const matrix3x3f& data) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix2x2f&
matrix2x2f::operator/=(const matrix4x4f& data) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix2x2f&
matrix2x2f::operator/=(const vector2f& data) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix2x2f&
matrix2x2f::operator/=(const vector3f& data) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix2x2f&
matrix2x2f::operator/=(const vector4f& data) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix2x2f& matrix2x2f::operator/=(const vector1f& vec) noexcept
{
	return this->operator/=(get_math_component_x(vec));
}

matrix2x2f matrix2x2f::operator+() const noexcept
{
	return *this;
}

matrix2x2f matrix2x2f::operator-() const noexcept
{
	matrix2x2f result;
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);

	row_original_0 = DirectX::XMVectorNegate(row_original_0);
	row_original_1 = DirectX::XMVectorNegate(row_original_1);

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&result.m_base._11
	    ),
		row_original_0
	);

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&result.m_base._21
	    ),
		row_original_1
	);

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	result = -this->m_base;
#endif
	return result;
}

bool matrix2x2f::operator==(const matrix2x2f& data
) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._31
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._21
		)
	);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._31
		)
	);

	bool is_equal_0 =
		DirectX::XMVector3Equal(row_original_0, row_argument_0);
	bool is_equal_1 =
		DirectX::XMVector3Equal(row_original_1, row_argument_1);
	bool is_equal_2 =
		DirectX::XMVector3Equal(row_original_2, row_argument_2);

	return (is_equal_0 && is_equal_1 && is_equal_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#else
	#error Unknown math library
#endif
}

bool matrix2x2f::operator!=(const matrix2x2f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&this->m_base._31
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._21
		)
	);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&data.m_base._31
		)
	);

	bool is_equal_0 = DirectX::XMVector3NotEqual(
		row_original_0, row_argument_0
	);
	bool is_equal_1 = DirectX::XMVector3NotEqual(
		row_original_1, row_argument_1
	);
	bool is_equal_2 = DirectX::XMVector3NotEqual(
		row_original_2, row_argument_2
	);

	return (is_equal_0 || is_equal_1 || is_equal_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#else
	#error Unknown math library
#endif
}

constexpr math_id_t matrix2x2f::size_of(void) const noexcept
{
	static_assert(
		sizeof(float[2][2]) == sizeof(m_base) &&
		"we gurantee that base type is equal to "
		"float[2][2] by size"
	);
	return static_cast<math_id_t>(sizeof(float[2][2]));
}

constexpr math_id_t matrix2x2f::get_column_count(void
) const noexcept
{
	return static_cast<math_id_t>(2);
}

constexpr math_id_t matrix2x2f::get_row_count(void
) const noexcept
{
	return static_cast<math_id_t>(2);
}

matrix2x2f& matrix2x2f::Set_Base(const base_mat2x2_t& data
) noexcept
{
	this->m_base = data;
	return *this;
}

base_mat2x2_t& matrix2x2f::Get_Base(void) noexcept
{
	return this->m_base;
}
const base_mat2x2_t& matrix2x2f::Get_Base(void) const noexcept
{
	return this->m_base;
}

float matrix2x2f::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	KOTEK_ASSERT(
		column_id >= this->get_column_count(), "out-of-range"
	);
	KOTEK_ASSERT(
		row_id >= this->get_row_count(), "out-of-range"
	);

	if (column_id >= this->get_column_count())
		column_id = this->get_column_count() - 1;

	if (row_id >= this->get_row_count())
		row_id = this->get_row_count() - 1;

	return this->m_base[column_id][row_id];
}

float& matrix2x2f::e(
	math_id_t column_id, math_id_t row_id
) noexcept
{
	KOTEK_ASSERT(
		column_id >= this->get_column_count(), "out-of-range"
	);
	KOTEK_ASSERT(
		row_id >= this->get_row_count(), "out-of-range"
	);

	if (column_id >= this->get_column_count())
		column_id = this->get_column_count() - 1;

	if (row_id >= this->get_row_count())
		row_id = this->get_row_count() - 1;

	return this->m_base[column_id][row_id];
}

vectornf_view_t matrix2x2f::c(math_id_t column_id) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	KOTEK_ASSERT(
		column_id >= this->get_column_count(), "out-of-range"
	);

	if (column_id >= this->get_column_count())
		column_id = this->get_column_count() - 1;

	return vectornf_view_t(
		&this->m_base[column_id].x, this->get_row_count()
	);
#endif
}

vectornf_const_view_t matrix2x2f::c(math_id_t column_id
) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	KOTEK_ASSERT(
		column_id >= this->get_column_count(), "out-of-range"
	);

	if (column_id >= this->get_column_count())
		column_id = this->get_column_count() - 1;

	return vectornf_const_view_t(
		&this->m_base[column_id].x, this->get_row_count()
	);
#endif
}

const float* matrix2x2f::data(void) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(this->m_base);
#endif
}

float* matrix2x2f::data(void) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(this->m_base);
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK