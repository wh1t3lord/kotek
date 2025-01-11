#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

enum class eFolderIndex;
enum class eResourceLoadingType;
enum class eResourceLoadingPolicy;
enum class eResourceCachingPolicy;
enum eEngineFeature;
enum eEngineFeatureRender;
enum eEngineFeatureRenderer;
enum eEngineFeatureRendererANGLE;
enum eEngineFeatureSDK;
enum eEngineFeatureWindow;
enum class eConsoleCommandIndex;
enum class eEngineSupportedRenderer;
enum class eInputType;
enum eInputControllerType;
enum eInputControllerMouseData;
enum eInputKeyboardKeys;
enum eInputKeyboardKeysNumbers;
enum eInputKeyboardKeysFunctionKeys;
enum eInputKeyboardKeysOther;
enum eInputKeyboardKeysEnter;
enum eInputKeyboardKeysNumpad;
enum eInputKeyboardKeysApplication;
enum eInputKeyboardKeysSystem;
enum eInputKeyboardCursorControlKeys;
enum eInputMouseKeys;
enum eInputPlatformBackend;
enum eInputAllKeys;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
	// TODO: provide static implementation especially with const char* implementations because strings live in .TEXT section
	ktk::cstring Translate_FolderIndex(eFolderIndex type);
	ktk::cstring Translate_EngineFeature(eEngineFeature type);
	ktk::cstring Translate_EngineFeatureRender(eEngineFeatureRender type);
	ktk::cstring Translate_EngineFeatureRenderer(eEngineFeatureRenderer type);
	ktk::cstring Translate_EngineSupportedRenderer(
		eEngineSupportedRenderer type);
	ktk::cstring Translate_EngineFeatureRendererANGLE(
		eEngineFeatureRendererANGLE type);
	ktk::cstring Translate_EngineFeatureSDK(eEngineFeatureSDK type);
	ktk::cstring Translate_EngineFeatureWindow(eEngineFeatureWindow type);

	ktk::cstring Translate_EngineSupportedRenderer(
		eEngineSupportedRenderer type);
	ktk::cstring Translate_ResourceLoadingType(eResourceLoadingType type);
	ktk::cstring Translate_ResourceLoadingPolicy(eResourceLoadingPolicy type);
	ktk::cstring Translate_ResourceCachingPolicy(eResourceCachingPolicy type);
	ktk::cstring Translate_ConsoleCommandIndex(eConsoleCommandIndex type);
	ktk::cstring Translate_InputType(eInputType type);


	const char* Translate_InputControllerType(eInputControllerType type);
	const char* Translate_InputControllerMouseData(
		eInputControllerMouseData type);
	const char* Translate_InputKeyboardKeys(eInputKeyboardKeys type);
	const char* Translate_InputKeyboardKeysNumbers(
		eInputKeyboardKeysNumbers type);
	const char* Translate_InputKeyboardKeysFunctionKeys(
		eInputKeyboardKeysFunctionKeys type);
	const char* Translate_InputKeyboardKeysOther(eInputKeyboardKeysOther type);
	const char* Translate_InputKeyboardKeysEnter(eInputKeyboardKeysEnter type);
	const char* Translate_InputKeyboardKeysNumpad(
		eInputKeyboardKeysNumpad type);
	const char* Translate_InputKeyboardKeysApplication(
		eInputKeyboardKeysApplication type);
	const char* Translate_InputKeyboardKeysSystem(
		eInputKeyboardKeysSystem type);
	const char* Translate_InputKeyboardCursorControlKeys(
		eInputKeyboardCursorControlKeys type);
	const char* Translate_InputMouseKeys(eInputMouseKeys type);
	const char* Translate_InputPlatformBackend(eInputPlatformBackend type);
	const char* Translate_InputAllKeys(eInputAllKeys type);
	
	/// @brief accepts the form like 'major_version.minor_version', for example
	/// it parses strings like '1.3', the string is not acceptable like this
	/// '1'.
	/// @param version_name your string that contains only numbers and one
	/// separated dot symbol
	/// @return converted to appropriate version of OpenGL
	eEngineSupportedRenderer TranslateFromStringToEnum_EngineSupportedRenderer(
		const ktk::cstring& renderer_name, const ktk::cstring& version_name);

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
