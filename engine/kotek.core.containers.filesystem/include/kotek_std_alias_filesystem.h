#pragma once

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
		namespace filesystem = std::filesystem;
#else
#endif
	} // namespace ktk
} // namespace Kotek