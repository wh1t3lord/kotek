#pragma once

#include <assimp/BaseImporter.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

class ktkModel
{
public:
	ktkModel(void);
	~ktkModel(void);

	bool Load(Core::ktkMainManager& main_manager, const ktk::string& path);

private:
	ktk::string m_path;
	ktk::string m_filename;
	Core::ktkFile m_file;
};

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK