#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class matrix2x2f
			{
			public:
#pragma region Constructors
				matrix2x2f(base_decimal_t m00, base_decimal_t m01,
					base_decimal_t m10, base_decimal_t m11) :
					m_base(m00, m01, {}, m10, m11, {}, {}, {}, {})
				{
				}
				matrix2x2f(const base_mat2x2_t& data) : m_base(data) {}
				matrix2x2f(const matrix2x2f& data) : m_base(data.m_base) {}
				matrix2x2f(void) : m_base{} {}
#pragma endregion

				~matrix2x2f(void) = default;

#pragma region Assignment operators
				matrix2x2f& operator=(const matrix2x2f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				matrix2x2f& operator=(const base_mat2x2_t& data)
				{
					this->m_base = data;
					return *this;
				}

				matrix2x2f& operator+=(const matrix2x2f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._21));

					row_original_0 =
						DirectX::XMVectorAdd(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorAdd(row_original_1, row_argument_1);

					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
						row_original_1);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix2x2f& operator+=(const base_mat2x2_t& data) noexcept
				{
					return this->operator+=(data);
				}

				matrix2x2f& operator-=(const matrix2x2f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._21));

					row_original_0 = DirectX::XMVectorSubtract(
						row_original_0, row_argument_0);
					row_original_1 = DirectX::XMVectorSubtract(
						row_original_1, row_argument_1);

					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
						row_original_1);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix2x2f& operator-=(const base_mat2x2_t& data) noexcept
				{
					return this->operator-=(data);
				}

				matrix2x2f& operator*=(const matrix2x2f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMMATRIX m1 = *this;
					DirectX::XMMATRIX m2 = data;

					auto result = DirectX::XMMatrixMultiply(m1, m2);

					DirectX::XMStoreFloat3x3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}

				matrix2x2f& operator*=(const base_mat2x2_t& data) noexcept
				{
					return this->operator*=(data);
				}

				matrix2x2f& operator*=(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));

					row_original_0 =
						DirectX::XMVectorScale(row_original_0, value);
					row_original_1 =
						DirectX::XMVectorScale(row_original_1, value);

					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
						row_original_1);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}

				matrix2x2f& operator/=(const matrix2x2f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._21));

					row_original_0 =
						DirectX::XMVectorDivide(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorDivide(row_original_1, row_argument_1);

					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
						row_original_1);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix2x2f& operator/=(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));

					base_decimal_t factor = 1.f / value;

					row_original_0 =
						DirectX::XMVectorScale(row_original_0, factor);
					row_original_1 =
						DirectX::XMVectorScale(row_original_1, factor);

					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat2(
						reinterpret_cast<DirectX::XMFLOAT2*>(&this->m_base._21),
						row_original_1);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}
#pragma endregion

#pragma region Unary operators
				matrix2x2f operator+() const noexcept { return *this; }

				matrix2x2f operator-() const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));

					row_original_0 = DirectX::XMVectorNegate(row_original_0);
					row_original_1 = DirectX::XMVectorNegate(row_original_1);

					matrix2x2f result;

					DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
											   &result.m_base._11),
						row_original_0);

					DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
											   &result.m_base._21),
						row_original_1);

					return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}
#pragma endregion

#pragma region Comparison operators
				bool operator==(const matrix2x2f& data) const noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._31));

					bool is_equal_0 =
						DirectX::XMVector3Equal(row_original_0, row_argument_0);
					bool is_equal_1 =
						DirectX::XMVector3Equal(row_original_1, row_argument_1);
					bool is_equal_2 =
						DirectX::XMVector3Equal(row_original_2, row_argument_2);

					return (is_equal_0 && is_equal_1 && is_equal_2);
				}

				bool operator!=(const matrix2x2f& data) noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat2(
						reinterpret_cast<const DirectX::XMFLOAT2*>(
							&data.m_base._31));

					bool is_equal_0 = DirectX::XMVector3NotEqual(
						row_original_0, row_argument_0);
					bool is_equal_1 = DirectX::XMVector3NotEqual(
						row_original_1, row_argument_1);
					bool is_equal_2 = DirectX::XMVector3NotEqual(
						row_original_2, row_argument_2);

					return (is_equal_0 || is_equal_1 || is_equal_2);
				}
#pragma endregion

#pragma region Cast operators
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				operator DirectX::XMMATRIX(void) const noexcept
				{
					return DirectX::XMLoadFloat3x3(&this->m_base);
				}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
#pragma endregion

				base_decimal_t Get_00(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._11;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_01(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._12;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_02(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._13;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_10(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._21;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_11(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._22;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_12(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._23;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_20(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._31;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_21(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._32;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_22(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._33;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				matrix2x2f& Set_00(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._11 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				matrix2x2f& Set_01(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._12 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix2x2f& Set_10(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._21 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix2x2f& Set_11(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._22 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix2x2f& Set_Base(const base_mat2x2_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}

				base_mat2x2_t& Get_Base(void) noexcept { return this->m_base; }
				const base_mat2x2_t& Get_Base(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_mat2x2_t m_base;
			};

#pragma region Binary operators
			inline matrix2x2f operator+(
				const matrix2x2f& left, const matrix2x2f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT2 left_row_0 = {left.Get_00(), left.Get_01()};
				DirectX::XMFLOAT2 left_row_1 = {left.Get_10(), left.Get_11()};

				DirectX::XMFLOAT2 right_row_0 = {
					right.Get_00(), right.Get_01()};
				DirectX::XMFLOAT2 right_row_1 = {
					right.Get_10(), right.Get_11()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat2(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat2(&left_row_1);

				DirectX::XMVECTOR row_argument_0 =
					DirectX::XMLoadFloat2(&right_row_0);
				DirectX::XMVECTOR row_argument_1 =
					DirectX::XMLoadFloat2(&right_row_1);

				row_original_0 =
					DirectX::XMVectorAdd(row_original_0, row_argument_0);
				row_original_1 =
					DirectX::XMVectorAdd(row_original_1, row_argument_1);

				matrix2x2f result;

				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._21),
					row_original_1);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix2x2f operator-(
				const matrix2x2f& left, const matrix2x2f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT2 left_row_0 = {left.Get_00(), left.Get_01()};
				DirectX::XMFLOAT2 left_row_1 = {left.Get_10(), left.Get_11()};

				DirectX::XMFLOAT2 right_row_0 = {
					right.Get_00(), right.Get_01()};
				DirectX::XMFLOAT2 right_row_1 = {
					right.Get_10(), right.Get_11()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat2(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat2(&left_row_1);

				DirectX::XMVECTOR row_argument_0 =
					DirectX::XMLoadFloat2(&right_row_0);
				DirectX::XMVECTOR row_argument_1 =
					DirectX::XMLoadFloat2(&right_row_1);

				row_original_0 =
					DirectX::XMVectorSubtract(row_original_0, row_argument_0);
				row_original_1 =
					DirectX::XMVectorSubtract(row_original_1, row_argument_1);

				matrix2x2f result;

				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._21),
					row_original_1);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix2x2f operator*(
				const matrix2x2f& left, const matrix2x2f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMMATRIX m1 = left;
				DirectX::XMMATRIX m2 = right;
				auto temp = DirectX::XMMatrixMultiply(m1, m2);

				matrix2x2f result;
				base_mat3x3_t data;
				DirectX::XMStoreFloat3x3(&data, temp);

				result.Set_Base(data);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix2x2f operator*(
				const matrix2x2f& left, base_decimal_t value) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT2 left_row_0 = {left.Get_00(), left.Get_01()};
				DirectX::XMFLOAT2 left_row_1 = {left.Get_10(), left.Get_11()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat2(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat2(&left_row_1);

				row_original_0 = DirectX::XMVectorScale(row_original_0, value);
				row_original_1 = DirectX::XMVectorScale(row_original_1, value);

				matrix2x2f result;

				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._21),
					row_original_1);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			}

			inline matrix2x2f operator*(
				base_decimal_t value, const matrix2x2f& right) noexcept
			{
				return operator*(right, value);
			}

			inline matrix2x2f operator/(
				const matrix2x2f& left, base_decimal_t value) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT2 left_row_0 = {left.Get_00(), left.Get_01()};
				DirectX::XMFLOAT2 left_row_1 = {left.Get_10(), left.Get_11()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat2(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat2(&left_row_1);

				base_decimal_t factor = 1.f / value;

				row_original_0 = DirectX::XMVectorScale(row_original_0, factor);
				row_original_1 = DirectX::XMVectorScale(row_original_1, factor);

				matrix2x2f result;

				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._21),
					row_original_1);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix2x2f operator/(
				const matrix2x2f& left, const matrix2x2f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT2 left_row_0 = {left.Get_00(), left.Get_01()};
				DirectX::XMFLOAT2 left_row_1 = {left.Get_10(), left.Get_11()};

				DirectX::XMFLOAT2 right_row_0 = {
					right.Get_00(), right.Get_01()};
				DirectX::XMFLOAT2 right_row_1 = {
					right.Get_10(), right.Get_11()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat2(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat2(&left_row_1);

				DirectX::XMVECTOR row_argument_0 =
					DirectX::XMLoadFloat2(&right_row_0);
				DirectX::XMVECTOR row_argument_1 =
					DirectX::XMLoadFloat2(&right_row_1);

				row_original_0 =
					DirectX::XMVectorDivide(row_original_0, row_argument_0);
				row_original_1 =
					DirectX::XMVectorDivide(row_original_1, row_argument_1);

				matrix2x2f result;

				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(
										   &result.Get_Base()._21),
					row_original_1);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}
#pragma endregion
		} // namespace math
	}     // namespace ktk
} // namespace Kotek