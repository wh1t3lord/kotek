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
		bool InitializeModule_Render_Shared_GL(Core::ktkMainManager*);
		bool ShutdownModule_Render_Shared_GL(Core::ktkMainManager*);
	} // namespace Render
} // namespace Kotek