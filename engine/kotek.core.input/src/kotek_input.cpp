#include "../include/kotek_input.h"

#include <kotek.core.defines_dependent.assert\include\kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkInput::ktkInput(void) :
	m_controller_mouse_key_states{},
	m_controller_keyboard_key_cursor_control_states{},
	m_controller_keyboard_key_system_states{},
	m_controller_keyboard_key_application_states{},
	m_controller_keyboard_key_enter_states{},
	m_controller_keyboard_key_numpad_states{},
	m_controller_keyboard_key_other_states{},
	m_controller_keyboard_key_function_states{},
	m_controller_keyboard_key_numbers_states{},
	m_controller_keyboard_key_typewriter{},
	m_current_platform{eInputPlatformBackend::kPlatformBackend_Unknown},
	m_controller_mouse_data{}
{
}

ktkInput::~ktkInput(void) {}

void ktkInput::Initialize(void)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	this->m_current_platform = eInputPlatformBackend::kPlatformBackend_WINAPI;
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#elif defined(KOTEK_USE_PLATFORM_MACOS)
	#error not implemented
#endif
}

void ktkInput::Shutdown(void) {}

bool ktkInput::Set_ControllerData(eInputControllerType controller_type,
	unsigned char data_field_index, float data)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return false;

	switch (controller_type)
	{
	case eInputControllerType::kControllerKeyboard:
	{
		KOTEK_ASSERT(false, "not implemented");

		break;
	}
	case eInputControllerType::kControllerMouse:
	{
		KOTEK_ASSERT(data_field_index <=
				static_cast<unsigned char>(
					sizeof(this->m_controller_mouse_data) /
						sizeof(this->m_controller_mouse_data[0]) -
					1),
			"overflow!");

		eInputControllerMouseData casted_index =
			static_cast<eInputControllerMouseData>(data_field_index);

		this->m_controller_mouse_data[casted_index] = data;

		break;
	}
	case eInputControllerType::kControllerGamepad:
	{
		KOTEK_ASSERT(false, "not implemented");

		break;
	}
	case eInputControllerType::kControllerJoystick:
	{
		KOTEK_ASSERT(false, "not implemented");

		break;
	}
	default:
	{
		KOTEK_ASSERT(false,
			"unhandled thing, you forgot to register a new type of controller");
	}
	}

	return true;
}

float ktkInput::Get_ControllerData(
	eInputControllerType controller_type, unsigned char data_field_index)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return 0.0f;

	switch (controller_type)
	{
	case eInputControllerType::kControllerKeyboard:
	{
		KOTEK_ASSERT(false, "not implemented");

		return 0.0f;
	}
	case eInputControllerType::kControllerMouse:
	{
		KOTEK_ASSERT(data_field_index <=
				static_cast<unsigned char>(
					sizeof(this->m_controller_mouse_data) /
						sizeof(this->m_controller_mouse_data[0]) -
					1),
			"overflow!");

		eInputControllerMouseData casted_index =
			static_cast<eInputControllerMouseData>(data_field_index);

		return this->m_controller_mouse_data[casted_index];
	}
	case eInputControllerType::kControllerGamepad:
	{
		KOTEK_ASSERT(false, "not implemented");

		return 0.0f;
	}
	case eInputControllerType::kControllerJoystick:
	{
		KOTEK_ASSERT(false, "not implemented");

		return 0.0f;
	}
	default:
	{
		KOTEK_ASSERT(false,
			"unhandled thing, you forgot to register a new type of controller");
		return 0.0f;
	}
	}
}

bool ktkInput::Is_KeyPressed(eInputControllerType controller_type, int keys)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return false;

	switch (controller_type)
	{
	case eInputControllerType::kControllerKeyboard:
	{
		return this->m_controller_keyboard_key_typewriter & keys;
	}
	case eInputControllerType::kControllerMouse:
	{
		return (this->m_controller_mouse_key_states & keys);
	}
	case eInputControllerType::kControllerGamepad:
	{
		KOTEK_ASSERT(false, "not implemented");
		return false;
	}
	case eInputControllerType::kControllerJoystick:
	{
		KOTEK_ASSERT(false, "not implemented");
		return false;
	}
	default:
	{
		KOTEK_ASSERT(false, "unhandled enum, you forgot to register");
		return false;
	}
	}
}

bool ktkInput::Is_KeyPressed(
	eInputControllerType controller_type, unsigned char category, int keys)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return false;

	switch (controller_type)
	{
	case eInputControllerType::kControllerKeyboard:
	{
		eInputControllerKeyboardCategory casted_category =
			static_cast<eInputControllerKeyboardCategory>(category);

		switch (casted_category)
		{
		case eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter:
		{
			return (this->m_controller_keyboard_key_typewriter & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState:
		{
			return (this->m_controller_keyboard_key_function_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysOtherState:
		{
			return (this->m_controller_keyboard_key_other_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysNumbers:
		{
			return (this->m_controller_keyboard_key_numbers_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysApplication:
		{
			KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
				"can't be you passed wrong enum flags");
			return (this->m_controller_keyboard_key_application_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysSystem:
		{
			KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
				"can't be you passed wrong enum flags");

			return (this->m_controller_keyboard_key_system_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysEnter:
		{
			KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
				"can't be you passed wrong enum flags");
			return (this->m_controller_keyboard_key_enter_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysNumpad:
		{
			return (this->m_controller_keyboard_key_numbers_states & keys);
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys:
		{
			KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
				"can't be you passed wrong enum flags");
			return (
				this->m_controller_keyboard_key_cursor_control_states & keys);
		}
		default:
		{
			KOTEK_ASSERT(
				false, "unhandled code, you forgot to register category!");
			return false;
		}
		}
	}
	case eInputControllerType::kControllerMouse:
	{
		KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
			"can't be, you passed wrong enum flags");
		return (this->m_controller_mouse_key_states & keys);
	}
	case eInputControllerType::kControllerGamepad:
	{
		KOTEK_ASSERT(false, "not implemented");
		return false;
	}
	case eInputControllerType::kControllerJoystick:
	{
		KOTEK_ASSERT(false, "not implemented");
		return false;
	}
	default:
	{
		KOTEK_ASSERT(false, "unhanleded enum, you forgot to register");
		return false;
	}
	}
}

const char* ktkInput::Get_TextInformationAboutController(
	eInputControllerType controller_type)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return "NOT_INITIALIZED";

	KOTEK_ASSERT(false, "not implemented");
	return nullptr;
}

bool ktkInput::Get_SupportedControllers(
	unsigned char* p_array, unsigned char length_of_array)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return false;

	unsigned char
		p_controllers[eInputControllerType::kControllerTotalAmountOfEnum];
	std::memset(p_controllers, 0, sizeof(p_controllers));

#ifdef KOTEK_USE_PLATFORM_WINDOWS

	UINT nNumOfDevices = -1;

	UINT nResult =
		GetRawInputDeviceList(NULL, &nNumOfDevices, sizeof(RAWINPUTDEVICELIST));

	if (nResult == 0)
	{
		RAWINPUTDEVICELIST pDevices[64];

		KOTEK_ASSERT(nNumOfDevices <= (sizeof(pDevices) / sizeof(pDevices[0])),
			"overflow, you should shrink array");

		nResult = GetRawInputDeviceList(
			pDevices, &nNumOfDevices, sizeof(RAWINPUTDEVICELIST));

		if (nResult != (UINT)-1)
		{
			for (unsigned char i = 0;
				 i < static_cast<unsigned char>(nNumOfDevices); ++i)
			{
				if (pDevices[i].dwType == RIM_TYPEKEYBOARD)
				{
					p_controllers[eInputControllerType::kControllerKeyboard] =
						unsigned char(1);
				}
				else if (pDevices[i].dwType == RIM_TYPEMOUSE)
				{
					p_controllers[eInputControllerType::kControllerMouse] =
						unsigned char(1);
				}
			}
		}
	}

#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#elif defined(KOTEK_USE_PLATFORM_MACOS)
	#error not implemented
#else
	#error unknown platform, report to developers
#endif

	std::memcpy(p_array, p_controllers, length_of_array);

	return false;
}

const char* ktkInput::Get_PlatformBackendName(void) const
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return "NOT_INITIALIZED";

	return helper::Translate_InputPlatformBackend(this->m_current_platform);
}

/*
 *
 *
 * GLFW3 BACKEND
 *
 *
 */
int p_glfw3_keyboard_keys_to_input[] = {-1, // 0
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, // 31
	eInputKeyboardKeysOther::kKEY_SPACE, -1, -1, -1, -1, -1, -1,
	eInputKeyboardKeysOther::kKEY_APOSTROPHE, -1, -1, -1, -1,
	eInputKeyboardKeysOther::kKEY_COMMA, eInputKeyboardKeysNumbers::kKEY_MINUS,
	eInputKeyboardKeysOther::kKEY_PERIOD, eInputKeyboardKeysOther::kKEY_SLASH,
	eInputKeyboardKeysNumbers::kKEY_0, eInputKeyboardKeysNumbers::kKEY_1,
	eInputKeyboardKeysNumbers::kKEY_2, eInputKeyboardKeysNumbers::kKEY_3,
	eInputKeyboardKeysNumbers::kKEY_4, eInputKeyboardKeysNumbers::kKEY_5,
	eInputKeyboardKeysNumbers::kKEY_6, eInputKeyboardKeysNumbers::kKEY_7,
	eInputKeyboardKeysNumbers::kKEY_8, eInputKeyboardKeysNumbers::kKEY_9, -1,
	eInputKeyboardKeysOther::KKEY_SEMICOLON, -1,
	eInputKeyboardKeysOther::kKEY_EQUAL, -1, -1, -1, eInputKeyboardKeys::kKEY_A,
	eInputKeyboardKeys::kKEY_B, eInputKeyboardKeys::kKEY_C,
	eInputKeyboardKeys::kKEY_D, eInputKeyboardKeys::kKEY_E,
	eInputKeyboardKeys::kKEY_F, eInputKeyboardKeys::kKEY_G,
	eInputKeyboardKeys::kKEY_H, eInputKeyboardKeys::kKEY_I,
	eInputKeyboardKeys::kKEY_J, eInputKeyboardKeys::kKEY_K,
	eInputKeyboardKeys::kKEY_L, eInputKeyboardKeys::kKEY_M,
	eInputKeyboardKeys::kKEY_N, eInputKeyboardKeys::kKEY_O,
	eInputKeyboardKeys::kKEY_P, eInputKeyboardKeys::kKEY_Q,
	eInputKeyboardKeys::kKEY_R, eInputKeyboardKeys::kKEY_S,
	eInputKeyboardKeys::kKEY_T, eInputKeyboardKeys::kKEY_U,
	eInputKeyboardKeys::kKEY_V, eInputKeyboardKeys::kKEY_W,
	eInputKeyboardKeys::kKEY_X, eInputKeyboardKeys::kKEY_Y,
	eInputKeyboardKeys::kKEY_Z, eInputKeyboardKeysOther::kKEY_LEFT_BRACKET,
	eInputKeyboardKeysOther::kKEY_BACKSLASH,
	eInputKeyboardKeysOther::kKEY_RIGHT_BRACKET, -1, -1,
	eInputKeyboardKeysOther::kKEY_GRAVE_ACCENT, // 96
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, eInputKeyboardKeysOther::kKEY_ESCAPE,
	eInputKeyboardKeysEnter::kKEY_ENTER, eInputKeyboardKeysOther::kKEY_TAB,
	eInputKeyboardKeysOther::kKEY_BACKSPACE,
	eInputKeyboardKeysOther::kKEY_INSERT, eInputKeyboardKeysOther::kKEY_DEL,
	eInputKeyboardCursorControlKeys::kKEY_ARROW_RIGHT,
	eInputKeyboardCursorControlKeys::kKEY_ARROW_LEFT,
	eInputKeyboardCursorControlKeys::kKEY_ARROW_DOWN,
	eInputKeyboardCursorControlKeys::kKEY_ARROW_UP,
	eInputKeyboardKeysOther::kKEY_PAGEUP,
	eInputKeyboardKeysOther::kKEY_PAGEDOWN, eInputKeyboardKeysOther::kKEY_HOME,
	eInputKeyboardKeysOther::kKEY_END, // 269
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	eInputKeyboardKeys::kKEY_CAPS_LOCK, // 280
	eInputKeyboardKeys::kKEY_SCROLL_LOCK,
	eInputKeyboardKeysNumpad::kKEY_NUMPAD_NUMLOCK,
	eInputKeyboardKeysOther::kKEY_PRTSC, eInputKeyboardKeysOther::kKEY_PAUSE,
	-1, -1, -1, -1, -1, eInputKeyboardKeysFunctionKeys::kKEY_F1,
	eInputKeyboardKeysFunctionKeys::kKEY_F2,
	eInputKeyboardKeysFunctionKeys::kKEY_F3,
	eInputKeyboardKeysFunctionKeys::kKEY_F4,
	eInputKeyboardKeysFunctionKeys::kKEY_F5,
	eInputKeyboardKeysFunctionKeys::kKEY_F6,
	eInputKeyboardKeysFunctionKeys::kKEY_F7,
	eInputKeyboardKeysFunctionKeys::kKEY_F8,
	eInputKeyboardKeysFunctionKeys::kKEY_F9,
	eInputKeyboardKeysFunctionKeys::kKEY_F10,
	eInputKeyboardKeysFunctionKeys::kKEY_F11,
	eInputKeyboardKeysFunctionKeys::kKEY_F12,
	-1, // F13
	-1, // F14
	-1, // F15
	-1, // F16
	-1, // F17
	-1, // F18
	-1, // F19
	-1, // F20
	-1, // F21
	-1, // F22
	-1, // F23
	-1, // F24
	-1, // F25
	-1, -1, -1, -1, -1,
	-1, // KP_0
	-1, // KP_1
	-1, // KP_2
	-1, // KP_3
	-1, // KP_4
	-1, // KP_5
	-1, // KP_6
	-1, // KP_7
	-1, // KP_8
	-1, // KP_9
	-1, // KP_DECIMAL
	-1, // KP_DIVIDE
	-1, // KP_MULTIPLY
	-1, // KP_SUBTRACT
	-1, // KP_ADD
	-1, // KP_ENTER
	-1, // KP_EQUAL
	-1, -1, -1, eInputKeyboardKeysOther::kKEY_LEFT_SHIFT,
	eInputKeyboardKeysOther::kKEY_LEFT_CONTROL,
	eInputKeyboardKeysApplication::kKEY_LEFT_ALT, -1,
	eInputKeyboardKeysOther::kKEY_RIGHT_SHIFT,
	eInputKeyboardKeysOther::kKEY_RIGHT_CONTROL,
	eInputKeyboardKeysApplication::kKEY_RIGHT_ALT, -1,
	eInputKeyboardKeysApplication::kKEY_MENU};

int p_glfw3_mouse_key_to_input[] = {eInputMouseKeys::kKey_LeftButton,
	eInputMouseKeys::kKey_RightButton, eInputMouseKeys::kKey_MiddleButton, -1,
	-1, -1, -1, -1};

eInputControllerKeyboardCategory p_glfw3_keyboard_key_to_category[] = {
	eInputControllerKeyboardCategory::kKeyboardUnknown, // 0
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown, // 31
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardKeysNumbers,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState, // 96
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysEnter,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys,
	eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys,
	eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys,
	eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState, // 269
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter, // 280
	eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter,
	eInputControllerKeyboardCategory::kKeyboardKeysNumpad,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState,
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F13
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F14
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F15
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F16
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F17
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F18
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F19
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F20
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F21
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F22
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F23
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F24
	eInputControllerKeyboardCategory::kKeyboardUnknown, // F25
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_0
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_1
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_2
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_3
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_4
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_5
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_6
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_7
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_8
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_9
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_DECIMAL
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_DIVIDE
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_MULTIPLY
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_SUBTRACT
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_ADD
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_ENTER
	eInputControllerKeyboardCategory::kKeyboardUnknown, // KP_EQUAL
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysApplication,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysOtherState,
	eInputControllerKeyboardCategory::kKeyboardKeysApplication,
	eInputControllerKeyboardCategory::kKeyboardUnknown,
	eInputControllerKeyboardCategory::kKeyboardKeysApplication};

void ktkInput::Update(void* args)
{
	eInputPlatformBackend backend;

	std::memcpy(&backend, args, sizeof(eInputPlatformBackend));

	switch (backend)
	{
	case eInputPlatformBackend::kPlatformBackend_GLFW3:
	{
		ktkInputPlatformBackendArgs_GLFW3* p_args =
			static_cast<ktkInputPlatformBackendArgs_GLFW3*>(args);

		KOTEK_ASSERT(
			p_args->controller != eInputControllerType::kControllerUnknown,
			"you must initialize args where you call this method!");

		this->Update_Controller(p_args, p_args->backend, p_args->controller);

		break;
	}
	case eInputPlatformBackend::kPlatformBackend_SDL2:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_SDL3:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_WINAPI:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_X11:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_MACOS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS1:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS2:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS3:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS4:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS5:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS6:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOX:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOX360:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXONE:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXSERIESS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXSERIESX:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_NS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	}
}

void ktkInput::Update_Controller(
	void* p_args, eInputPlatformBackend backend, eInputControllerType controller_type)
{
	KOTEK_ASSERT(p_args, "must be valid args");
	KOTEK_ASSERT(controller_type != eInputControllerType::kControllerUnknown,
		"must be valid controller!");

	switch (controller_type)
	{
	case eInputControllerType::kControllerKeyboard:
	{
		this->Update_Keyboard(p_args, backend);
		break;
	}
	case eInputControllerType::kControllerMouse:
	{
		this->Update_Mouse(p_args, backend);
		break;
	}
	case eInputControllerType::kControllerGamepad:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputControllerType::kControllerJoystick:
	{
		KOTEK_ASSERT(false, "not implemented!");
		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "unhanled code register your type");
		break;
	}
	}
}

void ktkInput::Update_Keyboard(void* p_raw_args, eInputPlatformBackend backend)
{
	switch (backend)
	{
	case eInputPlatformBackend::kPlatformBackend_GLFW3:
	{
		ktkInputPlatformBackendArgs_GLFW3* p_args =
			static_cast<ktkInputPlatformBackendArgs_GLFW3*>(p_raw_args);

		KOTEK_ASSERT(
			p_args->controller != eInputControllerType::kControllerUnknown,
			"you must initialize args where you call this method!");

		break;
	}
	case eInputPlatformBackend::kPlatformBackend_SDL2:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_SDL3:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_WINAPI:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_X11:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_MACOS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS1:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS2:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS3:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS4:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS5:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS6:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOX:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOX360:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXONE:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXSERIESS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXSERIESX:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_NS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	}
}

void ktkInput::Update_Mouse(void* p_raw_args, eInputPlatformBackend backend)
{
	switch (backend)
	{
	case eInputPlatformBackend::kPlatformBackend_GLFW3:
	{
		ktkInputPlatformBackendArgs_GLFW3* p_args =
			static_cast<ktkInputPlatformBackendArgs_GLFW3*>(p_raw_args);

		KOTEK_ASSERT(
			p_args->controller != eInputControllerType::kControllerUnknown,
			"you must initialize args where you call this method!");

		break;
	}
	case eInputPlatformBackend::kPlatformBackend_SDL2:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_SDL3:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_WINAPI:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_X11:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_MACOS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS1:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS2:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS3:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS4:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS5:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_PS6:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOX:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOX360:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXONE:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXSERIESS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_XBOXSERIESX:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	case eInputPlatformBackend::kPlatformBackend_NS:
	{
		KOTEK_ASSERT(false, "not implemented");
		break;
	}
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK