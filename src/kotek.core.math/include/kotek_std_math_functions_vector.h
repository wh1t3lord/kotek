#pragma once

#include "kotek_std_math_vector1f.h"
#include "kotek_std_math_vector2f.h"
#include "kotek_std_math_vector3f.h"
#include "kotek_std_math_vector4f.h"

#include "kotek_std_math_vectornf_view.h"
#include "kotek_std_math_vectornf_const_view.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

/*
 * FLOAT definitions
 */

inline float get_math_component_x(const vector1f& vec)
{
	return vec.e(0, 0);
}

inline float& get_math_component_x(vector1f& vec)
{
	return vec.e(0, 0);
}

inline float get_math_component_x(const vector2f& vec)
{
	return vec.e(0, 0);
}

inline float& get_math_component_x(vector2f& vec)
{
	return vec.e(0, 0);
}

inline float get_math_component_x(const vector3f& vec)
{
	return vec.e(0, 0);
}

inline float& get_math_component_x(vector3f& vec)
{
	return vec.e(0, 0);
}

inline float get_math_component_x(const vector4f& vec)
{
	return vec.e(0, 0);
}

inline float& get_math_component_x(vector4f& vec)
{
	return vec.e(0, 0);
}

inline float get_math_component_x(const vectornf_view_t& view)
{
	return view.e(0, 0);
}

inline float& get_math_component_x(vectornf_view_t& view)
{
	return view.e(0, 0);
}

inline float
get_math_component_x(const vectornf_const_view_t& view)
{
	return view.e(0, 0);
}

inline float get_math_component_y(const vector2f& vec)
{
	return vec.e(0, 1);
}

inline float& get_math_component_y(vector2f& vec)
{
	return vec.e(0, 1);
}

inline float get_math_component_y(const vectornf_view_t& view)
{
	return view.e(0, 1);
}

inline float& get_math_component_y(vectornf_view_t& view)
{
	return view.e(0, 1);
}

inline float get_math_component_z(const vector3f& vec)
{
	return vec.e(0, 2);
}

inline float& get_math_component_z(vector3f& vec)
{
	return vec.e(0, 2);
}

inline float get_math_component_z(const vectornf_view_t& view)
{
	return view.e(0, 2);
}

inline float& get_math_component_z(vectornf_view_t& view)
{
	return view.e(0, 2);
}

inline float get_math_component_w(const vector4f& vec)
{
	return vec.e(0, 3);
}

inline float& get_math_component_w(vector4f& vec)
{
	return vec.e(0, 3);
}

inline float get_math_component_w(const vectornf_view_t& view)
{
	return view.e(0, 3);
}

inline float& get_math_component_w(vectornf_view_t& view)
{
	return view.e(0, 3);
}

inline float const* get_math_value_ptr(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &data.Get_Base();
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* get_math_value_ptr(const vector2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return reinterpret_cast<float const*>(&data.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* get_math_value_ptr(const vector3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return reinterpret_cast<float const*>(&data.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* get_math_value_ptr(const vector4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return reinterpret_cast<float const*>(&data.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float get_math_length(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float com_x = get_math_component_x(data);
	return sqrt(com_x * com_x);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length(data.Get_Base());
#endif
}

inline float get_math_length(const vector2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};

	auto length = DirectX::XMVector2Length(data);

	DirectX::XMStoreFloat(&result, length);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length(data.Get_Base());
#endif
}

inline float get_math_length(const vector3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};

	auto length = DirectX::XMVector3Length(data);

	DirectX::XMStoreFloat(&result, length);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length(data.Get_Base());
#endif
}

inline float get_math_length(const vector4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};

	auto length = DirectX::XMVector4Length(data);

	DirectX::XMStoreFloat(&result, length);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length(data.Get_Base());
#endif
}

inline float get_math_length_squared(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return data.x() * data.x();
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length2(data.Get_Base());
#endif
}

inline float get_math_length_squared(const vector2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};
	auto length_sq = DirectX::XMVector2LengthSq(data);
	DirectX::XMStoreFloat(&result, length_sq);
	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length2(data.Get_Base());
#endif
}

inline float get_math_length_squared(const vector3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};
	auto length_sq = DirectX::XMVector3LengthSq(data);
	DirectX::XMStoreFloat(&result, length_sq);
	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length2(data.Get_Base());
#endif
}

inline float get_math_length_squared(const vector4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};
	auto length_sq = DirectX::XMVector4LengthSq(data);
	DirectX::XMStoreFloat(&result, length_sq);
	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::length2(data.Get_Base());
#endif
}

inline float get_math_distance_squared(
	const vector4f& left, const vector4f& right
)
{
	return get_math_length_squared(left - right);
}

inline float get_math_distance_squared(
	const vector3f& left, const vector3f& right
)
{
	return get_math_length_squared(left - right);
}

inline float get_math_distance_squared(
	const vector2f& left, const vector2f& right
)
{
	return get_math_length_squared(left - right);
}

inline float get_math_distance_squared(const vector1f& left, const vector1f& right)
{
	return get_math_length_squared(left - right);
}

inline float get_math_distance(const vector4f& left, const vector4f& right)
{
	return get_math_length(left - right);
}

inline float get_math_distance(const vector3f& left, const vector3f& right)
{
	return get_math_length(left - right);
}

inline float get_math_distance(const vector2f& left, const vector2f& right)
{
	return get_math_length(left - right);
}

inline float
get_math_distance(const vector1f& left, const vector1f& right)
{
	return get_math_length(left - right);
}

inline float
get_math_dot(const vector1f& left, const vector1f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return get_math_component_x(left) *
		get_math_component_x(right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::dot(left.Get_Base(), right.Get_Base());
#endif
}

inline float
get_math_dot(const vector2f& left, const vector2f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto dot = DirectX::XMVector2Dot(left, right);
	float result{};
	DirectX::XMStoreFloat(&result, dot);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::dot(left.Get_Base(), right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector2f
get_math_cross(const vector2f& left, const vector2f& right)
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Cross(left, right);
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vector3f(glm::cross(
		vector3f(left).Get_Base(), vector3f(right).Get_Base()
	));
	#endif
}

inline vector2f
get_math_cross(const vector2f& left, const vector3f& right)
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Cross(left, right);
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vector3f(
		glm::cross(vector3f(left).Get_Base(), right.Get_Base())
	);
	#endif
}

inline vector2f
get_math_cross(const vector2f& left, const vector4f& right)
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Cross(left, right);
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vector3f(glm::cross(
		vector3f(left).Get_Base(), vector3f(right).Get_Base()
	));
	#endif
}
#endif

inline float
get_math_dot(const vector3f& left, const vector3f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto dot = DirectX::XMVector3Dot(left, right);
	float result{};
	DirectX::XMStoreFloat(&result, dot);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::dot(left.Get_Base(), right.Get_Base());
#endif
}

inline vector3f
get_math_cross(const vector3f& left, const vector3f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::cross(left.Get_Base(), right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector3f
get_math_cross(const vector3f& left, const vector4f& right)
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::cross(
		left.Get_Base(), vector3f(right).Get_Base()
	);
	#endif
}
#endif

inline float
get_math_dot(const vector4f& left, const vector4f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto dot = DirectX::XMVector4Dot(left, right);
	float result{};
	DirectX::XMStoreFloat(&result, dot);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::dot(left.Get_Base(), right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector4f
get_math_cross(const vector4f& left, const vector3f& right)
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vector3f(
		glm::cross(vector3f(left).Get_Base(), right.Get_Base())
	);
	#endif
}
#endif

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector4f
get_math_cross(const vector4f& left, const vector4f& right)
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vector3f(glm::cross(
		vector3f(left).Get_Base(), vector3f(right).Get_Base()
	));
	#endif
}
#endif

inline vector1f get_math_normalize(const vector1f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return vector1f(1.0f);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::normalize(vec.Get_Base());
#endif
}

inline vector2f get_math_normalize(const vector2f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Normalize(vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::normalize(vec.Get_Base());
#endif
}

inline vector3f get_math_normalize(const vector3f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Normalize(vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::normalize(vec.Get_Base());
#endif
}

inline vector4f get_math_normalize(const vector4f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector4Normalize(vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::normalize(vec.Get_Base());
#endif
}

/*
 * DOUBLE definitions
 */

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK KOTEK_END_NAMESPACE_KOTEK