#pragma once

#include <kotek.core.constants.math/include/kotek_core_constants_math.h>
#include "kotek_std_utility_variant.h"
#include "kotek_std_utility_function.h"
#include "kotek_std_utility_hash.h"
#include <kotek.core.containers.queue\include\kotek_core_containers_queue.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename T>
T align_up(T val, T alignment) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return (val + alignment - (T)1) & ~(alignment - (T)1);
}

template <typename T>
T align_down(T val, T alignment) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return val & ~(alignment - (T)1);
}

/// @brief \~english use this for generating ids when you deallocated something
/// you also need to release that id to pool
/// no dynamic memory allocation except for constructor (fills queue from
/// 0..254) the invalid value of this will be uint8_t::max your pool of possible
/// ids from 0 to 254 (for performance critical resource management that's
/// enough)
class ktkUint8GeneratorID
{
public:
	ktkUint8GeneratorID()
	{
		constexpr kun_ktk uint8_t _kMaxSize =
			std::numeric_limits<kun_ktk uint8_t>::max();

		for (kun_ktk uint8_t i = 0; i < _kMaxSize; ++i)
		{
			this->m_storage.push(static_cast<kun_ktk uint8_t>(i));
		}
	}

	~ktkUint8GeneratorID() {}

	inline kun_ktk uint8_t allocate(void) KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		constexpr kun_ktk uint8_t _kMaxSize =
			std::numeric_limits<kun_ktk uint8_t>::max();

		kun_ktk uint8_t result = _kMaxSize;
		if (this->m_storage.empty())
		{
			KOTEK_ASSERT(
				false, "you try to allocate new id but you wasted all!");
			return result;
		}

		result = this->m_storage.front();
		this->m_storage.pop();

		return result;
	}

	inline void deallocate(kun_ktk uint8_t id) KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		constexpr kun_ktk uint8_t _kMaxSize =
			std::numeric_limits<kun_ktk uint8_t>::max();

		if (id < _kMaxSize)
		{
			this->m_storage.push(id);
		}
	}

private:
	ktk_queue<kun_ktk uint8_t, std::numeric_limits<kun_ktk uint8_t>::max()>
		m_storage;
};

bool is_equal(
	float a, float b, float relative_difference_factor = kun_ktk kMin_Float)
	KOTEK_CPP_KEYWORD_NOEXCEPT;

bool is_equal(
	double a, double b, double relative_difference_factor = kun_ktk kMin_Double)
	KOTEK_CPP_KEYWORD_NOEXCEPT;

bool is_equal(long double a, long double b,
	long double relative_difference_factor = kun_ktk kMin_Long_Double)
	KOTEK_CPP_KEYWORD_NOEXCEPT;

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
