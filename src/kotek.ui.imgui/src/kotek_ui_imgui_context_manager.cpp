#include "../include/kotek_ui_imgui_context_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkImguiContextManager::ktkImguiContextManager(void) noexcept :
	m_contexts{}, m_thread_bindings{}, m_p_default_context{nullptr},
	m_mutex{}
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
	kun_ktk kun_mt lock_guard<kun_ktk kun_mt mutex> lock(m_mutex);

	for (const auto& entry : m_contexts)
	{
		if (entry.name == p_name)
		{
			thread_binding_t* p_binding =
				this->find_thread_binding_locked();

			if (p_binding)
			{
				// re-bind: this thread switches to another named context
				p_binding->m_p_context = entry.p_context;
				p_binding->m_p_name = entry.name.c_str();
				return true;
			}

			if (m_thread_bindings.full())
			{
				KOTEK_ASSERT(false,
					"ktkImguiContextManager: thread binding limit "
					"reached, raise "
					"KOTEK_DEF_IMGUI_CONTEXT_MANAGER_MAX_BINDINGS");
				return false;
			}

			m_thread_bindings.push_back(thread_binding_t{
				std::this_thread::get_id(), entry.p_context,
				entry.name.c_str()});

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
	kun_ktk kun_mt lock_guard<kun_ktk kun_mt mutex> lock(m_mutex);

	for (kun_ktk size_t i = 0; i < m_thread_bindings.size(); ++i)
	{
		if (m_thread_bindings[i].m_thread_id ==
			std::this_thread::get_id())
		{
			// order of the table is irrelevant: swap-with-back + pop
			m_thread_bindings[i] = m_thread_bindings.back();
			m_thread_bindings.pop_back();
			return;
		}
	}
}

ImGuiContext* ktkImguiContextManager::Get_ThreadContext(void)
{
	kun_ktk kun_mt lock_guard<kun_ktk kun_mt mutex> lock(m_mutex);

	return this->get_thread_context_locked();
}

void ktkImguiContextManager::Lock(void)
{
	m_mutex.lock();

	ImGuiContext* p_context = this->get_thread_context_locked();

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
	m_thread_bindings.clear();
	m_p_default_context = nullptr;
}

ktkImguiContextManager::thread_binding_t*
ktkImguiContextManager::find_thread_binding_locked(void) noexcept
{
	thread_binding_t* p_result = nullptr;

	for (auto& binding : m_thread_bindings)
	{
		if (binding.m_thread_id == std::this_thread::get_id())
		{
			p_result = &binding;
			break;
		}
	}

	return p_result;
}

ImGuiContext*
ktkImguiContextManager::get_thread_context_locked(void) noexcept
{
	thread_binding_t* p_binding = this->find_thread_binding_locked();

	if (p_binding)
		return p_binding->m_p_context;

	return m_p_default_context;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
