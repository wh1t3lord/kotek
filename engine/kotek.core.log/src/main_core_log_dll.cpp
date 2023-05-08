#include "../include/kotek_core_log.h"

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/log/utility/setup.hpp>
#endif

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Log(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_BOOST_LIBRARY
	// TODO: filter messages when you pass type through cmake like
	// KOTEK_LOG_SEVERITY_LEVEL=info and will be generated preprocessor like
	// KOTEK_USE_LOG_SEVERITY_LEVEL info

	KOTEK_ASSERT(p_manager, "you pass an invalid main manager");
	KOTEK_ASSERT(p_manager->GetFileSystem(),
		"you must initialize filesystem before initializing this module!");

	auto path_to_folder = p_manager->GetFileSystem()->GetFolderByEnum(
		Kotek::Core::eFolderIndex::kFolderIndex_UserData);

	path_to_folder /= KOTEK_USE_LOG_OUTPUT_FILE_NAME;

	boost::log::add_file_log(
		reinterpret_cast<const char*>(path_to_folder.u8string().c_str()));
	boost::log::add_console_log();
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
