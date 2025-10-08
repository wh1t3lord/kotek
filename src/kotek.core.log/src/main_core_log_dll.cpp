#include "../include/kotek_core_log.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api.h>

#ifdef KOTEK_USE_LOG_LIBRARY_BOOST
	#ifdef KOTEK_USE_BOOST_LIBRARY
		#include <boost/log/utility/setup.hpp>
	#endif
#elif defined(KOTEK_USE_LOG_LIBRARY_SPDLOG)
	#include <spdlog/sinks/msvc_sink.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkLogger::ktkLogger(void) {}

ktkLogger::~ktkLogger(void) {}

void ktkLogger::Initialize(void) {}

void ktkLogger::Shutdown(void) {}

void* ktkLogger::Get(const char* p_logger_name)
{
	if (!strcmp(p_logger_name, kLoggerMainName))
	{
		return static_cast<void*>(m_pLoggerMain);
	}
	else if (!strcmp(p_logger_name, kLoggerMsvcOutputWindowName))
	{
		return static_cast<void*>(m_pLoggerMsvc);
	}

	return static_cast<void*>(nullptr);
}

void ktkLogger::Set(spdlog::logger* p_logger, const char* p_logger_name)
{
	if (!strcmp(p_logger_name, kLoggerMainName))
	{
		if (!m_pLoggerMain)
		{
			m_pLoggerMain = p_logger;
		}
	}
	else if (!strcmp(p_logger_name, kLoggerMsvcOutputWindowName))
	{
		if (!m_pLoggerMsvc)
		{
			m_pLoggerMsvc = p_logger;
		}
	}
}
void ktkLogger::Flush_All(void)
{
	#ifdef KOTEK_USE_LOG_LIBRARY_BOOST
	#elif defined(KOTEK_USE_LOG_LIBRARY_SPDLOG)
	if (m_pLoggerMain)
	{
		m_pLoggerMain->flush();
	}
	#endif
}
KOTEK_END_NAMESPACE_CORE

spdlog::logger* _pLoggerMain{};
spdlog::logger* _pLoggerMsvcOutput{};

spdlog::logger* Get_LoggerMain()
{
	return _pLoggerMain;
}

spdlog::logger* Get_LoggerMsvcOutput()
{
	return _pLoggerMsvcOutput;
}

void Set_LoggerMain(void* p_logger)
{
	_pLoggerMain = static_cast<spdlog::logger*>(p_logger);
}

void Set_LoggerMsvcOutput(void* p_logger)
{
	_pLoggerMsvcOutput = static_cast<spdlog::logger*>(p_logger);
}

KOTEK_END_NAMESPACE_KOTEK

#else
// provide your some additional headers for log library
#endif

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Log(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [log]");
		p_manager->Get_Splash()->Set_Progress();
	}

#ifdef KOTEK_USE_LOG_LIBRARY_BOOST
	#ifdef KOTEK_USE_BOOST_LIBRARY
	// TODO: filter messages when you pass type through cmake like
	// KOTEK_LOG_SEVERITY_LEVEL=info and will be generated preprocessor like
	// KOTEK_USE_LOG_SEVERITY_LEVEL info

	KOTEK_ASSERT(p_manager, "you pass an invalid main manager");
	KOTEK_ASSERT(p_manager->GetFileSystem(),
		"you must initialize filesystem before initializing this module!");

	auto path_to_folder = p_manager->GetFileSystem()->GetFolderByEnum(
		Kotek::Core::eFolderIndex::kFolderIndex_DataUser);

	path_to_folder /= KOTEK_USE_LOG_OUTPUT_FILE_NAME;

	boost::log::add_file_log(
		reinterpret_cast<const char*>(path_to_folder.u8string().c_str()));
	boost::log::add_console_log();
	#endif
#elif defined(KOTEK_USE_LOG_LIBRARY_SPDLOG)
	KOTEK_ASSERT(p_manager, "you pass an invalid main manager");
	KOTEK_ASSERT(p_manager->GetFileSystem(),
		"you must initialize filesystem before initializing this module!");

	ktk_filesystem_path path_to_folder;
	p_manager->GetFileSystem()->Make_Path(
		path_to_folder,
		kun_core eFolderIndex::kFolderIndex_DataUser);
	
	path_to_folder /= KOTEK_USE_LOG_OUTPUT_FILE_NAME;

	auto logger_main = spdlog::basic_logger_mt(kLoggerMainName,
		reinterpret_cast<const char*>(path_to_folder.u8string().c_str()), true);
	logger_main->sinks().push_back(
		std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());

	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
	auto logger_msvc =
		std::make_shared<spdlog::logger>(kLoggerMsvcOutputWindowName, sink);
	logger_msvc->sinks().push_back(
		std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
	spdlog::initialize_logger(logger_msvc);
	logger_msvc->set_level(spdlog::level::level_enum::trace);
	ktkLogger* p_logger_manager = new ktkLogger();
	p_manager->Set_Logger(p_logger_manager);

	if (p_manager->Get_Logger())
	{
		p_logger_manager->Set(logger_main.get(), kLoggerMainName);
		p_logger_manager->Set(logger_msvc.get(), kLoggerMsvcOutputWindowName);
	}

	Set_LoggerMain(logger_main.get());
	Set_LoggerMsvcOutput(logger_msvc.get());
#else
#endif

	return true;
}

bool SerializeModule_Core_Log(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Log(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Log(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
