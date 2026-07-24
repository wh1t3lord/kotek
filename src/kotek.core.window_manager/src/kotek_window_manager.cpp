#include "../include/kotek_window_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkWindowManager::ktkWindowManager(void) :
	m_p_active_window{}
{
}

ktkWindowManager::~ktkWindowManager(void) {}

void ktkWindowManager::Initialize()
{
}

void ktkWindowManager::Shutdown(void)
{
	if (this->m_p_active_window)
	{
		this->m_p_active_window->Shutdown();
		delete this->m_p_active_window;
		this->m_p_active_window = nullptr;
	}
}

void ktkWindowManager::ActiveWindow_PollEvents(void)
{
	if (this->m_p_active_window)
		this->m_p_active_window->PollEvents();
}

void* ktkWindowManager::ActiveWindow_GetHandle(void) const noexcept
{
	if (this->m_p_active_window)
		return this->m_p_active_window->GetHandle();

	return nullptr;
}

int ktkWindowManager::ActiveWindow_GetHeight(void) const noexcept
{
	if (this->m_p_active_window)
		return this->m_p_active_window->GetHeight();

	return -1;
}

int ktkWindowManager::ActiveWindow_GetWidth(void) const noexcept
{
	if (this->m_p_active_window)
		return this->m_p_active_window->GetWidth();

	return -1;
}

bool ktkWindowManager::ActiveWindow_ShouldToClose(void)
{
	if (this->m_p_active_window)
		return this->m_p_active_window->Is_NeedToClose();

	return true;
}

void ktkWindowManager::ActiveWindow_MakeContextCurrent(void) noexcept
{
	if (this->m_p_active_window)
		this->m_p_active_window->MakeContextCurrent();
}

ktkIWindow* ktkWindowManager::Get_ActiveWindow(void) const noexcept
{
	return this->m_p_active_window;
}

void ktkWindowManager::Set_ActiveWindow(ktkIWindow* p_window) noexcept 
{
	if (!this->m_p_active_window)
		this->m_p_active_window = p_window;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK