#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

// TODO: add helper namespace for translating this enum
enum class eFolderIndex : kun_ktk enum_base_t{kFolderIndex_Root,
	kFolderIndex_DataGame, kFolderIndex_DataGame_Configs,
	kFolderIndex_DataGame_Scripts, kFolderIndex_DataGame_Textures,
	kFolderIndex_DataGame_Shaders, kFolderIndex_DataGame_Shaders_GLSL,
	kFolderIndex_DataGame_Shaders_HLSL, kFolderIndex_DataGame_Shaders_WEBGPU,
	kFolderIndex_DataGame_Shaders_SPV, kFolderIndex_DataGame_Models,
	kFolderIndex_DataGame_Sounds, kFolderIndex_DataGame_Levels,
	kFolderIndex_DataGame_AI, kFolderIndex_DataUser_Tests,
	kFolderIndex_DataUser_ShaderCache, kFolderIndex_DataUser_SDK,
	kFolderIndex_DataUser_SDK_Settings, kFolderIndex_DataUser_SDK_Scenes,
	kFolderIndex_DataUser, kEndOfEnum};

enum class eResourceRequestOperationType : kun_ktk enum_base_t{
	kLoad, kSave, kEndOfEnum};

enum class eResourceRequestResourceType : kun_ktk enum_base_t{kText, kTexture,
	kModel, kModelStatic_Triangle, kModelStatic_Box, kModelStatic_Sphere,
	kSound, kVideo, kDLL, kAutoDetect, kBinary, kEndOfEnum, kUnknown = -1};

enum class eResourceRequestThreadingPolicy : kun_ktk enum_base_t{
	kAsync, kSync, kEndOfEnum};

enum class eResourceRequestCachingPolicy : kun_ktk enum_base_t{
	kCached, kNotCached, kEndOfEnum};

enum class eResourceLoadingType : kun_ktk enum_base_t{kText, kTexture, kModel,
	kModelStatic_Triangle, kModelStatic_Box, kModelStatic_Sphere, kSound,
	kVideo, kDLL, kAutoDetect, kEndOfEnum, kUnknown = -1};

enum class eResourceWritingType : kun_ktk enum_base_t{
	kText, kTexture, kEndOfEnum, kUnknown = -1};

enum class eResourceReadingType : kun_ktk enum_base_t{
	kText, kEndOfEnum, kUnknown = -1};

enum class eResourceLoadingPolicy : kun_ktk enum_base_t{
	kWhole, kStream, kEndOfEnum};

enum class eResourceThreadingPolicy : kun_ktk enum_base_t{
	kAsync, kSync, kEndOfEnum};

enum class eResourceReadingPolicy : kun_ktk enum_base_t{
	kAsync, kSync, kEndOfEnum};

enum class eResourceWritingPolicy : kun_ktk enum_base_t{
	kAsync, kSync, kEndOfEnum};

enum class eResourceCachingPolicy : kun_ktk enum_base_t{
	kCache, kWithoutCache, kEndOfEnum};

enum class eResourceWritingMode : kun_ktk enum_base_t{/// @brief ios::app
	kAppend,
	/// @brief ios::in | ios::out
	kNew,
	/// @brief ios::in | ios::out | ios::trunc
	kNew_Trunc, kEndOfEnum};

enum class eWindowTitleType : kun_ktk enum_base_t{
	// probably all possible cases for output in window's title
	kTitle_ApplicationName, kTitle_Time, kTitle_GitVersion,
	kTitle_ApplicationVersion, kTitle_CurrentSceneName,
	// that star * when scene was changed
	kTitle_CurrentSceneEditStatus, kTitle_FPS, kTitle_Ping, kTitle_PlayerName,
	kTitle_EntitiesCount, kTitle_CurrentLevelName,

	kEndOfEnum};

/// \~russian @brief Данное перечисление определяет какие возможности
/// имеет движок.
///
/// @warning Важно понимать, что данное перечисление было создано
/// только, чтобы отмечать какие функции сейчас работают в движке, но
/// это не значит что включая ту или иную возможность она реально
/// включается. Как это понимать? Ещё стоит отметить, что определять
/// когда мы реально должны указывать то или иное поле из перечисления
/// зависит от аргументов переданных в само приложение. К примеру есть
/// флаг '--sdk', и пользователь его передал приложению, в движке мы
/// можем считать а передал такой флаг пользователь нашему приложению?
/// Если да, то мы должны поставить true соответствующему полю (в данном
/// случае kEngine_Feature_SDK), однако это надо делать только в том
/// случае, когда мы вызвали и реализовали все функции отвечающие за
/// инициализацию СДК, иначе это не имеет никакого смысла, мы говорим
/// пользователю что возможность kEngine_Feature_SDK включена, когда на
/// деле ни одной функции по инициализации СДК вызвано не было. Это
/// можно вводить в заблуждение. Поэтому, если указано в
/// Kotek::Core::ktkEngineConfig, что поле "включено", то есть значит
/// что:
/// - Пользователь реализовал реальные функции которые отображают данную
/// возможность;
/// - Пользователь вызвал все необходимые функции;
/// - Когда конечный пользователь определяет статус включено ли поле,
/// если включено, то Пользователь гарантирует, что все функции были
/// вызваны в движке и они работают.
///
/// Рассмотрим пример:
///
/// @code
///
/// bool InitializeSDK_ImplementationMyMethodOrFunctionName() {
///		// какой-то код здесь
///		// что-то здесь написали
///
///		// самый конец метода или функции
///		// однако мы где-то определили Kotek::Core::ktkMainManager*
///(p_main_manager) 		Kotek::Core::ktkEngineConfig* p_config =
/// p_main_manager->Get_EngineConfig();
///
///		// Реально мы ее отмечаем только, однако уже конечному
/// пользователю даем понять какая функция в движке работает. Побольшей
/// части это и есть какое-то подобие конфига, в том смысле, что мы
/// определяем на логическом уровне, что у нас есть, а что у нас нет.
/// Чтобы уже на уровне выполнения кода мы могли обрабатывать условия в
/// динамике, к примеру сейчас включена такая "возможность"/функция, а
/// потом вдруг мы захотели ее отключить и соответственно все места
/// должны иметь покрытие на уровне p_config->IsFeatureEnabled и если
/// true то исполняем какую-то логику. То есть это формальное
/// обозначение того факта, что та или иная реализация отработала и как
/// бы она работает, то есть включена.
///		p_config->SetFeatureStatus(Kotek::Core::eEngineFeature::kEngine_Feature_SDK,
/// true);
///
///		return true;
/// }
///
///
/// // Где уже в коде СДК и каких-то его реализаций
///
/// bool ExecuteSomeCode_ButCheckIfSDKFeatureIsEnabled() {
///		Kotek::Core::ktkIFrameworkConfig* p_config =
/// p_main_manager->Get_EngineConfig();
///
///		if (p_config->IsFeatureEnabled(kEngine_Feature_SDK)) {
///			// Если такая функция была включена, то это значит что
/// пользовать реализовал инициализацию и вызвал все необходимые для
/// этого функции, то есть включена возможность = работает в движке прямо
/// сейчас.
///
///		}
///
///		return true;
/// }
///
/// @endcode
///
/// @attention Если вы хотите увидеть реальное применение перечисления
/// для Kotek::Core::ktkEngineConfig необходимо посмотреть на реализации
/// следующих мест Kotek::Core::ktkWindow::Initialize,
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
///(p_main_manager) somewhere too! Kotek::Core::ktkIFrameworkConfig*
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
///		Kotek::Core::ktkIFrameworkConfig* p_config =
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
enum eEngineFeature
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
	/// \~russian @brief Данное поле системное и используется для того,
	/// чтобы сказать что запрашиваемое поле не существует вообще, то
	/// есть в самом перечислении. В таком случае разработчик должен
	/// воспользоваться данным полем, чтобы сказать пользователю что его
	/// запрашиваемое поле не существует и неизвестно для системы.
	///
	/// Конкретный пример использования определен в методе
	/// GetRenderFeature в Kotek::Core::ktkEngineConfig.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_None = 0
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeature);

enum eEngineFeatureWindow
{
	/// \~english @brief This field specifies that (main) window is in
	/// windowed mode. So if user checks if this feature is in true
	/// state, so it means the window is in windowed mode. The developer
	/// must check that the field sets to true only if the window is in
	/// real windowed mode.
	/// \~russian @brief Данное поле означает, что (главное) окно
	/// приложения находится в оконном режиме. Для конечного
	/// пользователя это означает, что если он хочет проверить данное
	/// поле, то если оно включено, значит окно реально находится в
	/// оконном режиме, разработчик должен убедиться и гарантировать,
	/// что если поле включено, то это соответствует действительности.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Window_Windowed = 1 << 2,

	/// \~english @brief This field specifies that window is in
	/// borderless mode. So if the user checks if this field is set to
	/// true state, it means that window is in borderless mode. The
	/// developer must check that window is indeed in borderless mode
	/// and set this field in true state for notifying user.
	/// \~russian @brief Данное поле означает, что окно находится в
	/// оконном режиме, но без оконных рамок. Конечный пользователь при
	/// проверке должен получать состояние, что окно реально находится в
	/// соответствующем режиме. За этим должен следить разработчик и
	/// гарантировать это состояние.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Window_Borderless = 1 << 3,

	/// \~english @brief This field specifies that window is in
	/// fullscreen mode. If user checks that field is in true state it
	/// means that window is in real fullscreen mode. The developer must
	/// provide to user that window is in fullscreen and the appropriate
	/// is in true state.
	/// \~russian @brief Данное поле показывает что окно находится в
	/// полноэкранном режиме. Это означает, что если пользователь
	/// проверяет данное поле что оно включено, то это значит что окно
	/// реально находится в таком режиме. Разработчик должен
	/// гарантировать такое состояние.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Window_FullScreen = 1 << 4,

	kEngine_Feature_Window_None = 0
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeatureWindow);

enum eEngineFeatureSDK
{
	/// \~english @brief This field means that your engine is called SDK
	/// initialization or it means that your SDK implementation is
	/// working in Engine. So for user it means that if your status of
	/// this field equals true that means that your SDK is enabled and
	/// working in Engine.
	///
	/// \~russian @brief Данное поле обозначает что ваш СДК работает и
	/// все необходимые процедуры для создания были вызваны в движке.
	/// Для конечного пользователя будет означать следующее, что если
	/// это поле равно true, то пользователь может обрабатывать ситуации
	/// когда СДК реально работает в движке. Иначе СДК не был
	/// реализован, либо он просто не работает сейчас.
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
	/// \~russian @brief Данное поле означает, что вы имеете реализацию
	/// SDK основанного на парадигме ImGui. Для конечного пользователя
	/// это также означает, что если он хочет проверить включена ли
	/// такая возможность (поле в Kotek::Core::ktkEngineConfig), то все
	/// соответствующие процеду были выполнены для того, чтобы
	/// инициализировать/создать SDK основанного на ImGui.
	/// \~german @brief
	/// \~french @brief
	///
	///
	kEngine_Feature_SDK_ImGui = 1 << 1,

	kEngine_Feature_SDK_ImGui_Initialized = 1 << 2,

	kEngine_Feature_SDK_None = 0
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeatureSDK);

/// @brief
enum class eEngineSupportedRenderer : kun_ktk enum_base_t{kDirectX_7,
	kDirectX_8, kDirectX_9, kDirectX_10, kDirectX_11, kDirectX_12,
	kDirectX_Latest = kDirectX_12,

	kVulkan_1_0, kVulkan_1_1, kVulkan_1_2, kVulkan_1_3,
	kVulkan_Latest = kVulkan_1_3,

	kOpenGLES_1, kOpenGLES_2, kOpenGLES_3_0, kOpenGLES_3_1, kOpenGLES_3_2,
	kOpenGLES_Latest = kOpenGLES_3_2,

	kOpenGL_1_0, kOpenGL_1_1, kOpenGL_1_2, kOpenGL_1_3, kOpenGL_1_4,
	kOpenGL_1_5, kOpenGL_2_0, kOpenGL_2_1, kOpenGL_3_0, kOpenGL_3_1,
	kOpenGL_3_2, kOpenGL_3_3, kOpenGL_4_0, kOpenGL_4_1, kOpenGL_4_2,
	kOpenGL_4_3, kOpenGL_4_4, kOpenGL_4_5, kOpenGL_4_6,
	kOpenGL_Latest = kOpenGL_4_6, kEndOfEnum, kUnknown = -1};

enum eEngineFeatureRenderer
{
	/// \~english @brief This field means that engine uses OpenGL
	/// version 4.6. If this field is true it means that engine uses
	/// OpenGL 4.6 currently. The developer must check the valid state
	/// of this field in order to provide it to end user.
	/// \~russian @brief Данное поле обозначает, что движок использует
	/// рендерер OpenGL версии 4.6 (то есть текущую самую последнюю). Если поле
	/// имеет true состояние, то это значит что движок использует данный
	/// рендерер OpenGL 4.6. Разработчик должен гарантировать что состояние поля
	/// соответствует работе движка.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Renderer_OpenGL_Latest = 1 << 1,
	kEngine_Feature_Renderer_OpenGL_SpecifiedByUser = 1 << 2,

	kEngine_Feature_Renderer_DirectX_Latest = 1 << 3,
	kEngine_Feature_Renderer_DirectX_SpecifiedByUser = 1 << 4,

	/// \~english @brief This field means that renderer is Vulkan. In
	/// Engine it supposed that only one renderer can exist, thus if
	/// have a true state for this field it means that engine currently
	/// uses Vulkan renderer. The developer must provide a valid state
	/// when the Vulkan renderer is initialized and set state for this
	/// field as true.
	/// \~russian @brief Данное поле обозначает, что движок работает с
	/// рендерером Vulkan, при условии что само значение поле true.
	/// Разработчик должен следить за тем, что состояние этого поля
	/// соотносится с работой рендерера Vulkan.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Renderer_Vulkan_Latest = 1 << 5,
	kEngine_Feature_Renderer_Vulkan_SpecifiedByUser = 1 << 6,

	/// \~english @brief This field means that renderer is software. In
	/// Engine it supposed that only one renderer can exist, so if you
	/// have this field as state true that means that engine is
	/// currently working with Software Renderer. The developer must
	/// provide a valid state when this field is true.
	/// \~russian @brief Данное поле означает, что текущий рендерер
	/// работает только на ЦПУ без поддержки ГПУ. Предполагается, что
	/// движок может работать только с одним рендерером, а это значит,
	/// что если данное поле включено, то это значит движок работает с
	/// ЦПУ рендерером. Разработчик должен гарантировать, что если
	/// пользователь получил состаяние true, то и движок работает с
	/// данным рендерером.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Renderer_Software = 1 << 7,

	kEngine_Feature_Renderer_OpenGLES_Latest = 1 << 8,
	kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser = 1 << 9,

	kEngine_Feature_Renderer_None = 0,
	// defines amount of real fields before kNone
	// needed to be updated regularly
	kEndOfEnum = 9
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeatureRenderer);

enum eEngineFeatureRendererVendor
{
	kANGLE = 1 << 1,
	kBGFX = 1 << 2,
	kNative = 1 << 3,
	kNone = 0,
	kEndOfEnumeEngineFeatureRendererVendor = 3
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeatureRendererVendor);

/// @brief took information from https://github.com/google/angle
enum eEngineFeatureRendererANGLE
{
	kEngine_Feature_Renderer_ANGLE_Feature_Vulkan = 1 << 0,
	kEngine_Feature_Renderer_ANGLE_Feature_DirectX_9 = 1 << 1,
	kEngine_Feature_Renderer_ANGLE_Feature_DirectX_11 = 1 << 2,
	kEngine_Feature_Renderer_ANGLE_Feature_Desktop_GL = 1 << 3,
	kEngine_Feature_Renderer_ANGLE_Feature_GL_ES = 1 << 4,
	kEngine_Feature_Renderer_ANGLE_Feature_Metal = 1 << 5,
	kEngine_Feature_Renderer_ANGLE_Feature_None = 0
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeatureRendererANGLE);

enum eEngineFeatureRender
{
	/// \~english @brief This field means that renderer enabled MSAA
	/// feature. If the field's state is true it means that renderer
	/// implemented and enabled MSAA feature. The developer must set the
	/// valid state of field.
	/// \~russian @brief Данное поле означает что рендерер включил
	/// возможность MSAA. Если состояние поля true означает что
	/// разработчик реализовал и включил MSAA. Разработчик должен
	/// гарантировать что состояние поля соответствует работе рендерера.
	/// \~german @brief
	/// \~french @brief
	kEngine_Feature_Render_MSAA = 1 << 0,

	/// \~english @brief This field means that renderer enabled VSYNC
	/// feature. If the field's state is true it means that renderer
	/// implemented and enabled VSYNC feature. The developer must set
	/// the valid state of field.
	/// \~russian @brief Данное поле означает что рендерер имеет VSYNC
	/// функцию. Если поле имеет состояние true это означает, что
	/// реднерер реализовал и включил VSYNC функцию. Разработчик должен
	/// гарантировать что состояние поля соответствует работе рендерера.
	/// \~german @brief
	/// \~french @brief
	///
	kEngine_Feature_Render_VSYNC = 1 << 1,

	kEngine_Feature_Render_None = 0
};

KOTEK_IMPLEMENTATION_ENUM_FLAG_OPERATORS(eEngineFeatureRender);

/**
 * \~english @brief This is used for console manager class ktkConsole. And it
 * uses for define callback functions when we want to issue some command by
 * enum. For that case you use ktkConsole::Execute or ktkConsole::PushCommand.
 * The difference between two that one executes right now the second just pushes
 * to queue and executes on next tick.
 */
enum class eConsoleCommandIndex : kun_ktk enum_base_t{// (int width, int height)
	kConsoleCommand_App_Close,
	/// @brief
	kConsoleCommand_App_Hide,
	/// @brief
	kConsoleCommand_App_Show,
	/// @brief
	kConsoleCommand_App_AddTextToExistedWindowTitle,
	kConsoleCommand_App_Resize, // todo: implement this, note that render_resize
								// is about render target but app resize it is
								// about the window itself
	kConsoleCommand_App_Pause,

	/// @brief
	kConsoleCommand_Input_Type,

	kConsoleCommand_Render_UploadAllResourcesToGPU,
	kConsoleCommand_Render_CalculateBoundingPrimitive,
	kConsoleCommand_Render_Resize,

	kConsoleCommand_ResourceManager_Load,
	kConsoleCommand_ResourceManager_OpenForWriting,
	kConsoleCommand_ResourceManager_Write,
	kConsoleCommand_ResourceManager_FinishWriting,
	/// @brief
	kConsoleCommand_SDK_LoadScene,
	/// @brief
	kConsoleCommand_SDK_SaveScene,
	/// @brief
	kConsoleCommand_SDK_Redo,
	/// @brief
	kConsoleCommand_SDK_Undo,
	/// @brief
	kConsoleCommand_SDK_CloseCurrentScene,
	/// @brief
	kConsoleCommand_SDK_StartSimulate,
	/// @brief
	kConsoleCommand_SDK_StopSimulate,
	/// @brief
	kConsoleCommand_SDK_SelectEntity,
	/// @brief
	kConsoleCommand_SDK_DeleteComponentFromEntity,
	/// @brief
	kConsoleCommand_SDK_CreateComponentForEntity,
	kConsoleCommand_SDK_CreateEntity,
	/// @brief
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

	kConsoleCommand_SDK_ShowWindow,
	/// @brief
	kConsoleCommand_SDK_HideWindow,

	// prints as list of registered windows
	kConsoleCommand_SDK_PrintRegisteredWindows,

	kEndOfEnum};

// TODO: not obvious and may conflict with input system better to rename to
// something like eInputCursorType otherwise specify working field where that
// enum relates to
enum class eInputType : kun_ktk enum_base_t{kInputType_Cursor,
	kInputType_HiddenCursor, kInputType_DisabledCursor,

	kEndOfEnum};

enum class eResourceWritingDataType : kun_ktk enum_base_t{kInt8_t, kInt16_t,
	kInt32_t, kInt64_t, kInt128_t, kUInt8_t, kUInt16_t, kUInt32_t, kUInt64_t,
	kUInt128_t, kSize_t, kFloat_t, kDouble_t, kPIntWithSize_t, kPUIntWithSize_t,
	kPFloatWithSize_t, kPDoubleWithSize_t, kPChar_t, kPUChar_t,
	kPUCharWithSize_t, kPCharWithSize_t, kEndOfEnum, kUnknown = -1};

enum class eFileWritingControlCharacterType : kun_ktk enum_base_t{
	/// @brief just a white space aka " "
	kSpace,
	/// @brief aka std::endl
	kNewLine,
	/// @brief aka std::flush
	kFlush, kEndOfEnum};

enum class eResourceHowToWriteData : kun_ktk enum_base_t{kNone,
	kUseEndlAfterWrite, kUseSpaceAfterWrite, kUseSpaceAndEndlAfterWrite,
	kEndOfEnum, kUnknown = -1};

enum class eFolderVisibilityType : kun_ktk enum_base_t{
	kVisible, kHidden, kEndOfEnum};

enum class eFileIOState : kun_ktk enum_base_t{
	kStateEOF, kStateFail, kStateBad, kStateGood};

enum class eFileSeekDirectionType : kun_ktk enum_base_t{
	kSeekDirectionEnd, kSeekdDirectionCurrent, kSeekDirectionBegin, kEndOfEnum};

enum eInputControllerType
{
	kControllerKeyboard,
	kControllerMouse,
	kControllerGamepad,
	kControllerJoystick,
	kControllerTotalAmountOfEnum,
	kControllerUnknown =
		kControllerTotalAmountOfEnum // reserved for unspecified devices
};

/// @brief used classification of keys here:
/// https://en.wikipedia.org/wiki/Function_key
enum eInputControllerKeyboardCategory
{
	kKeyboardKeysTypeWriter,
	kKeyboardKeysFunctionKeysState,
	kKeyboardKeysOtherState,
	kKeyboardKeysNumbers,
	kKeyboardKeysApplication,
	kKeyboardKeysSystem,
	kKeyboardKeysEnter,
	kKeyboardKeysNumpad,
	kKeyboardKeysCursorControlKeys,
	kKeyboardTotalAmountOfEnum,
	kKeyboardUnknown = kKeyboardTotalAmountOfEnum
};

enum eInputControllerMouseData
{
	kMousePreviousCoordinateXInPixels,
	kMousePreviousCoordinateYInPixels,
	kMouseCoordinateXInPixels,
	kMouseCoordinateYInPixels,
	kMouseCoordinateXNormalized,
	kMouseCoordinateYNormalized,
	kMouseDeltaX,
	kMouseDeltaY,
	kMouseSensetivity,
	kControllerMouseDataTotalAmountOfEnum
};

enum eInputMouseKeys
{
	kKEY_LeftButton = 1 << 1,
	kKEY_RightButton = 1 << 2,
	kKEY_MiddleButton = 1 << 3, // wheel
	kKEY_MouseUnknown = 0
};

/// @brief CK = ControllerKeyboard; CM = ControllerMouse; CG =
/// ControllerGamepad; CJ = ControllerJoystick; CA = ControllerAny;
enum eInputAllKeys
{
	kCK_KEY_A,
	kCK_KEY_B,
	kCK_KEY_C,
	kCK_KEY_D,
	kCK_KEY_E,
	kCK_KEY_F,
	kCK_KEY_G,
	kCK_KEY_H,
	kCK_KEY_I,
	kCK_KEY_J,
	kCK_KEY_K,
	kCK_KEY_L,
	kCK_KEY_M,
	kCK_KEY_N,
	kCK_KEY_O,
	kCK_KEY_P,
	kCK_KEY_Q,
	kCK_KEY_R,
	kCK_KEY_S,
	kCK_KEY_T,
	kCK_KEY_U,
	kCK_KEY_V,
	kCK_KEY_W,
	kCK_KEY_X,
	kCK_KEY_Y,
	kCK_KEY_Z,
	kCK_KEY_CAPS_LOCK,
	kCK_KEY_SCROLL_LOCK,
	kCK_KEY_1,
	kCK_KEY_2,
	kCK_KEY_3,
	kCK_KEY_4,
	kCK_KEY_5,
	kCK_KEY_6,
	kCK_KEY_7,
	kCK_KEY_8,
	kCK_KEY_9,
	kCK_KEY_0,
	kCK_KEY_MINUS,
	kCK_KEY_PLUS,
	kCK_KEY_F1,
	kCK_KEY_F2,
	kCK_KEY_F3,
	kCK_KEY_F4,
	kCK_KEY_F5,
	kCK_KEY_F6,
	kCK_KEY_F7,
	kCK_KEY_F8,
	kCK_KEY_F9,
	kCK_KEY_F10,
	kCK_KEY_F11,
	kCK_KEY_F12,
	kCK_KEY_PRTSC,
	kCK_KEY_PAUSE,
	kCK_KEY_DEL,
	kCK_KEY_END,
	kCK_KEY_INSERT,
	kCK_KEY_HOME,
	kCK_KEY_PAGEUP,
	kCK_KEY_PAGEDOWN,
	kCK_KEY_SCROLLLOCK,
	kCK_KEY_ESC,
	kCK_KEY_SPACE,
	kCK_KEY_LEFT_SHIFT,
	kCK_KEY_RIGHT_SHIFT,
	kCK_KEY_LEFT_CONTROL,
	kCK_KEY_RIGHT_CONTROL,
	kCK_KEY_APOSTROPHE,
	kCK_KEY_COMMA,
	kCK_KEY_PERIOD,
	kCK_KEY_SLASH,
	kCK_KEY_BACKSLASH,
	kCK_KEY_SEMICOLON,
	kCK_KEY_EQUAL,
	kCK_KEY_LEFT_BRACKET,
	kCK_KEY_RIGHT_BRACKET,
	kCK_KEY_GRAVE_ACCENT,
	kCK_KEY_ESCAPE,
	kCK_KEY_TAB,
	kCK_KEY_BACKSPACE,
	kCK_KEY_ENTER,
	kCK_KEY_ENTER_NUMPAD,
	kCK_KEY_NUMPAD_NUMLOCK,
	kCK_KEY_NUMPAD_ENTER,
	kCK_KEY_NUMPAD_SLASH,
	kCK_KEY_NUMPAD_ASTERISK,
	kCK_KEY_NUMPAD_1,
	kCK_KEY_NUMPAD_2,
	kCK_KEY_NUMPAD_3,
	kCK_KEY_NUMPAD_4,
	kCK_KEY_NUMPAD_5,
	kCK_KEY_NUMPAD_6,
	kCK_KEY_NUMPAD_7,
	kCK_KEY_NUMPAD_8,
	kCK_KEY_NUMPAD_9,
	kCK_KEY_NUMPAD_0,
	kCK_KEY_NUMPAD_MINUS,
	kCK_KEY_NUMPAD_PLUS,
	kCK_KEY_MENU,
	kCK_KEY_LEFT_ALT,
	kCK_KEY_RIGHT_ALT,
	kCK_KEY_LEFT_SUPER,
	kCK_KEY_RIGHT_SUPER,
	kCK_KEY_WINDOWS,
	kCK_KEY_ARROW_LEFT,
	kCK_KEY_ARROW_UP,
	kCK_KEY_ARROW_RIGHT,
	kCK_KEY_ARROW_DOWN,
	kCM_KEY_LEFT,
	kCM_KEY_RIGHT,
	kCM_KEY_MIDDLE,
	kCA_KEY_END_ENUM,
	kCA_KEY_UNKNOWN = -1 // kCA = kControllerAny
};

enum eInputKeyboardKeys
{
	kKEY_A = 1 << 1,
	kKEY_B = 1 << 2,
	kKEY_C = 1 << 3,
	kKEY_D = 1 << 4,
	kKEY_E = 1 << 5,
	kKEY_F = 1 << 6,
	kKEY_G = 1 << 7,
	kKEY_H = 1 << 8,
	kKEY_I = 1 << 9,
	kKEY_J = 1 << 10,
	kKEY_K = 1 << 11,
	kKEY_L = 1 << 12,
	kKEY_M = 1 << 13,
	kKEY_N = 1 << 14,
	kKEY_O = 1 << 15,
	kKEY_P = 1 << 16,
	kKEY_Q = 1 << 17,
	kKEY_R = 1 << 18,
	kKEY_S = 1 << 19,
	kKEY_T = 1 << 20,
	kKEY_U = 1 << 21,
	kKEY_V = 1 << 22,
	kKEY_W = 1 << 23,
	kKEY_X = 1 << 24,
	kKEY_Y = 1 << 25,
	kKEY_Z = 1 << 26,
	kKEY_CAPS_LOCK = 1 << 27,
	kKEY_SCROLL_LOCK = 1 << 28,
	kKEY_UNKNOWN = 0
};

enum eInputKeyboardKeysNumbers
{
	kKEY_1 = 1 << 1,
	kKEY_2 = 1 << 2,
	kKEY_3 = 1 << 3,
	kKEY_4 = 1 << 4,
	kKEY_5 = 1 << 5,
	kKEY_6 = 1 << 6,
	kKEY_7 = 1 << 7,
	kKEY_8 = 1 << 8,
	kKEY_9 = 1 << 9,
	kKEY_0 = 1 << 10,
	kKEY_MINUS = 1 << 11,
	kKEY_PLUS = 1 << 12,
	kKEY_NUMBER_UNKNOWN = 0
};

enum eInputKeyboardKeysFunctionKeys
{
	kKEY_F1 = 1 << 1,
	kKEY_F2 = 1 << 2,
	kKEY_F3 = 1 << 3,
	kKEY_F4 = 1 << 4,
	kKEY_F5 = 1 << 5,
	kKEY_F6 = 1 << 6,
	kKEY_F7 = 1 << 7,
	kKEY_F8 = 1 << 8,
	kKEY_F9 = 1 << 9,
	kKEY_F10 = 1 << 10,
	kKEY_F11 = 1 << 11,
	kKEY_F12 = 1 << 12,
	kKEY_FUNCTION_KEY_UNKNOWN = 0
};

enum eInputKeyboardKeysOther
{
	kKEY_PRTSC = 1 << 1,
	kKEY_PAUSE = 1 << 2,
	kKEY_DEL = 1 << 3,
	kKEY_END = 1 << 4,
	kKEY_INSERT = 1 << 5,
	kKEY_HOME = 1 << 6,
	kKEY_PAGEUP = 1 << 7,
	kKEY_PAGEDOWN = 1 << 8,
	kKEY_SCROLLLOCK = 1 << 9,
	kKEY_ESC = 1 << 10,
	kKEY_SPACE = 1 << 11,
	kKEY_LEFT_SHIFT = 1 << 12,
	kKEY_RIGHT_SHIFT = 1 << 13,
	kKEY_LEFT_CONTROL = 1 << 14,
	kKEY_RIGHT_CONTROL = 1 << 15,
	kKEY_APOSTROPHE = 1 << 16, // '
	kKEY_COMMA = 1 << 17,      // ,
	kKEY_PERIOD = 1 << 18,     // .
	kKEY_SLASH = 1 << 19,      // /
	kKEY_BACKSLASH = 1 << 20,
	KKEY_SEMICOLON = 1 << 21,
	kKEY_EQUAL = 1 << 22,
	kKEY_LEFT_BRACKET = 1 << 23,
	kKEY_RIGHT_BRACKET = 1 << 24,
	kKEY_GRAVE_ACCENT = 1 << 25,
	kKEY_ESCAPE = 1 << 26,
	kKEY_TAB = 1 << 27,
	kKEY_BACKSPACE = 1 << 28,
	kKEY_OTHER_KEY_UNKNOWN = 0
};

enum eInputKeyboardKeysEnter
{
	kKEY_ENTER = 1 << 1,
	kKEY_ENTER_NUMPAD = 1 << 2,
	kKEY_ENTER_UNKNOWN = 0
};

enum eInputKeyboardKeysNumpad
{
	kKEY_NUMPAD_NUMLOCK = 1 << 1,
	kKEY_NUMPAD_ENTER = 1 << 2,
	kKEY_NUMPAD_SLASH = 1 << 3,    // "/"
	kKEY_NUMPAD_ASTERISK = 1 << 4, // "*"
	kKEY_NUMPAD_1 = 1 << 5,
	kKEY_NUMPAD_2 = 1 << 6,
	kKEY_NUMPAD_3 = 1 << 7,
	kKEY_NUMPAD_4 = 1 << 8,
	kKEY_NUMPAD_5 = 1 << 9,
	kKEY_NUMPAD_6 = 1 << 10,
	kKEY_NUMPAD_7 = 1 << 11,
	kKEY_NUMPAD_8 = 1 << 12,
	kKEY_NUMPAD_9 = 1 << 13,
	kKEY_NUMPAD_0 = 1 << 14,
	kKEY_NUMPAD_MINUS = 1 << 15,
	kKEY_NUMPAD_PLUS = 1 << 16,
	kKEY_NUMPAD_UNKNOWN = 0
};

enum eInputKeyboardKeysApplication
{
	kKEY_MENU = 1 << 1,
	kKEY_LEFT_ALT = 1 << 2,
	kKEY_RIGHT_ALT = 1 << 3,
	kKEY_LEFT_SUPER = 1 << 4,
	kKEY_RIGHT_SUPER = 1 << 5,
	kKEY_APPLICATION_UNKNOWN = 0
};

enum eInputKeyboardKeysSystem
{
	kKEY_WINDOWS = 1 << 1,
	kKEY_SYSTEM_UNKNOWN = 0
};

enum eInputKeyboardCursorControlKeys
{
	kKEY_ARROW_LEFT = 1 << 1,
	kKEY_ARROW_UP = 1 << 2,
	kKEY_ARROW_RIGHT = 1 << 3,
	kKEY_ARROW_DOWN = 1 << 4,
	kKEY_CURSOR_CONTROL_UNKNOWN = 0
};

enum eInputPlatformBackend
{
	kPlatformBackend_GLFW3,
	kPlatformBackend_SDL2,
	kPlatformBackend_SDL3,
	kPlatformBackend_WINAPI,
	kPlatformBackend_X11,
	kPlatformBackend_MACOS,
	kPlatformBackend_PS1,
	kPlatformBackend_PS2,
	kPlatformBackend_PS3,
	kPlatformBackend_PS4,
	kPlatformBackend_PS5,
	kPlatformBackend_PS6,
	kPlatformBackend_XBOX,
	kPlatformBackend_XBOX360,
	kPlatformBackend_XBOXONE,
	kPlatformBackend_XBOXSERIESS,
	kPlatformBackend_XBOXSERIESX,
	kPlatformBackend_NS, // Nintendo Switch
	kPlatformBackend_Unknown
};

static_assert(eInputKeyboardKeysEnter::kKEY_ENTER_NUMPAD ==
		eInputKeyboardKeysNumpad::kKEY_NUMPAD_ENTER &&
	"must be equal otherwise the conflict exists");

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK