#pragma once

#include "kotek_saver_file_text_json.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceSaverFile_Text : public ktkIResourceSaver
{
public:
	ktkResourceSaverFile_Text(ktkMainManager* p_main_manager);
	~ktkResourceSaverFile_Text();

	bool Save(const ktk::filesystem::path& path,
		ktk::any object_for_saving) noexcept override;

	bool DetectTypeByFullPath(
		const ktk::filesystem::path& path) noexcept override;

	ktk::string Get_UserDescription() const noexcept override;

	eResourceLoadingType Get_Type() const noexcept override;

	ktkIResourceSaver* Get_Saver(
		const ktk::filesystem::path& extension_of_file) noexcept override;

	ktk::string Get_AllSupportedFormats(void) const noexcept override;

private:
	void Register_Savers(void) noexcept;
	void Delete_Savers(void) noexcept;

private:
	ktkMainManager* m_p_main_manager;
	ktk::unordered_map<ktk::string, ktkIResourceSaver*> m_savers;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK