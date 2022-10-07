#include "../include/kotek_std_string.h"
#include <kotek.core.constants/include/kotek_core_constants.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

std::size_t hash_value(const string& instance)
{
	#ifdef KOTEK_USE_UNICODE
	hash<string_unicode> hasher;
	#else
	hash<string_legacy> hasher;
	#endif

	return hasher(instance.get_as_is());
}

ktk::string operator+(
	const ktk::string& data_left, const ktk::string& data_right) noexcept
{
	ktk::string result(data_left);

	result += data_right;

	return result;
}

ktk::string operator+(
	const ktk::string& data_left, const char* const p_string) noexcept
{
	ktk::string result(data_left);

	result += p_string;

	return result;
}

ktk::size_t string::get_hash(void) const noexcept
{
	return ktk::hash<ktk::string>()(*this);
}

void string::append_path(
	const ktk::string& your_folder_or_file_name_with_or_without_format) noexcept
{
	if (your_folder_or_file_name_with_or_without_format.empty())
	{
		KOTEK_MESSAGE_WARNING(
			"can't add text because you passed an empty string");
		return;
	}

	if (your_folder_or_file_name_with_or_without_format.get_as_is().back() !=
		kPathSeparator)
	{
		this->m_data += kPathSeparator;
	}

	this->m_data += your_folder_or_file_name_with_or_without_format.get_as_is();
}
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK