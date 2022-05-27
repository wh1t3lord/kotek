#pragma once

#define KOTEK_ASSERT(statement, text, ...)      \
	{                                           \
		bool _xstatus = statement;              \
		if (_xstatus == false)                  \
		{                                       \
			KOTEK_MESSAGE(text, ##__VA_ARGS__); \
			assert(_xstatus);                   \
		}                                       \
	}