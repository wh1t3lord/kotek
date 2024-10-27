#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkIWindowSplash
{
public:
	virtual ~ktkIWindowSplash(void) {}

	virtual int Get_Width(void) const noexcept = 0;
	virtual int Get_Height(void) const noexcept = 0;

	virtual void Show(void) noexcept = 0;
	virtual void Hide(void) noexcept = 0;

	virtual void Create(int width, int height, unsigned char* p_raw_image_data,
		float* p_max_progress) noexcept = 0;

	virtual void Set_Text(
		const char* p_string, int* p_color_rgb_array = nullptr) noexcept = 0;

	virtual void Set_Progress(float progress) noexcept = 0;
	virtual void Set_Progress(void) noexcept = 0;

	virtual bool Is_Initialized(void) const noexcept = 0;

	/// @brief implements message loop for your window, supposed to be called in
	/// separated thread because of purpose of window (splash - preview before
	/// loading the main window)
	virtual void Update() noexcept = 0;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK