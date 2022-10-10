#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.dll/include/kotek_core_containers_dll.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.constants.string/include/kotek_core_constants_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

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

	/**
	 * Checks if specified logical feature is enabled. It uses when we
	 * want to check if something from eEngineFeature enum is enabled in
	 * our engine/system.
	 *
	 * Logical feature means it is just a bit for telling user that a
	 * such feature was initialized/created somewhere. But
	 * SetFeatureStatus is not for user! (Except the situation if he
	 * doesn't provide his own implementations)
	 *
	 * \param id the field of enum eEngineFeature
	 * \return true means feature is enabled otherwise it doesn't enable
	 * in system
	 *
	 * @see eEngineFeature enum that contains all supported or possible
	 * features that engine could have.
	 *
	 * @code
	 * // checks if current renderer is DirectX 11
	 * p_main_manager->Get_EngineConfig()->IsFeatureEnabled(eEngineFeature::kEngine_Render_Renderer_DirectX_11);
	 * @endcode
	 */
	bool IsFeatureEnabled(eEngineFeature id) const noexcept override;

	/**
	 * Setter for specify if feature we need enable or disable. Depends
	 * on bool value.
	 *
	 * \param id field from eEngineFeature enum.
	 * \param status true means we set the feature in map as enabled.
	 * But it doesn't enable physically something it is just a marker
	 * for noticing to user that a such feature is enabled in system (or
	 * somewhere was initialized). Otherwise we mark that feature is
	 * disable (e.g. it might be useful when you switch the renderer in
	 * one session like we go to OpenGL and after switch to DirectX, so
	 * OpenGL features will be set to false). \return void
	 */
	void SetFeatureStatus(eEngineFeature id, bool status) noexcept override;

	/**
	 * Get current renderer name in human-readable form.
	 *
	 * \return ktk::string
	 */
	ktk::string GetRenderName(void) const noexcept override;

	/**
	 * Get current renderer as a eEngineFeature type.
	 *
	 * \return some field from eEngineFeature enum.
	 */
	eEngineFeature GetRenderFeature(void) const noexcept override;

	/**
	 * All Graphics APIs that were created before Vulkan and DirectX12
	 * (and newer) marked as Legacy.
	 *
	 * \return if it is not DirectX12 or Vulkan it returns true
	 * otherwise it is a modern Graphics API.
	 */
	bool IsCurrentRenderLegacy(void) const noexcept override;

	/**
	 * Checks if selected and initialized renderer in system is modern.
	 * Modern by definition of author it is Vulkan or DirectX12 (or
	 * newer).
	 *
	 * \return if Vulkan or DirectX12 means true otherwise false means
	 * legacy.
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

private:
	/**
	 * Checks if feature is Graphics API. It means if the passed feature
	 * from enum eEngineFeature is Graphics API like DirectX, OpenGL,
	 * Vulkan, and etc.
	 *
	 * \param feature any field from eEngineFeature or anything what you
	 * like to pass in it from eEngineFeature enum. \return true means
	 * your feature is Graphics API like OpenGL or DirectX (more
	 * specifically like kEngine_Render_Renderer_DirectX_9 or
	 * kEngine_Render_Renderer_Vulkan). Otherwise it is not Graphics
	 * API.
	 */
	bool IsFeatureRender(eEngineFeature feature) const noexcept;

	void Parse_CommandLine(void) noexcept;

private:
	int m_argc;
	char** m_argv;
	ktk::mt::atomic<bool> m_is_running;
	ktk::vector<ktk::string> m_parsed_command_line_arguments;
	ktk::unordered_map<eEngineFeature, bool> m_engine_flags;
	ktk::dll::shared_library m_user_dll;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK