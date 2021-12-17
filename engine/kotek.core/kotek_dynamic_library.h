#pragma once

#include "kotek_std_os.h"
#include "kotek_std_string.h"

namespace Kotek
{
	namespace Core
	{
		class ktkDynamicLibrary
		{
		public:
			ktkDynamicLibrary(const ktk::string& library_name);
			ktkDynamicLibrary(void);
			~ktkDynamicLibrary(void);

			void SetLibraryName(const ktk::string& library_name) noexcept;
			bool Load(void) noexcept;
			void UnLoad(void) noexcept;
			bool IsLoaded(void) const noexcept;

			#ifdef KOTEK_PLATFORM_WINDOWS
			FARPROC GetUserCallback(const ktk::string& function_name) noexcept;
			#elif KOTEK_PLATFORM_LINUX
			#endif
		private:
			ktk::string m_library_name;
#ifdef KOTEK_PLATFORM_WINDOWS
			HMODULE m_p_library_handle;
#elif KOTEK_PLATFORM_LINUX
#endif
		};
	} // namespace Core
} // namespace Kotek