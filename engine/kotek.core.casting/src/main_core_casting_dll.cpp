#include "../include/kotek_core_casting.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Casting(ktkMainManager* p_manager) 
		{
			InitializeModule_Core_Casting_Lexical(p_manager);
			InitializeModule_Core_Casting_String(p_manager);

			return true; 
		}

		bool ShutdownModule_Core_Casting(ktkMainManager* p_manager) 
		{
			ShutdownModule_Core_Casting_Lexical(p_manager);
			ShutdownModule_Core_Casting_String(p_manager);

			return true;
		}

		bool SerializeModule_Core_Casting(ktkMainManager* p_manager) 
		{
			SerializeModule_Core_Casting_Lexical(p_manager);
			SerializeModule_Core_Casting_String(p_manager);

			return true; 
		}

		bool DeserializeModule_Core_Casting(ktkMainManager* p_manager) 
		{
			DeserializeModule_Core_Casting_Lexical(p_manager);
			DeserializeModule_Core_Casting_String(p_manager);

			return true; 
		}
	} // namespace Core
} // namespace Kotek