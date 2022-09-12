#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

namespace Kotek
{
	namespace Core
	{
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
		///������������ ���� ������ ����� ������� � ������ ��������. ���������
		///����� ��� � ���� �����-�� ������� �������, � ��� ������, ��� ��
		///���������� �� ���������� ������, ��� � ��� ����, � ��� � ��� ���.
		///����� ��� �� ������ ���������� ���� �� ����� ������������ ������� �
		///��������, � ������� ������ �������� ����� "�����������"/�������, �
		///����� ����� �� �������� �� ��������� � �������������� ��� �����
		///������ ����� �������� �� ������ p_config->IsFeatureEnabled � ����
		/// true �� ��������� �����-�� ������. �� ���� ��� ����������
		/// ����������� ���� �����, ��� �� ��� ���� ���������� ���������� � ���
		///�� ��� ��������, �� ���� ��������.
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
		///���������� ���������� ������������� � ������ ��� ����������� ���
		///����� �������, �� ���� �������� ����������� = �������� � ������ �����
		///������.
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
			kEngine_Feature_SDK,

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
			kEngine_Feature_SDK_ImGui,

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
			kEngine_Window_Windowed,

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
			kEngine_Window_Borderless,

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
			kEngine_Window_FullScreen,

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
			kEngine_Render_Feature_MSAA,

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
			kEngine_Render_Feature_VSYNC,

			// don't use, internal usage only
			/// \~english @brief This field is system and it means that it
			/// doesn't use in purpose for detecting which renderer is use. It
			/// is created for determine if renderer's kind is DirectX.	So it is
			/// for internal use, it means that for developer's purpose. See
			/// example in IsFeatureRender of Kotek::Core::ktkEngineConfig.
			/// \~russian @brief ������ ���� ������������ ��� ����������� ����
			/// �����, ���� ���� �������� ���������� ����������� � DirectX. ���
			/// �� ������������ ��� ����������� ����������� ���������. ������
			/// ������������� ���� � IsFeatureRender ������
			/// Kotek::Core::ktkEngineConfig
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX,

			/// \~english @brief This field means that engine uses DirectX 7. If
			/// field equals true means that engine uses DirectX 7 currently.
			/// The developer must provide a valid state of this field that
			/// corresponds to appropriate renderer initialization.
			/// \~russian @brief ������ ���� �������� ��� ������ �������� �
			/// DirectX 7. ���� ��������� ����� true ��� ������ ��� ������
			/// �������� ������ DirectX 7. ����������� ������ ������������� ���
			/// ��������� ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX_7,

			/// \~english @brief This field means that engine uses DirectX 8. If
			/// field equals true means that engine uses DirectX 8 currently.
			/// The developer must provide a valid state of this field that
			/// corresponds to appropriate renderer initialization.
			/// \~russian @brief ������ ���� �������� ��� ������ �������� �
			/// DirectX 8. ���� ��������� ����� true ��� ������ ������ ��������
			/// ������ DirectX 8. ����������� ������ ������������� ��� ���������
			/// ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX_8,

			/// \~english @brief This field means that engine uses DirectX 9. If
			/// the field has a true state it means that engine uses DirectX 9
			/// currently. The developer must check the state of field in order
			/// to verify the valid state of DirectX 9.
			/// \~russian @brief ������ ���� �������� ��� ������ ����������
			/// DirectX 9. ���� ���� ����� ��������� true ��� ������ ��� ������
			/// ���������� ������ DirectX 9. ����������� ������ �������������
			/// ��� ��������� ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX_9,

			/// \~english @brief This field means that engine uses DirectX 10.
			/// If the field equals true that means that engine uses DirectX 10
			/// currently. The developer must check the state of this field.
			/// \~russian @brief ������ ���� �������� ��� ������ ����������
			/// DirectX 10. ���� ���� ����� ��������� true, ��� ������ ������
			/// ������ ���������� DirectX 10. ����������� ������ �������������
			/// ��� ��������� ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX_10,

			/// \~english @brief This field means that engine uses DirectX 11.
			/// If the field equals true that means that engine uses DirectX 11
			/// renderer currently. The developer must provide a valid state of
			/// this field.
			/// \~russian @brief ������ ���� �������� ��� ������ �����
			/// DirectX 11. ���� ���� ����� ��������� true, ��� ������ ���
			/// �������� DirectX 11 ������ �������� � ������. ����������� ������
			/// ������������� ��� ��������� ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX_11,

			/// \~english @brief This field means that engine uses (or not)
			/// DirectX version 12. If this field equals true this means that
			/// engine uses DirectX version 12 currently. The developer must
			/// gurantee that field works in accordance DirectX 12 initilization
			/// and creation.
			/// \~russian @brief ������ ���� ��������, ��� ������ ����������
			/// �������� DirectX 12. ���� ���� ����� ��������� ������ true, ��
			/// DirectX 12 ������������ ������� ������. ����������� ������
			/// �������������, ��� ��������� ������� ���� ������������� ������
			/// ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_DirectX_12,

			// don't use, internal usage only
			/// \~english @brief This field is system and doesn't apply to real
			/// definition of renderer usage. So it means that it uses for
			/// determine if the current renderer is OpenGL, but doesn't
			/// detemine which is version, so it is useful when we need to
			/// compare from OpenGL Renderer to something else. Otherwise it is
			/// hard to define a place where OpenGL renderers start in enum. Of
			/// course we could use kEngine_Render_Renderer_OpenGL1_0, but what
			/// if some older OpenGL's versions exist? The enum will be changed
			/// and the kEngine_Render_Renderer_OpenGL1_0 will not be first in
			/// order to specify that from that field starts OpenGL renderers.
			/// To see real example see the IsFeatureRender in
			/// Kotek::Core::ktkEngineConfig. (but it is applied to DirectX, but
			/// it doesn't change the sense)
			/// \~russian @brief ������ ���� ��������� � �� �������� ��
			/// ������������ ��� ����������� ������-�� ���������, ������� �����
			/// ������������ ������ ������. ��������, ��� ������������ ������
			/// ��� ����, ����� ��������� ����������� ���� �����, � � ������
			/// ���� ���������� ����� ������������ ���� �� �������� ��� ����
			/// ������. � �������, �� ����� ������� ��������, ��� ������ OpenGL
			/// ��������� �������� �����������, � ��� ���� ����� ��������� ����
			/// �� ������� ����. � �������, ���� �� �������
			/// kEngine_Render_Renderer_OpenGL1_0, �� � ��� ��� �������
			/// ��������, ��� �� ����� ��� ����� ������� ������ OpenGL, �������
			/// ����� ���������� � ������ ���������. �� ����� ������, ��� ����
			/// ����� ���������� � �������� ������� ���, ������� ���� �������
			/// ��� ���� kEngine_Render_Renderer_OpenGL, ����� ��������, ���
			/// ����� ���� ���� ������ ���������� OpenGL ���������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_OpenGL,

			/// \~english @brief This field means tht engine uses OpenGL
			/// version 1.0. If this field is true it means that engine uses
			/// OpenGL 1.0. The developer must provide a valid state of this
			/// field for end user.
			/// \~russian @brief ������ ���� ��������, ��� ������ ����������
			/// �������� OpenGL ������ 1.0. ���� ���� ����� ��������� true,
			/// �������� ��� ������ ���������� ������ OpenGL ������ 1.0.
			/// ����������� ������ ������������� ���������� ��������� ���
			/// ������� ����.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_OpenGL1_0,

			/// \~english @brief This field means that engine uses OpenGL
			/// version 2.0. If this field is true it means that engine uses
			/// OpenGL 2.0. The developer must provide a valid state of this
			/// field for end user.
			/// \~russian @brief ������ ���� ��������, ��� ������ ����������
			/// �������� OpenGL ������ 2.0. ���� ���� ����� true, �� ������
			/// ���������� ������ �������� OpenGL 3.3. ����������� ������
			/// ������������� ��� ��������� ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_OpenGL2_0,

			/// \~english @brief This field means that engine uses OpenGL
			/// version 3.3. If this field is true it means that engine uses
			/// OpenGL 3.3. The developer must provide a valid state of this
			/// field for end user.
			/// \~russian @brief ������ ���� ��������, ��� ������ ����������
			/// �������� OpenGL ������ 3.3. ���� ������ ���� ����� ���������
			/// true, �� ��� ���������� ��� ������ ������ �������� � ����������
			/// OpenGL ������ 3.3. ����������� ������ ������������� ���
			/// ��������� ���� ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_OpenGL3_3,

			/// \~english @brief This field means that engine uses OpenGL
			/// version 4.6. If this field is true it means that engine uses
			/// OpenGL 4.6 currently. The developer must check the valid state
			/// of this field in order to provide it to end user.
			/// \~russian @brief ������ ���� ����������, ��� ������ ����������
			/// �������� OpenGL ������ 4.6. ���� ���� ����� true ���������, ��
			/// ��� ������ ��� ������ ���������� ������ �������� OpenGL 4.6.
			/// ����������� ������ ������������� ��� ��������� ����
			/// ������������� ������ ������.
			/// \~german @brief
			/// \~french @brief
			kEngine_Render_Renderer_OpenGL4_6,

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
			kEngine_Render_Renderer_Vulkan,

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
			kEngine_Render_Renderer_Software,

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
			kEngine_Feature_Unknown = -1
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
	} // namespace Core
} // namespace Kotek