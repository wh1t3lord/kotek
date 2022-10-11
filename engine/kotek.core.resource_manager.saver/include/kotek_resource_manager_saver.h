#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceSaverManager : public ktkIResourceSaver
{
public:
	ktkResourceSaverManager(void);
	~ktkResourceSaverManager(void);

	void Initialize(ktkIFileSystem* p_filesystem) override;
	void Shutdown(void) override;

	/**
	 * Creates a file with content that you passed to this function
	 *
	 * \param path full path to your folder where file will be created,
	 * without file name and format. \param data is ktkFile* with valid
	 * m_file_name field that will be called from
	 * Kotek::Core::ktkFile#Get_FileName, that field contains filename
	 * and format something like "example_txt.kFormatFile_Text". \return
	 * true means that saving is successed otherwise something went
	 * wrong
	 */
	bool Save_Text(
		const ktk::filesystem::path& path, ktk::any data) noexcept override;

	/**
	 * Save file as #Save_Text but with formatting the file makign it
	 * looks pretty good and readable for user.
	 *
	 * \param path full path to your folder where file will be created
	 * without file name and format. \param data is ktkFile* \return
	 * true means success otherwise something went bad.
	 *
	 * @see Kotek::Core::ktkResourceSaverManager#FormatTextFile_Json is
	 * an implementation of formatting the file which is called in
	 * Save_Text_Formatted method
	 * @see Save_Text is not formatted version
	 */
	bool Save_Text_Formatted(
		const ktk::filesystem::path& path, ktk::any data) noexcept override;

private:
	/**
	 * Formats every field in json.
	 *
	 * \param file your ktk::ofstream instance for writing in it.
	 * \param json your json passed as .GetObject (boost)
	 * \param indent
	 * \return void
	 */
	void FormatTextFile_Json(ktk::ofstream& file, const ktk::json::value& json,
		std::string* indent = nullptr) noexcept;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK