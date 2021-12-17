#include "kotek_dynamic_library.h"

namespace Kotek
{
	namespace Core
	{
		ktkDynamicLibrary::ktkDynamicLibrary(const ktk::string& library_name) :
			m_library_name(library_name), m_p_library_handle(nullptr)
		{
		}

		ktkDynamicLibrary::ktkDynamicLibrary(void) : m_p_library_handle(nullptr)
		{
		}

		ktkDynamicLibrary::~ktkDynamicLibrary(void) {}

		void ktkDynamicLibrary::SetLibraryName(
			const ktk::string& library_name) noexcept
		{
			this->m_library_name = library_name;
		}

		bool ktkDynamicLibrary::Load(void) noexcept
		{
			KOTEK_ASSERT(this->m_library_name.empty() == false,
				"you must initialize library name in your class! Can't load "
				"library!");

#ifdef KOTEK_PLATFORM_WINDOWS

			this->m_p_library_handle =
				LoadLibrary(this->m_library_name.get_as_is().c_str());
			auto status = GetLastError();

			KOTEK_ASSERT(this->m_p_library_handle,
				"can't load library: {}, GetLastError: {} (can't find "
			    "dependencies for your loading library, so e.g. you don't "
			    "place wxWidgets .dll files or something else)",
				this->m_library_name.get_as_is(), status);
#elif KOTEK_PLATFORM_LINUX
#endif

			return true;
		}

		void ktkDynamicLibrary::UnLoad(void) noexcept
		{
#ifdef KOTEK_PLATFORM_WINDOWS
			if (this->m_p_library_handle)
			{
				auto status = FreeLibrary(this->m_p_library_handle);

				KOTEK_ASSERT(status, "failed to FreeLibrary, GetLastError={}",
					GetLastError());

				this->m_p_library_handle = nullptr;
			}
#elif KOTEK_PLATFORM_LINUX

#endif

			KOTEK_MESSAGE(
				"Library is unloaded: {}", this->m_library_name.get_as_is());
		}
		bool ktkDynamicLibrary::IsLoaded(void) const noexcept
		{
			return !!this->m_p_library_handle;
		}

		FARPROC ktkDynamicLibrary::GetUserCallback(
			const ktk::string& function_name) noexcept
		{
			KOTEK_ASSERT(function_name.empty() == false,
				"you can't pass an empty function name");

			auto result = GetProcAddress(this->m_p_library_handle,
				function_name.get_as_legacy().c_str());

			if (result == nullptr)
			{
				KOTEK_MESSAGE("can't obtain function: {}, GetLastError: {}",
					function_name.get_as_is(), GetLastError());
			}

			return result;
		}
	} // namespace Core
} // namespace Kotek