#pragma once

#include <filesystem>

namespace Kotek
{
	namespace ktk
	{
		using path = std::filesystem::path;

		// TODO: rename this project into just kotek.core.containers.filesystem
		namespace filesystem = std::filesystem;
	}
} // namespace Kotek