#pragma once

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
		bool InitializeModule_Core(ktkMainManager& main_manager);
		bool SerializeModule_Core(void);
		bool DeserializeModule_Core(void);
		bool ShutdownModule_Core(void);

		void RegisterTests_String_ForModule_Core(void);
		void RegisterTests_Filesystem_ForModule_Core(void);
	} // namespace Core
} // namespace Kotek
