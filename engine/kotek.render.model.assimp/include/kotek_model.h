#pragma once

#include <assimp/BaseImporter.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkModel
{
public:
	ktkModel(void);
	~ktkModel(void);

	bool Load(Core::ktkMainManager& main_manager, const ktk::ustring& path);

private:
	ktk::ustring m_path;
	ktk::ustring m_filename;
	Core::ktkFileText m_file;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK