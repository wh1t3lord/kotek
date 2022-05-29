#pragma once


#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include "kotek_filesystem.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_FileSystem(ktkMainManager* p_manager);
		bool SerializeModule_Core_FileSystem(ktkMainManager* p_manager);
		bool DeserializeModule_Core_FileSystem(ktkMainManager* p_manager);
		bool ShutdownModule_Core_FileSystem(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek