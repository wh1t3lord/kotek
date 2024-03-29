#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

class ktkVideoPlayerAVIF : public Core::ktkIVideoPlayerManager
{
public:
	ktkVideoPlayerAVIF();
	~ktkVideoPlayerAVIF();

	void Initialize(void) noexcept override;
	void Shutdown(void) noexcept override;
	void Render(void) noexcept override;

private:

};

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
