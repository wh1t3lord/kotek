#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

#ifdef KOTEK_USE_LOG_LIBRARY_BOOST
	#ifdef KOTEK_USE_BOOST_LIBRARY

	#endif
#elif defined(KOTEK_USE_LOG_LIBRARY_SPDLOG)
	#include <spdlog/spdlog.h>
	#include <spdlog/sinks/basic_file_sink.h>
#elif defined(KOTEK_USE_LOG_LIBRARY_CUSTOM)
	// kotek's own no-dependency backend (task K17/K4)
	#include "kotek_custom_log.h"
#else
// provide your headers for log library
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkLogger : public KUN_KOTEK KUN_CORE ktkILogger
{
public:
	ktkLogger(void);
	~ktkLogger(void);

	void Initialize(void) override;
	void Shutdown(void) override;
	void* Get(const char* p_logger_name) override;

#ifdef KOTEK_USE_LOG_LIBRARY_SPDLOG
	void Set(spdlog::logger* p_logger, const char* p_logger_name);
#elif defined(KOTEK_USE_LOG_LIBRARY_CUSTOM)
	void Set(ktkCustomLogger* p_logger, const char* p_logger_name);
#endif
	void Flush_All(void) override;

private:
#ifdef KOTEK_USE_LOG_LIBRARY_SPDLOG
	spdlog::logger* m_pLoggerMain{};
	spdlog::logger* m_pLoggerMsvc{};
#elif defined(KOTEK_USE_LOG_LIBRARY_CUSTOM)
	ktkCustomLogger* m_pLoggerMain{};
	ktkCustomLogger* m_pLoggerMsvc{};
#endif
};
KOTEK_END_NAMESPACE_CORE

constexpr const char* kLoggerMainName = "all";
constexpr const char* kLoggerMsvcOutputWindowName = "tracer";

#ifdef KOTEK_USE_LOG_LIBRARY_SPDLOG
spdlog::logger* Get_LoggerMain();
spdlog::logger* Get_LoggerMsvcOutput();
void Set_LoggerMain(void* p_logger);
void Set_LoggerMsvcOutput(void* p_logger);
#elif defined(KOTEK_USE_LOG_LIBRARY_CUSTOM)
Core::ktkCustomLogger* Get_LoggerMain();
Core::ktkCustomLogger* Get_LoggerMsvcOutput();
void Set_LoggerMain(void* p_logger);
void Set_LoggerMsvcOutput(void* p_logger);
#endif

KOTEK_END_NAMESPACE_KOTEK