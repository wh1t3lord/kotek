#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.api/include/kotek_api.h>

namespace Rml
{
	class RenderInterface;
	class SystemInterface;
	class Context;
} // namespace Rml

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

class ktkGameUI_RMLUI : public Core::ktkIGameUIManager
{
public:
	ktkGameUI_RMLUI(void);
	~ktkGameUI_RMLUI(void);

	void Initialize(Core::ktkIEngineConfig* p_config,
		void* p_os_window_handle, int width, int height) noexcept override;
	void Shutdown(void) noexcept override;

	void Render(void) noexcept override;
	void Update(void) noexcept override;
	bool LoadDocument(const char* p_path_to_file) override;
};

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK