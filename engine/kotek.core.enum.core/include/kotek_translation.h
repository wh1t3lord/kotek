#pragma once

namespace Kotek
{
	namespace ktk
	{
		class string;
	}

	namespace Core
	{
		enum class eFolderIndex;
		enum class eResourceLoadingType;
		enum class eResourceLoadingPolicy;
		enum class eResourceCachingPolicy;
		enum class eEngineFeature;
		enum class eConsoleCommandIndex;
	} // namespace Core
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		namespace helper
		{
			ktk::string Translate_FolderIndex(eFolderIndex type);
			ktk::string Translate_EngineFeature(eEngineFeature type);
			ktk::string Translate_ResourceLoadingType(
				eResourceLoadingType type);
			ktk::string Translate_ResourceLoadingPolicy(
				eResourceLoadingPolicy type);
			ktk::string Translate_ResourceCachingPolicy(
				eResourceCachingPolicy type);
			ktk::string Translate_ConsoleCommandIndex(
				eConsoleCommandIndex type);
		} // namespace helper
	}     // namespace Core
} // namespace Kotek