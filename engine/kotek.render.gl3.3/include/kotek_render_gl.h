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
	namespace Render
	{
		// TODO: rename to GL3_3
		bool InitializeModule_Render_GL3_3(Core::ktkMainManager* main_manager);
		bool ShutdownModule_Render_GL3_3(Core::ktkMainManager* main_manager);
	} // namespace Render
} // namespace Kotek