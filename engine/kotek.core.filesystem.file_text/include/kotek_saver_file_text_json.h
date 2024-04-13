#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.io/include/kotek_core_containers_io.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkSaverFile_JSON : public ktkIResourceSaver
{
public:
	ktkSaverFile_JSON(ktkMainManager* p_main_manager);
	~ktkSaverFile_JSON();

	/// @brief This method saves your file on disk where you specified your full
	/// path
	/// @param path is not relative and you must specify full path to file. It
	/// means that you must specify folder where you want to save and filename
	/// with extension. For example, this path is invalid "C:/something" but
	/// this is valid "C:/something/filename.formatname". You must pass with
	/// file name and format name because system automatically detect what type
	/// of saver it should pick for saving your file.
	/// @param object_for_saving your data for saving, but it must be
	/// ktkTextFile instance
	/// @return status about saving, if it returns true means operation was
	/// successful otherwise it couldn't save your file
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
	/**
	 * Formats every field in json.
	 *
	 * \param file your ktk::ofstream instance for writing in it.
	 * \param json your json passed as .GetObject (boost)
	 * \param indent
	 * \return void
	 */
	void FormatTextFile_JSON(ktk::cofstream& file, const ktk::json::value& json,
		std::string* indent = nullptr) noexcept;

private:
	ktkMainManager* m_p_main_manager;
	ktk_unordered_map<ktk::cstring, ktkIResourceSaver*,
		KOTEK_DEF_JSON_RESOURCE_SAVERS_COUNT>
		m_savers;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
