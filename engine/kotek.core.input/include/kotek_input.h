#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.constants.window/include/kotek_core_constants_window.h>
#include <kotek.core.enum.core\include\kotek_core_enum_core.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

struct ktkInputPlatformBackendArgs_GLFW3
{
	const eInputPlatformBackend backend =
		eInputPlatformBackend::kPlatformBackend_GLFW3; 
	int scancode;
	int key;
	int action;
	int mods;
};

struct ktkInputPlatformBackendArgs_WINAPI
{
	const eInputPlatformBackend backend =
		eInputPlatformBackend::kPlatformBackend_WINAPI;
};

struct ktkInputPlatformBackendArgs_X11
{
	const eInputPlatformBackend backend =
		eInputPlatformBackend::kPlatformBackend_X11;
};

class ktkInput : public ktkIInput
{
public:
	ktkInput(void);
	~ktkInput(void);

	void Initialize(void) override;
	void Shutdown(void) override;

	 bool Set_ControllerData(eInputControllerType controller_type,
		unsigned char data_field_index, float data) override;
	 float Get_ControllerData(eInputControllerType controller_type,
		unsigned char data_field_index) override;

	 bool Is_KeyPressed(
		eInputControllerType controller_type, int keys) override;
	 bool Is_KeyPressed(eInputControllerType controller_type,
		 unsigned char category, int keys) override;

	 const char* Get_TextInformationAboutController(
		eInputControllerType controller_type) override;

	/// @brief fills array with supported controllers
	/// @param p_array somewhere allocated unsigned char array with size =
	/// unsigned char[eInputControllerType::kControllerTotalAmountOfEnum]
	/// @param length_of_array length that user passes for validation if size
	/// was incorrect you will get an assertion
	/// @return if system has implementation of this method will return true and
	/// if was all okay generally otherwise false, in order to check the
	/// supported controller use eInputControllerType fields as look-up indexer
	/// and if field of your passed array was set to unsigned char(1) it means
	/// that controller is supported by engine
	 bool Get_SupportedControllers(
		unsigned char* p_array, unsigned char size_of_array) override;

	 const char* Get_PlatformBackendName(void) const override;

	 void Update(void* p_args) override;

private:
	unsigned char m_controller_mouse_key_states;
	
	unsigned char m_controller_keyboard_key_cursor_control_states;
	unsigned char m_controller_keyboard_key_system_states;
	unsigned char m_controller_keyboard_key_application_states;
	unsigned char m_controller_keyboard_key_enter_states;
	int m_controller_keyboard_key_numpad_states;
	int m_controller_keyboard_key_other_states;
	int m_controller_keyboard_key_function_states;
	int m_controller_keyboard_key_numbers_states;
	int m_controller_keyboard_key_typewriter;

	eInputPlatformBackend m_current_platform;

	float m_controller_mouse_data
		[eInputControllerMouseData::kControllerMouseDataTotalAmountOfEnum];
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
