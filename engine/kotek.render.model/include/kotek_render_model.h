#pragma once

#include <kotek.render.model.assimp/include/kotek_render_model_assimp.h>
#include <kotek.render.model.cgltf/include/kotek_render_model_cgltf.h>

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
		bool InitializeModule_Render_Model(Core::ktkMainManager* p_main_manager);
		bool ShutdownModule_Render_Model(Core::ktkMainManager* p_main_manager);
	} // namespace Render
} // namespace Kotek