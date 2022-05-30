#pragma once

#include "kotek_api_resource_manager.h"
#include "kotek_sdk_ui_element.h"
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.containers.shared_ptr/include/kotek_core_containers_shared_ptr.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
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

			virtual void Initialize(Core::ktkMainManager& main_manager) = 0;
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

		class ktkIConsole
		{
		public:
			virtual ~ktkIConsole(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIFileSystem
		{
		public:
			virtual ~ktkIFileSystem(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIInput
		{
		public:
			virtual ~ktkIInput(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
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
			kAutoDetect,
			kUnknown = kAutoDetect
		};

		class ktkIResourceLoader
		{
		public:
			virtual ~ktkIResourceLoader(void) {}

			virtual ktk::any LoadText(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadTexture(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadModel(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadSound(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadVideo(const ktk::string& path) noexcept = 0;

			virtual ktk::any LoadText(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadTexture(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadModel(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadSound(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadVideo(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

		protected:
			virtual eResourceLoadingType DetectResourceTypeByFileFormat(
				const ktk::string& path) noexcept = 0;
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

			// Using temporary instances that resource manager has
			kWithoutCache
		};

		class ktkLoadingRequest
		{
		public:
			ktkLoadingRequest(eResourceLoadingPolicy type_loading,
				eResourceCachingPolicy type_policy_caching,
				eResourceLoadingType type_of_loading_resource,
				const ktk::string& resource_path) :
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

			ktkLoadingRequest& SetLoadingPolicy(
				eResourceLoadingPolicy policy) noexcept;
			eResourceLoadingPolicy GetLoadingPolicy(void) const noexcept;

			ktkLoadingRequest& SetCachingPolicy(
				eResourceCachingPolicy policy) noexcept;
			eResourceCachingPolicy GetCachingPolicy(void) const noexcept;

			ktkLoadingRequest& SetResourceType(
				eResourceLoadingType type) noexcept;
			eResourceLoadingType GetResourceType() const noexcept;

			ktkLoadingRequest& SetResourcePath(
				const ktk::string& path) noexcept;
			const ktk::string& GetResourcePath(void) const noexcept;

		private:
			eResourceLoadingPolicy m_policy_loading;
			eResourceCachingPolicy m_policy_caching;
			eResourceLoadingType m_resource_type;
			ktk::string m_resource_path;
		};

		class ktkIResourceManager
		{
		public:
			virtual ~ktkIResourceManager(void) {}

			template <typename ResourceType>
			ktk::shared_ptr<ResourceType> Load(
				const ktkLoadingRequest& request) noexcept
			{
				return any_cast<ktk::shared_ptr<ResourceType>>(
					this->LoadResource(request));
			}

		protected:
			virtual ktk::any LoadResource(const ktkLoadingRequest& request) = 0;
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

		};

		bool InitializeModule_Core_API(ktkMainManager*);
		bool ShutdownModule_Core_API(ktkMainManager*);
		bool SerializeModule_Core_API(ktkMainManager*);
		bool DeserializeModule_Core_API(ktkMainManager*);
	} // namespace Core
} // namespace Kotek