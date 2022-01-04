#pragma once

#include "../kotek.core/kotek_file.h"

namespace Kotek
{
	namespace Render
	{
		class kotek_model
		{
		public:
			kotek_model(void);
			~kotek_model(void);

			bool load(
				Core::ktkMainManager& main_manager, const ktk::string& path);

		private:
			ktk::string m_path;
			ktk::string m_filename;
			Core::ktkFile m_file;
		};
	} // namespace Render
} // namespace Kotek