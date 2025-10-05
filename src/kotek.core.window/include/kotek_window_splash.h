#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

enum class eEngineFeature : kun_ktk uint32_t;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkWindowSplash : public ktkIWindowSplash
{
public:
	ktkWindowSplash();
	~ktkWindowSplash();

	int Get_Width(void) const noexcept override;
	int Get_Height(void) const noexcept override;

	void Show(void) noexcept override;
	void Hide(void) noexcept override;

	void Create(int width, int height, unsigned char* p_raw_image_data,
		float* p_max_progress) noexcept override;
	void Set_Text(
		const char* p_string, int* p_color_rgb_array=nullptr) noexcept override;
	void Set_Progress(float progress) noexcept override;
	void Set_Progress(void) noexcept override;
	void Update() noexcept override;

	bool Is_Initialized(void) const noexcept override;

	const int* Get_TextColor(void) const noexcept;
	float Get_TextOffsetWidth(void) const noexcept;
	float Get_TextOffsetHeight(void) const noexcept;
	const char* Get_Label(void) const noexcept;
	bool Is_Show() const noexcept;

	void* Get_Impl() const noexcept;

private:
	void Create_Window(int width, int height);

	void Create_Windows(int width, int height);
	void Create_Linux();
	void Create_MacOS();
	void Create_Android();

	void Center_Window(int width, int height, int& x, int& y);

	void Get_DisplaySize(int* p_width, int* p_height);

	void Failed();

private:
	bool m_is_show;
	int m_width;
	int m_height;
	float m_max_progress;
	float m_current_progress;
	void* m_p_private_impl;
	float m_text_width;
	float m_text_height;
	int m_p_current_color_text[3];
	char m_p_label[128];
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK