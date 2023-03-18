#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceSaverManager : public ktkIResourceSaverManager
{
public:
	ktkResourceSaverManager(void);
	~ktkResourceSaverManager(void);

	void Initialize(ktkIFileSystem* p_filesystem, ktkMainManager* p_main_manager) override;
	void Shutdown(void) override;

	void Set_Saver(eResourceLoadingType resource_type,
		ktkIResourceSaver* p_saver) override;

	ktkIResourceSaver* Get_Saver(
		eResourceLoadingType resource_type) const noexcept override;

	bool Save(
		const ktk::filesystem::path& path, ktk::any data) noexcept override;

protected:
	eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk::filesystem::path& path) noexcept override;

private:

	ktk::unordered_map<eResourceLoadingType, ktkIResourceSaver*> m_savers;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK