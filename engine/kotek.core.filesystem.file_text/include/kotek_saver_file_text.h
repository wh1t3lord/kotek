#pragma once

#include "kotek_saver_file_text_json.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceSaverFile_Text : public ktkIResourceSaver
{
public:
	ktkResourceSaverFile_Text(ktkMainManager* p_main_manager);
	~ktkResourceSaverFile_Text();

	bool Save(const ktk_filesystem_path& path,
		ktk::any object_for_saving) noexcept override;

	bool DetectTypeByFullPath(
		const ktk_filesystem_path& path) noexcept override;

    ktk::cstring Get_UserDescription() const noexcept override;

	eResourceLoadingType Get_Type() const noexcept override;

	ktkIResourceSaver* Get_Saver(
		const ktk_filesystem_path& extension_of_file) noexcept override;

    ktk::cstring Get_AllSupportedFormats(void) const noexcept override;

private:
	void Register_Savers(void) noexcept;
	void Delete_Savers(void) noexcept;

private:
	ktkMainManager* m_p_main_manager;
	ktk_unordered_map<ktk::cstring, ktkIResourceSaver*,
		KOTEK_DEF_TEXT_RESOURCE_SAVERS_COUNT>
		m_savers;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
