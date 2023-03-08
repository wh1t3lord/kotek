#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_CORE
enum class eFolderIndex;
enum class eResourceLoadingType;
enum class eResourceLoadingPolicy;
enum class eResourceCachingPolicy;
enum class eEngineFeature;
enum class eEngineFeatureRender;
enum class eEngineFeatureRenderer;
enum class eEngineFeatureRendererANGLE;
enum class eEngineFeatureSDK;
enum class eEngineFeatureWindow;
enum class eConsoleCommandIndex;
enum class eEngineSupportedOpenGLVersion;
enum class eEngineSupportedDirectXVersion;
enum class eEngineSupportedVulkanVersion;
enum class eInputType;
KOTEK_END_NAMESPACE_CORE

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
    ktk::cstring Translate_FolderIndex(eFolderIndex type);
    ktk::cstring Translate_EngineFeature(eEngineFeature type);
    ktk::cstring Translate_EngineFeatureRender(eEngineFeatureRender type);
    ktk::cstring Translate_EngineFeatureRenderer(eEngineFeatureRenderer type);
    ktk::cstring Translate_EngineFeatureRendererANGLE(
		eEngineFeatureRendererANGLE type);
    ktk::cstring Translate_EngineFeatureSDK(eEngineFeatureSDK type);
    ktk::cstring Translate_EngineFeatureWindow(eEngineFeatureWindow type);
    ktk::cstring Translate_EngineSupportedDirectXVersion(
		eEngineSupportedDirectXVersion type);
    ktk::cstring Translate_EngineSupportedOpenGLVersion(
		eEngineSupportedOpenGLVersion type);
    ktk::cstring Translate_EngineSupportedVulkanVersion(
		eEngineSupportedVulkanVersion type);
    ktk::cstring Translate_ResourceLoadingType(eResourceLoadingType type);
    ktk::cstring Translate_ResourceLoadingPolicy(eResourceLoadingPolicy type);
    ktk::cstring Translate_ResourceCachingPolicy(eResourceCachingPolicy type);
    ktk::cstring Translate_ConsoleCommandIndex(eConsoleCommandIndex type);
	ktk::cstring Translate_InputType(eInputType type);

	/// @brief accepts the form like 'major_version.minor_version', for example
	/// it parses strings like '1.3', the string is not acceptable like this
	/// '1'.
	/// @param version_name your string that contains only numbers and one
	/// separated dot symbol
	/// @return converted to appropriate version of OpenGL
	eEngineSupportedOpenGLVersion
	TranslateFromStringToEnum_EngineSupportedOpenGLVersion(
        const ktk::cstring& version_name);

	eEngineSupportedVulkanVersion
	TranslateFromStringToEnum_EngineSupportedVulkanVersion(
        const ktk::cstring& version_name);

	eEngineSupportedDirectXVersion
	TranslateFromStringToEnum_EngineSupportedDirectXVersion(
        const ktk::cstring& version_name);

	/// \~english @brief all converted becomes as specified_by_user or it takes
	/// the final version like it doesn't have specified_by_user and latest e.g.
	/// ANGLE or Software
	/// @param renderer_name ANGLE, Software, DirectX, Vulkan, OpenGL as quoted
	/// strings
	/// @return eEngineFeatureRenderer
	eEngineFeatureRenderer TranslateFromStringToEnum_EngineFeatureRenderer(
        const ktk::cstring& renderer_name);
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
