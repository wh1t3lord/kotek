#pragma once

#include "kotek_api_resource_manager.h"
#include "kotek_sdk_ui_element.h"
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

		// TODO: add helper namespace for translating this enum
		enum class folder_index_t : int
		{
			kFolderIndex_Root,
			kFolderIndex_Gamedata,
			kFolderIndex_Configs,
			kFolderIndex_Scripts,
			kFolderIndex_Textures,
			kFolderIndex_Shaders,
			kFolderIndex_Models,
			kFolderIndex_Sound,
			kFolderIndex_UserTests,
			kFolderIndex_UserData
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
				folder_index_t id) const noexcept = 0;
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

		enum class eResourceLoadingType : ktk::enum_base_t
		{
			kText,
			kTexture,
			kModel,
			kSound,
			kVideo,
			kDLL,
			kAutoDetect,
			kUnknown = -1
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

		enum class eResourceLoadingPolicy : ktk::enum_base_t
		{
			kAsync,
			kSync
		};

		enum class eResourceCachingPolicy : ktk::enum_base_t
		{
			// Returns constructed object
			kCache,

			// TODO: think about it and do we need really implement this?
			// Using temporary instances that resource manager has
			kWithoutCache
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
		};

		enum class eEngineFeature : ktk::enum_base_t
		{
			kEngine_Window_Windowed,
			kEngine_Window_Borderless,
			kEngine_Window_FullScreen,
			kEngine_Render_Feature_MSAA,
			kEngine_Render_Feature_VSYNC,
			kEngine_Render_Renderer_DirectX_7,
			kEngine_Render_Renderer_DirectX_8,
			kEngine_Render_Renderer_DirectX_9,
			kEngine_Render_Renderer_DirectX_10,
			kEngine_Render_Renderer_DirectX_11,
			kEngine_Render_Renderer_DirectX_12,
			kEngine_Render_Renderer_OpenGL3_3,
			kEngine_Render_Renderer_OpenGL4_6,
			kEngine_Render_Renderer_Vulkan,
			kEngine_Render_Renderer_Software,
			kEngine_Feature_Unknown = -1
		};

		constexpr const ktk::tchar* kRenderName_OpenGL = KOTEK_TEXT("OpenGL");
		constexpr const ktk::tchar* kRenderName_Vulkan = KOTEK_TEXT("Vulkan");

		constexpr const ktk::tchar* kRenderName_DirectX12 =
			KOTEK_TEXT("DirectX12");
		constexpr const ktk::tchar* kRenderName_DirectX11 =
			KOTEK_TEXT("DirectX11");
		constexpr const ktk::tchar* kRenderName_DirectX10 =
			KOTEK_TEXT("DirectX10");
		constexpr const ktk::tchar* kRenderName_DirectX9 =
			KOTEK_TEXT("DirectX9");
		constexpr const ktk::tchar* kRenderName_DirectX8 =
			KOTEK_TEXT("DirectX8");
		constexpr const ktk::tchar* kRenderName_DirectX7 =
			KOTEK_TEXT("DirectX7");

		constexpr const ktk::tchar* kRenderName_Software =
			KOTEK_TEXT("Software");

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