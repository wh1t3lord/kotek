#pragma once

#include "../kotek.core/kotek_file.h"
#include "kotek_gltf.h"

namespace Kotek
{
	namespace Render
	{
		class kotek_gltf_model
		{
		public:
			kotek_gltf_model(void);
			~kotek_gltf_model(void);

			bool load(
				Core::ktkMainManager& main_manager, const ktk::string& path);

		private:
			ktk::string m_path;
			ktk::string m_filename;
			Core::ktkFile m_file;
		};
	} // namespace Render
} // namespace Kotek