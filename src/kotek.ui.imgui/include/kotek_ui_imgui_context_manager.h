#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_std_alias_static_vector.h>
#include <kotek.core.containers.string/include/kotek_std_alias_static_string.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

#include "imgui.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

/// @brief \~english see ktkIImguiContextManager (kotek.core.api) for the two
/// supported multithreading models. Concrete implementation owned by
/// ktkImguiWrapper; UI code should only ever touch the interface.
class ktkImguiContextManager : public kun_core ktkIImguiContextManager
{
public:
	ktkImguiContextManager(void) noexcept;
	virtual ~ktkImguiContextManager(void) override;

	bool CreateContextForThread(const char* p_name) override;
	bool BindThreadContext(const char* p_name) override;
	void UnbindThreadContext(void) override;
	ImGuiContext* Get_ThreadContext(void) override;
	void AdoptDefaultContext(ImGuiContext* p_context) override;
	void Lock(void) override;
	void Unlock(void) override;
	void Shutdown(void) override;

private:
	static constexpr kun_ktk size_t _kMaxContexts = 16;
	static constexpr kun_ktk size_t _kMaxNameLength = 64;

	struct context_entry_t
	{
		kun_ktk static_cstring<_kMaxNameLength> name;
		ImGuiContext* p_context;
	};

	kun_kotek static_vector_t<context_entry_t, _kMaxContexts> m_contexts;
	ImGuiContext* m_p_default_context;
	kun_ktk kun_mt mutex m_mutex;
};

/// @brief \~english RAII guard for model 2 (context-per-thread +
/// serialization): locks imgui access and SetCurrentContext to the calling
/// thread's bound context on construction, unlocks on destruction. Bracket
/// every block of ImGui calls from a non-UI thread with this guard.
class ktkImguiLockGuard
{
public:
	explicit ktkImguiLockGuard(
		kun_core ktkIImguiContextManager* p_manager) noexcept :
		m_p_manager(p_manager)
	{
		if (m_p_manager)
			m_p_manager->Lock();
	}

	~ktkImguiLockGuard(void)
	{
		if (m_p_manager)
			m_p_manager->Unlock();
	}

	ktkImguiLockGuard(const ktkImguiLockGuard&) = delete;
	ktkImguiLockGuard& operator=(const ktkImguiLockGuard&) = delete;

private:
	kun_core ktkIImguiContextManager* m_p_manager;
};

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
