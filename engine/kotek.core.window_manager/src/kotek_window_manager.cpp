#include "../include/kotek_window_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkWindowManager::ktkWindowManager(void) : m_p_active_window{} {}

ktkWindowManager::~ktkWindowManager(void) {}

void ktkWindowManager::Initialize(ktkIWindow* p_active_window)
{
	this->m_p_active_window = p_active_window;
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
	this->m_p_active_window->PollEvents();
}

void* ktkWindowManager::ActiveWindow_GetHandle(void) const noexcept
{
	return this->m_p_active_window->GetHandle();
}

int ktkWindowManager::ActiveWindow_GetHeight(void) const noexcept
{
	return this->m_p_active_window->GetHeight();
}

int ktkWindowManager::ActiveWindow_GetWidth(void) const noexcept
{
	return this->m_p_active_window->GetWidth();
}

bool ktkWindowManager::ActiveWindow_ShouldToClose(void)
{
	return this->m_p_active_window->Is_NeedToClose();
}

void ktkWindowManager::ActiveWindow_MakeContextCurrent(void) noexcept
{
	this->m_p_active_window->MakeContextCurrent();
}

ktkIWindow* ktkWindowManager::Get_ActiveWindow(void) const noexcept
{
	return this->m_p_active_window;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK