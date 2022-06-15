#pragma once

namespace Kotek
{
	namespace Game
	{
		bool InitializeModule_Game(Core::ktkMainManager* main_manager);

		// Main Loop
		bool ExecuteModule_Game(Core::ktkMainManager* main_manager, float dt);

		bool serializeModule_Game(void);
		bool deserializeModule_Game(void);

		bool ShutdownModule_Game(Core::ktkMainManager* main_manager);
	} // namespace Game
} // namespace Kotek