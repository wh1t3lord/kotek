#pragma once

#include <kotek.core.log/include/kotek_core_log.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>
#include <kotek.core.format/include/kotek_core_format.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

#ifdef KOTEK_USE_LOG_LIBRARY_BOOST
	#ifdef KOTEK_USE_BOOST_LIBRARY

		#define KOTEK_MESSAGE_STRING(variable, ...) \
			{                                       \
			BOOST_LOG_TRIVIAL(info)                                          \
                << reinterpret_cast<const char*>((Kotek::ktk::format(variable,
   ##__VA_ARGS__)) \
                       .c_str());
   }

	   // TODO: add feature that message can do log in file, but we can pass
	   // argument like KOTEK_MESSAGE_WITH_LOG=ON or OFF if ON means
	   // KOTEK_MESSAGE will write in text file if not ON it means message just
	   // write in our console.

	   // TODO: create KOTEK_LOG to separate operation into writing in console
	   // or text file

	   // If you want to use unicode version you must wrap your text by
	   // KOTEK_TEXT, this preprocessor doesn't handle it at all!

		#define KOTEK_MESSAGE(text, ...)                                 \
			{                                                            \
		BOOST_LOG_TRIVIAL(info)                                          \
            << "[" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ \
            << "]"                                                       \
            << reinterpret_cast<const char*>((Kotek::ktk::format(text,
##__VA_ARGS__))     \
                   .c_str());
}

		#define KOTEK_MESSAGE_WARNING(text, ...)                             \
			{                                                                \
				BOOST_LOG_TRIVIAL(warning) << reinterpret_cast<const char*>( \
					(Kotek::ktk::format(text, ##__VA_ARGS__)).c_str());      \
			}

		#define KOTEK_MESSAGE_ERROR(text, ...)                             \
			{                                                              \
				BOOST_LOG_TRIVIAL(error) << reinterpret_cast<const char*>( \
					(Kotek::ktk::format(text, ##__VA_ARGS__).c_str()));    \
			}

	#endif
#elif defined(KOTEK_USE_LOG_LIBRARY_SPDLOG)
	#define KOTEK_MESSAGE_STRING(text, ...)                            \
		{                                                              \
			auto p_logger = KUN_KOTEK Get_LoggerMain();                \
			if (p_logger)                                              \
				p_logger->info(reinterpret_cast<const char*>(          \
					Kotek::ktk::format(text, ##__VA_ARGS__).c_str())); \
		}

	#define KOTEK_MESSAGE(text, ...)                                         \
		{                                                                    \
			auto p_logger = KUN_KOTEK Get_LoggerMain();                      \
			if (p_logger)                                                    \
				p_logger->info("[{}:{}:{}] {}", __FILE__, __FUNCTION__,     \
					__LINE__,                                                \
					reinterpret_cast<const char*>(                           \
						(Kotek::ktk::format(text, ##__VA_ARGS__)).c_str())); \
		}

	#define KOTEK_MESSAGE_WARNING(text, ...)                           \
		{                                                              \
			auto p_logger = KUN_KOTEK Get_LoggerMain();                \
			if (p_logger)                                              \
				p_logger->warn(reinterpret_cast<const char*>(          \
					Kotek::ktk::format(text, ##__VA_ARGS__).c_str())); \
		}

	#define KOTEK_MESSAGE_ERROR(text, ...)                             \
		{                                                              \
			auto p_logger = KUN_KOTEK Get_LoggerMain();                \
			if (p_logger)                                              \
				p_logger->error(reinterpret_cast<const char*>(         \
					Kotek::ktk::format(text, ##__VA_ARGS__).c_str())); \
		}

// writes to log
	#define KOTEK_MESSAGE_TRACE(text, ...)                             \
		{                                                              \
			auto p_logger = KUN_KOTEK Get_LoggerMain();                \
			if (p_logger)                                              \
				p_logger->trace(reinterpret_cast<const char*>(         \
					Kotek::ktk::format(text, ##__VA_ARGS__).c_str())); \
		}

// writes to IDE output window
	#define KOTEK_TRACE(text, ...)                                     \
		{                                                              \
			auto p_logger = KUN_KOTEK Get_LoggerMsvcOutput();          \
			if (p_logger)                                              \
				p_logger->trace(reinterpret_cast<const char*>(         \
					Kotek::ktk::format(text, ##__VA_ARGS__).c_str())); \
		}
#else
// provide your implementation as overloading those preprocessors that used in
// framework
#endif
