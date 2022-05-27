#pragma once

#ifdef KOTEK_USE_UNICODE

	#define KOTEK_MESSAGE_STRING(variable, ...)                    \
		{                                                          \
			std::wcout << "[" << __FILE__ << "]"                   \
					   << "[" << __FUNCTION__ << "]"               \
					   << "[" << __LINE__ << "]" << L" "           \
					   << Kotek::ktk::format(                      \
							  variable.get_as_is(), ##__VA_ARGS__) \
							  .get_as_is()                         \
					   << std::endl;                               \
		}

	#define KOTEK_MESSAGE(text, ...)                             \
		{                                                        \
			std::wcout << "[" << __FILE__ << "]"                 \
					   << "[" << __FUNCTION__ << "]"             \
					   << "[" << __LINE__ << "]" << L" "         \
					   << (Kotek::ktk::format(                   \
							   KOTEK_TEXT(text), ##__VA_ARGS__)) \
							  .get_as_is()                       \
					   << std::endl;                             \
		}

	#define KOTEK_MESSAGE_WARNING(text, ...)                     \
		{                                                        \
			std::wcout << "[" << __FILE__ << "]"                 \
					   << "[" << __FUNCTION__ << "]"             \
					   << "[" << __LINE__ << "]"                 \
					   << "["                                    \
					   << "WARNING"                              \
					   << "] ! "                                 \
					   << " "                                    \
					   << (Kotek::ktk::format(                   \
							   KOTEK_TEXT(text), ##__VA_ARGS__)) \
							  .get_as_is()                       \
					   << std::endl;                             \
		}
#endif

#define KOTEK_MESSAGE_LEGACY(text, ...)                                  \
	{                                                                    \
		std::cout << "[" << __FILE__ << "]"                              \
				  << "[" << __FUNCTION__ << "]"                          \
				  << "[" << __LINE__ << "]"                              \
				  << " "                                                 \
				  << Kotek::ktk::format(text, ##__VA_ARGS__).get_as_is() \
				  << std::endl;                                          \
	}

#define KOTEK_MESSAGE_WARNING_LEGACY(text, ...)                          \
	{                                                                    \
		std::cout << "[" << __FILE__ << "]"                              \
				  << "[" << __FUNCTION__ << "]"                          \
				  << "[" << __LINE__ << "]"                              \
				  << " "                                                 \
				  << "["                                                 \
				  << "WARNING"                                           \
				  << "] ! "                                              \
				  << " "                                                 \
				  << Kotek::ktk::format(text, ##__VA_ARGS__).get_as_is() \
				  << std::endl;                                          \
	}

#define KOTEK_MESSAGE_ERROR(text, ...)                                     \
	{                                                                      \
		std::wcout << "[" << __FILE__ << "]"                               \
				   << "[" << __FUNCTION__ << "]"                           \
				   << "[" << __LINE__ << "]"                               \
				   << "["                                                  \
				   << "ERROR"                                              \
				   << "]"                                                  \
				   << " "                                                  \
				   << (Kotek::ktk::format(KOTEK_TEXT(text), ##__VA_ARGS__) \
							  .get_as_is())                                \
				   << std::endl;                                           \
		KOTEK_ASSERT(false, "");                                           \
	}

#define KOTEK_MESSAGE_ERROR_LEGACY(text, ...)                                \
	{                                                                        \
		std::cout << "[" << __FILE__ << "]"                                  \
				  << "[" << __FUNCTION__ << "]"                              \
				  << "[" << __LINE__ << "]"                                  \
				  << " "                                                     \
				  << "["                                                     \
				  << "ERROR"                                                 \
				  << "]"                                                     \
				  << " "                                                     \
				  << Kotek::ktk::format(text, ##__VA_ARGS__).get_as_legacy() \
				  << std::endl;                                              \
		KOTEK_ASSERT(false, "");                                             \
	}