#pragma once

#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>

#define KOTEK_ASSERT(statement, text, ...)      \
	{                                           \
		bool _xstatus = statement;              \
		if (_xstatus == false)                  \
		{                                       \
			KOTEK_MESSAGE(text, ##__VA_ARGS__); \
			assert(_xstatus);                   \
		}                                       \
	}