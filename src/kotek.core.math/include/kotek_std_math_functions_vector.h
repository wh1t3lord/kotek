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

inline float x(const vector1f& vec) 
{
	return vec.e(0, 0);
}

inline float& x(vector1f& vec) 
{
	return vec.e(0, 0);
}

inline float x(const vectornf_view_t& view) 
{
	return view.e(0, 0);
}

inline float& x(vectornf_view_t& view) 
{
	return view.e(0, 0);
}


inline float const* value_ptr(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &data.Get_Base();
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* value_ptr(const vector2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return reinterpret_cast<float const*>(&data.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* value_ptr(const vector3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return reinterpret_cast<float const*>(&data.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* value_ptr(const vector4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return reinterpret_cast<float const*>(&data.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float length(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return sqrt(data.x() * data.x());
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline float length(const vector2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};

	auto length = DirectX::XMVector2Length(data);

	DirectX::XMStoreFloat(&result, length);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline float length(const vector3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};

	auto length = DirectX::XMVector3Length(data);

	DirectX::XMStoreFloat(&result, length);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline float length(const vector4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};

	auto length = DirectX::XMVector4Length(data);

	DirectX::XMStoreFloat(&result, length);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline float length_squared(const vector1f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return data.x() * data.x();
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline float length_squared(const vector2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};
	auto length_sq = DirectX::XMVector2LengthSq(data);
	DirectX::XMStoreFloat(&result, length_sq);
	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline float length_squared(const vector3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};
	auto length_sq = DirectX::XMVector3LengthSq(data);
	DirectX::XMStoreFloat(&result, length_sq);
	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline float length_squared(const vector4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float result{};
	auto length_sq = DirectX::XMVector4LengthSq(data);
	DirectX::XMStoreFloat(&result, length_sq);
	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline float distance_squared(const vector1f& from, const vector1f& to)
{
	return length_squared((from - to));
}

inline float distance_squared(const vector2f& from, const vector2f& to)
{
	return length_squared((from - to));
}

inline float distance_squared(const vector3f& from, const vector2f& to)
{
	vector3f result((from.x() - to.x()), (from.y() - to.y()), from.z());
	return length_squared(result);
}

inline float distance_squared(const vector3f& from, const vector3f& to)
{
	return length_squared((from - to));
}

inline float distance_squared(const vector4f& from, const vector2f& to)
{
	vector4f result(
		(from.x() - to.x()), (from.y() - to.y()), from.z(), from.w());
	return length_squared(result);
}

inline float distance_squared(const vector4f& from, const vector3f& to)
{
	vector4f result((from.x() - to.x()), (from.y() - from.y()),
		(from.z() - to.z()), from.w());

	return length_squared(result);
}

inline float distance_squared(const vector4f& from, const vector4f& to)
{
	return length_squared((from - to));
}

inline float dot(const vector1f& left, const vector1f& right)
{
	return left.x() * left.x();
}

inline float dot(const vector2f& left, const vector2f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto dot = DirectX::XMVector2Dot(left, right);
	float result{};
	DirectX::XMStoreFloat(&result, dot);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline vector2f cross(const vector2f& left, const vector2f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector2f cross(const vector2f& left, const vector3f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector2f cross(const vector2f& left, const vector4f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline float dot(const vector3f& left, const vector3f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto dot = DirectX::XMVector3Dot(left, right);
	float result{};
	DirectX::XMStoreFloat(&result, dot);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline vector3f cross(const vector3f& left, const vector3f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector3f cross(const vector3f& left, const vector4f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline float dot(const vector4f& left, const vector4f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	auto dot = DirectX::XMVector4Dot(left, right);
	float result{};
	DirectX::XMStoreFloat(&result, dot);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

inline vector4f cross(const vector4f& left, const vector3f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector4f cross(const vector4f& left, const vector4f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Cross(left, right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector1f normalize(const vector1f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return vector1f(1.0f);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector2f normalize(const vector2f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector2Normalize(vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector3f normalize(const vector3f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector3Normalize(vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline vector4f normalize(const vector4f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMVector4Normalize(vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

// double

KOTEK_END_NAMESPACE_MATH KOTEK_END_NAMESPACE_KTK KOTEK_END_NAMESPACE_KOTEK