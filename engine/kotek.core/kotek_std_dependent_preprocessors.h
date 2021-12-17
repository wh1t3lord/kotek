#pragma once

#include "kotek_std_alias_string.h"
#include <iostream>

#ifdef KOTEK_USE_UNICODE

	#define KOTEK_MESSAGE_STRING(variable, ...)                                \
		{                                                                      \
			std::wcout << "[" << __FILE__ << "]"                               \
					   << "[" << __FUNCTION__ << "]"                           \
					   << "[" << __LINE__ << "]" << L" "                       \
					   << Kotek::ktk::cast::to_wchar_string(                   \
							  fmt::format(variable.get_as_is(), ##__VA_ARGS__) \
								  .c_str())                                    \
					   << std::endl;                                           \
		}

	#define KOTEK_MESSAGE(text, ...)                                         \
		{                                                                    \
			std::wcout                                                       \
				<< "[" << __FILE__ << "]"                                    \
				<< "[" << __FUNCTION__ << "]"                                \
				<< "[" << __LINE__ << "]" << L" "                            \
				<< Kotek::ktk::cast::to_wchar_string(                        \
					   fmt::format(KOTEK_TEXT(text), ##__VA_ARGS__).c_str()) \
				<< std::endl;                                                \
		}

	#define KOTEK_MESSAGE_WARNING(text, ...)                                 \
		{                                                                    \
			std::wcout                                                       \
				<< "[" << __FILE__ << "]"                                    \
				<< "[" << __FUNCTION__ << "]"                                \
				<< "[" << __LINE__ << "]"                                    \
				<< "["                                                       \
				<< "WARNING"                                                 \
				<< "] ! "                                                    \
				<< " "                                                       \
				<< Kotek::ktk::cast::to_wchar_string(                        \
					   fmt::format(KOTEK_TEXT(text), ##__VA_ARGS__).c_str()) \
				<< std::endl;                                                \
		}

	#define KOTEK_MESSAGE_ERROR(text, ...)                                   \
		{                                                                    \
			std::wcout                                                       \
				<< "[" << __FILE__ << "]"                                    \
				<< "[" << __FUNCTION__ << "]"                                \
				<< "[" << __LINE__ << "]"                                    \
				<< "["                                                       \
				<< "ERROR"                                                   \
				<< "]"                                                       \
				<< " "                                                       \
				<< Kotek::ktk::cast::to_wchar_string(                        \
					   fmt::format(KOTEK_TEXT(text), ##__VA_ARGS__).c_str()) \
				<< std::endl;                                                \
		}
#endif

#define KOTEK_MESSAGE_LEGACY(text, ...)                              \
	{                                                                \
		std::cout << "[" << __FILE__ << "]"                          \
				  << "[" << __FUNCTION__ << "]"                      \
				  << "[" << __LINE__ << "]"                          \
				  << " " << fmt::format(text, ##__VA_ARGS__).c_str() \
				  << std::endl;                                      \
	}

#define KOTEK_MESSAGE_WARNING_LEGACY(text, ...)                      \
	{                                                                \
		std::cout << "[" << __FILE__ << "]"                          \
				  << "[" << __FUNCTION__ << "]"                      \
				  << "[" << __LINE__ << "]"                          \
				  << " "                                             \
				  << "["                                             \
				  << "WARNING"                                       \
				  << "] ! "                                          \
				  << " " << fmt::format(text, ##__VA_ARGS__).c_str() \
				  << std::endl;                                      \
	}

#define KOTEK_MESSAGE_ERROR_LEGACY(text, ...)                        \
	{                                                                \
		std::cout << "[" << __FILE__ << "]"                          \
				  << "[" << __FUNCTION__ << "]"                      \
				  << "[" << __LINE__ << "]"                          \
				  << " "                                             \
				  << "["                                             \
				  << "ERROR"                                         \
				  << "]"                                             \
				  << " " << fmt::format(text, ##__VA_ARGS__).c_str() \
				  << std::endl;                                      \
	}

#define KOTEK_ASSERT(statement, text, ...)      \
	{                                           \
		bool _xstatus = statement;              \
		if (_xstatus == false)                  \
		{                                       \
			KOTEK_MESSAGE(text, ##__VA_ARGS__); \
			assert(_xstatus);                   \
		}                                       \
	}

#ifdef KOTEK_DEBUG
	#define VMA_DEBUG_LOG
#endif