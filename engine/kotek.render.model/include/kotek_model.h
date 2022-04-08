#pragma once

#include <kotek.core/include/kotek_file.h>

namespace Kotek
{
	namespace Render
	{
		class ktkModel
		{
		public:
			ktkModel(void);
			~ktkModel(void);

			bool Load(
				Core::ktkMainManager& main_manager, const ktk::string& path);

		private:
			ktk::string m_path;
			ktk::string m_filename;
			Core::ktkFile m_file;
		};
	} // namespace Render
} // namespace Kotek