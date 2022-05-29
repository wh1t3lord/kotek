#pragma once

#include "kotek_file_text.h"

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
		bool InitializeModule_Core_FileSystem_File_Text(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_FileSystem_File_Text(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_FileSystem_File_Text(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_FileSystem_File_Text(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek