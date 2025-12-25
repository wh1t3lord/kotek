#include "../include/kotek_core_containers_dll.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

#ifdef KOTEK_USE_STD_LIBRARY
	#include <kotek.core.os/include/kotek_core_os.h>
	#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

namespace dll
{
	shared_library::shared_library() : p_lib{} {}

	shared_library::shared_library(const char* p_path_to_file) :
		p_lib{}
	{
	#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (p_path_to_file && strlen(p_path_to_file))
		{
			p_lib = reinterpret_cast<void*>(
				LoadLibraryA(p_path_to_file)
			);

			KOTEK_ASSERT(
				p_lib,
				"failed to load library: [{}]",
				p_path_to_file
			);
		}
	#elif defined(KOTEK_USE_PLATFORM_LINUX)
		#error todo: provide implementation
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
		#error todo: provide implementation
	#else
		#error unknown platform (did you forget to add?)
	#endif
	}

	shared_library::~shared_library()
	{
	#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (p_lib)
		{
			auto status =
				FreeLibrary(reinterpret_cast<HMODULE>(p_lib));

			KOTEK_ASSERT(
				status > 0,
				"failed FreeLibrary calling: GetLastError={}",
				GetLastError()
			);

			p_lib = nullptr;
		}
	#elif defined(KOTEK_USE_PLATFORM_LINUX)
		#error todo: provide implementation
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
		#error todo: provide implementation
	#else
		#error unknown platform (did you forget to add?)
	#endif
	}

	bool shared_library::load(const char* p_path)
	{
		bool result = false;

		if (p_lib)
		{
			bool unload_status = this->unload();

			KOTEK_ASSERT(unload_status, "failed to unload");
		}

		if (!p_path)
			return result;

		if (strlen(p_path) == 0)
			return result;

		p_lib = LoadLibraryA(p_path);

		KOTEK_ASSERT(
			p_lib, "failed to load library: [{}]", p_path
		);

		result = !!(p_lib);

		return result;
	}

	bool shared_library::unload()
	{
		bool result = false;

		auto status =
			FreeLibrary(reinterpret_cast<HMODULE>(p_lib));

		KOTEK_ASSERT(
			status > 0,
			"failed FreeLibrary calling: GetLastError={}",
			GetLastError()
		);

		result = status > 0;

		p_lib = nullptr;

		return result;
	}

	void* shared_library::get(const char* p_func_name)
	{
		void* p_result = nullptr;

		if (!p_func_name)
			return p_result;

		if (strlen(p_func_name) == 0)
			return p_result;

		if (!p_lib)
			return p_result;

		if (p_lib)
		{
	#ifdef KOTEK_USE_PLATFORM_WINDOWS

			p_result = GetProcAddress(
				reinterpret_cast<HMODULE>(p_lib), p_func_name
			);

			KOTEK_ASSERT(
				p_result,
				"failed to obtain function from dll: {}",
				p_func_name
			);

	#elif defined(KOTEK_USE_PLATFORM_LINUX)
		#error todo: provide implementation
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
		#error todo: provide implementation
	#else
		#error unknown platform (did you forget to add?)
	#endif
		}

		return p_result;
	}
} // namespace dll
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_DLL(
	ktkMainManager* p_manager
)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text(
			"[core]: init [containers][dll]"
		);
		p_manager->Get_Splash()->Set_Progress();
	}

	return true;
}

bool SerializeModule_Core_Containers_DLL(
	ktkMainManager* p_manager
)
{
	return true;
}

bool DeserializeModule_Core_Containers_DLL(
	ktkMainManager* p_manager
)
{
	return true;
}

bool ShutdownModule_Core_Containers_DLL(
	ktkMainManager* p_manager
)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK