#include "../include/kotek_window_console.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_PLATFORM_WINDOWS
struct ktkPrivateImpl
{
	HWND m_p_handle;
};
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif

ktkWindowConsole::ktkWindowConsole() :
	m_show{}, m_file_reader_id{kun_ktk uint32_t(-1)}, m_p_private_impl{}, m_p_view_buffer{}
{
}

ktkWindowConsole::~ktkWindowConsole()
{
	if (this->m_p_private_impl)
	{
		delete this->m_p_private_impl;
		this->m_p_private_impl = nullptr;
	}
}

void ktkWindowConsole::Initialize(ktkIWindow* p_window,
	ktkIResourceManager* p_manager,
	const ktk_filesystem_path& full_path_to_log_file)
{
	KOTEK_ASSERT(p_window, "must be valid");
	KOTEK_ASSERT(p_manager, "must be valid");
	KOTEK_ASSERT(!full_path_to_log_file.empty(), "can't be empty!");

	if (p_window)
	{
		this->m_p_private_impl = new ktkPrivateImpl();

		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

#ifdef KOTEK_USE_PLATFORM_WINDOWS
		p_impl->m_p_handle = static_cast<HWND>(p_window->GetHandle());
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif

		if (p_manager)
		{
			this->m_file_reader_id = p_manager->GenerateFileIDFor_Reading();

			kun_kotek kun_core ktkResourceReadingRequest request(
				this->m_file_reader_id,
				kun_kotek kun_core eResourceReadingType::kText,
				kun_kotek kun_core eResourceReadingPolicy::kSync,
				full_path_to_log_file);

			p_manager->Open(request);
		}
	}
}

void ktkWindowConsole::Shutdown(ktkIResourceManager* p_manager)
{
	KOTEK_ASSERT(p_manager, "must be valid manager");

	if (p_manager)
	{
		p_manager->Close(this->m_file_reader_id);
	}
}

void ktkWindowConsole::Update()
{
	if (this->m_p_private_impl)
	{
		if (this->m_show)
		{
		}
	}
}

void ktkWindowConsole::Render()
{
	if (this->m_p_private_impl)
	{
		if (this->m_show)
		{
		}
	}
}

void ktkWindowConsole::Show()
{
	this->m_show = true;
}

void ktkWindowConsole::Hide()
{
	this->m_show = false;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK