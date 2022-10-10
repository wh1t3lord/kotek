#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK
class string;
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_CORE
enum class eFolderIndex;
enum class eResourceLoadingType;
enum class eResourceLoadingPolicy;
enum class eResourceCachingPolicy;
enum class eEngineFeature;
enum class eConsoleCommandIndex;
KOTEK_END_NAMESPACE_CORE

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
	ktk::string Translate_FolderIndex(eFolderIndex type);
	ktk::string Translate_EngineFeature(eEngineFeature type);
	ktk::string Translate_ResourceLoadingType(eResourceLoadingType type);
	ktk::string Translate_ResourceLoadingPolicy(eResourceLoadingPolicy type);
	ktk::string Translate_ResourceCachingPolicy(eResourceCachingPolicy type);
	ktk::string Translate_ConsoleCommandIndex(eConsoleCommandIndex type);
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK