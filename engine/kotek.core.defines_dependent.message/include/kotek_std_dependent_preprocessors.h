#pragma once

#include <kotek.core.log/include/kotek_core_log.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>
#include <kotek.core.format/include/kotek_core_format.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#define KOTEK_MESSAGE_STRING(variable, ...)                              \
		{                                                                    \
			BOOST_LOG_TRIVIAL(info)                                          \
				<< (Kotek::ktk::format(variable.get_as_is(), ##__VA_ARGS__)) \
					   .get_as_is();                                         \
		}

	#define KOTEK_MESSAGE(text, ...)                                     \
		{                                                                \
			BOOST_LOG_TRIVIAL(info)                                      \
				<< (Kotek::ktk::format(KOTEK_TEXT(text), ##__VA_ARGS__)) \
					   .get_as_is();                                     \
		}

	#define KOTEK_MESSAGE_WARNING(text, ...)                             \
		{                                                                \
			BOOST_LOG_TRIVIAL(warning)                                   \
				<< (Kotek::ktk::format(KOTEK_TEXT(text), ##__VA_ARGS__)) \
					   .get_as_is();                                     \
		}

	#define KOTEK_MESSAGE_ERROR(text, ...)                              \
		{                                                               \
			BOOST_LOG_TRIVIAL(error)                                    \
				<< (Kotek::ktk::format(KOTEK_TEXT(text), ##__VA_ARGS__) \
						   .get_as_is());                               \
		}

	#define KOTEK_MESSAGE_LEGACY(text, ...)                                 \
		{                                                                   \
			BOOST_LOG_TRIVIAL(info)                                         \
				<< Kotek::ktk::format(text, ##__VA_ARGS__).get_as_legacy(); \
		}

	#define KOTEK_MESSAGE_WARNING_LEGACY(text, ...)                         \
		{                                                                   \
			BOOST_LOG_TRIVIAL(warning)                                      \
				<< Kotek::ktk::format(text, ##__VA_ARGS__).get_as_legacy(); \
		}

	#define KOTEK_MESSAGE_ERROR_LEGACY(text, ...)                           \
		{                                                                   \
			BOOST_LOG_TRIVIAL(error)                                        \
				<< Kotek::ktk::format(text, ##__VA_ARGS__).get_as_legacy(); \
		}
#endif