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
	kFolderIndex_Sound,
	kFolderIndex_UserTests,
	kFolderIndex_UserData_ShaderCache,
	kFolderIndex_UserData
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
///		Kotek::Core::ktkIEngineConfig* p_config =
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
	kNone = 0
};

enum class eEngineFeatureWindow : ktk::enum_base_t
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
	kEngine_Window_Windowed = 1 << 2,

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
	kEngine_Window_Borderless = 1 << 3,

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

	kNone = 0
};

/// @brief For checking what version the glad initialized you need to take a
/// notice on message: 'Initialized GLAD for: Your_Printed_Version_Here'
enum class eEngineSupportedOpenGLVersion : ktk::enum_base_t
{
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

	/// @brief don't forget to update this field if a new version with a break
	/// changes came
	kOpenGL_Latest = kOpenGL_4_6,
	kUnknown = -1
};

/// @brief 
enum class eEngineSupportedDirectXVersion : ktk::enum_base_t
{
	kDirectX_7,
	kDirectX_8,
	kDirectX_9,
	kDirectX_10,
	kDirectX_11,
	kDirectX_12,

	/// @brief don't forget to update this field if a new version with a break
	/// changes came
	kDirectX_Latest = kDirectX_12,
	kUnknown = -1
};

enum class eEngineFeatureRenderer : ktk::enum_base_t
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
	kEngine_Render_Renderer_OpenGL_Latest = 1 << 11,

	kEngine_Render_Renderer_DirectX_Latest = 1 << 12,

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
	kEngine_Render_Renderer_Vulkan = 1 << 13,

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
	kEngine_Render_Renderer_Software = 1 << 14,

	kEngine_Render_Renderer_ANGLE = 1 << 15,

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
	/// \~russian @brief Данное поле означает что рендерер включил
	/// возможность MSAA. Если состояние поля true означает что
	/// разработчик реализовал и включил MSAA. Разработчик должен
	/// гарантировать что состояние поля соответствует работе рендерера.
	/// \~german @brief
	/// \~french @brief
	kEngine_Render_Feature_MSAA = 1 << 0,

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
	kEngine_Render_Feature_VSYNC = 1 << 1,

	kNone = 0
};

enum class eConsoleCommandIndex : ktk::enum_base_t
{
	// (int width, int height)
	kConsoleCommand_Resize,

	kConsoleCommand_App_Close,
	kConsoleCommand_App_Hide,
	kConsoleCommand_App_Show,
	kConsoleCommand_Render_UploadAllResourcesToGPU
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK