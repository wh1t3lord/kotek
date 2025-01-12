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
	eInputControllerType controller = eInputControllerType::kControllerUnknown;
	int scancode;
	int key;
	int action;
	int mods;
};

struct ktkInputPlatformBackendArgs_WINAPI
{
	const eInputPlatformBackend backend =
		eInputPlatformBackend::kPlatformBackend_WINAPI;
	eInputControllerType controller = eInputControllerType::kControllerUnknown;
};

struct ktkInputPlatformBackendArgs_X11
{
	const eInputPlatformBackend backend =
		eInputPlatformBackend::kPlatformBackend_X11;
	eInputControllerType controller = eInputControllerType::kControllerUnknown;
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
		eInputControllerType controller_type, eInputAllKeys key) override;

	bool Is_KeyHolding(
		eInputControllerType controller_type, eInputAllKeys key, unsigned char frames=16) override;

	bool Is_KeyReleased(
		eInputControllerType controller_type, eInputAllKeys key) override;

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

	void Update(void) override;
	void Update_Controller(void* p_args) override;

	bool WriteKeyAsStringToBuffer_IfPressed(eInputControllerType controller, char* p_buffer,
		kun_ktk size_t length_of_buffer) override;

	bool WriteKeyAsStringToBuffer_IfHolding(eInputControllerType controller,
		char* p_buffer, kun_ktk size_t length_of_buffer) override;

	bool WriteKeyAsStringToBuffer_IfReleased(eInputControllerType controller,
		char* p_buffer, kun_ktk size_t length_of_buffer) override;

private:
	void Update_Controller(void* p_args, eInputPlatformBackend backend,
		eInputControllerType controller_type);
	void Update_Keyboard(void* p_args, eInputPlatformBackend backend);
	void Update_Mouse(void* p_args, eInputPlatformBackend backend);

	int Convert_AllKeysToFlags(eInputAllKeys field);

	/// @brief returns -1 means no category for controller, -2 means error
	/// @param field from eInputAllKeys enum
	/// @return -1 means no category for controller; -2 means error;
	int Convert_AllKeysToCategory(eInputAllKeys field);

	void Determine_Platform(void);

	void Update_ReleasedKeys(void);

private:
	bool m_need_to_updated_released_keys;

	unsigned char m_controller_mouse_key_pressed;
	unsigned char m_controller_mouse_key_released;

	// keyboard //
	unsigned char m_controller_keyboard_key_cursor_control_pressed;
	unsigned char m_controller_keyboard_key_cursor_control_released;

	unsigned char m_controller_keyboard_key_system_pressed;
	unsigned char m_controller_keyboard_key_system_released;

	unsigned char m_controller_keyboard_key_application_pressed;
	unsigned char m_controller_keyboard_key_application_released;

	unsigned char m_controller_keyboard_key_enter_pressed;
	unsigned char m_controller_keyboard_key_enter_released;

	int m_controller_keyboard_key_numpad_pressed;
	int m_controller_keyboard_key_numpad_released;
	int m_controller_keyboard_key_other_pressed;
	int m_controller_keyboard_key_other_released;
	int m_controller_keyboard_key_function_pressed;
	int m_controller_keyboard_key_function_released;
	int m_controller_keyboard_key_numbers_pressed;
	int m_controller_keyboard_key_numbers_released;
	int m_controller_keyboard_key_typewriter_pressed;
	int m_controller_keyboard_key_typewriter_released;

	eInputPlatformBackend m_current_platform;

	float m_controller_mouse_data
		[eInputControllerMouseData::kControllerMouseDataTotalAmountOfEnum];
	unsigned char m_controller_key_ticks[eInputAllKeys::kCA_KEY_END_ENUM];
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
