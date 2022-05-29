#pragma once

#include "kotek_std_dependent_preprocessors.h"

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
		bool InitializeModule_Core_Defines_Dependent_Text(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Defines_Dependent_Text(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Defines_Dependent_Text(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Defines_Dependent_Text(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek