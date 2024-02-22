#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_LOG_LIBRARY_BOOST
	#ifdef KOTEK_USE_BOOST_LIBRARY

	#endif
#elif defined(KOTEK_USE_LOG_LIBRARY_SPDLOG)
	#include <spdlog/spdlog.h>
	#include <spdlog/sinks/basic_file_sink.h>
#else
// provide your headers for log library
#endif