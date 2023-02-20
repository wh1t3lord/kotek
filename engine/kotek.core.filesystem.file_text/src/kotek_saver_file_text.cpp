#include "../include/kotek_saver_file_text.h"
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceSaverFile_Text::ktkResourceSaverFile_Text(
	ktkMainManager* p_main_manager) :
	m_p_main_manager{p_main_manager}
{
	this->Register_Savers();
}

ktkResourceSaverFile_Text::~ktkResourceSaverFile_Text()
{
	this->Delete_Savers();
}

bool ktkResourceSaverFile_Text::Save(
	const ktk::filesystem::path& path, ktk::any object_for_saving) noexcept
{
	KOTEK_ASSERT(this->m_p_main_manager,
		"you must initialize main manager for this loader");

	KOTEK_ASSERT(path.empty() == false,
		"you can't pass an empty string of your path to file!");

	auto* p_validation = this->Get_Saver(path.extension());

	KOTEK_ASSERT(p_validation,
		"this class doesn't support your file format: [{}]", path.extension());

	bool status = p_validation->Save(path, object_for_saving);

	return status;
}

bool ktkResourceSaverFile_Text::DetectTypeByFullPath(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(
		path.empty() == false, "you must pass a not empty path to file!");

	KOTEK_ASSERT(path.has_extension(),
		"you must have extension for your file, supported extensions "
		"for analyze: [{}]",
		this->Get_AllSupportedFormats());

	return this->m_savers.find(reinterpret_cast<const char*>(
			   path.extension().u8string().c_str())) != this->m_savers.end();
}

ktk::cstring ktkResourceSaverFile_Text::Get_UserDescription() const noexcept
{
	return KOTEK_TEXT("this is saver for Text files");
}

eResourceLoadingType ktkResourceSaverFile_Text::Get_Type() const noexcept
{
	return eResourceLoadingType::kText;
}

ktkIResourceSaver* ktkResourceSaverFile_Text::Get_Saver(
	const ktk::filesystem::path& extension_of_file) noexcept
{
	KOTEK_ASSERT(extension_of_file.empty() == false,
		"your extension is an empty string");

	Core::ktkIResourceSaver* p_result{};
	if (this->m_savers.find(reinterpret_cast<const char*>(
			extension_of_file.u8string().c_str())) == this->m_savers.end())
		return p_result;

	p_result = this->m_savers.at(
		reinterpret_cast<const char*>(extension_of_file.u8string().c_str()));

	KOTEK_ASSERT(p_result,
		"your m_loaders field contains invalid pointer of loader instance");

	return p_result;
}

ktk::cstring ktkResourceSaverFile_Text::Get_AllSupportedFormats(
	void) const noexcept
{
	ktk::cstring result;
	for (const auto& [format_name, p_saver] : this->m_savers)
	{
		result += format_name;
		result += " ; ";
	}

	result.pop_back();
	result.pop_back();
	result.pop_back();

	return result;
}

void ktkResourceSaverFile_Text::Register_Savers(void) noexcept
{
	this->m_savers[".json"] = new ktkSaverFile_JSON(this->m_p_main_manager);
}

void ktkResourceSaverFile_Text::Delete_Savers(void) noexcept
{
	for (const auto& [format_name, p_saver] : this->m_savers)
	{
#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("deleting saver: {}", p_saver->Get_UserDescription());
#endif
		delete p_saver;
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
