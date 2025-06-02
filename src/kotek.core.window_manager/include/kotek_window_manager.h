#pragma once

#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/*
* TODO: provide complex implementation when is needed. Mostly splash + main is enough for general purpose
*/
class ktkWindowManager : public ktkIWindowManager
{
public:
	ktkWindowManager(void);
	~ktkWindowManager(void);

	void Initialize(void) override;
	void Shutdown(void) override;

	void ActiveWindow_PollEvents(void) override;
	void* ActiveWindow_GetHandle(void) const noexcept override;
	int ActiveWindow_GetHeight(void) const noexcept override;
	int ActiveWindow_GetWidth(void) const noexcept override;
	bool ActiveWindow_ShouldToClose(void) override;

	void ActiveWindow_MakeContextCurrent(void) noexcept override;
	ktkIWindow* Get_ActiveWindow(void) const noexcept override;

	void Set_ActiveWindow(ktkIWindow* p_window) noexcept override;

private:
	ktkIWindow* m_p_active_window;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK