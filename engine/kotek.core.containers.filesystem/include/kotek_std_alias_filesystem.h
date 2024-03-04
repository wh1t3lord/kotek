#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
namespace filesystem = std::filesystem;

// todo: rename to filesystem when you finish static_path and all replacement to
// ktk_filesystem_path
namespace fs
{
	inline bool remove(const std::filesystem::path& target)
	{
		return std::filesystem::remove(target);
	}

	inline bool remove(const std::filesystem::path& target, std::error_code& code)
	{
		return std::filesystem::remove(target, code);
	}
}

#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK