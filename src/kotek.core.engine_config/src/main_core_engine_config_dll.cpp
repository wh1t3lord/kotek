#include "../include/kotek_core_engine_config.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>
#include <kotek.core.filesystem/include/kotek_core_filesystem.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Engine_Config(
	ktkMainManager* p_manager
)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text(
			"[core]: init [engine][config]"
		);
		p_manager->Get_Splash()->Set_Progress();
	}

	ktkFrameworkConfig* p_instance = new ktkFrameworkConfig();
	p_instance->Initialize();

	p_instance->SetARGC(p_manager->Get_ARGC());
	p_instance->SetARGV(p_manager->Get_ARGV());

	auto renderer_type =
		eEngineFeatureRenderer::KOTEK_USE_STARTUP_RENDERER;
	auto renderer_vendor = eEngineFeatureRendererVendor::
		KOTEK_USE_STARTUP_RENDERER_VENDOR;

	p_instance->SetFeatureStatus(renderer_type, true);

	eEngineSupportedRenderer renderer_version{};

	switch (renderer_type)
	{
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_DirectX_Latest:
	{
		renderer_version =
			eEngineSupportedRenderer::kDirectX_Latest;
		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_DirectX_SpecifiedByUser:
	{
		renderer_version = eEngineSupportedRenderer::
			KOTEK_USE_STARTUP_RENDERER_VERSION;

		KOTEK_ASSERT(
			renderer_version >=
					eEngineSupportedRenderer::kDirectX_7 &&
				renderer_version <=
					eEngineSupportedRenderer::kDirectX_Latest,
			"You passed DirectX renderer but version is not "
		    "for DirectX at "
			"all!"
		);

		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_OpenGLES_Latest:
	{
		renderer_version =
			eEngineSupportedRenderer::kOpenGLES_Latest;

		KOTEK_ASSERT(
			renderer_version >=
					eEngineSupportedRenderer::kOpenGLES_1 &&
				renderer_version <=
					eEngineSupportedRenderer::kOpenGLES_Latest,
			"you passed OpenGL ES renderer but version is not "
		    "for OpenGL ES at "
			"all!"
		);
		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser:
	{
		renderer_version = eEngineSupportedRenderer::
			KOTEK_USE_STARTUP_RENDERER_VERSION;

		KOTEK_ASSERT(
			renderer_version >=
					eEngineSupportedRenderer::kOpenGLES_1 &&
				renderer_version <=
					eEngineSupportedRenderer::kOpenGLES_Latest,
			"you passed OpenGL ES renderer but version is not "
		    "for OpenGL ES at "
			"all!"
		);

		bool isBGFX = (renderer_vendor &
		               eEngineFeatureRendererVendor::kBGFX) ==
			eEngineFeatureRendererVendor::kBGFX;
		bool isANGLE = (renderer_vendor &
		                eEngineFeatureRendererVendor::kANGLE) ==
			eEngineFeatureRendererVendor::kANGLE;

		// todo: when angle[vulkan] package will be added to
		// vcpkg you should delete this assert and warning
		if (isANGLE)
		{
			KOTEK_MESSAGE_WARNING(
				"you shouldn't use ANGLE right now because it "
			    "provides poor "
				"implementation on Windows due to DX11 "
			    "backend, but vcpkg "
				"doesn't provide vulkan version of angle yet. "
			    "So choose BGFX "
				"please!"
			);

			if (!isBGFX)
			{
				renderer_vendor |=
					eEngineFeatureRendererVendor::kBGFX;

				KOTEK_MESSAGE_WARNING(
					"you forgot to add BGFX to your flag, "
				    "engine did for you"
				);
			}
		}

		// todo: when angle[vulkan] package will be added to
		// vcpkg you should delete this assert and warning
		KOTEK_ASSERT(
			isBGFX, "right now we prioritize BGFX over ANGLE"
		);

		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_OpenGL_Latest:
	{
		renderer_version = eEngineSupportedRenderer::
			KOTEK_USE_STARTUP_RENDERER_VERSION;

		KOTEK_ASSERT(
			renderer_version >=
					eEngineSupportedRenderer::kOpenGL_1_0 &&
				renderer_version <=
					eEngineSupportedRenderer::kOpenGL_Latest,
			"you passed OpenGL renderer but version is not for "
		    "OpenGL at all!"
		);
		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_OpenGL_SpecifiedByUser:
	{
		renderer_version = eEngineSupportedRenderer::
			KOTEK_USE_STARTUP_RENDERER_VERSION;

		KOTEK_ASSERT(
			renderer_version >=
					eEngineSupportedRenderer::kOpenGL_1_0 &&
				renderer_version <=
					eEngineSupportedRenderer::kOpenGL_Latest,
			"you passed OpenGL renderer but version is not for "
		    "OpenGL at all!"
		);
		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_Vulkan_Latest:
	{
		renderer_version =
			eEngineSupportedRenderer::kVulkan_Latest;
		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_Vulkan_SpecifiedByUser:
	{
		renderer_version = eEngineSupportedRenderer::
			KOTEK_USE_STARTUP_RENDERER_VERSION;

		KOTEK_ASSERT(
			renderer_version >=
					eEngineSupportedRenderer::kVulkan_1_0 &&
				renderer_version <=
					eEngineSupportedRenderer::kVulkan_Latest,
			"you passed Vulkan but version is not for Vulkan "
		    "at all!"
		);
		break;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_Software:
	{
		KOTEK_ASSERT(false, "think about it");
		break;
	}
	}

	p_instance->Set_VideoMemoryForInitialize(1024 * 1024 * 32);
	p_instance->SetFeatureStatus(renderer_version, true);
	p_instance->SetFeatureStatus(renderer_vendor, true);
	p_manager->Set_FrameworkConfig(p_instance);

	return true;
}

bool SerializeModule_Core_Engine_Config(
	ktkMainManager* p_manager
)
{
	return true;
}

bool DeserializeModule_Core_Engine_Config(
	ktkMainManager* p_manager
)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text(
			"[core]: deserialize [engine][config]"
		);
		p_manager->Get_Splash()->Set_Progress();
	}

	auto* p_filesystem = p_manager->GetFileSystem();

	KOTEK_ASSERT(
		p_filesystem,
		"you must initialize filesystem instance before "
	    "calling this function"
	);
	/*
	auto path_to_sys_info_json = p_filesystem->GetFolderByEnum(
		eFolderIndex::kFolderIndex_Root
	);

	path_to_sys_info_json /= kConfigFileNameSystemInfo;

	if (!p_filesystem->IsValidPath(path_to_sys_info_json))
	{
		KOTEK_ASSERT(
			p_manager->GetResourceManager(),
			"you must initialize resource manager"
		);
		KOTEK_ASSERT(
			p_manager->GetResourceManager()->Get_ResourceSaver(
			),
			"you must initialize general manager saver"
		);
		// so we didn't find our file, we need to generate that

		// it is our standard we can't change and alter name of
		// sys_info config! All who uses that must follow one
		// line otherwise it causes break changes and it is not
		// standartization way :)))))
		ktkFileText sys_info("sys_info");

		sys_info.Write(
			kSysInfoFieldName_InitializeCallback,
			kUserCallbackName_Initialize
		);
		sys_info.Write(
			kSysInfoFieldName_ShutdownCallback,
			kUserCallbackName_Shutdown
		);
		sys_info.Write(
			kSysInfoFieldName_UpdateCallback,
			kUserCallbackName_Update
		);
		sys_info.Write(
			kSysInfoFieldName_InitializeCallback_Render,
			kUserCallbackName_Initialize_Render
		);

		// TODO: make predefined on cmake side preprocessor !!!
		// Important
		sys_info.Write(
			kSysInfoFieldName_UserLibraryName,
			KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME
		);

		p_manager->GetResourceManager()
			->Get_ResourceSaver()
			->Save(
				path_to_sys_info_json,
				ktkResourceHandle(&sys_info, true)
			);
	}
	else
	{
	}

	auto path_to_user_data = p_filesystem->GetFolderByEnum(
		eFolderIndex::kFolderIndex_DataUser
	);

	ktk::cstring user_data_settings_name =
		KOTEK_USE_USER_DATA_CONFIG_NAME;
	user_data_settings_name += kFormatFile_Text;

	auto path_to_user_data_config =
		path_to_user_data / user_data_settings_name.c_str();
	if (!p_filesystem->IsValidPath(path_to_user_data_config))
	{
	}
	else
	{
	}
	*/

	return true;
}

bool ShutdownModule_Core_Engine_Config(ktkMainManager* p_manager
)
{
	ktkFrameworkConfig* p_instance =
		dynamic_cast<ktkFrameworkConfig*>(
			p_manager->Get_EngineConfig()
		);

	KOTEK_ASSERT(
		p_instance,
		"failed to cast to ktkFrameworkConfig. You must have a "
	    "valid "
		"instance of it, otherwise something is wrong"
	);

	p_instance->Shutdown();
	delete p_instance;

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
