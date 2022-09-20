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
	namespace UI
	{
		bool InitializeModule_UI_CEF(Core::ktkMainManager* p_main_manager);
		bool ShutdownModule_UI_CEF(Core::ktkMainManager* p_main_manager);
		bool SerializeModule_UI_CEF(Core::ktkMainManager* p_main_manager);
		bool DeserializeModule_UI_CEF(Core::ktkMainManager* p_main_manager);
	} // namespace UI
} // namespace Kotek
