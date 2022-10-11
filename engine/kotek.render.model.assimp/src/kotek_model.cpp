#include "../include/kotek_model.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
ktkModel::ktkModel(void) {}

ktkModel::~ktkModel(void) {}

bool ktkModel::Load(Core::ktkMainManager& main_manager, const ktk::string& path)
{
	if (path.empty())
	{
		KOTEK_MESSAGE("you passed an empty path!");
		return false;
	}

	// TODO: write loader for this stuff, file can't call from itself loader and
	// saver
	//		bool status = this->m_file.Load(main_manager, path);
	bool status = false;
	KOTEK_ASSERT(false, "not implemented!");

	if (status == false)
	{
		KOTEK_MESSAGE(
			"failed to load json (maybe it's invalid): {}", path.get_as_is());
		return false;
	}

	if (this->m_file.IsKeyExist(KOTEK_TEXT("buffers")))
	{
		const Core::ktkJson& json = this->m_file.Get(KOTEK_TEXT("buffers"));

		KOTEK_MESSAGE("size of buffers: {}", json.GetObject().size());
	}

	return true;
}
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK