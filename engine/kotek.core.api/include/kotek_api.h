#pragma once

#include "kotek_api_resource_manager.h"
#include "kotek_sdk_ui_element.h"
#include <kotek.core.enum/include/kotek_core_enum.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.containers.shared_ptr/include/kotek_core_containers_shared_ptr.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

// TODO: add ifdef for appropriate things
// if gl3 we need to check if gl3 is enabled
// if glfw we need to check if glfw is enabled and etc
#include <kotek.ui.imgui/include/imgui.h>
#include <kotek.ui.imgui/include/imgui_impl_glfw.h>
#include <kotek.ui.imgui/include/imgui_impl_opengl3.h>

#include "kotek_api_sdk.h"
#include "kotek_api_no_std.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;
class ktkIRenderDevice;
class ktkIRenderSwapchain;
class ktkIRenderGraph;
class ktkIRenderImgui;
class ktkIRenderResourceManager;
class ktkIRenderer;
class ktkProfiler;
class ktkConsole;
KOTEK_END_NAMESPACE_CORE

// TODO: replace namespace to preprocessor
namespace Engine
{
	class ktkWindow;
}

KOTEK_BEGIN_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_MATH
class vector2f;
class vector3f;
class vector4f;
class matrix2x2f;
class matrix3x3f;
class matrix4x4f;
class quaternionf;
KOTEK_END_NAMESPACE_MATH

KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_RENDER
class ktkRenderStats;
KOTEK_END_NAMESPACE_RENDER

KOTEK_END_NAMESPACE_KOTEK

// without namespaces definitions
struct GLFWwindow;
struct ImGuiPlatformIO;
struct ImGuiViewport;
struct ImVec2;
struct ImVec4;

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceHandle
{
public:
	ktkResourceHandle(void* p_allocated, bool is_allocated_on_stack = false
#ifdef KOTEK_DEBUG
		,
		const kun_ktk static_cstring_view& debug_type_name = "",
		const kun_ktk static_cstring_view& file_creation = "",
		const kun_ktk static_cstring_view& place_name = ""
#endif
		) :
		m_is_allocated_on_stack{is_allocated_on_stack},
		m_p_any_data_allocated{p_allocated}
#ifdef KOTEK_DEBUG
		,
		m_debug_type_name{debug_type_name.data()},
		m_file_name{file_creation.data()}, m_function_name{place_name.data()}
#endif
	{
	}

	ktkResourceHandle() = delete;
	~ktkResourceHandle()
	{
		if (!m_is_allocated_on_stack)
		{
			if (this->m_p_any_data_allocated)
			{
				delete this->m_p_any_data_allocated;
				this->m_p_any_data_allocated = nullptr;
			}
		}
	}

	bool Is_AllocatedOnStack(void) const noexcept
	{
		return this->m_is_allocated_on_stack;
	}

	void* Get_Resource(void) const noexcept
	{
		return this->m_p_any_data_allocated;
	}

private:
	bool m_is_allocated_on_stack;
	void* m_p_any_data_allocated;

#ifdef KOTEK_DEBUG
	kun_kotek kun_ktk static_cstring<128> m_debug_type_name;
	kun_kotek kun_ktk static_cstring<128> m_file_name;
	kun_kotek kun_ktk static_cstring<128> m_function_name;
#endif
};

class ktkIRenderDevice
{
public:
	virtual ~ktkIRenderDevice(void) {}

	virtual void Initialize(Core::ktkMainManager* main_manager) = 0;
	virtual void Shutdown(void) = 0;
	virtual void Resize(ktkIRenderSwapchain* p_raw_swapchain,
		ktkIRenderer* p_raw_renderer,
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

	virtual void Present(
		ktkMainManager* p_main_manager, ktkIRenderDevice* p_render_device) = 0;
};

class ktkIRenderResourceManager
{
public:
	virtual ~ktkIRenderResourceManager(void) {}

	// TODO: change signature on void
	// TODO: think about dynamic memory if we are exceeded we can use more
	// memory and etc
	virtual void initialize(ktkIRenderDevice* p_raw_device,
		ktkIRenderSwapchain* p_raw_swapchain,
		ktk::size_t memory_size = 1024 * 1024 * 32) = 0;

	// TODO: change signature on void
	virtual void shutdown(ktkIRenderDevice* p_raw_device) = 0;

	virtual ktk::shared_ptr<kun_core ktkResourceHandle> LoadGeometry(
		ktk::enum_base_t resource_loading_type, ktk::uint32_t id) = 0;
	virtual ktk::shared_ptr<kun_core ktkResourceHandle> LoadGeometry(
		ktk::enum_base_t resource_loading_type,
		const ktk_filesystem_path& path_to_file, ktk::uint32_t id) = 0;

	virtual void Resize(ktkIRenderDevice* p_raw_device,
		ktkIRenderSwapchain* p_raw_swapchain) = 0;

	virtual Render::ktkRenderStats* Get_Statistic(
		Core::eRenderStatistics type) noexcept = 0;
};

class ktkIRenderGraphResourceManager
{
public:
	virtual ~ktkIRenderGraphResourceManager(void) {}

	virtual void Initialize() = 0;
	virtual void Shutdown(void) = 0;
};

class ktkIRenderImgui
{
public:
	virtual ~ktkIRenderImgui(void) {}

	// TODO: change signature on void
	virtual void initialize(ktkMainManager& main_manager) noexcept = 0;

	// TODO: change signature on void
	virtual void shutdown(ktkIRenderDevice* p_raw_device) noexcept = 0;
};

class ktkIRenderGraph
{
public:
	virtual ~ktkIRenderGraph(void) {}

	virtual void Initialize(kun_core ktkMainManager* p_main_manager,
		kun_core ktkIRenderResourceManager*) = 0;
	virtual void Shutdown(void) = 0;
};

class ktkIRenderer
{
public:
	virtual ~ktkIRenderer(void) {}
	virtual void draw(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void Resize(void) = 0;
	virtual const char* Get_Name(void) const noexcept = 0;

	virtual const kun_kotek kun_ktk vector<ktkISDKUIElement*>&
	Get_UIImGuiElements(void) const = 0;
};

class ktkIFileSystem
{
public:
	virtual ~ktkIFileSystem(void) {}

	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual bool IsValidPath(
		const ktk_filesystem_path& path) const noexcept = 0;

	virtual void Create_Directory(
		const ktk_filesystem_path& path, Core::eFolderVisibilityType type) = 0;

	// TODO: check todo in implementation class ktkFileSystem and it is
	// a temporary virtual function delete it
	virtual ktk::ustring ReadFile(
		const ktk_filesystem_path& absolute_path_to_file) const noexcept = 0;

	// be careful! this method's purpose is only on stack and for stack
	// purposes! You should copy the content of p_buffer and (if updated)
	// length_of_buffer because if you suppose that you use 128 char buffer for
	// reading file but the real size is bigger than 128 than it used predefined
	// buffer as a defense but it is only for operations that don't store
	// pointers for session or longer time otherwise just copy the content and
	// don't store as string_view or native raw pointer string in your data, it
	// is for fast reading without using dynamic version based on ustring alias
	// (std::string class). So pointer of p_buffer and value of length_of_buffer
	// can be changed and that means they use data from predefined string in
	// filesystem, but it depends on user implementation tbh
	virtual bool Read_File(char*& p_buffer, size_t& length_of_buffer,
		const kun_ktk kun_filesystem
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
				absolute_path_to_file) noexcept = 0;

	virtual ktk_filesystem_path GetFolderByEnum(
		eFolderIndex id) const noexcept = 0;
};

enum eInputControllerType;
enum eInputAllKeys;

class ktkIInput
{
public:
	virtual ~ktkIInput(void) {}

	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;

	virtual bool Set_ControllerData(eInputControllerType controller_type,
		unsigned char data_field_index, float data) = 0;
	virtual float Get_ControllerData(eInputControllerType controller_type,
		unsigned char data_field_index) = 0;

	/// @brief simplified version (but you can't unite that buttons as you do
	/// with enum flags with | bitshift operator) of Is_KeyPressed where you can
	/// use any key but only one per calling from eInputAllKeys enum
	/// @param controller_type specified controller, keep in mind that you need
	/// to specify enum for specified controller you can't pass kCK_A for
	/// controller which is 'mouse' otherwise you will get an assert
	/// @param key field from enum eInputAllKeys
	/// @return if key was pressed means true otherwise false. Pressed means
	/// that it checks only first frame when this method was requested in code
	/// after that checking they key can be checked for release or holding
	/// states.
	virtual bool Is_KeyPressed(
		eInputControllerType controller_type, eInputAllKeys key) = 0;

	// TODO: add preprocessor for frames count as default arg
	virtual bool Is_KeyHolding(eInputControllerType controller_type,
		eInputAllKeys key, unsigned char frames = 16) = 0;

	virtual bool Is_KeyReleased(
		eInputControllerType controller_type, eInputAllKeys key) = 0;

	virtual const char* Get_TextInformationAboutController(
		eInputControllerType controller_type) = 0;

	/// @brief fills array with supported controllers
	/// @param p_array somewhere allocated unsigned char array with size =
	/// unsigned char[eInputControllerType::kControllerTotalAmountOfEnum]
	/// @param length_of_array length that user passes for validation if size
	/// was incorrect you will get an assertion
	/// @return if system has implementation of this method will return true and
	/// if was all okay generally otherwise false, in order to check the
	/// supported controller use eInputControllerType fields as look-up indexer
	/// and if field of your passed array was set to unsigned char(1) it means
	/// that controller is supported by engine
	virtual bool Get_SupportedControllers(
		unsigned char* p_array, unsigned char length_of_array) = 0;

	virtual const char* Get_PlatformBackendName(void) const = 0;

	virtual bool WriteKeyAsStringToBuffer_IfPressed(
		eInputControllerType controller, char* p_buffer,
		kun_ktk size_t length_of_buffer) = 0;

	virtual bool WriteKeyAsStringToBuffer_IfHolding(eInputControllerType controller,
		char* p_buffer, kun_ktk size_t length_of_buffer) = 0;

	// you need to use it in message loop of window
	virtual void Update(void* p_args) = 0;
};

class ktkIGameManager
{
public:
	virtual ~ktkIGameManager(void) {}

	virtual void Initialize(ktkMainManager* p_main_manager) = 0;
	virtual void Shutdown(ktkMainManager* p_main_manager) = 0;

	virtual ktkIRenderer* GetRenderer(void) const noexcept = 0;

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

/// \~english @brief This class stands for implementing own loader for
/// that case it has only 'Load' method names it means that you specify
/// what the implementation does. Does it load text or model or even any
/// other type?
/// Our standard is that user implements one general class for each type of
/// possible data Like model, text, video, but he provides and implements a
/// classes for each format and user must follow to these rules For example, I
/// want to have a loader for Videos, I create ktkLoaderVideo (formally
/// ktkLoaderTypeOfDataName) Then, I create for each format of that data type
/// like ktkLoaderVideo_MP4, ktkLoaderVideo_AV1, ktkLoaderVideo_XXX and etc In
/// general class it registers all classes what we created earlier and we
/// register to main ktkResourceManagerLoader You need to provide two private
/// methods (they are not virtual!!!, you provide them by your own), like say it
/// is Register_Loaders and Delete_Loaders (see our default implementation
/// loader classes) and with a such design you will understand where you have
/// 'general' class and where you have the ended implementation of a format,
/// because ended implementation doesn't have any registered loaders because it
/// is final!
///
/// So let's see on detailed illustration
// clang-format off
/*
                           ktkResourceLoaderManager
                                       ▲
                                       │
                                       │                        ▼
                                       │
                                       │
                                       │
         ┌────────────────────────►ktkLoaderVideo◄───────────────┐
         │                                                       │
         │                                                       │
         │                                                       │
         │                                                       │
         │                                                       │
         │                                                       │
         │                                                       │
         │                                                       │
         │                                              ktkLoaderVideo_AV1
ktkLoaderVideo_MP4
*/
// clang-format on
class ktkIResourceLoader
{
public:
	virtual ~ktkIResourceLoader(void) {}

	/// \~english @brief This method constucts an object that was passed
	/// on stack. It means it doesn't create shared_ptr and uses only
	/// for situations where user wants to pass an instance that was
	/// allocated temporary
	/// @param path
	/// @param object_from_construct
	/// @return
	virtual bool Load(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle object_from_construct) noexcept = 0;

	virtual bool DetectTypeByFullPath(
		const ktk_filesystem_path& path) noexcept = 0;

	/// \~english @brief This is only for user. You just provide your
	/// description of loader's implementation and access it through interface.
	/// @return Returns ktk::ustring instance by const&
	virtual ktk::cstring Get_UserDescription() const noexcept
	{
		return KOTEK_TEXTU("USER_DIDNT_PROVIDE_DESCRIPTION_FOR_LOADER");
	}

	/// \~english @brief This method is for validation purpose and for
	/// automatization purpose when LoaderManager picks the loader for analyzed
	/// path with extension. So for example you pass the path like
	/// 'C:/mygame/gamedata/models/some_stuff/test.obj' so if you registered a
	/// loader that contains format '.obj' it must return
	/// eResourceLoadingType::kModel enum value.
	/// @return What you specified in overriding, otherwise default value is
	/// eResourceLoadingType::kUnknown. If you got
	/// eResourceLoadingType::kUnknown it means you forgot to override the
	/// method.
	virtual eResourceLoadingType Get_Type() const noexcept
	{
		return eResourceLoadingType::kUnknown;
	}

	// TODO: ask a question to community: is it reasonable to support files
	// without formats?

	/// \~english @brief this method needs in case when you have one loader (for
	/// example you implement for eResourceLoadingType::kModel) but it specifies
	/// three different formats like (.fbx, .obj and .glb) in such case you need
	/// to implement three own loaders (because the implementation of loading
	/// process is different), but you need to pass them to this class through
	/// constructor (IMO the best option, because you strictly specify for user
	/// what you must have for allocating a such class, instead of deffered
	/// initialization like AddLoaderByExtension, it is just an example naming
	/// and an example approach we don't strict you there at all)
	///
	/// So how to imagine what was written about?
	///
	/// As a standard we provide one class per enum. It means if I have
	/// eResourceLoadingType::kModel, it means I can provide only one loader for
	/// this set of files (formats). But of course some users want to support
	/// many formats and these formats can have different loading algorithms.
	/// For that case you need to implement 'general' class that will contain
	/// implementation for each format that you registered in your 'general'
	/// class.
	///
	/// Let's on minimalistic example:
	/// @code
	/// class MyGeneralLoaderFor_kModel_Enum : public
	/// Kotek::Core::ktkIResourceLoader
	/// {
	///	public:
	///		// as we stated previously we need to register for .obj;.fbx;.glb.
	///		MyGeneralLoaderFor_kModel_Enum(Kotek::Core::ktkIResourceLoader*
	///	p_loader_obj, Kotek::Core::ktkIResourceLoader* p_loader_fbx,
	///	Kotek::Core::ktkIResourceLoader* p_loader_fbx);
	///
	///		// in this example we didn't provide overridings (in this case the
	///		// implementation of pure virtual functions) so we just demonstrate
	///		// the
	///		// idea
	///
	///			virtual ktkIResourceLoader* Get_Loader(
	///			const ktk::filesystem::path& extension_of_file) noexcept
	///			override
	///			{
	///				// of course you can provide some checking if it contains
	///				// the key
	///
	///				// and provide so default implementation or something else,
	///				//but
	///				// still
	///
	///
	///				/// we just show the idea
	///				return this->m_loaders.at(extension_of_file);
	///			}
	///
	/// private:
	///		ktk::unordered_map<ktk::ustring, Kotek::Core::ktkIResourceLoader*>
	/// m_loaders;
	/// };
	/// @endcode
	///
	///
	///
	/// @param extension_of_file it is an extension of file (e.g.
	/// '.obj;.gltf;.txt;.png;.jpg;.mp4; etc'), but important, the string must
	/// be with DOT! So you can't pass just the name of extension, you need to
	/// pass the '.some_name'. Currently engine doesn't support files without
	/// formats.
	/// @return If user registered loader it would return your registered loader
	/// that mapped to specified extension. For example if you set a key to your
	/// map as '.txt' and set the value as new ktkMyLoaderForTxTExampleName so
	/// as the result of overriding of this method you must get your instance of
	/// ktkMyLoaderForTxTExampleName by passing '.txt' string to that method.
	/// (You can choose any other container/method/methodology for returning
	/// your instance that corresponds to passed argument)
	///
	/// @see Kotek::Render::ktkLoaderModel_CGLTF default implementation of cgltf
	/// loader library
	virtual ktkIResourceLoader* Get_Loader(
		const ktk_filesystem_path& extension_of_file) noexcept = 0;

	virtual ktk::cstring Get_AllSupportedFormats(void) const noexcept = 0;
};

class ktkIResourceLoaderManager
{
public:
	ktkIResourceLoaderManager(void) : m_p_manager_filesystem{} {}

	virtual ~ktkIResourceLoaderManager(void) {}

	virtual void Initialize(ktkIFileSystem*, ktkMainManager*) = 0;
	virtual void Shutdown(void) = 0;

	virtual void Set_Loader(
		eResourceLoadingType resoruce_type, ktkIResourceLoader* p_loader) = 0;

	virtual ktkIResourceLoader* Get_Loader(
		eResourceLoadingType resource_type) const noexcept = 0;

	virtual bool Load(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle object_from_construct) noexcept = 0;

protected:
	virtual eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk_filesystem_path& path) noexcept = 0;

	ktkIFileSystem* m_p_manager_filesystem;
};

class ktkIResourceSaver
{
public:
	virtual ~ktkIResourceSaver(void) {}

	virtual bool Save(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle object_for_saving) noexcept = 0;

	virtual bool DetectTypeByFullPath(
		const ktk_filesystem_path& path) noexcept = 0;

	virtual ktk::cstring Get_UserDescription() const noexcept
	{
		return KOTEK_TEXTU("USER_DIDNT_PROVIDE_DESCRIPTION_FOR_SAVER");
	}

	virtual eResourceLoadingType Get_Type() const noexcept
	{
		return eResourceLoadingType::kUnknown;
	}

	virtual ktkIResourceSaver* Get_Saver(
		const ktk_filesystem_path& extension_of_file) noexcept = 0;

	virtual ktk::cstring Get_AllSupportedFormats(void) const noexcept = 0;
};

class ktkIResourceSaverManager
{
public:
	ktkIResourceSaverManager(void) : m_p_manager_filesystem{} {}

	/**
	 * Just a virtual destructor in order to being called from child
	 * destructors
	 *
	 */
	virtual ~ktkIResourceSaverManager(void) {}

	virtual void Initialize(ktkIFileSystem*, ktkMainManager*) = 0;
	virtual void Shutdown(void) = 0;

	virtual void Set_Saver(
		eResourceLoadingType resource_type, ktkIResourceSaver* p_saver) = 0;
	virtual ktkIResourceSaver* Get_Saver(
		eResourceLoadingType resource_type) const noexcept = 0;

	virtual bool Save(const ktk_filesystem_path& path,
		kun_core ktkResourceHandle data) noexcept = 0;

	virtual bool Open(const ktk_filesystem_path& path,
		eResourceWritingType resource_type, eResourceWritingPolicy policy,
		eResourceWritingMode mode, ktk::uint32_t id) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, const char* p_string) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const char* p_string,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id,
		const unsigned char* p_raw_memory) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id,
		const unsigned char* p_raw_memory, ktk::size_t size) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::int32_t value) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::float_t value) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::double_t value) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::int32_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::uint32_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::float_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::double_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::int8_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::int16_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::uint16_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id,
		Core::eFileWritingControlCharacterType type) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::size_t value) noexcept = 0;
	virtual void Seekg(ktk::uint32_t resource_id, ktk::size_t bytes,
		eFileSeekDirectionType type) = 0;
	virtual void Seekp(ktk::uint32_t resource_id, ktk::size_t bytes,
		eFileSeekDirectionType type) = 0;
	virtual ktk::size_t Tellp(ktk::uint32_t resource_id) = 0;
	virtual ktk::size_t Tellg(ktk::uint32_t resource_id) = 0;
	virtual void Read(
		ktk::uint32_t resource_id, char* p_buffer, ktk::size_t size) = 0;
	virtual bool Is_Open(ktk::uint32_t resource_id) noexcept = 0;
	virtual bool Close(ktk::uint32_t id) noexcept = 0;

	/// \~english @brief seeks for available instance of ofstream and returns
	/// its id
	/// @param
	/// @return
	virtual ktk::uint32_t GenerateFileID(void) noexcept = 0;

protected:
	virtual eResourceLoadingType DetectResourceTypeByFileFormat(
		const ktk_filesystem_path& path) noexcept = 0;

	ktkIFileSystem* m_p_manager_filesystem;
};

class ktkLoadingRequest
{
public:
	ktkLoadingRequest(eResourceLoadingPolicy type_loading,
		eResourceCachingPolicy type_policy_caching,
		eResourceLoadingType type_of_loading_resource,
		const ktk_filesystem_path& resource_path) :
		m_policy_loading{type_loading}, m_policy_caching{type_policy_caching},
		m_resource_type{type_of_loading_resource}, m_id{ktk::uint32_t(-1)},
		m_resource_path{resource_path}
	{
	}

	ktkLoadingRequest(eResourceLoadingPolicy type_loading,
		eResourceCachingPolicy type_policy_caching,
		eResourceLoadingType type_of_loading_resource,
		const ktk_filesystem_path& resource_path, ktk::uint32_t id) :
		m_policy_loading{type_loading}, m_policy_caching{type_policy_caching},
		m_resource_type{type_of_loading_resource}, m_id{id},
		m_resource_path{resource_path}
	{
	}

	ktkLoadingRequest(void) :
		m_policy_caching{}, m_policy_loading{eResourceLoadingPolicy::kAsync},
		m_resource_type{eResourceLoadingType::kAutoDetect}, m_id{}
	{
	}

	~ktkLoadingRequest() = default;

	ktkLoadingRequest& Set_LoadingPolicy(eResourceLoadingPolicy policy) noexcept
	{
		this->m_policy_loading = policy;
		return *this;
	}

	eResourceLoadingPolicy Get_LoadingPolicy(void) const noexcept
	{
		return this->m_policy_loading;
	}

	ktkLoadingRequest& Set_CachingPolicy(eResourceCachingPolicy policy) noexcept
	{
		this->m_policy_caching = policy;
		return *this;
	}

	eResourceCachingPolicy Get_CachingPolicy(void) const noexcept
	{
		return this->m_policy_caching;
	}

	ktkLoadingRequest& Set_ResourceType(eResourceLoadingType type) noexcept
	{
		this->m_resource_type = type;
		return *this;
	}

	eResourceLoadingType Get_ResourceType() const noexcept
	{
		return this->m_resource_type;
	}

	ktkLoadingRequest& Set_ResourcePath(
		const ktk_filesystem_path& path) noexcept
	{
		this->m_resource_path = path;
		return *this;
	}

	const ktk_filesystem_path& Get_ResourcePath(void) const noexcept
	{
		return this->m_resource_path;
	}

	bool Is_ForEntity(void) const noexcept
	{
		return this->m_id != ktk::uint32_t(-1);
	}

	ktk::uint32_t Get_EntityID(void) const noexcept { return this->m_id; }

private:
	eResourceLoadingPolicy m_policy_loading;
	eResourceCachingPolicy m_policy_caching;
	eResourceLoadingType m_resource_type;
	ktk::uint32_t m_id;
	ktk_filesystem_path m_resource_path;
};

class ktkResourceWritingRequest
{
public:
	ktkResourceWritingRequest() :
		m_id{}, m_writing_mode{Kotek::Core::eResourceWritingMode::kNew_Trunc},
		m_resource_type{Kotek::Core::eResourceWritingType::kUnknown},
		m_policy{Kotek::Core::eResourceWritingPolicy::kSync}
	{
	}

	ktkResourceWritingRequest(ktk::uint32_t id, eResourceWritingMode mode,
		eResourceWritingType type, eResourceWritingPolicy policy,
		const ktk_filesystem_path& path) :
		m_id{id}, m_writing_mode{mode}, m_resource_type{type},
		m_filepath_for_writing{path}, m_policy{policy}
	{
	}
	~ktkResourceWritingRequest() = default;

	eResourceWritingType Get_ResourceType(void) const noexcept
	{
		return this->m_resource_type;
	}

	ktkResourceWritingRequest& Set_ResourceType(
		eResourceWritingType type) noexcept
	{
		this->m_resource_type = type;
		return *this;
	}

	eResourceWritingMode Get_WritingMode(void) const noexcept
	{
		return this->m_writing_mode;
	}

	ktkResourceWritingRequest& Set_WritingMode(
		eResourceWritingMode mode) noexcept
	{
		this->m_writing_mode = mode;
		return *this;
	}

	ktk::uint32_t Get_ID(void) const noexcept { return this->m_id; }
	void Set_ID(ktk::uint32_t id) noexcept { this->m_id = id; }

	const ktk_filesystem_path& Get_Path(void) const noexcept
	{
		return this->m_filepath_for_writing;
	}

	ktkResourceWritingRequest& Set_Path(
		const ktk_filesystem_path& path) noexcept
	{
		this->m_filepath_for_writing = path;
		return *this;
	}

	eResourceWritingPolicy Get_Policy(void) const noexcept
	{
		return this->m_policy;
	}

private:
	ktk::uint32_t m_id;
	eResourceWritingMode m_writing_mode;
	eResourceWritingType m_resource_type;
	eResourceWritingPolicy m_policy;
	ktk_filesystem_path m_filepath_for_writing;
};

class ktkResourceWritingStatus
{
public:
	ktkResourceWritingStatus() : m_can_be_closed{}, m_is_writing{} {}
	~ktkResourceWritingStatus() {}

	bool Is_Writing(void) const noexcept { return this->m_is_writing; }
	bool Is_CanBeClosed(void) const noexcept { return this->m_can_be_closed; }

	void Set_Writing(bool status) { this->m_is_writing = status; }
	void Set_CanBeClosed(bool status) { this->m_can_be_closed = status; }

private:
	bool m_can_be_closed;
	bool m_is_writing;
};

/*
class ktkResourceWritingData
{
public:
    ktkResourceWritingData() :
        m_type{eResourceWritingDataType::kUnknown}, m_resource_id{}, m_size{},
        m_data{}
    {
    }
    ~ktkResourceWritingData() {}

    eResourceWritingDataType Get_Type(void) const noexcept
    {
        return this->m_type;
    }

    void Set_Type(eResourceWritingDataType type) { this->m_type = type; }

    kun_core ktkResourceHandle Get_Data(void) const noexcept
    {
        return this->m_data;
    }

    void Set_Data(kun_core ktkResourceHandle data) { this->m_data = data; }

    ktk::size_t Get_ElementCount(void) const noexcept { return this->m_size; }

    void Set_ElementCount(ktk::size_t size) { this->m_size = size; }

    void Set_ResourceID(ktk::uint32_t id) { this->m_resource_id = id; }

    ktk::uint32_t Get_ResourceID(void) const noexcept
    {
        return this->m_resource_id;
    }

private:
    /// \~english @brief for casting
    eResourceWritingDataType m_type;
    ktk::uint32_t m_resource_id;
    ktk::size_t m_size;
    kun_core ktkResourceHandle m_data;
};
*/

class ktkIResourceManager
{
public:
	virtual ~ktkIResourceManager(void) {}

	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;

	virtual kun_ktk shared_ptr<ktkResourceHandle> Load(
		const ktkLoadingRequest& request) noexcept = 0;

	virtual void Open(const ktkResourceWritingRequest& request) noexcept = 0;

	virtual void Write(
		ktk::uint32_t resource_id, const char* p_string) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const char* p_string,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id,
		const unsigned char* p_raw_memory) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id,
		const unsigned char* p_raw_memory, ktk::size_t size) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::int32_t value) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::float_t value) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::double_t value) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::int32_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::uint32_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::float_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::double_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::int8_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::int16_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id, const ktk::uint16_t* p_arr,
		ktk::size_t size) noexcept = 0;
	virtual void Write(ktk::uint32_t resource_id,
		Core::eFileWritingControlCharacterType) noexcept = 0;
	virtual void Write(
		ktk::uint32_t resource_id, ktk::size_t value) noexcept = 0;
	virtual void Seekg(ktk::uint32_t resource_id, ktk::size_t bytes,
		eFileSeekDirectionType type) = 0;
	virtual void Seekp(ktk::uint32_t resource_id, ktk::size_t bytes,
		eFileSeekDirectionType type) = 0;
	virtual ktk::size_t Tellp(ktk::uint32_t resource_id) = 0;
	virtual ktk::size_t Tellg(ktk::uint32_t resource_id) = 0;
	virtual void Read(
		ktk::uint32_t resource_id, char* p_buffer, ktk::size_t size) = 0;
	virtual bool Is_Open(ktk::uint32_t resource_id) = 0;
	virtual void Close(ktk::uint32_t resource_id) noexcept = 0;

	virtual ktk::uint32_t GenerateFileID(void) noexcept = 0;

	virtual void Set_ResourceLoader(
		ktkIResourceLoaderManager* p_instance) noexcept = 0;

	virtual ktkIResourceLoaderManager* Get_ResourceLoader(
		void) const noexcept = 0;

	virtual void Set_ResourceSaver(
		ktkIResourceSaverManager* p_instance) noexcept = 0;

	virtual ktkIResourceSaverManager* Get_ResourceSaver(
		void) const noexcept = 0;

	virtual void Set_RenderResourceManager(
		ktkIRenderResourceManager* p_instance) noexcept = 0;

	virtual ktkIRenderResourceManager* Get_RenderResourceManager(
		void) const noexcept = 0;

	virtual void Set_MainManager(ktkMainManager* p_instance) noexcept = 0;
	virtual ktkMainManager* Get_MainManager(void) const noexcept = 0;

	// TODO: saving implement
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

class ktkILogger
{
public:
	virtual ~ktkILogger(void) {}
	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void* Get(const char* p_logger_name) = 0;
};

class ktkIEngineConfig
{
public:
	virtual ~ktkIEngineConfig(void) {}

	virtual void Initialize(void) = 0;
	virtual void Shutdown(void) = 0;

	virtual bool IsFeatureEnabled(eEngineFeature id) const noexcept = 0;
	virtual bool IsFeatureEnabled(eEngineFeatureRender id) const noexcept = 0;
	virtual bool IsFeatureEnabled(eEngineFeatureRenderer id) const noexcept = 0;
	virtual bool IsFeatureEnabled(eEngineFeatureSDK id) const noexcept = 0;
	virtual bool IsFeatureEnabled(eEngineFeatureWindow id) const noexcept = 0;

	virtual void SetFeatureStatus(eEngineFeature id, bool status) noexcept = 0;
	virtual void SetFeatureStatus(
		eEngineFeatureRender id, bool status) noexcept = 0;
	virtual void SetFeatureStatus(
		eEngineFeatureRenderer id, bool status) noexcept = 0;
	virtual void SetFeatureStatus(
		eEngineFeatureSDK id, bool status) noexcept = 0;
	virtual void SetFeatureStatus(
		eEngineFeatureWindow id, bool status) noexcept = 0;

	virtual void SetFeatureStatus(
		eEngineSupportedRenderer version, bool status) noexcept = 0;

	virtual void SetFeatureStatus(const ktk_vector<eEngineSupportedRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>&
			fallback_versions) noexcept = 0;
	virtual void SetFeatureStatus(const ktk_vector<eEngineFeatureRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_COUNT>& gapis) noexcept = 0;

	virtual eEngineFeature GetEngineFeature(void) const noexcept = 0;
	virtual eEngineFeatureRender GetEngineFeatureRender(
		void) const noexcept = 0;
	virtual eEngineFeatureRenderer GetEngineFeatureRenderer(
		void) const noexcept = 0;
	virtual eEngineFeatureSDK GetEngineFeatureSDK(void) const noexcept = 0;
	virtual eEngineFeatureWindow GetEngineFeatureWindow(
		void) const noexcept = 0;

	virtual eEngineSupportedRenderer GetRendererVersionEnum(
		void) const noexcept = 0;
	virtual ktk::enum_base_t GetRendererVersion(void) const noexcept = 0;
	virtual const ktk_vector<eEngineFeatureRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_COUNT>&
	GetFallbackRendereres(void) const noexcept = 0;
	virtual const ktk_vector<eEngineSupportedRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>&
	GetFallbackRendererVersions(void) const noexcept = 0;

	virtual ktk::cstring GetRenderName(void) const noexcept = 0;

	virtual ktk::size_t Get_VideoMemoryTotal(void) const noexcept = 0;
	virtual ktk::size_t Get_VideoMemoryForInitialize(void) const noexcept = 0;
	virtual void Set_VideoMemoryForInitialize(ktk::size_t value) noexcept = 0;

	virtual bool IsCurrentRenderLegacy(void) const noexcept = 0;
	virtual bool IsCurrentRenderModern(void) const noexcept = 0;
	virtual int GetARGC(void) const noexcept = 0;
	virtual char** GetARGV(void) const noexcept = 0;
	virtual void SetARGC(int) noexcept = 0;
	virtual void SetARGV(char**) noexcept = 0;
	virtual bool IsContainsConsoleCommandLineArgument(
		const ktk::cstring& your_argument) const noexcept = 0;

	/// @brief This method means that argument line of application contains
	/// valid request for creating renderer. It means that user can specify only
	/// one renderer and one version for that. For example this line will be
	/// invalid: --render_dx_9 --render_vk1_3 or this line: --render_vk1_0
	/// --render_vk1_3 we can't understand what user wanted to say, so we
	/// support only this type of request when user pass only one line with
	/// --render_yourrednerername_version or
	/// --render_yourrenderernameversion_subversion
	/// @param void, passes nothing to this method
	/// @return if line is valid returns true otherwise is false
	virtual bool IsUserSpecifiedValidRenderer(void) const noexcept = 0;

	// TODO: add ANGLE
	virtual bool IsUserSpecifiedRendererOpenGLInCommandLine(
		void) const noexcept = 0;
	virtual bool IsUserSpecifiedRendererDirectXInCommandLine(
		void) const noexcept = 0;
	virtual bool IsUserSpecifiedRendererVulkanInCommandLine(
		void) const noexcept = 0;

	virtual eEngineSupportedRenderer GetRendererVersionFromCommandLine(
		void) const noexcept = 0;

	// TODO: add for angle here

	virtual bool IsApplicationWorking(void) const noexcept = 0;
	virtual void SetApplicationWorking(bool status) noexcept = 0;
	virtual void Set_UserLibrary(
		const ktk_filesystem_path& path_to_library) noexcept = 0;
	virtual void* Get_UserLibrary(void) noexcept = 0;
};

class ktkIComponentAllocator
{
public:
	virtual ~ktkIComponentAllocator() {}

	virtual bool Create(ktk::uint32_t id) noexcept = 0;
	virtual void* Get(ktk::uint32_t id) noexcept = 0;
	virtual bool Remove(ktk::uint32_t id) noexcept = 0;
	virtual ktk::cstring GetDebugName(void) const noexcept = 0;
	virtual ktk::ustring GetComponentName(void) const noexcept = 0;
	virtual void DrawImGui(Kotek::Core::ktkMainManager* main_manager,
		ktk::uint32_t entity_id) noexcept = 0;
};

class ktkIWindow
{
public:
	virtual ~ktkIWindow(void) {}

	virtual int GetWidth(void) const noexcept = 0;
	virtual int GetHeight(void) const noexcept = 0;

	// TODO: be sure that if we don't use any window library we need to
	// implement own and in such case we should return native HWND, linux
	// window's handle and etc
	/// @brief it depends. If you use GLFW = glfwWindow, SDL = sdl's window
	/// handle and etc
	/// @param
	/// @return
	virtual void* GetHandle(void) const noexcept = 0;
	virtual void Initialize(Core::eEngineSupportedRenderer version) = 0;
	virtual void Shutdown(void) = 0;
	virtual void PollEvents(void) = 0;
	virtual bool Is_NeedToClose(void) = 0;
	virtual void MakeContextCurrent(void) noexcept = 0;
	virtual void SetStringToTitle(
		ktk::enum_base_t id, const char* p_utf8_or_char_string) noexcept = 0;
	virtual void RemoveStringFromTitle(ktk::enum_base_t id) noexcept = 0;
	virtual ktk::cstring GetTitle(void) const noexcept = 0;

	virtual void Set_InputType(ktk::enum_base_t type) noexcept = 0;
};

class ktkIWindowManager
{
public:
	virtual ~ktkIWindowManager(void) {}

	virtual void Initialize() = 0;
	virtual void Shutdown(void) = 0;

	virtual void ActiveWindow_PollEvents(void) = 0;
	virtual void* ActiveWindow_GetHandle(void) const noexcept = 0;
	virtual int ActiveWindow_GetHeight(void) const noexcept = 0;
	virtual int ActiveWindow_GetWidth(void) const noexcept = 0;
	virtual bool ActiveWindow_ShouldToClose(void) = 0;
	virtual void ActiveWindow_MakeContextCurrent(void) noexcept = 0;

	virtual ktkIWindow* Get_ActiveWindow(void) const noexcept = 0;
	virtual void Set_ActiveWindow(ktkIWindow* p_window) noexcept = 0;
};

class ktkIGameUIManager
{
public:
	virtual ~ktkIGameUIManager(void) {}

	virtual void Initialize(ktkIEngineConfig* p_config,
		void* p_os_window_handle, int width, int height) noexcept = 0;

	virtual void Render(void) noexcept = 0;
	virtual void Update(void) noexcept = 0;
	virtual void Shutdown(void) noexcept = 0;
	virtual bool LoadDocument(const char* p_path_to_file) = 0;
};

class ktkILogManager
{
public:
	virtual ~ktkILogManager(void) {}

	virtual void Initialize(void) noexcept = 0;
	virtual void Shutdown(void) noexcept = 0;

	virtual void AddText(const ktk::ustring& message) noexcept = 0;
};

class ktkIVideoPlayerManager
{
public:
	virtual ~ktkIVideoPlayerManager(void) {}

	virtual void Initialize(void) noexcept = 0;
	virtual void Shutdown(void) noexcept = 0;
	virtual void Render(void) noexcept = 0;
};

/// \~russian @brief данный класс создан чтобы пользователь и
/// разработчик могли определять текущий wrapper для imgui библиотеки.
/// Их всего две это ImGui и Nuklear. Сделано это с одной целью, чтобы
/// пользователь мог иметь возможность создания окна в exe, но
/// определять логику оконной библиотеки в dll.
class ktkIImguiWrapper
{
public:
	virtual ~ktkIImguiWrapper(void) {}

	virtual void EditDragVec2f(
		const char* label, ktk::math::vector2f* p_vec) = 0;
	virtual void EditDragVec3f(
		const char* label, ktk::math::vector3f* p_vec) = 0;
	virtual void EditDragVec4f(
		const char* label, ktk::math::vector4f* p_vec) = 0;

	virtual void EditDragMat2x2f(
		const char* label, ktk::math::matrix2x2f* p_mat) = 0;
	virtual void EditDragMat3x3f(
		const char* label, ktk::math::matrix3x3f* p_mat) = 0;
	virtual void EditDragMat4x4f(
		const char* label, ktk::math::matrix4x4f* p_mat) = 0;

	virtual void EditDragQuatf(
		const char* label, ktk::math::quaternionf* p_quat) = 0;

	virtual bool ImGui_ImplGlfw_InitForOpenGL(
		GLFWwindow* window, bool install_callbacks) = 0;
	virtual bool ImGui_ImplGlfw_InitForVulkan(
		GLFWwindow* window, bool install_callbacks) = 0;
	virtual bool ImGui_ImplGlfw_InitForOther(
		GLFWwindow* window, bool install_callbacks) = 0;
	virtual void ImGui_ImplGlfw_Shutdown() = 0;
	virtual void ImGui_ImplGlfw_NewFrame() = 0;

	virtual void ImGui_ImplGlfw_WindowFocusCallback(
		GLFWwindow* window, int focused) = 0;
	virtual void ImGui_ImplGlfw_CursorEnterCallback(
		GLFWwindow* window, int entered) = 0;
	virtual void ImGui_ImplGlfw_MouseButtonCallback(
		GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void ImGui_ImplGlfw_ScrollCallback(
		GLFWwindow* window, double xoffset, double yoffset) = 0;
	virtual void ImGui_ImplGlfw_KeyCallback(
		GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
	virtual void ImGui_ImplGlfw_CharCallback(
		GLFWwindow* window, unsigned int c) = 0;
	virtual void ImGui_ImplGlfw_MonitorCallback(
		GLFWmonitor* monitor, int event) = 0;
	virtual void ImGui_ImplGlfw_CursorPosCallback(
		GLFWwindow* window, double x, double y) = 0;

	virtual bool ImGui_ImplOpenGL3_Init(const char* glsl_version = NULL) = 0;
	virtual void ImGui_ImplOpenGL3_Shutdown() = 0;
	virtual void ImGui_ImplOpenGL3_NewFrame() = 0;
	virtual void ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data) = 0;

	virtual bool ImGui_ImplOpenGL3_CreateFontsTexture() = 0;
	virtual void ImGui_ImplOpenGL3_DestroyFontsTexture() = 0;
	virtual bool ImGui_ImplOpenGL3_CreateDeviceObjects() = 0;
	virtual void ImGui_ImplOpenGL3_DestroyDeviceObjects() = 0;

	virtual void* CreateContext(void* shared_font_atlas = NULL) = 0;
	virtual void DestroyContext(void* ctx = NULL) = 0;
	virtual ImGuiContext* GetCurrentContext() = 0;
	virtual void SetCurrentContext(ImGuiContext* ctx) = 0;
	virtual ImGuiIO& GetIO() = 0;
	virtual ImGuiStyle& GetStyle() = 0;
	virtual void NewFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Render() = 0;
	virtual ImDrawData* GetDrawData() = 0;

	virtual void ShowDemoWindow(bool* p_open = NULL) = 0;
	virtual void ShowMetricsWindow(bool* p_open = NULL) = 0;
	virtual void ShowStackToolWindow(bool* p_open = NULL) = 0;
	virtual void ShowAboutWindow(bool* p_open = NULL) = 0;
	virtual void ShowStyleEditor(ImGuiStyle* ref = NULL) = 0;
	virtual bool ShowStyleSelector(const char* label) = 0;
	virtual void ShowFontSelector(const char* label) = 0;
	virtual void ShowUserGuide() = 0;
	virtual const char* GetVersion() = 0;
	virtual void StyleColorsDark(void* dst = NULL) = 0;
	virtual void StyleColorsLight(ImGuiStyle* dst = NULL) = 0;
	virtual void StyleColorsClassic(ImGuiStyle* dst = NULL) = 0;

	virtual bool Begin(
		const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0) = 0;
	virtual void End() = 0;

	virtual bool BeginChild(const char* str_id,
		const ImVec2& size = ImVec2(0, 0), bool border = false,
		ImGuiWindowFlags flags = 0) = 0;
	virtual bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0),
		bool border = false, ImGuiWindowFlags flags = 0) = 0;
	virtual void EndChild() = 0;

	virtual void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0,
		const ImVec2& pivot = ImVec2(0, 0)) = 0;
	virtual void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0) = 0;
	virtual void SetNextWindowSizeConstraints(const ImVec2& size_min,
		const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL,
		void* custom_callback_data = NULL) = 0;
	virtual void SetNextWindowContentSize(const ImVec2& size) = 0;
	virtual void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0) = 0;
	virtual void SetNextWindowFocus() = 0;
	virtual void SetNextWindowBgAlpha(float alpha) = 0;
	virtual void SetNextWindowViewport(ImGuiID viewport_id) = 0;
	virtual void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0) = 0;
	virtual void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0) = 0;
	virtual void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0) = 0;
	virtual void SetWindowFocus() = 0;
	virtual void SetWindowFontScale(float scale) = 0;
	virtual void SetWindowPos(
		const char* name, const ImVec2& pos, ImGuiCond cond = 0) = 0;
	virtual void SetWindowSize(
		const char* name, const ImVec2& size, ImGuiCond cond = 0) = 0;
	virtual void SetWindowCollapsed(
		const char* name, bool collapsed, ImGuiCond cond = 0) = 0;
	virtual void SetWindowFocus(const char* name) = 0;

	virtual float GetScrollX() = 0;
	virtual float GetScrollY() = 0;
	virtual void SetScrollX(float scroll_x) = 0;
	virtual void SetScrollY(float scroll_y) = 0;
	virtual float GetScrollMaxX() = 0;
	virtual float GetScrollMaxY() = 0;
	virtual void SetScrollHereX(float center_x_ratio = 0.5f) = 0;
	virtual void SetScrollHereY(float center_y_ratio = 0.5f) = 0;
	virtual void SetScrollFromPosX(
		float local_x, float center_x_ratio = 0.5f) = 0;
	virtual void SetScrollFromPosY(
		float local_y, float center_y_ratio = 0.5f) = 0;

	virtual void PushFont(ImFont* font) = 0;
	virtual void PopFont() = 0;
	virtual void PushStyleColor(ImGuiCol idx, ImU32 col) = 0;
	virtual void PushStyleColor(ImGuiCol idx, const ImVec4& col) = 0;
	virtual void PopStyleColor(int count = 1) = 0;
	virtual void PushStyleVar(ImGuiStyleVar idx, float val) = 0;
	virtual void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val) = 0;
	virtual void PopStyleVar(int count = 1) = 0;
	virtual void PushAllowKeyboardFocus(bool allow_keyboard_focus) = 0;
	virtual void PopAllowKeyboardFocus() = 0;
	virtual void PushButtonRepeat(bool repeat) = 0;
	virtual void PopButtonRepeat() = 0;

	virtual void PushItemWidth(float item_width) = 0;
	virtual void PopItemWidth() = 0;
	virtual void SetNextItemWidth(float item_width) = 0;
	virtual float CalcItemWidth() = 0;
	virtual void PushTextWrapPos(float wrap_local_pos_x = 0.0f) = 0;
	virtual void PopTextWrapPos() = 0;

	virtual ImFont* GetFont() = 0;
	virtual float GetFontSize() = 0;
	virtual ImVec2 GetFontTexUvWhitePixel() = 0;
	virtual ImU32 GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f) = 0;
	virtual ImU32 GetColorU32(const ImVec4& col) = 0;
	virtual ImU32 GetColorU32(ImU32 col) = 0;
	virtual const ImVec4& GetStyleColorVec4(ImGuiCol idx) = 0;

	virtual void Separator() = 0;
	virtual void SameLine(
		float offset_from_start_x = 0.0f, float spacing = -1.0f) = 0;
	virtual void NewLine() = 0;
	virtual void Spacing() = 0;
	virtual void Dummy(const ImVec2& size) = 0;
	virtual void Indent(float indent_w = 0.0f) = 0;
	virtual void Unindent(float indent_w = 0.0f) = 0;
	virtual void BeginGroup() = 0;
	virtual void EndGroup() = 0;
	virtual ImVec2 GetCursorPos() = 0;
	virtual float GetCursorPosX() = 0;
	virtual float GetCursorPosY() = 0;
	virtual void SetCursorPos(const ImVec2& local_pos) = 0;
	virtual void SetCursorPosX(float local_x) = 0;
	virtual void SetCursorPosY(float local_y) = 0;
	virtual ImVec2 GetCursorStartPos() = 0;
	virtual ImVec2 GetCursorScreenPos() = 0;
	virtual void SetCursorScreenPos(const ImVec2& pos) = 0;
	virtual void AlignTextToFramePadding() = 0;
	virtual float GetTextLineHeight() = 0;
	virtual float GetTextLineHeightWithSpacing() = 0;
	virtual float GetFrameHeight() = 0;
	virtual float GetFrameHeightWithSpacing() = 0;

	virtual void PushID(const char* str_id) = 0;
	virtual void PushID(const char* str_id_begin, const char* str_id_end) = 0;
	virtual void PushID(const void* ptr_id) = 0;
	virtual void PushID(int int_id) = 0;
	virtual void PopID() = 0;
	virtual ImGuiID GetID(const char* str_id) = 0;
	virtual ImGuiID GetID(const char* str_id_begin, const char* str_id_end) = 0;
	virtual ImGuiID GetID(const void* ptr_id) = 0;

	virtual void TextUnformatted(
		const char* text, const char* text_end = NULL) = 0;
	virtual void Text(const char* fmt, ...) = 0;
	virtual void TextV(const char* fmt, va_list args) = 0;
	virtual void TextColored(const ImVec4& col, const char* fmt, ...) = 0;
	virtual void TextColoredV(
		const ImVec4& col, const char* fmt, va_list args) = 0;
	virtual void TextDisabled(const char* fmt, ...) = 0;
	virtual void TextDisabledV(const char* fmt, va_list args) = 0;
	virtual void TextWrapped(const char* fmt, ...) = 0;
	virtual void TextWrappedV(const char* fmt, va_list args) = 0;
	virtual void LabelText(const char* label, const char* fmt, ...) = 0;
	virtual void LabelTextV(
		const char* label, const char* fmt, va_list args) = 0;
	virtual void BulletText(const char* fmt, ...) = 0;
	virtual void BulletTextV(const char* fmt, va_list args) = 0;

	virtual bool Button(
		const char* label, const ImVec2& size = ImVec2(0, 0)) = 0;
	virtual bool SmallButton(const char* label) = 0;
	virtual bool InvisibleButton(
		const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0) = 0;
	virtual bool ArrowButton(const char* str_id, ImGuiDir dir) = 0;
	virtual void Image(ImTextureID user_texture_id, const ImVec2& size,
		const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1),
		const ImVec4& tint_col = ImVec4(1, 1, 1, 1),
		const ImVec4& border_col = ImVec4(0, 0, 0, 0)) = 0;
	virtual bool ImageButton(const char* str_id, ImTextureID user_texture_id,
		const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0),
		const ImVec2& uv1 = ImVec2(1, 1),
		const ImVec4& bg_col = ImVec4(0, 0, 0, 0),
		const ImVec4& tint_col = ImVec4(1, 1, 1, 1)) = 0; // <0 frame_
	virtual bool Checkbox(const char* label, bool* v) = 0;
	virtual bool CheckboxFlags(
		const char* label, int* flags, int flags_value) = 0;
	virtual bool CheckboxFlags(
		const char* label, unsigned int* flags, unsigned int flags_value) = 0;
	virtual bool RadioButton(const char* label, bool active) = 0;
	virtual bool RadioButton(const char* label, int* v, int v_button) = 0;
	virtual void ProgressBar(float fraction,
		const ImVec2& size_arg = ImVec2(-FLT_MIN, 0),
		const char* overlay = NULL) = 0;
	virtual void Bullet() = 0;

	virtual bool BeginCombo(const char* label, const char* preview_value,
		ImGuiComboFlags flags = 0) = 0;
	virtual void EndCombo() = 0;
	virtual bool Combo(const char* label, int* current_item,
		const char* const items[], int items_count,
		int popup_max_height_in_items = -1) = 0;
	virtual bool Combo(const char* label, int* current_item,
		const char* items_separated_by_zeros,
		int popup_max_height_in_items = -1) = 0;
	virtual bool Combo(const char* label, int* current_item,
		bool (*items_getter)(void* data, int idx, const char** out_text),
		void* data, int items_count, int popup_max_height_in_items = -1) = 0;
	virtual bool DragFloat(const char* label, float* v, float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragFloatRange2(const char* label, float* v_current_min,
		float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f,
		float v_max = 0.0f, const char* format = "%.3f",
		const char* format_max = NULL, ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragInt(const char* label, int* v, float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragInt2(const char* label, int v[2], float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragInt3(const char* label, int v[3], float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragInt4(const char* label, int v[4], float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragIntRange2(const char* label, int* v_current_min,
		int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0,
		const char* format = "%d", const char* format_max = NULL,
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragScalar(const char* label, ImGuiDataType data_type,
		void* p_data, float v_speed = 1.0f, const void* p_min = NULL,
		const void* p_max = NULL, const char* format = NULL,
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool DragScalarN(const char* label, ImGuiDataType data_type,
		void* p_data, int components, float v_speed = 1.0f,
		const void* p_min = NULL, const void* p_max = NULL,
		const char* format = NULL, ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderFloat(const char* label, float* v, float v_min,
		float v_max, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderFloat2(const char* label, float v[2], float v_min,
		float v_max, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderFloat3(const char* label, float v[3], float v_min,
		float v_max, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderFloat4(const char* label, float v[4], float v_min,
		float v_max, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderAngle(const char* label, float* v_rad,
		float v_degrees_min = -360.0f, float v_degrees_max = +360.0f,
		const char* format = "%.0f deg", ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderInt(const char* label, int* v, int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderInt2(const char* label, int v[2], int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderInt3(const char* label, int v[3], int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderInt4(const char* label, int v[4], int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderScalar(const char* label, ImGuiDataType data_type,
		void* p_data, const void* p_min, const void* p_max,
		const char* format = NULL, ImGuiSliderFlags flags = 0) = 0;
	virtual bool SliderScalarN(const char* label, ImGuiDataType data_type,
		void* p_data, int components, const void* p_min, const void* p_max,
		const char* format = NULL, ImGuiSliderFlags flags = 0) = 0;
	virtual bool VSliderFloat(const char* label, const ImVec2& size, float* v,
		float v_min, float v_max, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool VSliderInt(const char* label, const ImVec2& size, int* v,
		int v_min, int v_max, const char* format = "%d",
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool VSliderScalar(const char* label, const ImVec2& size,
		ImGuiDataType data_type, void* p_data, const void* p_min,
		const void* p_max, const char* format = NULL,
		ImGuiSliderFlags flags = 0) = 0;
	virtual bool InputText(const char* label, char* buf, size_t buf_size,
		ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL,
		void* user_data = NULL) = 0;
	virtual bool InputTextMultiline(const char* label, char* buf,
		size_t buf_size, const ImVec2& size = ImVec2(0, 0),
		ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL,
		void* user_data = NULL) = 0;
	virtual bool InputTextWithHint(const char* label, const char* hint,
		char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0,
		ImGuiInputTextCallback callback = NULL, void* user_data = NULL) = 0;
	virtual bool InputFloat(const char* label, float* v, float step = 0.0f,
		float step_fast = 0.0f, const char* format = "%.3f",
		ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputFloat2(const char* label, float v[2],
		const char* format = "%.3f", ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputFloat3(const char* label, float v[3],
		const char* format = "%.3f", ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputFloat4(const char* label, float v[4],
		const char* format = "%.3f", ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputInt(const char* label, int* v, int step = 1,
		int step_fast = 100, ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputInt2(
		const char* label, int v[2], ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputInt3(
		const char* label, int v[3], ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputInt4(
		const char* label, int v[4], ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputDouble(const char* label, double* v, double step = 0.0,
		double step_fast = 0.0, const char* format = "%.6f",
		ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputScalar(const char* label, ImGuiDataType data_type,
		void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL,
		const char* format = NULL, ImGuiInputTextFlags flags = 0) = 0;
	virtual bool InputScalarN(const char* label, ImGuiDataType data_type,
		void* p_data, int components, const void* p_step = NULL,
		const void* p_step_fast = NULL, const char* format = NULL,
		ImGuiInputTextFlags flags = 0) = 0;
	virtual bool ColorEdit3(
		const char* label, float col[3], ImGuiColorEditFlags flags = 0) = 0;
	virtual bool ColorEdit4(
		const char* label, float col[4], ImGuiColorEditFlags flags = 0) = 0;
	virtual bool ColorPicker3(
		const char* label, float col[3], ImGuiColorEditFlags flags = 0) = 0;
	virtual bool ColorPicker4(const char* label, float col[4],
		ImGuiColorEditFlags flags = 0, const float* ref_col = NULL) = 0;
	virtual bool ColorButton(const char* desc_id, const ImVec4& col,
		ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0)) = 0;
	virtual void SetColorEditOptions(ImGuiColorEditFlags flags) = 0;
	virtual bool TreeNode(const char* label) = 0;
	virtual bool TreeNode(const char* str_id, const char* fmt, ...) = 0;
	virtual bool TreeNode(const void* ptr_id, const char* fmt, ...) = 0;
	virtual bool TreeNodeV(
		const char* str_id, const char* fmt, va_list args) = 0;
	virtual bool TreeNodeV(
		const void* ptr_id, const char* fmt, va_list args) = 0;
	virtual bool TreeNodeEx(
		const char* label, ImGuiTreeNodeFlags flags = 0) = 0;
	virtual bool TreeNodeEx(
		const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) = 0;
	virtual bool TreeNodeEx(
		const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) = 0;
	virtual bool TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags,
		const char* fmt, va_list args) = 0;
	virtual bool TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags,
		const char* fmt, va_list args) = 0;
	virtual void TreePush(const char* str_id) = 0;
	virtual void TreePush(const void* ptr_id = NULL) = 0;
	virtual void TreePop() = 0;
	virtual float GetTreeNodeToLabelSpacing() = 0;
	virtual bool CollapsingHeader(
		const char* label, ImGuiTreeNodeFlags flags = 0) = 0;
	virtual bool CollapsingHeader(
		const char* label, bool* p_visible, ImGuiTreeNodeFlags flags = 0) = 0;
	virtual void SetNextItemOpen(bool is_open, ImGuiCond cond = 0) = 0;
	virtual bool Selectable(const char* label, bool selected = false,
		ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)) = 0;
	virtual bool Selectable(const char* label, bool* p_selected,
		ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)) = 0;
	virtual bool BeginListBox(
		const char* label, const ImVec2& size = ImVec2(0, 0)) = 0;
	virtual void EndListBox() = 0;
	virtual bool ListBox(const char* label, int* current_item,
		const char* const items[], int items_count,
		int height_in_items = -1) = 0;
	virtual bool ListBox(const char* label, int* current_item,
		bool (*items_getter)(void* data, int idx, const char** out_text),
		void* data, int items_count, int height_in_items = -1) = 0;
	virtual void PlotLines(const char* label, const float* values,
		int values_count, int values_offset = 0,
		const char* overlay_text = NULL, float scale_min = FLT_MAX,
		float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0),
		int stride = sizeof(float)) = 0;
	virtual void PlotLines(const char* label,
		float (*values_getter)(void* data, int idx), void* data,
		int values_count, int values_offset = 0,
		const char* overlay_text = NULL, float scale_min = FLT_MAX,
		float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)) = 0;
	virtual void PlotHistogram(const char* label, const float* values,
		int values_count, int values_offset = 0,
		const char* overlay_text = NULL, float scale_min = FLT_MAX,
		float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0),
		int stride = sizeof(float)) = 0;
	virtual void PlotHistogram(const char* label,
		float (*values_getter)(void* data, int idx), void* data,
		int values_count, int values_offset = 0,
		const char* overlay_text = NULL, float scale_min = FLT_MAX,
		float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)) = 0;
	virtual void Value(const char* prefix, bool b) = 0;
	virtual void Value(const char* prefix, int v) = 0;
	virtual void Value(const char* prefix, unsigned int v) = 0;
	virtual void Value(
		const char* prefix, float v, const char* float_format = NULL) = 0;

	virtual bool BeginMenuBar() = 0;
	virtual void EndMenuBar() = 0;
	virtual bool BeginMainMenuBar() = 0;
	virtual void EndMainMenuBar() = 0;
	virtual bool BeginMenu(const char* label, bool enabled = true) = 0;
	virtual void EndMenu() = 0;
	virtual bool MenuItem(const char* label, const char* shortcut = NULL,
		bool selected = false, bool enabled = true) = 0;
	virtual bool MenuItem(const char* label, const char* shortcut,
		bool* p_selected, bool enabled = true) = 0;

	virtual void BeginTooltip() = 0;
	virtual void EndTooltip() = 0;
	virtual void SetTooltip(const char* fmt, ...) = 0;
	virtual void SetTooltipV(const char* fmt, va_list args) = 0;

	virtual bool BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0) = 0;
	virtual bool BeginPopupModal(
		const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0) = 0;
	virtual void EndPopup() = 0;

	virtual void OpenPopup(
		const char* str_id, ImGuiPopupFlags popup_flags = 0) = 0;
	virtual void OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0) = 0;
	virtual void OpenPopupOnItemClick(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) = 0;
	virtual void CloseCurrentPopup() = 0;

	virtual bool BeginPopupContextItem(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) = 0;
	virtual bool BeginPopupContextWindow(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) = 0;
	virtual bool BeginPopupContextVoid(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) = 0;

	virtual bool IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0) = 0;

	virtual bool BeginTable(const char* str_id, int column,
		ImGuiTableFlags flags = 0,
		const ImVec2& outer_size = ImVec2(0.0f, 0.0f),
		float inner_width = 0.0f) = 0;
	virtual void EndTable() = 0;
	virtual void TableNextRow(
		ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f) = 0;
	virtual bool TableNextColumn() = 0;
	virtual bool TableSetColumnIndex(int column_n) = 0;

	virtual void TableSetupColumn(const char* label,
		ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f,
		ImGuiID user_id = 0) = 0;
	virtual void TableSetupScrollFreeze(int cols, int rows) = 0;
	virtual void TableHeadersRow() = 0;
	virtual void TableHeader(const char* label) = 0;

	virtual ImGuiTableSortSpecs* TableGetSortSpecs() = 0;

	virtual int TableGetColumnCount() = 0;
	virtual int TableGetColumnIndex() = 0;
	virtual int TableGetRowIndex() = 0;
	virtual const char* TableGetColumnName(int column_n = -1) = 0;
	virtual ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1) = 0;
	virtual void TableSetColumnEnabled(int column_n, bool v) = 0;
	virtual void TableSetBgColor(
		ImGuiTableBgTarget target, ImU32 color, int column_n = -1) = 0;

	virtual void Columns(
		int count = 1, const char* id = NULL, bool border = true) = 0;
	virtual void NextColumn() = 0;
	virtual int GetColumnIndex() = 0;
	virtual float GetColumnWidth(int column_index = -1) = 0;
	virtual void SetColumnWidth(int column_index, float width) = 0;
	virtual float GetColumnOffset(int column_index = -1) = 0;
	virtual void SetColumnOffset(int column_index, float offset_x) = 0;
	virtual int GetColumnsCount() = 0;

	virtual bool BeginTabBar(
		const char* str_id, ImGuiTabBarFlags flags = 0) = 0;
	virtual void EndTabBar() = 0;
	virtual bool BeginTabItem(const char* label, bool* p_open = NULL,
		ImGuiTabItemFlags flags = 0) = 0;
	virtual void EndTabItem() = 0;
	virtual bool TabItemButton(
		const char* label, ImGuiTabItemFlags flags = 0) = 0;
	virtual void SetTabItemClosed(const char* tab_or_docked_window_label) = 0;

// TODO: implement docking preprocessor for enabling
#ifdef KOTEK_USE_IMGUI_DOCKING
	virtual ImGuiID DockSpace(ImGuiID id, const ImVec2& size = ImVec2(0, 0),
		ImGuiDockNodeFlags flags = 0,
		const ImGuiWindowClass* window_class = NULL) = 0;
	virtual ImGuiID DockSpaceOverViewport(const ImGuiViewport* viewport = NULL,
		ImGuiDockNodeFlags flags = 0,
		const ImGuiWindowClass* window_class = NULL) = 0;
	virtual void SetNextWindowDockID(ImGuiID dock_id, ImGuiCond cond = 0) = 0;
	virtual void SetNextWindowClass(const ImGuiWindowClass* window_class) = 0;
	virtual ImGuiID GetWindowDockID() = 0;
	virtual bool IsWindowDocked() = 0;
#endif

	virtual void LogToTTY(int auto_open_depth = -1) = 0;
	virtual void LogToFile(
		int auto_open_depth = -1, const char* filename = NULL) = 0;
	virtual void LogToClipboard(int auto_open_depth = -1) = 0;
	virtual void LogFinish() = 0;
	virtual void LogButtons() = 0;
	virtual void LogText(const char* fmt, ...) = 0;
	virtual void LogTextV(const char* fmt, va_list args) = 0;

	virtual bool BeginDragDropSource(ImGuiDragDropFlags flags = 0) = 0;
	virtual bool SetDragDropPayload(
		const char* type, const void* data, size_t sz, ImGuiCond cond = 0) = 0;
	virtual void EndDragDropSource() = 0;
	virtual bool BeginDragDropTarget() = 0;
	virtual const ImGuiPayload* AcceptDragDropPayload(
		const char* type, ImGuiDragDropFlags flags = 0) = 0;
	virtual void EndDragDropTarget() = 0;
	virtual const ImGuiPayload* GetDragDropPayload() = 0;

	virtual void BeginDisabled(bool disabled = true) = 0;
	virtual void EndDisabled() = 0;

	virtual void PushClipRect(const ImVec2& clip_rect_min,
		const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect) = 0;
	virtual void PopClipRect() = 0;

	virtual void SetItemDefaultFocus() = 0;
	virtual void SetKeyboardFocusHere(int offset = 0) = 0;

	virtual bool IsItemHovered(ImGuiHoveredFlags flags = 0) = 0;
	virtual bool IsItemActive() = 0;
	virtual bool IsItemFocused() = 0;
	virtual bool IsItemClicked(ImGuiMouseButton mouse_button = 0) = 0;
	virtual bool IsItemVisible() = 0;
	virtual bool IsItemEdited() = 0;
	virtual bool IsItemActivated() = 0;
	virtual bool IsItemDeactivated() = 0;
	virtual bool IsItemDeactivatedAfterEdit() = 0;
	virtual bool IsItemToggledOpen() = 0;
	virtual bool IsAnyItemHovered() = 0;
	virtual bool IsAnyItemActive() = 0;
	virtual bool IsAnyItemFocused() = 0;
	virtual ImVec2 GetItemRectMin() = 0;
	virtual ImVec2 GetItemRectMax() = 0;
	virtual ImVec2 GetItemRectSize() = 0;
	virtual void SetItemAllowOverlap() = 0;

	virtual ImGuiViewport* GetMainViewport() = 0;

	virtual bool IsRectVisible(const ImVec2& size) = 0;
	virtual bool IsRectVisible(
		const ImVec2& rect_min, const ImVec2& rect_max) = 0;
	virtual double GetTime() = 0;
	virtual int GetFrameCount() = 0;
	virtual ImDrawList* GetBackgroundDrawList() = 0;
	virtual ImDrawList* GetForegroundDrawList() = 0;
	virtual ImDrawList* GetBackgroundDrawList(ImGuiViewport* viewport) = 0;
	virtual ImDrawList* GetForegroundDrawList(ImGuiViewport* viewport) = 0;
	virtual ImDrawListSharedData* GetDrawListSharedData() = 0;
	virtual const char* GetStyleColorName(ImGuiCol idx) = 0;
	virtual void SetStateStorage(ImGuiStorage* storage) = 0;
	virtual ImGuiStorage* GetStateStorage() = 0;
	virtual bool BeginChildFrame(
		ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0) = 0;
	virtual void EndChildFrame() = 0;

	virtual ImVec2 CalcTextSize(const char* text, const char* text_end = NULL,
		bool hide_text_after_double_hash = false, float wrap_width = -1.0f) = 0;

	virtual ImVec4 ColorConvertU32ToFloat4(ImU32 in) = 0;
	virtual ImU32 ColorConvertFloat4ToU32(const ImVec4& in) = 0;
	virtual void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h,
		float& out_s, float& out_v) = 0;
	virtual void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r,
		float& out_g, float& out_b) = 0;

	virtual int GetKeyIndex(ImGuiKey imgui_key) = 0;
	virtual bool IsKeyDown(int user_key_index) = 0;
	virtual bool IsKeyPressed(int user_key_index, bool repeat = true) = 0;
	virtual bool IsKeyReleased(int user_key_index) = 0;
	virtual int GetKeyPressedAmount(
		int key_index, float repeat_delay, float rate) = 0;
	virtual void SetNextFrameWantCaptureKeyboard(
		bool want_capture_keyboard_value = true) = 0;

	virtual bool IsMouseDown(ImGuiMouseButton button) = 0;
	virtual bool IsMouseClicked(
		ImGuiMouseButton button, bool repeat = false) = 0;
	virtual bool IsMouseReleased(ImGuiMouseButton button) = 0;
	virtual bool IsMouseDoubleClicked(ImGuiMouseButton button) = 0;
	virtual bool IsMouseHoveringRect(
		const ImVec2& r_min, const ImVec2& r_max, bool clip = true) = 0;
	virtual bool IsMousePosValid(const ImVec2* mouse_pos = NULL) = 0;
	virtual bool IsAnyMouseDown() = 0;
	virtual ImVec2 GetMousePos() = 0;
	virtual ImVec2 GetMousePosOnOpeningCurrentPopup() = 0;
	virtual bool IsMouseDragging(
		ImGuiMouseButton button, float lock_threshold = -1.0f) = 0;
	virtual ImVec2 GetMouseDragDelta(
		ImGuiMouseButton button = 0, float lock_threshold = -1.0f) = 0;
	virtual void ResetMouseDragDelta(ImGuiMouseButton button = 0) = 0;
	virtual ImGuiMouseCursor GetMouseCursor() = 0;
	virtual void SetMouseCursor(ImGuiMouseCursor cursor_type) = 0;
	virtual void SetNextFrameWantCaptureMouse(
		bool want_capture_mouse_value = true) = 0;

	virtual const char* GetClipboardText() = 0;
	virtual void SetClipboardText(const char* text) = 0;

	virtual void LoadIniSettingsFromDisk(const char* ini_filename) = 0;
	virtual void LoadIniSettingsFromMemory(
		const char* ini_data, size_t ini_size = 0) = 0;
	virtual void SaveIniSettingsToDisk(const char* ini_filename) = 0;
	virtual const char* SaveIniSettingsToMemory(
		size_t* out_ini_size = NULL) = 0;

	virtual bool DebugCheckVersionAndDataLayout(const char* version_str,
		size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4,
		size_t sz_drawvert, size_t sz_drawidx) = 0;

	virtual void SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func,
		ImGuiMemFreeFunc free_func, void* user_data = NULL) = 0;
	virtual void GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func,
		ImGuiMemFreeFunc* p_free_func, void** p_user_data) = 0;
	virtual void* MemAlloc(size_t size) = 0;
	virtual void MemFree(void* ptr) = 0;

#ifdef KOTEK_USE_IMGUI_DOCKING
	virtual ImGuiPlatformIO& GetPlatformIO() = 0;
#endif

	virtual void UpdatePlatformWindows() = 0;
	virtual void RenderPlatformWindowsDefault(
		void* platform_render_arg = NULL, void* renderer_render_arg = NULL) = 0;
	virtual void DestroyPlatformWindows() = 0;
	virtual ImGuiViewport* FindViewportByID(ImGuiID id) = 0;
	virtual ImGuiViewport* FindViewportByPlatformHandle(
		void* platform_handle) = 0;
};

bool InitializeModule_Core_API(ktkMainManager*);
bool ShutdownModule_Core_API(ktkMainManager*);
bool SerializeModule_Core_API(ktkMainManager*);
bool DeserializeModule_Core_API(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
