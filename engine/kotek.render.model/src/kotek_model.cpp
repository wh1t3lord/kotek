#include "../include/kotek_model.h"
#include <kotek.core/include/kotek_main_manager.h>

namespace Kotek
{
	namespace Render
	{
		ktkModel::ktkModel(void) {}

		ktkModel::~ktkModel(void) {}

		bool ktkModel::Load(
			Core::ktkMainManager& main_manager, const ktk::string& path)
		{
			if (path.empty())
			{
				KOTEK_MESSAGE("you passed an empty path!");
				return false;
			}

			if (main_manager.GetFileSystem()->IsValidPath(path) == false)
			{
				KOTEK_MESSAGE("you passed an invalid path!");
				return false;
			}

			bool status = this->m_file.Load(main_manager, path);

			if (status == false)
			{
				KOTEK_MESSAGE("failed to load json (maybe it's invalid): {}",
					path.get_as_is());
				return false;
			}

			if (this->m_file.IsKeyExist(KOTEK_TEXT("buffers")))
			{
				const Core::ktkJson& json =
					this->m_file.Get(KOTEK_TEXT("buffers"));

				KOTEK_MESSAGE("size of buffers: {}", json.GetObject().size());
			}

			return true;
		}
	} // namespace Render
} // namespace Kotek
