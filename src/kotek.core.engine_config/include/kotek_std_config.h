#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.dll/include/kotek_core_containers_dll.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.constants.string/include/kotek_core_constants_string.h>
#include <kotek.core.containers.unordered_set/include/kotek_core_containers_unordered_set.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
// TODO: implement unit test for testing all methods about flags
// and class in general!
class ktkEngineConfig : public ktkIFrameworkConfig
{
public:
	ktkEngineConfig(void);

	~ktkEngineConfig(void);

	void Initialize() override;

	void Shutdown(void) override;

	bool IsFeatureEnabled(eEngineFeature id
	) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureRender id
	) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureRenderer id
	) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureSDK id
	) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureWindow id
	) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureRendererVendor id
	) const noexcept override;

	void SetFeatureStatus(
		eEngineFeature id, bool status
	) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureRender id, bool status
	) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureRenderer id, bool status
	) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureSDK id, bool status
	) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureWindow id, bool status
	) noexcept override;

	// passing false set to kUnknown
	void SetFeatureStatus(
		eEngineSupportedRenderer version, bool status
	) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureRendererVendor vendor, bool status
	) noexcept override;

	void SetFeatureStatus(
		const ktk_vector<
			eEngineSupportedRenderer,
			KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>&
			fallback_versions
	) noexcept override;
	void
	SetFeatureStatus(const ktk_vector<
					 eEngineFeatureRenderer,
					 KOTEK_DEF_FALLBACK_RENDERERS_COUNT>& gapis
	) noexcept override;

	eEngineFeature GetEngineFeature(void
	) const noexcept override;
	eEngineFeatureRender GetEngineFeatureRender(void
	) const noexcept override;
	eEngineFeatureRenderer GetEngineFeatureRenderer(void
	) const noexcept override;
	eEngineFeatureRendererVendor
	GetEngineFeatureRendererVendor(void
	) const noexcept override;
	eEngineFeatureSDK GetEngineFeatureSDK(void
	) const noexcept override;
	eEngineFeatureWindow GetEngineFeatureWindow(void
	) const noexcept override;
	eEngineSupportedRenderer GetRendererVersionEnum(void
	) const noexcept override;
	ktk::enum_base_t GetRendererVersion(void
	) const noexcept override;

	const ktk_vector<
		eEngineFeatureRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_COUNT>&
	GetFallbackRendereres(void) const noexcept override;
	const ktk_vector<
		eEngineSupportedRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>&
	GetFallbackRendererVersions(void) const noexcept override;

	ktk::cstring GetRenderName(void) const noexcept override;

	bool IsCurrentRenderLegacy(void) const noexcept override;

	bool IsCurrentRenderModern(void) const noexcept override;

	int GetARGC(void) const noexcept override;

	void SetARGC(int) noexcept override;

	char** GetARGV(void) const noexcept override;

	void SetARGV(char** p_char) noexcept override;

	bool IsContainsConsoleCommandLineArgument(
		const ktk::cstring& your_argument
	) const noexcept override;

	bool IsUserSpecifiedValidRenderer(void
	) const noexcept override;

	bool IsUserSpecifiedRendererOpenGLInCommandLine(void
	) const noexcept override;
	bool IsUserSpecifiedRendererDirectXInCommandLine(void
	) const noexcept override;
	bool IsUserSpecifiedRendererVulkanInCommandLine(void
	) const noexcept override;

	eEngineSupportedRenderer
	GetRendererVersionFromCommandLine(void
	) const noexcept override;

	bool IsApplicationWorking(void) const noexcept override;

	void SetApplicationWorking(bool status) noexcept override;

	void
	Set_UserLibrary(const ktk_filesystem_path& path_to_library
	) noexcept override;

	void* Get_UserLibrary(void) noexcept override;

	// we can't standardize the types of fields so we provide
	// these not methods for accessing through casting,
	// otherwise user must implement own version of engine
	// config with his interface if he doesn't like something in
	// ours. These methods for situation where user wants to
	// implement a functionality where fallback renderes are
	// differs of versions like if we failed to start 11 version
	// we go to 10 if failed 10 we go to 9 if failed 9 we go
	// to 8. Of course it is the most non trivial case and I
	// guess nobody will do that but who knows...
	// Standartization means standartization and you must handle
	// all possible situations...

	kun_ktk size_t Get_VideoMemoryTotal(void
	) const noexcept override;
	kun_ktk size_t Get_VideoMemoryForInitialize(void
	) const noexcept override;
	void Set_VideoMemoryForInitialize(kun_ktk size_t value
	) noexcept override;


	void Set_FS_PriorityList(const kun_ktk uint8_t (&arr
	)[static_cast<kun_ktk uint8_t>(
		eFileSystemPriorityType::kEndOfEnum
	)]) override;
	const kun_ktk uint8_t* Get_FS_PriorityList(void
	) const noexcept override;

	kun_ktk uint8_t Get_FS_PriorityListSize(void
	) const noexcept override;

	void Set_FS_FeaturesFlag(kun_ktk uint16_t features
	) override;

	kun_ktk uint16_t Get_FS_FeaturesFlag(void
	) const noexcept override;

	void Set_UserLibrary_CallbackName(
		eUserEngineLibraryCallbacks callback_id,
		const ktk_cstring<
			KOTEK_DEF_USER_ENGINE_LIBRARY_CALLBACK_NAME_LENGTH>&
			name
	) override;
	const char* Get_UserLibrary_CallbackName(
		eUserEngineLibraryCallbacks callback_id
	) const noexcept override;

	void Set_UserLibrary_Name(
		const ktk_cstring<
			KOTEK_DEF_USER_ENGINE_LIBRARY_NAME_LENGTH>& name
	) override;
	const char* Get_UserLibrary_Name(void) const noexcept override;

private:
	void Parse_CommandLine(void) noexcept;

private:
	kun_ktk uint8_t m_fs_priority_list[static_cast<
		kun_ktk uint8_t>(eFileSystemPriorityType::kEndOfEnum)];
	kun_ktk uint16_t m_fs_features_flag;
	int m_argc;
	char** m_argv;
	kun_ktk kun_mt atomic<bool> m_is_running;
	eEngineFeature m_engine_feature_flags;
	eEngineFeatureRender m_engine_feature_render_flags;
	eEngineFeatureRenderer m_engine_feature_renderer_flags;
	eEngineFeatureRendererVendor
		m_engine_feature_renderer_vendor_flags;
	eEngineFeatureSDK m_engine_feature_sdk_flags;
	eEngineFeatureWindow m_engine_feature_window_flags;
	kun_ktk enum_base_t m_version_renderer;
	kun_ktk size_t m_video_memory_for_initialize;
	ktk_cstring<KOTEK_DEF_USER_ENGINE_LIBRARY_NAME_LENGTH>
		m_user_dll_name;
	ktk_vector<
		ktk_cstring<
			KOTEK_DEF_USER_ENGINE_LIBRARY_CALLBACK_NAME_LENGTH>,
		static_cast<kun_ktk uint8_t>(
			eUserEngineLibraryCallbacks::kEndOfEnum
		)>
		m_user_engine_library_callbacks;
	ktk_vector<
		eEngineFeatureRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_COUNT>
		m_fallback_renderers;
	ktk_vector<
		eEngineSupportedRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>
		m_fallback_renderers_versions;
	ktk_unordered_set<
		kun_ktk cstring,
		KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT>
		m_parsed_command_line_arguments;
	kun_ktk dll::shared_library m_user_dll;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
