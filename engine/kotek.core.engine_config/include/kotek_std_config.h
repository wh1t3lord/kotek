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
// TODO: implement unit test for testing all methods about flags and class in
// general!
/**
 * Implementation class of ktkIEngineConfig interface.
 */
class ktkEngineConfig : public ktkIEngineConfig
{
public:
	/**
	 * default constructor
	 *
	 */
	ktkEngineConfig(void);

	/**
	 * default destructor
	 *
	 */
	~ktkEngineConfig(void);

	/**
	 * You must call this method for initializing the instance
	 *
	 */
	void Initialize(void) override;

	/**
	 * You must call this method for destroying the instance
	 *
	 */
	void Shutdown(void) override;

	bool IsFeatureEnabled(eEngineFeature id) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureRender id) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureRenderer id) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureSDK id) const noexcept override;
	bool IsFeatureEnabled(eEngineFeatureWindow id) const noexcept override;

	void SetFeatureStatus(eEngineFeature id, bool status) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureRender id, bool status) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureRenderer id, bool status) noexcept override;
	void SetFeatureStatus(eEngineFeatureSDK id, bool status) noexcept override;
	void SetFeatureStatus(
		eEngineFeatureWindow id, bool status) noexcept override;

	/// \~english @brief As a standard you can specify two versions, but one
	/// uses as loading and the second one for fallback scenarios. @see
	/// doxygen_standards_about_renderers
	/// @param version your version of eEngineSupportedOpenGLVersion
	/// @param status true means it will be added to set otherwise it will be
	/// removed from set
	void SetFeatureStatus(
		eEngineSupportedOpenGLVersion version, bool status) noexcept override;

	/// \~english @brief As a standard you can specify two versions, but one
	/// uses as loading and the second one for fallback scenarios. @see
	/// doxygen_standards_about_renderers
	/// @param version your version of eEngineSupportedDirectXVersion
	/// @param status true means it will be added to set otherwise it will be
	/// removed from set
	void SetFeatureStatus(
		eEngineSupportedDirectXVersion version, bool status) noexcept override;

	/// \~english @brief As a standard you can specify two versions, but one
	/// uses as loading and the second one for fallback scenarios. @see
	/// doxygen_standards_about_renderers
	/// @param version your version of eEngineSupportedVulkanVersion
	/// @param status true means it will be added to set otherwise it will be
	/// removed from set
	void SetFeatureStatus(
		eEngineSupportedVulkanVersion version, bool status) noexcept override;

	eEngineFeature GetEngineFeature(void) const noexcept override;
	eEngineFeatureRender GetEngineFeatureRender(void) const noexcept override;
	eEngineFeatureRenderer GetEngineFeatureRenderer(
		void) const noexcept override;
	eEngineFeatureSDK GetEngineFeatureSDK(void) const noexcept override;
	eEngineFeatureWindow GetEngineFeatureWindow(void) const noexcept override;

	eEngineSupportedDirectXVersion GetCurrentDirectXVersion(
		void) const noexcept override;
	eEngineSupportedOpenGLVersion GetCurrentOpenGLVersion(
		void) const noexcept override;
	eEngineSupportedVulkanVersion GetCurrentVulkanVersion(
		void) const noexcept override;

	eEngineSupportedDirectXVersion GetFallbackDirectXVersion(
		void) const noexcept override;
	eEngineSupportedOpenGLVersion GetFallbackOpenGLVersion(
		void) const noexcept override;
	eEngineSupportedVulkanVersion GetFallbackVulkanVersion(
		void) const noexcept override;

	/// @brief
	/// @param
	/// @return if it returns eEngineSupportedDirectXVersion::kUnknown it means
	/// that you didn't have any command line argument for DirectX
	eEngineSupportedDirectXVersion GetDirectXVersionFromCommandLine(
		void) const noexcept override;

	/// @brief
	/// @param
	/// @return if it returns eEngineSupportedOpenGLVersion::kUnknown it means
	/// that you didn't have any command line argument for OpenGL
	eEngineSupportedOpenGLVersion GetOpenGLVersionFromCommandLine(
		void) const noexcept override;

	/// @brief
	/// @param
	/// @return if it returns eEngineSupportedVulkanVersion::kUnknown it means
	/// that you didn't have any command line argument for Vulkan
	eEngineSupportedVulkanVersion GetVulkanVersionFromCommandLine(
		void) const noexcept override;

	/**
	 * Get current renderer name in human-readable form.
	 *
	 * \return ktk::string
	 */
	ktk::string GetRenderName(void) const noexcept override;

	/**
	 * All Graphics APIs that were created before Vulkan and DirectX12
	 * (and newer) marked as Legacy.
	 *
	 * \return if it is not IsCurrentRenderModern (e.g. OpenGL 3.3 or Vulkan 1.1
	 * or DirectX 11)
	 */
	bool IsCurrentRenderLegacy(void) const noexcept override;

	/**
	 * Checks if selected and initialized renderer in system is modern.
	 * Modern by definition of author it is Vulkan or DirectX12 (or
	 * newer).
	 *
	 * \return if your specified renderer version equals kRendererName_Latest
	 * means it is a modern version, otherwise false means legacy. (e.g. DirectX
	 * 12, OpenGL 4.6, Vulkan 1.3)
	 */
	bool IsCurrentRenderModern(void) const noexcept override;

	/**
	 * ARGC of main (entry point of application, see kotek project and
	 * its entry_point.cpp file)
	 *
	 * \return argc of main
	 */
	int GetARGC(void) const noexcept override;

	/**
	 * Setter for m_argc field
	 *
	 * \param data from argc of main function in entry_point.cpp of
	 * kotek project \return void
	 */
	void SetARGC(int) noexcept override;

	/**
	 * Getter of m_argv field. ARGV of main function in entry_point.cpp
	 * of kotek project.
	 *
	 * \return array of char* means everything that you specified in
	 * application.
	 */
	char** GetARGV(void) const noexcept override;

	/**
	 * Setter for argv of main function in entry_point.cpp of kotek
	 * project.
	 *
	 * \param p_char your argv
	 * \return void
	 */
	void SetARGV(char** p_char) noexcept override;

	/**
	 * Checks if specified string exists in console command line
	 * argument list or just in argv (m_argv field of class).
	 *
	 * \param your_argument your string
	 * \return true means it exists otherwise it doesn't present
	 */
	bool IsContainsConsoleCommandLineArgument(
		const ktk::string& your_argument) const noexcept override;

	bool IsUserSpecifiedValidRenderer(void) const noexcept override;

	bool IsUserSpecifiedRendererOpenGLInCommandLine(
		void) const noexcept override;
	bool IsUserSpecifiedRendererDirectXInCommandLine(
		void) const noexcept override;
	bool IsUserSpecifiedRendererVulkanInCommandLine(
		void) const noexcept override;

	/**
	 * Returns the status of application working.
	 *
	 * \return true means that application is working and should work.
	 * Otherwise if it was set to false it means that ALL things (while
	 * loops) will be terminated and leave their scopes, it means that
	 * application goes to shutdown mode and quits.
	 */
	bool IsApplicationWorking(void) const noexcept override;

	/**
	 * Setter for specifying status of executing the application.
	 *
	 * \param status passing true means application should work, passing
	 * false means we quit from application immediately! \return void
	 */
	void SetApplicationWorking(bool status) noexcept override;

	/**
	 * Loader for passing .dll or .so or any other file that represents
	 * the compiled file that contains user implementation of engine.
	 *
	 * \param path_to_library full path where the file is located. It
	 * means you need to pass with filename and format. \return nothing
	 */
	void Set_UserLibrary(
		const ktk::filesystem::path& path_to_library) noexcept override;

	/**
	 * Return the hidden instance of ktk::dll::shared_library.
	 *
	 * \return anonymous representation of ktk::dll::shared_library
	 * class. It means you need to cast to ktk::dll::shared_library*
	 * type.
	 */
	void* Get_UserLibrary(void) noexcept override;

	// we can't standardize the types of fields so we provide these not virtual
	// methods for accessing through casting, otherwise user must implement own
	// version of engine config with his interface if he doesn't like something
	// in ours. These methods for situation where user wants to implement a
	// functionality where fallback renderes are differs of versions like if we
	// failed to start 11 version we go to 10 if failed 10 we go to 9 if failed
	// 9 we go to 8. Of course it is the most non trivial case and I guess
	// nobody will do that but who knows...
	// Standartization means standartization and you must handle all possible
	// situations...

	const ktk::unordered_set<eEngineSupportedDirectXVersion>&
	Get_SpecifiedVersionsDirectX(void) const noexcept;
	const ktk::unordered_set<eEngineSupportedOpenGLVersion>&
	Get_SpecifiedVersionsOpenGL(void) const noexcept;
	const ktk::unordered_set<eEngineSupportedVulkanVersion>&
	Get_SpecifiedVersionsVulkan(void) const noexcept;

private:
	void Parse_CommandLine(void) noexcept;

private:
	int m_argc;
	char** m_argv;
	ktk::mt::atomic<bool> m_is_running;
	eEngineFeature m_engine_feature_flags;
	eEngineFeatureRender m_engine_feature_render_flags;
	eEngineFeatureRenderer m_engine_feature_renderer_flags;
	eEngineFeatureSDK m_engine_feature_sdk_flags;
	eEngineFeatureWindow m_engine_feature_window_flags;
	ktk::unordered_set<eEngineSupportedDirectXVersion>
		m_engine_specified_versions_directx;
	ktk::unordered_set<eEngineSupportedOpenGLVersion>
		m_engine_specified_versions_opengl;
	ktk::unordered_set<eEngineSupportedVulkanVersion>
		m_engine_specified_versions_vulkan;
	ktk::unordered_set<ktk::string> m_parsed_command_line_arguments;
	ktk::dll::shared_library m_user_dll;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK