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
	namespace Engine
	{
		bool InitializeEngine(Core::ktkMainManager* main_manager);
		bool ExecuteEngine(Core::ktkMainManager* main_manager);
		bool ShutdownEngine(Core::ktkMainManager* main_manager);
		bool serializeEngine(void);
		bool deserializeEngine(void);
	} // namespace Engine
} // namespace Kotek
