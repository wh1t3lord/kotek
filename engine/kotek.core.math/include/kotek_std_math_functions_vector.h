#pragma once

#include "kotek_std_math_vector1f.h"
#include "kotek_std_math_vector2f.h"
#include "kotek_std_math_vector3f.h"
#include "kotek_std_math_vector4f.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

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

KOTEK_END_NAMESPACE_MATH KOTEK_END_NAMESPACE_KTK KOTEK_END_NAMESPACE_KOTEK