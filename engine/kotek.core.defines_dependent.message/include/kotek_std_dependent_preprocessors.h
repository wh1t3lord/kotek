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

// TODO: add feature that message can do log in file, but we can pass argument
// like KOTEK_MESSAGE_WITH_LOG=ON or OFF if ON means KOTEK_MESSAGE will write in
// text file if not ON it means message just write in our console.

// TODO: create KOTEK_LOG to separate operation into writing in console or text
// file
	#define KOTEK_MESSAGE(text, ...)                                         \
		{                                                                    \
			BOOST_LOG_TRIVIAL(info)                                          \
				<< "[" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ \
				<< "]"                                                       \
				<< (Kotek::ktk::format(KOTEK_TEXT(text), ##__VA_ARGS__))     \
					   .get_as_is();                                         \
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