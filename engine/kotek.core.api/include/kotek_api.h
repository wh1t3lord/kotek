#pragma once

#include "kotek_api_resource_manager.h"
#include "kotek_sdk_ui_element.h"
#include <kotek.core.enum/include/kotek_core_enum.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.containers.shared_ptr/include/kotek_core_containers_shared_ptr.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
		class ktkIRenderDevice;
		class ktkIRenderSwapchain;
		class ktkIRenderGraph;
		class kotek_i_render_imgui;
		class ktkIRenderResourceManager;
		class kotek_i_renderer;
		class ktkProfiler;
		class ktkConsole;
	} // namespace Core

	namespace Engine
	{
		class ktkWindow;
	}

	namespace ktk
	{
		class string;
	}
} // namespace Kotek

struct GLFWwindow;

namespace Kotek
{
	namespace Core
	{
		class ktkIRenderDevice
		{
		public:
			virtual ~ktkIRenderDevice(void) {}

			virtual void Initialize(Core::ktkMainManager* main_manager) = 0;
			virtual void Shutdown(void) = 0;
			virtual void Resize(ktkIRenderSwapchain* p_raw_swapchain,
				kotek_i_renderer* p_raw_renderer,
				ktkIRenderResourceManager* p_raw_resource_manager, int width,
				int height) = 0;

			virtual int GetWidth(void) const noexcept = 0;
			virtual int GetHeight(void) const noexcept = 0;
			virtual void GPUFlush(void) = 0;
		};

		class ktkIRenderSwapchain
		{
		public:
			virtual ~ktkIRenderSwapchain(void) {}

			virtual void Initialize(ktkIRenderDevice* p_render_device) = 0;
			virtual void Shutdown(ktkIRenderDevice* p_render_device) = 0;
			virtual void Resize(
				ktkIRenderDevice* p_render_device, int width, int height) = 0;
		};

		class ktkIRenderResourceManager
		{
		public:
			virtual ~ktkIRenderResourceManager(void) {}

			// TODO: change signature on void
			virtual void initialize(ktkIRenderDevice* p_raw_device,
				ktkIRenderSwapchain* p_raw_swapchain) = 0;

			// TODO: change signature on void
			virtual void shutdown(ktkIRenderDevice* p_raw_device) = 0;

			virtual void Resize(ktkIRenderDevice* p_raw_device,
				ktkIRenderSwapchain* p_raw_swapchain) = 0;
		};

		class ktkIRenderGraphResourceManager
		{
		public:
			virtual ~ktkIRenderGraphResourceManager(void) {}

			virtual void Initialize(
				Kotek::Render::gl::eRenderGraphBuilderType type_of_framebuffer,
				Kotek ::Render::gl::eRenderGraphBuilderPipelineRenderingType
					type_videocard_pipeline) = 0;
			virtual void Shutdown(void) = 0;
		};

		class kotek_i_render_imgui
		{
		public:
			virtual ~kotek_i_render_imgui(void) {}

			// TODO: change signature on void
			virtual void initialize(ktkMainManager& main_manager) noexcept = 0;

			// TODO: change signature on void
			virtual void shutdown(ktkIRenderDevice* p_raw_device) noexcept = 0;
		};

		class ktkIRenderGraph
		{
		public:
			virtual ~ktkIRenderGraph(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class kotek_i_renderer
		{
		public:
			virtual ~kotek_i_renderer(void) {}
			virtual void draw(void) = 0;
			virtual void Shutdown(void) = 0;
			virtual void Resize(void) = 0;
			virtual ktk::string GetName(void) const noexcept = 0;
		};

		class ktkIFileSystem
		{
		public:
			virtual ~ktkIFileSystem(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
			virtual bool IsValidPath(
				const ktk::filesystem::path& path) const noexcept = 0;

			// TODO: check todo in implementation class ktkFileSystem and it is
			// a temporary virtual function delete it
			virtual ktk::string ReadFile(
				const ktk::filesystem::path& path_to_file) const noexcept = 0;

			virtual const ktk::filesystem::path& GetFolderByEnum(
				eFolderIndex id) const noexcept = 0;
		};

		class ktkIInput
		{
		public:
			virtual ~ktkIInput(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

			virtual void SetMouseX(float value) noexcept = 0;
			virtual float GetMouseX(void) const noexcept = 0;

			virtual void SetMouseY(float value) noexcept = 0;
			virtual float GetMouseY(void) const noexcept = 0;

			virtual void SetMouseLastX(float value) noexcept = 0;
			virtual float GetMouseLastX(void) const noexcept = 0;

			virtual void SetMouseLastY(float value) noexcept = 0;
			virtual float GetMouseLastY(void) const noexcept = 0;

			virtual void SetMouseSensitivity(float value) noexcept = 0;
			virtual float GetMouseSensitivity(void) const noexcept = 0;
		};

		class ktkIGameManager
		{
		public:
			virtual ~ktkIGameManager(void) {}

			virtual void Initialize(ktkMainManager* p_main_manager) = 0;

			virtual void Shutdown(ktkMainManager* p_main_manager) = 0;

			virtual kotek_i_renderer* GetRenderer(void) const noexcept = 0;

			virtual void* GetWindowHandle(void) const noexcept = 0;
			virtual ktkProfiler* GetProfiler(void) const noexcept = 0;
			virtual int GetWindowWidth(void) const noexcept = 0;
			virtual int GetWindowHeight(void) const noexcept = 0;
			virtual ktkConsole* GetConsole(void) const noexcept = 0;

			// @ returns USER render resource manager it's not kotek
			virtual void* GetRenderResourceManager(void) const noexcept = 0;
			virtual void* CreateSurface(ktkMainManager* p_main_manager,
				void* p_instance, const void* p_callbacks) = 0;
		};

		class ktkIResourceLoader
		{
		public:
			virtual ~ktkIResourceLoader(void) {}

			virtual void Initialize(ktkIFileSystem*) = 0;
			virtual void Shutdown(void) = 0;

#pragma region Load only by path
			virtual ktk::any Load_Text(
				const ktk::filesystem::path& path) noexcept = 0;

			virtual ktk::any Load_Texture(
				const ktk::filesystem::path& path) noexcept = 0;

			virtual ktk::any Load_Model(
				const ktk::filesystem::path& path) noexcept = 0;

			virtual ktk::any Load_Sound(
				const ktk::filesystem::path& path) noexcept = 0;

			virtual ktk::any Load_Video(
				const ktk::filesystem::path& path) noexcept = 0;

			virtual ktk::any Load_CPlusPlusLibrary(
				const ktk::filesystem::path& path) noexcept = 0;
#pragma endregion

#pragma region Load path& object_from_construct
			virtual bool Load_Text(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept = 0;

			virtual bool Load_Texture(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept = 0;

			virtual bool Load_Model(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept = 0;

			virtual bool Load_Sound(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept = 0;

			virtual bool Load_Video(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept = 0;
#pragma endregion

		protected:
			virtual eResourceLoadingType DetectResourceTypeByFileFormat(
				const ktk::filesystem::path& path) noexcept = 0;

			ktkIFileSystem* m_p_manager_filesystem;
		};

		class ktkIResourceSaver
		{
		public:
			ktkIResourceSaver(void) : m_p_manager_filesystem{} {}

			/**
			 * Just a virtual destructor in order to being called from child
			 * destructors
			 *
			 */
			virtual ~ktkIResourceSaver(void) {}

			virtual void Initialize(ktkIFileSystem*) = 0;
			virtual void Shutdown(void) = 0;

			/**
			 * Interface (pure virtual) method for saving text file without
			 * formatting @see
			 * Kotek::Core::ktkIResourceSaver#Save_Text_Formatted
			 *
			 * \param path supposed to be a path where to save the file with
			 * file name and format of it. \param data user dependent. Default
			 * implementation is based on ktkFile class. @see ktkFile. \return
			 * simplified status of executing. true means success otherwise
			 * something went wrong. User dependent.
			 */
			virtual bool Save_Text(
				const ktk::filesystem::path& path, ktk::any data) noexcept = 0;

			/**
			 * Interface (pure virtual) method for saving text file with
			 * formatting that applied in user implementation. @see
			 * Kotek::Core::ktkIResourceSaver#Save_Text it is not formatting
			 * method for saving.
			 *
			 * \param path supposed a path where to save the file with file name
			 * and format of it. \param data user dependent. Default
			 * implementation is @see ktkFile class. \return simplified status
			 * of executing. True means success otherwise something went wrong.
			 * User dependent.
			 *
			 *
			 * Example if you want to save your file on stack. Otherwise
			 * you will get from your resource manager (or from default
			 * implementation) your ktkFile* and you need to pass to that
			 * method) ktkFile text_file_instance;
			 *
			 * @code
			 * text_file_instance.Write("my_new_field", "string_data");
			 *
			 * Kotek::Core::ktkIResourceSaver*
			 * p_valid_interface_instance->Save_Text_Formatted("C:/YourFolder/filename.json",
			 * &text_file_instance);
			 * @endcode
			 */
			virtual bool Save_Text_Formatted(
				const ktk::filesystem::path& path, ktk::any data) noexcept = 0;

		protected:
			ktkIFileSystem* m_p_manager_filesystem;
		};

		class ktkLoadingRequest
		{
		public:
			ktkLoadingRequest(eResourceLoadingPolicy type_loading,
				eResourceCachingPolicy type_policy_caching,
				eResourceLoadingType type_of_loading_resource,
				const ktk::filesystem::path& resource_path) :
				m_policy_loading{type_loading},
				m_policy_caching{type_policy_caching},
				m_resource_type{type_of_loading_resource}, m_resource_path{
															   resource_path}
			{
			}

			ktkLoadingRequest(void) :
				m_policy_caching{},
				m_policy_loading{eResourceLoadingPolicy::kAsync},
				m_resource_type{eResourceLoadingType::kAutoDetect}
			{
			}

			~ktkLoadingRequest() = default;

			virtual ktkLoadingRequest& Set_LoadingPolicy(
				eResourceLoadingPolicy policy) noexcept
			{
				this->m_policy_loading = policy;
			}

			virtual eResourceLoadingPolicy Get_LoadingPolicy(
				void) const noexcept
			{
				return this->m_policy_loading;
			}

			virtual ktkLoadingRequest& Set_CachingPolicy(
				eResourceCachingPolicy policy) noexcept
			{
				this->m_policy_caching = policy;
			}

			virtual eResourceCachingPolicy Get_CachingPolicy(
				void) const noexcept
			{
				return this->m_policy_caching;
			}

			virtual ktkLoadingRequest& Set_ResourceType(
				eResourceLoadingType type) noexcept
			{
				this->m_resource_type = type;
			}

			virtual eResourceLoadingType Get_ResourceType() const noexcept
			{
				return this->m_resource_type;
			}

			virtual ktkLoadingRequest& Set_ResourcePath(
				const ktk::filesystem::path& path) noexcept
			{
				this->m_resource_path = path;
			}

			virtual const ktk::filesystem::path& Get_ResourcePath(
				void) const noexcept
			{
				return this->m_resource_path;
			}

		private:
			eResourceLoadingPolicy m_policy_loading;
			eResourceCachingPolicy m_policy_caching;
			eResourceLoadingType m_resource_type;
			ktk::filesystem::path m_resource_path;
		};

		class ktkIResourceManager
		{
		public:
			virtual ~ktkIResourceManager(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

			template <typename ResourceType>
			ResourceType Load(const ktkLoadingRequest& request) noexcept
			{
				return any_cast<ResourceType>(this->Load_Resource(request));
			}

			virtual void Set_ResourceLoader(
				ktkIResourceLoader* p_instance) noexcept = 0;
			virtual ktkIResourceLoader* Get_ResourceLoader(
				void) const noexcept = 0;

			virtual void Set_MainManager(
				ktkMainManager* p_instance) noexcept = 0;
			virtual ktkMainManager* Get_MainManager(void) const noexcept = 0;

			virtual void Update_WorkerQueue(void) noexcept = 0;

			// TODO: implement saving

		protected:
			virtual ktk::any Load_Resource(
				const ktkLoadingRequest& request) = 0;
		};

		class ktkIResourceCacherManager
		{
		public:
			virtual ~ktkIResourceCacherManager(void) {}
		};

		class ktkIConsole
		{
		public:
			virtual ~ktkIConsole() {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIProfiler
		{
		public:
			virtual ~ktkIProfiler(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

			virtual void FrameMark(void) = 0;
		};

		class ktkIProfilerCPU
		{
		public:
			virtual ~ktkIProfilerCPU(void) {}
			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIProfilerGPU
		{
		public:
			virtual ~ktkIProfilerGPU(void) {}
			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIEngineConfig
		{
		public:
			virtual ~ktkIEngineConfig(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

			virtual bool IsFeatureEnabled(eEngineFeature id) const noexcept = 0;
			virtual void SetFeatureStatus(
				eEngineFeature id, bool status) noexcept = 0;
			virtual ktk::string GetRenderName(void) const noexcept = 0;
			virtual eEngineFeature GetRenderFeature(void) const noexcept = 0;
			virtual bool IsCurrentRenderLegacy(void) const noexcept = 0;
			virtual bool IsCurrentRenderModern(void) const noexcept = 0;
			virtual int GetARGC(void) const noexcept = 0;
			virtual char** GetARGV(void) const noexcept = 0;
			virtual void SetARGC(int) noexcept = 0;
			virtual void SetARGV(char**) noexcept = 0;
			virtual bool IsContainsConsoleCommandLineArgument(
				const ktk::string& your_argument) const noexcept = 0;
			virtual bool IsApplicationWorking(void) const noexcept = 0;
			virtual void SetApplicationWorking(bool status) noexcept = 0;
			virtual void Set_UserLibrary(
				const ktk::filesystem::path& path_to_library) noexcept = 0;
			virtual void* Get_UserLibrary(void) noexcept = 0;
		};

		class ktkIComponentAllocator
		{
		public:
			virtual ~ktkIComponentAllocator() {}

			virtual bool Create(ktk::entity_t id) noexcept = 0;
			virtual void* Get(ktk::entity_t id) noexcept = 0;
			virtual bool Remove(ktk::entity_t id) noexcept = 0;
			virtual ktk::string GetDebugName(void) const noexcept = 0;
			virtual ktk::string GetComponentName(void) const noexcept = 0;
			virtual void DrawImGui(Kotek::Core::ktkMainManager* main_manager,
				Kotek::ktk::entity_t entity_id) noexcept = 0;
		};

		bool InitializeModule_Core_API(ktkMainManager*);
		bool ShutdownModule_Core_API(ktkMainManager*);
		bool SerializeModule_Core_API(ktkMainManager*);
		bool DeserializeModule_Core_API(ktkMainManager*);
	} // namespace Core
} // namespace Kotek