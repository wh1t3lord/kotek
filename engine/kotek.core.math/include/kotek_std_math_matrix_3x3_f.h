#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class matrix3x3f
			{
			public:
				matrix3x3f(float m00, float m01,
					float m02, float m10, float m11,
					float m12, float m20, float m21,
					float m22) :
					m_base(m00, m01, m02, m10, m11, m12, m20, m21, m22)
				{
				}
				matrix3x3f(const base_mat3x3_t& data) : m_base(data) {}
				matrix3x3f(const matrix3x3f& data) : m_base(data.m_base) {}
				matrix3x3f(void) : m_base{} {}

				~matrix3x3f(void) = default;

				matrix3x3f& operator=(const matrix3x3f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				matrix3x3f& operator=(const base_mat3x3_t& data)
				{
					this->m_base = data;
					return *this;
				}

				matrix3x3f& operator+=(const matrix3x3f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					row_original_0 =
						DirectX::XMVectorAdd(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorAdd(row_original_1, row_argument_1);
					row_original_2 =
						DirectX::XMVectorAdd(row_original_2, row_argument_2);

					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
						row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& operator+=(const base_mat3x3_t& data) noexcept
				{
					return this->operator+=(data);
				}

				matrix3x3f& operator-=(const matrix3x3f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					row_original_0 = DirectX::XMVectorSubtract(
						row_original_0, row_argument_0);
					row_original_1 = DirectX::XMVectorSubtract(
						row_original_1, row_argument_1);
					row_original_2 = DirectX::XMVectorSubtract(
						row_original_2, row_argument_2);

					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
						row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& operator-=(const base_mat3x3_t& data) noexcept
				{
					return this->operator-=(data);
				}

				matrix3x3f& operator*=(const matrix3x3f& data) noexcept
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

				matrix3x3f& operator*=(const base_mat3x3_t& data) noexcept
				{
					return this->operator*=(data);
				}

				matrix3x3f& operator*=(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					row_original_0 =
						DirectX::XMVectorScale(row_original_0, value);
					row_original_1 =
						DirectX::XMVectorScale(row_original_1, value);
					row_original_2 =
						DirectX::XMVectorScale(row_original_2, value);

					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
						row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}

				matrix3x3f& operator/=(const matrix3x3f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					row_original_0 =
						DirectX::XMVectorDivide(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorDivide(row_original_1, row_argument_1);
					row_original_2 =
						DirectX::XMVectorDivide(row_original_2, row_argument_2);

					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
						row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& operator/=(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					float factor = 1.f / value;

					row_original_0 =
						DirectX::XMVectorScale(row_original_0, factor);
					row_original_1 =
						DirectX::XMVectorScale(row_original_1, factor);
					row_original_2 =
						DirectX::XMVectorScale(row_original_2, factor);

					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat3(
						reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
						row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}

				matrix3x3f operator+() const noexcept { return *this; }

				matrix3x3f operator-() const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					row_original_0 = DirectX::XMVectorNegate(row_original_0);
					row_original_1 = DirectX::XMVectorNegate(row_original_1);
					row_original_2 = DirectX::XMVectorNegate(row_original_2);

					matrix3x3f result;

					DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(
											   &result.m_base._11),
						row_original_0);

					DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(
											   &result.m_base._21),
						row_original_1);

					DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(
											   &result.m_base._31),
						row_original_2);

					return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				bool operator==(const matrix3x3f& data) const noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					bool is_equal_0 =
						DirectX::XMVector3Equal(row_original_0, row_argument_0);
					bool is_equal_1 =
						DirectX::XMVector3Equal(row_original_1, row_argument_1);
					bool is_equal_2 =
						DirectX::XMVector3Equal(row_original_2, row_argument_2);

					return (is_equal_0 && is_equal_1 && is_equal_2);
				}

				bool operator!=(const matrix3x3f& data) noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					bool is_equal_0 = DirectX::XMVector3NotEqual(
						row_original_0, row_argument_0);
					bool is_equal_1 = DirectX::XMVector3NotEqual(
						row_original_1, row_argument_1);
					bool is_equal_2 = DirectX::XMVector3NotEqual(
						row_original_2, row_argument_2);

					return (is_equal_0 || is_equal_1 || is_equal_2);
				}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				operator DirectX::XMMATRIX(void) const noexcept
				{
					return DirectX::XMLoadFloat3x3(&this->m_base);
				}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
#pragma endregion

				float Get_00(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._11;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_01(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._12;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_02(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._13;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_10(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._21;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_11(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._22;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_12(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._23;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_20(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._31;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_21(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._32;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				float Get_22(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._33;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				matrix3x3f& Set_00(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._11 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				matrix3x3f& Set_01(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._12 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_02(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._13 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_10(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._21 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_11(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._22 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_12(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._23 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_20(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._31 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_21(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._32 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_22(float value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._33 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix3x3f& Set_Base(const base_mat3x3_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}

				base_mat3x3_t& Get_Base(void) noexcept { return this->m_base; }
				const base_mat3x3_t& Get_Base(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_mat3x3_t m_base;
			};

			inline matrix3x3f operator+(
				const matrix3x3f& left, const matrix3x3f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT3 left_row_0 = {
					left.Get_00(), left.Get_01(), left.Get_02()};
				DirectX::XMFLOAT3 left_row_1 = {
					left.Get_10(), left.Get_11(), left.Get_12()};
				DirectX::XMFLOAT3 left_row_2 = {
					left.Get_20(), left.Get_21(), left.Get_22()};

				DirectX::XMFLOAT3 right_row_0 = {
					right.Get_00(), right.Get_01(), right.Get_02()};
				DirectX::XMFLOAT3 right_row_1 = {
					right.Get_10(), right.Get_11(), right.Get_12()};
				DirectX::XMFLOAT3 right_row_2 = {
					right.Get_20(), right.Get_21(), right.Get_22()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat3(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat3(&left_row_1);
				DirectX::XMVECTOR row_original_2 =
					DirectX::XMLoadFloat3(&left_row_2);

				DirectX::XMVECTOR row_argument_0 =
					DirectX::XMLoadFloat3(&right_row_0);
				DirectX::XMVECTOR row_argument_1 =
					DirectX::XMLoadFloat3(&right_row_1);
				DirectX::XMVECTOR row_argument_2 =
					DirectX::XMLoadFloat3(&right_row_2);

				row_original_0 =
					DirectX::XMVectorAdd(row_original_0, row_argument_0);
				row_original_1 =
					DirectX::XMVectorAdd(row_original_1, row_argument_1);
				row_original_2 =
					DirectX::XMVectorAdd(row_original_2, row_argument_2);

				matrix3x3f result;

				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
					row_original_1);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
					row_original_2);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix3x3f operator-(
				const matrix3x3f& left, const matrix3x3f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT3 left_row_0 = {
					left.Get_00(), left.Get_01(), left.Get_02()};
				DirectX::XMFLOAT3 left_row_1 = {
					left.Get_10(), left.Get_11(), left.Get_12()};
				DirectX::XMFLOAT3 left_row_2 = {
					left.Get_20(), left.Get_21(), left.Get_22()};

				DirectX::XMFLOAT3 right_row_0 = {
					right.Get_00(), right.Get_01(), right.Get_02()};
				DirectX::XMFLOAT3 right_row_1 = {
					right.Get_10(), right.Get_11(), right.Get_12()};
				DirectX::XMFLOAT3 right_row_2 = {
					right.Get_20(), right.Get_21(), right.Get_22()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat3(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat3(&left_row_1);
				DirectX::XMVECTOR row_original_2 =
					DirectX::XMLoadFloat3(&left_row_2);

				DirectX::XMVECTOR row_argument_0 =
					DirectX::XMLoadFloat3(&right_row_0);
				DirectX::XMVECTOR row_argument_1 =
					DirectX::XMLoadFloat3(&right_row_1);
				DirectX::XMVECTOR row_argument_2 =
					DirectX::XMLoadFloat3(&right_row_2);

				row_original_0 =
					DirectX::XMVectorSubtract(row_original_0, row_argument_0);
				row_original_1 =
					DirectX::XMVectorSubtract(row_original_1, row_argument_1);
				row_original_2 =
					DirectX::XMVectorSubtract(row_original_2, row_argument_2);

				matrix3x3f result;

				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
					row_original_1);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
					row_original_2);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix3x3f operator*(
				const matrix3x3f& left, const matrix3x3f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMMATRIX m1 = left;
				DirectX::XMMATRIX m2 = right;
				auto temp = DirectX::XMMatrixMultiply(m1, m2);

				matrix3x3f result;
				base_mat3x3_t data;
				DirectX::XMStoreFloat3x3(&data, temp);

				result.Set_Base(data);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix3x3f operator*(
				const matrix3x3f& left, float value) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT3 left_row_0 = {
					left.Get_00(), left.Get_01(), left.Get_02()};
				DirectX::XMFLOAT3 left_row_1 = {
					left.Get_10(), left.Get_11(), left.Get_12()};
				DirectX::XMFLOAT3 left_row_2 = {
					left.Get_20(), left.Get_21(), left.Get_22()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat3(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat3(&left_row_1);
				DirectX::XMVECTOR row_original_2 =
					DirectX::XMLoadFloat3(&left_row_2);

				row_original_0 = DirectX::XMVectorScale(row_original_0, value);
				row_original_1 = DirectX::XMVectorScale(row_original_1, value);
				row_original_2 = DirectX::XMVectorScale(row_original_2, value);

				matrix3x3f result;

				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
					row_original_1);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
					row_original_2);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			}
			
			inline matrix3x3f operator*(
				float value, const matrix3x3f& right) noexcept
			{
				return operator*(right, value);
			}

			inline matrix3x3f operator/(
				const matrix3x3f& left, float value) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT3 left_row_0 = {
					left.Get_00(), left.Get_01(), left.Get_02()};
				DirectX::XMFLOAT3 left_row_1 = {
					left.Get_10(), left.Get_11(), left.Get_12()};
				DirectX::XMFLOAT3 left_row_2 = {
					left.Get_20(), left.Get_21(), left.Get_22()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat3(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat3(&left_row_1);
				DirectX::XMVECTOR row_original_2 =
					DirectX::XMLoadFloat3(&left_row_2);

				float factor = 1.f / value;

				row_original_0 = DirectX::XMVectorScale(row_original_0, factor);
				row_original_1 = DirectX::XMVectorScale(row_original_1, factor);
				row_original_2 = DirectX::XMVectorScale(row_original_2, factor);

				matrix3x3f result;

				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
					row_original_1);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
					row_original_2);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}

			inline matrix3x3f operator/(
				const matrix3x3f& left, const matrix3x3f& right) noexcept
			{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				DirectX::XMFLOAT3 left_row_0 = {
					left.Get_00(), left.Get_01(), left.Get_02()};
				DirectX::XMFLOAT3 left_row_1 = {
					left.Get_10(), left.Get_11(), left.Get_12()};
				DirectX::XMFLOAT3 left_row_2 = {
					left.Get_20(), left.Get_21(), left.Get_22()};

				DirectX::XMFLOAT3 right_row_0 = {
					right.Get_00(), right.Get_01(), right.Get_02()};
				DirectX::XMFLOAT3 right_row_1 = {
					right.Get_10(), right.Get_11(), right.Get_12()};
				DirectX::XMFLOAT3 right_row_2 = {
					right.Get_20(), right.Get_21(), right.Get_22()};

				DirectX::XMVECTOR row_original_0 =
					DirectX::XMLoadFloat3(&left_row_0);
				DirectX::XMVECTOR row_original_1 =
					DirectX::XMLoadFloat3(&left_row_1);
				DirectX::XMVECTOR row_original_2 =
					DirectX::XMLoadFloat3(&left_row_2);

				DirectX::XMVECTOR row_argument_0 =
					DirectX::XMLoadFloat3(&right_row_0);
				DirectX::XMVECTOR row_argument_1 =
					DirectX::XMLoadFloat3(&right_row_1);
				DirectX::XMVECTOR row_argument_2 =
					DirectX::XMLoadFloat3(&right_row_2);

				row_original_0 =
					DirectX::XMVectorDivide(row_original_0, row_argument_0);
				row_original_1 =
					DirectX::XMVectorDivide(row_original_1, row_argument_1);
				row_original_2 =
					DirectX::XMVectorDivide(row_original_2, row_argument_2);

				matrix3x3f result;

				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
					row_original_0);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
					row_original_1);
				DirectX::XMStoreFloat3(
					reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
					row_original_2);

				return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			}
		} // namespace math
	}     // namespace ktk
} // namespace Kotek