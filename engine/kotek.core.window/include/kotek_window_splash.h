#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

enum eEngineFeature;

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
	void Add_Text(float normalized_width, float normalized_height,
		const char* p_string) noexcept override;
	void Set_Progress(float progress, const char* p_string) noexcept override;
	void Update() noexcept override;

	bool Is_Initialized(void) const noexcept override;

private:
	void Create_Window(int width, int height);

	void Create_Windows(int width, int height);
	void Create_Linux();
	void Create_MacOS();
	void Create_Android();

	void Center_Window(int width, int height);

	void Get_DisplaySize(int* p_width, int* p_height);

private:
	bool m_is_show;
	int m_width;
	int m_height;
	float m_max_progress;
	float m_current_progress;
	void* m_p_private_impl;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK