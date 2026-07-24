#include "../include/kotek_ui_imgui_context_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

namespace
{
	// per-thread binding of a named context (model 2); nullptr = unbound,
	// meaning "use the default context" (model 1, single UI thread)
	thread_local ImGuiContext* _tls_bound_context = nullptr;
	thread_local const char* _tls_bound_name = nullptr;
}

ktkImguiContextManager::ktkImguiContextManager(void) noexcept :
	m_contexts{}, m_p_default_context{nullptr}, m_mutex{}
{
}

ktkImguiContextManager::~ktkImguiContextManager(void)
{
	KOTEK_ASSERT(m_contexts.empty(),
		"ktkImguiContextManager destroyed without Shutdown(), contexts leak");
}

void ktkImguiContextManager::AdoptDefaultContext(ImGuiContext* p_context)
{
	m_p_default_context = p_context;
}

bool ktkImguiContextManager::CreateContextForThread(const char* p_name)
{
	if (p_name == nullptr || p_name[0] == '\0')
		return false;

	for (const auto& entry : m_contexts)
	{
		if (entry.name == p_name)
			return false;
	}

	if (m_contexts.full())
	{
		KOTEK_ASSERT(false, "ktkImguiContextManager: context limit reached");
		return false;
	}

	ImGuiContext* p_context = ImGui::CreateContext();

	if (p_context == nullptr)
		return false;

	m_contexts.push_back(context_entry_t{p_name, p_context});

	return true;
}

bool ktkImguiContextManager::BindThreadContext(const char* p_name)
{
	for (const auto& entry : m_contexts)
	{
		if (entry.name == p_name)
		{
			_tls_bound_context = entry.p_context;
			_tls_bound_name = entry.name.c_str();
			return true;
		}
	}

	KOTEK_ASSERT(false,
		"ktkImguiContextManager::BindThreadContext with unknown name, call "
		"CreateContextForThread first");

	return false;
}

void ktkImguiContextManager::UnbindThreadContext(void)
{
	_tls_bound_context = nullptr;
	_tls_bound_name = nullptr;
}

ImGuiContext* ktkImguiContextManager::Get_ThreadContext(void)
{
	if (_tls_bound_context)
		return _tls_bound_context;

	return m_p_default_context;
}

void ktkImguiContextManager::Lock(void)
{
	m_mutex.lock();

	ImGuiContext* p_context = Get_ThreadContext();

	KOTEK_ASSERT(p_context != nullptr,
		"ktkImguiContextManager::Lock with no context available: bind one or "
		"adopt a default first");

	ImGui::SetCurrentContext(p_context);
}

void ktkImguiContextManager::Unlock(void)
{
	m_mutex.unlock();
}

void ktkImguiContextManager::Shutdown(void)
{
	for (auto& entry : m_contexts)
	{
		ImGui::DestroyContext(entry.p_context);
		entry.p_context = nullptr;
	}

	m_contexts.clear();
	m_p_default_context = nullptr;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
