#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

// TODO: add helper namespace for translating this enum
enum class eFolderIndex : ktk::enum_base_t
{
	kFolderIndex_Root,
	kFolderIndex_Gamedata,
	kFolderIndex_Configs,
	kFolderIndex_Scripts,
	kFolderIndex_Textures,
	kFolderIndex_Shaders,
	kFolderIndex_Shaders_GLSL,
	kFolderIndex_Shaders_HLSL,
	kFolderIndex_Shaders_WEBGPU,
	kFolderindex_Shaders_SPV,
	kFolderIndex_Models,
	kFolderIndex_Sounds,
	kFolderIndex_Levels,
	kFolderIndex_AI,
	kFolderIndex_UserTests,
	kFolderIndex_UserData_ShaderCache,
	kFolderIndex_UserData,
	kEndOfEnum
};

enum class eResourceLoadingType : ktk::enum_base_t
{
	kText,
	kTexture,
	kModel,
	kModelStatic_Triangle,
	kModelStatic_Box,
	kModelStatic_Sphere,
	kSound,
	kVideo,
	kDLL,
	kAutoDetect,
	kEndOfEnum,
	kUnknown = -1
};

enum class eResourceLoadingPolicy : ktk::enum_base_t
{
	kAsync,
	kSync,
	kEndOfEnum
};

enum class eResourceCachingPolicy : ktk::enum_base_t
{
	kCache,
	kWithoutCache,
	kEndOfEnum
};

enum class eWindowTitleType : ktk::enum_base_t
{
	// probably all possible cases for output in window's title
	kTitle_ApplicationName,
	kTitle_Time,
	kTitle_GitVersion,
	kTitle_ApplicationVersion,
	kTitle_CurrentSceneName,
	// that star * when scene was changed
	kTitle_CurrentSceneEditStatus,
	kTitle_FPS,
	kTitle_Ping,
	kTitle_PlayerName,
	kTitle_EntitiesCount,
	kTitle_CurrentLevelName,

	kEndOfEnum
};

/// \~russian @brief ������ ������������ ���������� ����� �����������
/// ����� ������.
///
/// @warning ����� ��������, ��� ������ ������������ ���� �������
/// ������, ����� �������� ����� ������� ������ �������� � ������, ��
/// ��� �� ������ ��� ������� �� ��� ���� ����������� ��� �������
/// ����������. ��� ��� ��������? ��� ����� ��������, ��� ����������
/// ����� �� ������� ������ ��������� �� ��� ���� ���� �� ������������
/// ������� �� ���������� ���������� � ���� ����������. � ������� ����
/// ���� '--sdk', � ������������ ��� ������� ����������, � ������ ��
/// ����� ������� � ������� ����� ���� ������������ ������ ����������?
/// ���� ��, �� �� ������ ��������� true ���������������� ���� (� ������
/// ������ kEngine_Feature_SDK), ������ ��� ���� ������ ������ � ���
/// ������, ����� �� ������� � ����������� ��� ������� ���������� ��
/// ������������� ���, ����� ��� �� ����� �������� ������, �� �������
/// ������������ ��� ����������� kEngine_Feature_SDK ��������, ����� ��
/// ���� �� ����� ������� �� ������������� ��� ������� �� ����. ���
/// ����� ������� � �����������. �������, ���� ������� �
/// Kotek::Core::ktkEngineConfig, ��� ���� "��������", �� ���� ������
/// ���:
/// - ������������ ���������� �������� ������� ������� ���������� ������
/// �����������;
/// - ������������ ������ ��� ����������� �������;
/// - ����� �������� ������������ ���������� ������ �������� �� ����,
/// ���� ��������, �� ������������ �����������, ��� ��� ������� ����
/// ������� � ������ � ��� ��������.
///
/// ���������� ������:
///
/// @code
///
/// bool InitializeSDK_ImplementationMyMethodOrFunctionName() {
///		// �����-�� ��� �����
///		// ���-�� ����� ��������
///
///		// ����� ����� ������ ��� �������
///		// ������ �� ���-�� ���������� Kotek::Core::ktkMainManager*
///(p_main_manager) 		Kotek::Core::ktkEngineConfig* p_config =
/// p_main_manager->Get_EngineConfig();
///
///		// ������� �� �� �������� ������, ������ ��� ���������
/// ������������ ���� ������ ����� ������� � ������ ��������. ���������
/// ����� ��� � ���� �����-�� ������� �������, � ��� ������, ��� ��
/// ���������� �� ���������� ������, ��� � ��� ����, � ��� � ��� ���.
/// ����� ��� �� ������ ���������� ���� �� ����� ������������ ������� �
/// ��������, � ������� ������ �������� ����� "�����������"/�������, �
/// ����� ����� �� �������� �� ��������� � �������������� ��� �����
/// ������ ����� �������� �� ������ p_config->IsFeatureEnabled � ����
/// true �� ��������� �����-�� ������. �� ���� ��� ����������
/// ����������� ���� �����, ��� �� ��� ���� ���������� ���������� � ���
/// �� ��� ��������, �� ���� ��������.
///		p_config->SetFeatureStatus(Kotek::Core::eEngineFeature::kEngine_Feature_SDK,
/// true);
///
///		return true;
/// }
///
///
/// // ��� ��� � ���� ��� � �����-�� ��� ����������
///
/// bool ExecuteSomeCode_ButCheckIfSDKFeatureIsEnabled() {
///		Kotek::Core::ktkIEngineConfig* p_config =
/// p_main_manager->Get_EngineConfig();
///
///		if (p_config->IsFeatureEnabled(kEngine_Feature_SDK)) {
///			// ���� ����� ������� ���� ��������, �� ��� ������ ���
/// ���������� ���������� ������������� � ������ ��� ����������� ���
/// ����� �������, �� ���� �������� ����������� = �������� � ������ �����
/// ������.
///
///		}
///
///		return true;
/// }
///
/// @endcode
///
/// @attention ���� �� ������ ������� �������� ���������� ������������
/// ��� Kotek::Core::ktkEngineConfig ���������� ���������� �� ����������
/// ��������� ���� Kotek::Core::ktkWindow::Initialize,
/// Kotek::Core::ktkEngineConfig::GetRenderFeature.
///
///
/// @see Kotek::Core::ktkWindow
/// @see Kotek::Core::ktkEngineConfig
/// @see Kotek::Core::ktkMainManager
///
/// \~english @brief This enumeration is for specifying what features
/// the engine supports for runtime usage.
///
/// @warning You need to understand the purpose of this enumeration.
/// When you want to tell a user that some feature is supported by
/// Engine in code (at runtime), you need to call IsFeatureEnabled
/// method from Kotek::Core::ktkEngineConfig instance in order to get
/// status of the appropriate feature. Like if you implement your SDK
/// you put the calling of setting feature with true status that means
/// this feature is working in Engine right now. Otherwise the feature
/// can't exist or it is not working like status is false. So you need
/// to treat it like a flag when something was initialized in Engine and
/// at runtime you want to check it through one place like
/// Kotek::Core::ktkEngineConfig, but it is not a flag to tell Engine
/// that Engine must enable (call it) because you passed the flag, no!
/// So it is just writing current features that called somewhere and
/// they work. Also determing when a feature should be enabled based on
/// console command arguments that user passed to application. Like if I
/// want to enable SDK I should pass a flag '--sdk' so formally you need
/// to check if this flag contains in command argument line and if it is
/// true you should put this to feature in config, but only when
/// initialization was called and successfully completed otherwise it
/// doesn't make any sense if you tell a user that this feature is
/// enabled, but in real nothing was called for its existance in Engine.
///
/// For example:
///
/// @code
///
/// bool InitializeSDK_ImplementationMethodOrFunctionName() {
///		// some code is here
///		// ...
///		// the end of method
///
///		// probably interface is often used, but we make it more obvious
/// with ktkEngineConfig instance
///		// and you obtained Kotek::Core::ktkMainManager*
///(p_main_manager) somewhere too! Kotek::Core::ktkIEngineConfig*
/// p_config = p_main_manager->Get_EngineConfig();
///
///		p_config->SetFeatureStatus(Kotek::Core::eEngineFeature::kEngine_Feature_SDK,
/// true);
///
///		return true;
/// }
///
/// // somewhere in SDK handlers instances like SDK resource manager or
/// some window
///
/// bool ExecuteSomeCode_ButCheckIfSDKFeatureIsEnabled() {
///		Kotek::Core::ktkIEngineConfig* p_config =
/// p_main_manager->Get_EngineConfig();
///
///		if (p_config->IsFeatureEnabled(kEngine_Feature_SDK)) {
///			// do some real action here, because SDK initialization was
/// called somewhere
///
///		}
///
///		return true;
/// }
///
/// @endcode
///
/// @attention For observing real examples of usage
/// Kotek::Core::ktkEngineConfig you have to check
/// Kotek::Core::ktkWindow::Initialize method and
/// Kotek::Core::ktkEngineConfig::GetRenderFeature method respectively.
///
/// @see Kotek::Core::ktkEngineConfig
/// @see Kotek::Core::ktkMainManager
/// @see Kotek::Core::ktkWindow
///
/// \~german
///
///
/// \~french
enum class eEngineFeature : ktk::enum_base_t
{
	/// \~english @brief This field is system and it means that if the
	/// required feature is not implemenented or exist you need to use
	/// this field. For example, the user asks for determining if
	/// kEngine_Feature_SomethingThatDoesntExistInEnum exists in engine.
	/// But we can't return anything else as false state, and for
	/// obtaining the field if the user asks for the field we will
	/// return kEngine_Feature_Unknown.
	///
	/// For understanding check Kotek::Core::ktkEngineConfig's method
	/// GetRenderFeature.
	/// \~russian @brief ������ ���� ��������� � ������������ ��� ����,
	/// ����� ������� ��� ������������� ���� �� ���������� ������, ��
	/// ���� � ����� ������������. � ����� ������ ����������� ������
	/// ��������������� ������ �����, ����� ������� ������������ ��� ���
	/// ������������� ���� �� ���������� � ���������� ��� �������.
	///
	/// ���������� ������ ������������� ��������� � ������
	/// GetRenderFeature � Kotek::Core::ktkEngineConfig.
	/// \~german @brief
	/// \~french @brief
	kNone = 0
};

enum class eEngineFeatureWindow : ktk::enum_base_t
{
	/// \~english @brief This field specifies that (main) window is in
	/// windowed mode. So if user checks if this feature is in true
	/// state, so it means the window is in windowed mode. The developer
	/// must check that the field sets to true only if the window is in
	/// real windowed mode.
	/// \~russian @brief ������ ���� ��������, ��� (�������) ����
	/// ���������� ��������� � ������� ������. ��� ���������
	/// ������������ ��� ��������, ��� ���� �� ����� ��������� ������
	/// ����, �� ���� ��� ��������, ������ ���� ������� ��������� �
	/// ������� ������, ����������� ������ ��������� � �������������,
	/// ��� ���� ���� ��������, �� ��� ������������� ����������������.
	/// \~german @brief
	/// \~french @brief
	kEngine_Window_Windowed = 1 << 2,

	/// \~english @brief This field specifies that window is in
	/// borderless mode. So if the user checks if this field is set to
	/// true state, it means that window is in borderless mode. The
	/// developer must check that window is indeed in borderless mode
	/// and set this field in true state for notifying user.
	/// \~russian @brief ������ ���� ��������, ��� ���� ��������� �
	/// ������� ������, �� ��� ������� �����. �������� ������������ ���
	/// �������� ������ �������� ���������, ��� ���� ������� ��������� �
	/// ��������������� ������. �� ���� ������ ������� ����������� �
	/// ������������� ��� ���������.
	/// \~german @brief
	/// \~french @brief
	kEngine_Window_Borderless = 1 << 3,

	/// \~english @brief This field specifies that window is in
	/// fullscreen mode. If user checks that field is in true state it
	/// means that window is in real fullscreen mode. The developer must
	/// provide to user that window is in fullscreen and the appropriate
	/// is in true state.
	/// \~russian @brief ������ ���� ���������� ��� ���� ��������� �
	/// ������������� ������. ��� ��������, ��� ���� ������������
	/// ��������� ������ ���� ��� ��� ��������, �� ��� ������ ��� ����
	/// ������� ��������� � ����� ������. ����������� ������
	/// ������������� ����� ���������.
	/// \~german @brief
	/// \~french @brief
	kEngine_Window_FullScreen = 1 << 4,

	kNone = 0
};

enum class eEngineFeatureSDK : ktk::enum_base_t
{
	/// \~english @brief This field means that your engine is called SDK
	/// initialization or it means that your SDK implementation is
	/// working in Engine. So for user it means that if your status of
	/// this field equals true that means that your SDK is enabled and
	/// working in Engine.
	///
	/// \~russian @brief ������ ���� ���������� ��� ��� ��� �������� �
	/// ��� ����������� ��������� ��� �������� ���� ������� � ������.
	/// ��� ��������� ������������ ����� �������� ���������, ��� ����
	/// ��� ���� ����� true, �� ������������ ����� ������������ ��������
	/// ����� ��� ������� �������� � ������. ����� ��� �� ���
	/// ����������, ���� �� ������ �� �������� ������.
	///
	///
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_SDK = 1 << 0,

	/// \~english @brief This field means that your engine implemented
	/// SDK based on ImGui. So for end user the checking status of this
	/// feature will be meant that you implemented and called all things
	/// that related for Initialization/Creation SDK which is based on
	/// ImGui and it means that it works in Engine right now.
	/// \~russian @brief ������ ���� ��������, ��� �� ������ ����������
	/// SDK ����������� �� ��������� ImGui. ��� ��������� ������������
	/// ��� ����� ��������, ��� ���� �� ����� ��������� �������� ��
	/// ����� ����������� (���� � Kotek::Core::ktkEngineConfig), �� ���
	/// ��������������� ������� ���� ��������� ��� ����, �����
	/// ����������������/������� SDK ����������� �� ImGui.
	/// \~german @brief
	/// \~french @brief
	///
	///
	kEngine_Feature_SDK_ImGui = 1 << 1,

	kEngine_Feature_SDK_ImGui_Initialized = 1 << 2,

	kNone = 0
};

/// @brief
enum class eEngineSupportedRenderer : ktk::enum_base_t
{
	kDirectX_7,
	kDirectX_8,
	kDirectX_9,
	kDirectX_10,
	kDirectX_11,
	kDirectX_12,
	kDirectX_Latest = kDirectX_12,

	kVulkan_1_0,
	kVulkan_1_1,
	kVulkan_1_2,
	kVulkan_1_3,
	kVulkan_Latest = kVulkan_1_3,

	kOpenGLES_1,
	kOpenGLES_2,
	kOpenGLES_3_0,
	kOpenGLES_3_1,
	kOpenGLES_3_2,
	kOpenGLES_Latest = kOpenGLES_3_2,

	kOpenGL_1_0,
	kOpenGL_1_1,
	kOpenGL_1_2,
	kOpenGL_1_3,
	kOpenGL_1_4,
	kOpenGL_1_5,
	kOpenGL_2_0,
	kOpenGL_2_1,
	kOpenGL_3_0,
	kOpenGL_3_1,
	kOpenGL_3_2,
	kOpenGL_3_3,
	kOpenGL_4_0,
	kOpenGL_4_1,
	kOpenGL_4_2,
	kOpenGL_4_3,
	kOpenGL_4_4,
	kOpenGL_4_5,
	kOpenGL_4_6,
	kOpenGL_Latest = kOpenGL_4_6,

	kUnknown = -1,
	kEndOfEnum
};

enum class eEngineFeatureRenderer : ktk::enum_base_t
{
	/// \~english @brief This field means that engine uses OpenGL
	/// version 4.6. If this field is true it means that engine uses
	/// OpenGL 4.6 currently. The developer must check the valid state
	/// of this field in order to provide it to end user.
	/// \~russian @brief ������ ���� ����������, ��� ������ ����������
	/// �������� OpenGL ������ 4.6 (�� ���� ������� ����� ���������). ���� ����
	/// ����� true ���������, �� ��� ������ ��� ������ ���������� ������
	/// �������� OpenGL 4.6. ����������� ������ ������������� ��� ��������� ����
	/// ������������� ������ ������.
	/// \~german @brief
	/// \~french @brief
	kEngine_Render_Renderer_OpenGL_Latest = 1 << 1,
	kEngine_Render_Renderer_OpenGL_SpecifiedByUser = 1 << 2,

	kEngine_Render_Renderer_DirectX_Latest = 1 << 3,
	kEngine_Render_Renderer_DirectX_SpecifiedByUser = 1 << 4,

	/// \~english @brief This field means that renderer is Vulkan. In
	/// Engine it supposed that only one renderer can exist, thus if
	/// have a true state for this field it means that engine currently
	/// uses Vulkan renderer. The developer must provide a valid state
	/// when the Vulkan renderer is initialized and set state for this
	/// field as true.
	/// \~russian @brief ������ ���� ����������, ��� ������ �������� �
	/// ���������� Vulkan, ��� ������� ��� ���� �������� ���� true.
	/// ����������� ������ ������� �� ���, ��� ��������� ����� ����
	/// ����������� � ������� ��������� Vulkan.
	/// \~german @brief
	/// \~french @brief
	kEngine_Render_Renderer_Vulkan_Latest = 1 << 5,
	kEngine_Render_Renderer_Vulkan_SpecifiedByUser = 1 << 6,

	/// \~english @brief This field means that renderer is software. In
	/// Engine it supposed that only one renderer can exist, so if you
	/// have this field as state true that means that engine is
	/// currently working with Software Renderer. The developer must
	/// provide a valid state when this field is true.
	/// \~russian @brief ������ ���� ��������, ��� ������� ��������
	/// �������� ������ �� ��� ��� ��������� ���. ��������������, ���
	/// ������ ����� �������� ������ � ����� ����������, � ��� ������,
	/// ��� ���� ������ ���� ��������, �� ��� ������ ������ �������� �
	/// ��� ����������. ����������� ������ �������������, ��� ����
	/// ������������ ������� ��������� true, �� � ������ �������� �
	/// ������ ����������.
	/// \~german @brief
	/// \~french @brief
	kEngine_Render_Renderer_Software = 1 << 7,

	kEngine_Render_Renderer_OpenGLES_Latest = 1 << 8,
	kEngine_Render_Renderer_OpenGLES_SpecifiedByUser = 1 << 9,

	kNone = 0
};

/// @brief took information from https://github.com/google/angle
enum class eEngineFeatureRendererANGLE : ktk::enum_base_t
{
	kEngine_Render_Renderer_ANGLE_Feature_Vulkan = 1 << 0,
	kEngine_Render_Renderer_ANGLE_Feature_DirectX_9 = 1 << 1,
	kEngine_Render_Renderer_ANGLE_Feature_DirectX_11 = 1 << 2,
	kEngine_Render_Renderer_ANGLE_Feature_Desktop_GL = 1 << 3,
	kEngine_Render_Renderer_ANGLE_Feature_GL_ES = 1 << 4,
	kEngine_Render_Renderer_ANGLE_Feature_Metal = 1 << 5,
	kNone = 0
};

enum class eEngineFeatureRender : ktk::enum_base_t
{
	/// \~english @brief This field means that renderer enabled MSAA
	/// feature. If the field's state is true it means that renderer
	/// implemented and enabled MSAA feature. The developer must set the
	/// valid state of field.
	/// \~russian @brief ������ ���� �������� ��� �������� �������
	/// ����������� MSAA. ���� ��������� ���� true �������� ���
	/// ����������� ���������� � ������� MSAA. ����������� ������
	/// ������������� ��� ��������� ���� ������������� ������ ���������.
	/// \~german @brief
	/// \~french @brief
	kEngine_Render_Feature_MSAA = 1 << 0,

	/// \~english @brief This field means that renderer enabled VSYNC
	/// feature. If the field's state is true it means that renderer
	/// implemented and enabled VSYNC feature. The developer must set
	/// the valid state of field.
	/// \~russian @brief ������ ���� �������� ��� �������� ����� VSYNC
	/// �������. ���� ���� ����� ��������� true ��� ��������, ���
	/// �������� ���������� � ������� VSYNC �������. ����������� ������
	/// ������������� ��� ��������� ���� ������������� ������ ���������.
	/// \~german @brief
	/// \~french @brief
	///
	kEngine_Render_Feature_VSYNC = 1 << 1,

	kNone = 0
};

/**
 * \~english @brief This is used for console manager class ktkConsole. And it
 * uses for define callback functions when we want to issue some command by
 * enum. For that case you use ktkConsole::Execute or ktkConsole::PushCommand.
 * The difference between two that one executes right now the second just pushes
 * to queue and executes on next tick.
 */
enum class eConsoleCommandIndex : ktk::enum_base_t
{
	// (int width, int height)
	kConsoleCommand_Resize,

	kConsoleCommand_App_Close,
	kConsoleCommand_App_Hide,
	kConsoleCommand_App_Show,
	kConsoleCommand_App_AddTextToExistedWindowTitle,

	kConsoleCommand_Input_Type,

	kConsoleCommand_Render_UploadAllResourcesToGPU,

	// arg1=vertex_data, arg2=index_data, arg3=bounding_primitive_type
	kConsoleCommand_Render_CalculateBoundingPrimitive,

	kConsoleCommand_ResourceManager_Load,

	kConsoleCommand_SDK_LoadScene,
	kConsoleCommand_SDK_SaveScene,
	kConsoleCommand_SDK_Redo,
	kConsoleCommand_SDK_Undo,
	kConsoleCommand_SDK_CloseCurrentScene,
	kConsoleCommand_SDK_StartSimulate,
	kConsoleCommand_SDK_StopSimulate,
	kConsoleCommand_SDK_SelectEntity,
	kConsoleCommand_SDK_DeleteComponentFromEntity,
	kConsoleCommand_SDK_CreateComponentForEntity,
	kConsoleCommand_SDK_CreateEntity,
	kConsoleCommand_SDK_DeleteEntity,

	/**
	 * \~english @brief Defines functionality to your log window when issued it
	 * must send message to log
	 */
	kConsoleCommand_SDK_SendMessageToLogWindow,

	/**
	 * \~english @brief Sends warning message (in my opinion it could be yellow
	 * color) to log window so it depends on your implementation how you will do
	 * that in your 'business logic'
	 */
	kConsoleCommand_SDK_SendMessageWarningToLogWindow,

	/**
	 * \~english @brief Sends error message (in my opinion it could be red
	 * color) to log window so it depends on your implementation how you will do
	 * that in your 'business logic'
	 */
	kConsoleCommand_SDK_SendMessageErrorToLogWindow,

	/**
	 * \~english @brief Sends info message (in my opinion it could be blue
	 * color) to log window so it depends on your implementation how you will do
	 * that in your 'business logic'
	 */
	kConsoleCommand_SDK_SendMessageInfoToLogWindow,

	/**
	 * \~english @brief Sends grey message to log window so it depends on your
	 * implementation how you will do that in your 'business logic'. Of course
	 * we could define a such enum like SendNotImportantMessageToLogWindow but
	 * you know it is really hard to define from that perspective it is just
	 * grey and user can define in his engine what he wants to see it could be
	 * not important or message from physics or anything else
	 */
	kConsoleCommand_SDK_SendMessageGreyToLogWindow,

	/**
	 * \~english @brief As you see it means we want to show modal window that
	 * define that window that asks us about what we want to do with current
	 * scene save and close or just close scene without saving what we have in
	 * all editors about editing something we can save and close our application
	 * or we can close our application without saving our editing instance
	 */
	kConsoleCommand_SDK_ShowModalWindow_SaveAndCloseOrCloseScene,

	/**
	 * \~english @brief it means that we have some component like
	 * component_camera, but we say that component_camera can't exist without
	 * component_input because it is pointless to have camera input especially
	 * in your editor, so for that case define components that are required for
	 * creation of component_camera in our case it is component_input. So when
	 * we want to add component_camera have two ways like we just print warning
	 * message that we can't create that component because you don't have the
	 * required one (e.g. component_input) or we can automatically can
	 * components that are required for creation so it means when we add
	 * component_camera we automatically create component_input without any
	 * notifications so sometimes it could be useful, but user doesn't to enable
	 * a such feature like we provide a such thing that he always must see what
	 * components are required. But I guess it is pointless to have a such thing
	 * like you need always manually add required components instead of
	 * 'automatization', but who knows who wants to add a such things through
	 * this way...
	 *
	 * @warning You need to interpret that like you enable or disable feature so
	 * it doesn't mean that it issues some code that adds components to entity,
	 * no it is about some flag enable/disable state.
	 */
	kConsoleCommand_SDK_SetFeature_AddComponentsToEntity_ThatRequiredForCreation,

	kEndOfEnum
};

enum class eInputType : ktk::enum_base_t
{
	kInputType_Cursor,
	kInputType_HiddenCursor,
	kInputType_DisabledCursor,

	kEndOfEnum
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK