#pragma once

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
}

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Defines(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Defines(ktkMainManager* p_manager);
		bool SerializeModule_Core_Defines(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Defines(ktkMainManager* p_manager);
	}
}