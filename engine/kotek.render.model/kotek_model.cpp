#include "kotek_gltf_model.h"
#include "../kotek.core/kotek_main_manager.h"

namespace Kotek
{
	namespace Render
	{
		kotek_gltf_model::kotek_gltf_model(void) {}

		kotek_gltf_model::~kotek_gltf_model(void) {}

		bool kotek_gltf_model::load(
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
