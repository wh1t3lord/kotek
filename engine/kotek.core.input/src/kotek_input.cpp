#include "../include/kotek_input.h"

#include <kotek.core.defines_dependent.assert\include\kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkInput::ktkInput(void) :
	m_controller_mouse_key_pressed{}, m_controller_mouse_key_released{},
	m_controller_keyboard_key_cursor_control_pressed{},
	m_controller_keyboard_key_cursor_control_released{},
	m_controller_keyboard_key_system_pressed{},
	m_controller_keyboard_key_system_released{},
	m_controller_keyboard_key_application_pressed{},
	m_controller_keyboard_key_application_released{},
	m_controller_keyboard_key_enter_pressed{},
	m_controller_keyboard_key_enter_released{},
	m_controller_keyboard_key_numpad_pressed{},
	m_controller_keyboard_key_numpad_released{},
	m_controller_keyboard_key_other_pressed{},
	m_controller_keyboard_key_other_released{},
	m_controller_keyboard_key_function_pressed{},
	m_controller_keyboard_key_function_released{},
	m_controller_keyboard_key_numbers_pressed{},
	m_controller_keyboard_key_numbers_released{},
	m_controller_keyboard_key_typewriter_pressed{},
	m_controller_keyboard_key_typewriter_released{},
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

/*
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
        return this->m_controller_keyboard_key_typewriter_pressed & keys;
    }
    case eInputControllerType::kControllerMouse:
    {
        return (this->m_controller_mouse_key_pressed & keys);
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
            return (this->m_controller_keyboard_key_typewriter_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState:
        {
            return (this->m_controller_keyboard_key_function_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysOtherState:
        {
            return (this->m_controller_keyboard_key_other_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysNumbers:
        {
            return (this->m_controller_keyboard_key_numbers_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysApplication:
        {
            KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
                "can't be you passed wrong enum flags");
            return (this->m_controller_keyboard_key_application_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysSystem:
        {
            KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
                "can't be you passed wrong enum flags");

            return (this->m_controller_keyboard_key_system_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysEnter:
        {
            KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
                "can't be you passed wrong enum flags");
            return (this->m_controller_keyboard_key_enter_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysNumpad:
        {
            return (this->m_controller_keyboard_key_numbers_pressed & keys);
        }
        case eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys:
        {
            KOTEK_ASSERT(keys <= std::numeric_limits<unsigned char>::max(),
                "can't be you passed wrong enum flags");
            return (
                this->m_controller_keyboard_key_cursor_control_pressed & keys);
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
        return (this->m_controller_mouse_key_pressed & keys);
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
*/

bool ktkInput::Is_KeyPressed(
	eInputControllerType controller_type, eInputAllKeys key)
{
	KOTEK_ASSERT(this->m_current_platform !=
			eInputPlatformBackend::kPlatformBackend_Unknown,
		"you forgot to call ::Initialize method!");

	if (this->m_current_platform ==
		eInputPlatformBackend::kPlatformBackend_Unknown)
		return false;

	unsigned char ticks = this->m_controller_key_ticks[key];

	switch (controller_type)
	{
	case eInputControllerType::kControllerKeyboard:
	{
		int category = this->Convert_AllKeysToCategory(key);
		int flag = this->Convert_AllKeysToFlags(key);

		KOTEK_ASSERT(category > -1,
			"something is wrong, keyboard has > 30 buttons as controller");

		switch (static_cast<eInputControllerKeyboardCategory>(category))
		{
		case eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_typewriter_pressed, flag);

			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_function_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysOtherState:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_other_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysNumbers:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_numbers_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysApplication:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_application_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysSystem:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_system_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysEnter:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_enter_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysNumpad:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_numpad_pressed, flag);
			return status && ticks < 2;
		}
		case eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys:
		{
			bool status = KOTEK_CHECK_FLAG(
				this->m_controller_keyboard_key_cursor_control_pressed, flag);
			return status && ticks < 2;
		}
		default:
		{
			KOTEK_ASSERT(false, "you forgot to register a new situation!");
			return false;
		}
		}
	}
	case eInputControllerType::kControllerMouse:
	{
#ifdef KOTEK_DEBUG
		int category = this->Convert_AllKeysToCategory(key);
		KOTEK_ASSERT(
			category == -1, "no category for this controller must be!");
		KOTEK_ASSERT(this->Convert_AllKeysToFlags(key) <=
				std::numeric_limits<
					decltype(this->m_controller_mouse_key_pressed)>::max(),
			"overflow, something is wrong, maybe make your type larger?");
#endif

		unsigned char flag = this->Convert_AllKeysToFlags(key);

		bool status =
			KOTEK_CHECK_FLAG(this->m_controller_mouse_key_pressed, flag);

		return status && ticks < 2;
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

	return false;
}

bool ktkInput::Is_KeyHolding(eInputControllerType controller_type,
	eInputAllKeys key, unsigned char frames)
{
	return false;
}

bool ktkInput::Is_KeyReleased(
	eInputControllerType controller_type, eInputAllKeys key)
{
	return false;
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

int p_glfw3_keyboard_keys_to_all_keys[] = {eInputAllKeys::kCA_KEY_UNKNOWN, // 0
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, // 31
	eInputAllKeys::kCK_KEY_SPACE, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_APOSTROPHE,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCK_KEY_COMMA, eInputAllKeys::kCK_KEY_MINUS,
	eInputAllKeys::kCK_KEY_PERIOD, eInputAllKeys::kCK_KEY_SLASH,
	eInputAllKeys::kCK_KEY_0, eInputAllKeys::kCK_KEY_1,
	eInputAllKeys::kCK_KEY_2, eInputAllKeys::kCK_KEY_3,
	eInputAllKeys::kCK_KEY_4, eInputAllKeys::kCK_KEY_5,
	eInputAllKeys::kCK_KEY_6, eInputAllKeys::kCK_KEY_7,
	eInputAllKeys::kCK_KEY_8, eInputAllKeys::kCK_KEY_9,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_SEMICOLON,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_EQUAL,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_A,
	eInputAllKeys::kCK_KEY_B, eInputAllKeys::kCK_KEY_C,
	eInputAllKeys::kCK_KEY_D, eInputAllKeys::kCK_KEY_E,
	eInputAllKeys::kCK_KEY_F, eInputAllKeys::kCK_KEY_G,
	eInputAllKeys::kCK_KEY_H, eInputAllKeys::kCK_KEY_I,
	eInputAllKeys::kCK_KEY_J, eInputAllKeys::kCK_KEY_K,
	eInputAllKeys::kCK_KEY_L, eInputAllKeys::kCK_KEY_M,
	eInputAllKeys::kCK_KEY_N, eInputAllKeys::kCK_KEY_O,
	eInputAllKeys::kCK_KEY_P, eInputAllKeys::kCK_KEY_Q,
	eInputAllKeys::kCK_KEY_R, eInputAllKeys::kCK_KEY_S,
	eInputAllKeys::kCK_KEY_T, eInputAllKeys::kCK_KEY_U,
	eInputAllKeys::kCK_KEY_V, eInputAllKeys::kCK_KEY_W,
	eInputAllKeys::kCK_KEY_X, eInputAllKeys::kCK_KEY_Y,
	eInputAllKeys::kCK_KEY_Z, eInputAllKeys::kCK_KEY_LEFT_BRACKET,
	eInputAllKeys::kCK_KEY_BACKSLASH, eInputAllKeys::kCK_KEY_RIGHT_BRACKET,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCK_KEY_GRAVE_ACCENT, // 96
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_ESCAPE,
	eInputAllKeys::kCK_KEY_ENTER, eInputAllKeys::kCK_KEY_TAB,
	eInputAllKeys::kCK_KEY_BACKSPACE, eInputAllKeys::kCK_KEY_INSERT,
	eInputAllKeys::kCK_KEY_DEL, eInputAllKeys::kCK_KEY_ARROW_RIGHT,
	eInputAllKeys::kCK_KEY_ARROW_LEFT, eInputAllKeys::kCK_KEY_ARROW_DOWN,
	eInputAllKeys::kCK_KEY_ARROW_UP, eInputAllKeys::kCK_KEY_PAGEUP,
	eInputAllKeys::kCK_KEY_PAGEDOWN, eInputAllKeys::kCK_KEY_HOME,
	eInputAllKeys::kCK_KEY_END, // 269
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCK_KEY_CAPS_LOCK, // 280
	eInputAllKeys::kCK_KEY_SCROLL_LOCK, eInputAllKeys::kCK_KEY_NUMPAD_NUMLOCK,
	eInputAllKeys::kCK_KEY_PRTSC, eInputAllKeys::kCK_KEY_PAUSE,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_F1,
	eInputAllKeys::kCK_KEY_F2, eInputAllKeys::kCK_KEY_F3,
	eInputAllKeys::kCK_KEY_F4, eInputAllKeys::kCK_KEY_F5,
	eInputAllKeys::kCK_KEY_F6, eInputAllKeys::kCK_KEY_F7,
	eInputAllKeys::kCK_KEY_F8, eInputAllKeys::kCK_KEY_F9,
	eInputAllKeys::kCK_KEY_F10, eInputAllKeys::kCK_KEY_F11,
	eInputAllKeys::kCK_KEY_F12,
	eInputAllKeys::kCA_KEY_UNKNOWN, // F13
	eInputAllKeys::kCA_KEY_UNKNOWN, // F14
	eInputAllKeys::kCA_KEY_UNKNOWN, // F15
	eInputAllKeys::kCA_KEY_UNKNOWN, // F16
	eInputAllKeys::kCA_KEY_UNKNOWN, // F17
	eInputAllKeys::kCA_KEY_UNKNOWN, // F18
	eInputAllKeys::kCA_KEY_UNKNOWN, // F19
	eInputAllKeys::kCA_KEY_UNKNOWN, // F20
	eInputAllKeys::kCA_KEY_UNKNOWN, // F21
	eInputAllKeys::kCA_KEY_UNKNOWN, // F22
	eInputAllKeys::kCA_KEY_UNKNOWN, // F23
	eInputAllKeys::kCA_KEY_UNKNOWN, // F24
	eInputAllKeys::kCA_KEY_UNKNOWN, // F25
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_0
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_1
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_2
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_3
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_4
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_5
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_6
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_7
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_8
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_9
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_DECIMAL
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_DIVIDE
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_MULTIPLY
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_SUBTRACT
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_ADD
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_ENTER
	eInputAllKeys::kCA_KEY_UNKNOWN, // KP_EQUAL
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCA_KEY_UNKNOWN,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_LEFT_SHIFT,
	eInputAllKeys::kCK_KEY_LEFT_CONTROL, eInputAllKeys::kCK_KEY_LEFT_ALT,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_RIGHT_SHIFT,
	eInputAllKeys::kCK_KEY_RIGHT_CONTROL, eInputAllKeys::kCK_KEY_RIGHT_ALT,
	eInputAllKeys::kCA_KEY_UNKNOWN, eInputAllKeys::kCK_KEY_MENU};

int p_glfw3_mouse_key_to_input[] = {eInputMouseKeys::kKEY_LeftButton,
	eInputMouseKeys::kKEY_RightButton, eInputMouseKeys::kKEY_MiddleButton, -1,
	-1, -1, -1, -1};

int p_glfw3_mouse_key_to_all_keys[] = {eInputAllKeys::kCM_KEY_LEFT,
	eInputAllKeys::kCM_KEY_RIGHT, eInputAllKeys::kCM_KEY_MIDDLE, -1, -1, -1, -1,
	-1};

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

void ktkInput::Update_Controller(void* p_args, eInputPlatformBackend backend,
	eInputControllerType controller_type)
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

		constexpr unsigned char _kGLFWActionPress = 1;
		constexpr unsigned char _kGLFWActionRelease = 0;
		constexpr unsigned char _kGLFWActionRepeat = 2;

		switch (p_args->action)
		{
		case _kGLFWActionRelease:
		{
			eInputControllerKeyboardCategory category =
				p_glfw3_keyboard_key_to_category[p_args->key];
			int converted_key = p_glfw3_keyboard_keys_to_input[p_args->key];

			if (converted_key == -1)
				return;

			eInputAllKeys converted_all_key = static_cast<eInputAllKeys>(
				p_glfw3_keyboard_keys_to_all_keys[p_args->key]);
			this->m_controller_key_ticks[static_cast<int>(converted_all_key)] =
				0;

			switch (category)
			{
			case eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter:
			{
				KOTEK_SET_FLAG(
					this->m_controller_keyboard_key_typewriter_released,
					converted_key);
				KOTEK_REMOVE_FLAG(
					this->m_controller_keyboard_key_typewriter_pressed,
					converted_key);

				break;
			}
			case eInputControllerKeyboardCategory::
				kKeyboardKeysFunctionKeysState:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysOtherState:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysNumbers:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysApplication:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysSystem:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysEnter:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysNumpad:
			{
				break;
			}
			case eInputControllerKeyboardCategory::
				kKeyboardKeysCursorControlKeys:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardTotalAmountOfEnum:
			{
				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "unhandled category, you forgot to register");
				break;
			}
			}

			break;
		}
		case _kGLFWActionPress:
		{
			eInputControllerKeyboardCategory category =
				p_glfw3_keyboard_key_to_category[p_args->key];
			int converted_key = p_glfw3_keyboard_keys_to_input[p_args->key];

			if (converted_key == -1)
				return;

			eInputAllKeys converted_all_key = static_cast<eInputAllKeys>(
				p_glfw3_keyboard_keys_to_all_keys[p_args->key]);
			this->m_controller_key_ticks[static_cast<int>(converted_all_key)] =
				0;

			switch (category)
			{
			case eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter:
			{
				KOTEK_SET_FLAG(
					this->m_controller_keyboard_key_typewriter_pressed,
					converted_key);
				KOTEK_REMOVE_FLAG(
					this->m_controller_keyboard_key_typewriter_released,
					converted_key);

				this->m_controller_key_ticks[static_cast<int>(
					converted_all_key)] += 1;

				break;
			}
			case eInputControllerKeyboardCategory::
				kKeyboardKeysFunctionKeysState:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysOtherState:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysNumbers:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysApplication:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysSystem:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysEnter:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysNumpad:
			{
				break;
			}
			case eInputControllerKeyboardCategory::
				kKeyboardKeysCursorControlKeys:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardTotalAmountOfEnum:
			{
				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "unhandled category, you forgot to register");
				break;
			}
			}

			break;
		}
		case _kGLFWActionRepeat:
		{
			static_assert(sizeof(this->m_controller_key_ticks[0]) ==
					sizeof(unsigned char) &&
				"did you change type? If yes fix the below line and this "
			    "assert "
				"after");

			constexpr auto _kMaxTickAmount =
				std::numeric_limits<unsigned char>::max();

			eInputControllerKeyboardCategory category =
				p_glfw3_keyboard_key_to_category[p_args->key];
			int converted_key = p_glfw3_keyboard_keys_to_input[p_args->key];

			if (converted_key == -1)
				return;

			eInputAllKeys converted_all_key = static_cast<eInputAllKeys>(
				p_glfw3_keyboard_keys_to_all_keys[p_args->key]);

			switch (category)
			{
			case eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter:
			{
				KOTEK_ASSERT(
					KOTEK_CHECK_FLAG(
						this->m_controller_keyboard_key_typewriter_pressed,
						converted_key) == true,
					"can't be!");

				this->m_controller_key_ticks[static_cast<int>(
					converted_all_key)] = _kMaxTickAmount;

				break;
			}
			case eInputControllerKeyboardCategory::
				kKeyboardKeysFunctionKeysState:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysOtherState:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysNumbers:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysApplication:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysSystem:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysEnter:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardKeysNumpad:
			{
				break;
			}
			case eInputControllerKeyboardCategory::
				kKeyboardKeysCursorControlKeys:
			{
				break;
			}
			case eInputControllerKeyboardCategory::kKeyboardTotalAmountOfEnum:
			{
				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "unhandled category, you forgot to register");
				break;
			}
			}

			break;
		}
		default:
		{
			KOTEK_ASSERT(
				false, "new api? unhanlded action from keyboard callback");
			break;
		}
		}

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

int ktkInput::Convert_AllKeysToFlags(eInputAllKeys field)
{
	switch (field)
	{
	case eInputAllKeys::kCK_KEY_A:
		return eInputKeyboardKeys::kKEY_A;
	case eInputAllKeys::kCK_KEY_B:
		return eInputKeyboardKeys::kKEY_B;
	case eInputAllKeys::kCK_KEY_C:
		return eInputKeyboardKeys::kKEY_C;
	case eInputAllKeys::kCK_KEY_D:
		return eInputKeyboardKeys::kKEY_D;
	case eInputAllKeys::kCK_KEY_E:
		return eInputKeyboardKeys::kKEY_E;
	case eInputAllKeys::kCK_KEY_F:
		return eInputKeyboardKeys::kKEY_F;
	case eInputAllKeys::kCK_KEY_G:
		return eInputKeyboardKeys::kKEY_G;
	case eInputAllKeys::kCK_KEY_H:
		return eInputKeyboardKeys::kKEY_H;
	case eInputAllKeys::kCK_KEY_I:
		return eInputKeyboardKeys::kKEY_I;
	case eInputAllKeys::kCK_KEY_J:
		return eInputKeyboardKeys::kKEY_J;
	case eInputAllKeys::kCK_KEY_K:
		return eInputKeyboardKeys::kKEY_K;
	case eInputAllKeys::kCK_KEY_L:
		return eInputKeyboardKeys::kKEY_L;
	case eInputAllKeys::kCK_KEY_M:
		return eInputKeyboardKeys::kKEY_M;
	case eInputAllKeys::kCK_KEY_N:
		return eInputKeyboardKeys::kKEY_N;
	case eInputAllKeys::kCK_KEY_O:
		return eInputKeyboardKeys::kKEY_O;
	case eInputAllKeys::kCK_KEY_P:
		return eInputKeyboardKeys::kKEY_P;
	case eInputAllKeys::kCK_KEY_Q:
		return eInputKeyboardKeys::kKEY_Q;
	case eInputAllKeys::kCK_KEY_R:
		return eInputKeyboardKeys::kKEY_R;
	case eInputAllKeys::kCK_KEY_S:
		return eInputKeyboardKeys::kKEY_S;
	case eInputAllKeys::kCK_KEY_T:
		return eInputKeyboardKeys::kKEY_T;
	case eInputAllKeys::kCK_KEY_U:
		return eInputKeyboardKeys::kKEY_U;
	case eInputAllKeys::kCK_KEY_V:
		return eInputKeyboardKeys::kKEY_V;
	case eInputAllKeys::kCK_KEY_W:
		return eInputKeyboardKeys::kKEY_W;
	case eInputAllKeys::kCK_KEY_X:
		return eInputKeyboardKeys::kKEY_X;
	case eInputAllKeys::kCK_KEY_Y:
		return eInputKeyboardKeys::kKEY_Y;
	case eInputAllKeys::kCK_KEY_Z:
		return eInputKeyboardKeys::kKEY_Z;
	case eInputAllKeys::kCK_KEY_CAPS_LOCK:
		return eInputKeyboardKeys::kKEY_CAPS_LOCK;
	case eInputAllKeys::kCK_KEY_SCROLL_LOCK:
		return eInputKeyboardKeys::kKEY_SCROLL_LOCK;
	case eInputAllKeys::kCK_KEY_1:
		return eInputKeyboardKeysNumbers::kKEY_1;
	case eInputAllKeys::kCK_KEY_2:
		return eInputKeyboardKeysNumbers::kKEY_2;
	case eInputAllKeys::kCK_KEY_3:
		return eInputKeyboardKeysNumbers::kKEY_3;
	case eInputAllKeys::kCK_KEY_4:
		return eInputKeyboardKeysNumbers::kKEY_4;
	case eInputAllKeys::kCK_KEY_5:
		return eInputKeyboardKeysNumbers::kKEY_5;
	case eInputAllKeys::kCK_KEY_6:
		return eInputKeyboardKeysNumbers::kKEY_6;
	case eInputAllKeys::kCK_KEY_7:
		return eInputKeyboardKeysNumbers::kKEY_7;
	case eInputAllKeys::kCK_KEY_8:
		return eInputKeyboardKeysNumbers::kKEY_8;
	case eInputAllKeys::kCK_KEY_9:
		return eInputKeyboardKeysNumbers::kKEY_9;
	case eInputAllKeys::kCK_KEY_0:
		return eInputKeyboardKeysNumbers::kKEY_0;
	case eInputAllKeys::kCK_KEY_MINUS:
		return eInputKeyboardKeysNumbers::kKEY_MINUS;
	case eInputAllKeys::kCK_KEY_PLUS:
		return eInputKeyboardKeysNumbers::kKEY_PLUS;
	case eInputAllKeys::kCK_KEY_F1:
		return eInputKeyboardKeysFunctionKeys::kKEY_F1;
	case eInputAllKeys::kCK_KEY_F2:
		return eInputKeyboardKeysFunctionKeys::kKEY_F2;
	case eInputAllKeys::kCK_KEY_F3:
		return eInputKeyboardKeysFunctionKeys::kKEY_F3;
	case eInputAllKeys::kCK_KEY_F4:
		return eInputKeyboardKeysFunctionKeys::kKEY_F4;
	case eInputAllKeys::kCK_KEY_F5:
		return eInputKeyboardKeysFunctionKeys::kKEY_F5;
	case eInputAllKeys::kCK_KEY_F6:
		return eInputKeyboardKeysFunctionKeys::kKEY_F6;
	case eInputAllKeys::kCK_KEY_F7:
		return eInputKeyboardKeysFunctionKeys::kKEY_F7;
	case eInputAllKeys::kCK_KEY_F8:
		return eInputKeyboardKeysFunctionKeys::kKEY_F8;
	case eInputAllKeys::kCK_KEY_F9:
		return eInputKeyboardKeysFunctionKeys::kKEY_F9;
	case eInputAllKeys::kCK_KEY_F10:
		return eInputKeyboardKeysFunctionKeys::kKEY_F10;
	case eInputAllKeys::kCK_KEY_F11:
		return eInputKeyboardKeysFunctionKeys::kKEY_F11;
	case eInputAllKeys::kCK_KEY_F12:
		return eInputKeyboardKeysFunctionKeys::kKEY_F12;
	case eInputAllKeys::kCK_KEY_PRTSC:
		return eInputKeyboardKeysOther::kKEY_PRTSC;
	case eInputAllKeys::kCK_KEY_PAUSE:
		return eInputKeyboardKeysOther::kKEY_PAUSE;
	case eInputAllKeys::kCK_KEY_DEL:
		return eInputKeyboardKeysOther::kKEY_DEL;
	case eInputAllKeys::kCK_KEY_END:
		return eInputKeyboardKeysOther::kKEY_END;
	case eInputAllKeys::kCK_KEY_INSERT:
		return eInputKeyboardKeysOther::kKEY_INSERT;
	case eInputAllKeys::kCK_KEY_HOME:
		return eInputKeyboardKeysOther::kKEY_HOME;
	case eInputAllKeys::kCK_KEY_PAGEUP:
		return eInputKeyboardKeysOther::kKEY_PAGEUP;
	case eInputAllKeys::kCK_KEY_PAGEDOWN:
		return eInputKeyboardKeysOther::kKEY_PAGEDOWN;
	case eInputAllKeys::kCK_KEY_SCROLLLOCK:
		return eInputKeyboardKeysOther::kKEY_SCROLLLOCK;
	case eInputAllKeys::kCK_KEY_ESC:
		return eInputKeyboardKeysOther::kKEY_ESC;
	case eInputAllKeys::kCK_KEY_SPACE:
		return eInputKeyboardKeysOther::kKEY_SPACE;
	case eInputAllKeys::kCK_KEY_LEFT_SHIFT:
		return eInputKeyboardKeysOther::kKEY_LEFT_SHIFT;
	case eInputAllKeys::kCK_KEY_RIGHT_SHIFT:
		return eInputKeyboardKeysOther::kKEY_RIGHT_SHIFT;
	case eInputAllKeys::kCK_KEY_LEFT_CONTROL:
		return eInputKeyboardKeysOther::kKEY_LEFT_CONTROL;
	case eInputAllKeys::kCK_KEY_RIGHT_CONTROL:
		return eInputKeyboardKeysOther::kKEY_RIGHT_CONTROL;
	case eInputAllKeys::kCK_KEY_APOSTROPHE:
		return eInputKeyboardKeysOther::kKEY_APOSTROPHE;
	case eInputAllKeys::kCK_KEY_COMMA:
		return eInputKeyboardKeysOther::kKEY_COMMA;
	case eInputAllKeys::kCK_KEY_PERIOD:
		return eInputKeyboardKeysOther::kKEY_PERIOD;
	case eInputAllKeys::kCK_KEY_SLASH:
		return eInputKeyboardKeysOther::kKEY_SLASH;
	case eInputAllKeys::kCK_KEY_BACKSLASH:
		return eInputKeyboardKeysOther::kKEY_BACKSLASH;
	case eInputAllKeys::kCK_KEY_SEMICOLON:
		return eInputKeyboardKeysOther::KKEY_SEMICOLON;
	case eInputAllKeys::kCK_KEY_EQUAL:
		return eInputKeyboardKeysOther::kKEY_EQUAL;
	case eInputAllKeys::kCK_KEY_LEFT_BRACKET:
		return eInputKeyboardKeysOther::kKEY_LEFT_BRACKET;
	case eInputAllKeys::kCK_KEY_RIGHT_BRACKET:
		return eInputKeyboardKeysOther::kKEY_RIGHT_BRACKET;
	case eInputAllKeys::kCK_KEY_GRAVE_ACCENT:
		return eInputKeyboardKeysOther::kKEY_GRAVE_ACCENT;
	case eInputAllKeys::kCK_KEY_ESCAPE:
		return eInputKeyboardKeysOther::kKEY_ESCAPE;
	case eInputAllKeys::kCK_KEY_TAB:
		return eInputKeyboardKeysOther::kKEY_TAB;
	case eInputAllKeys::kCK_KEY_BACKSPACE:
		return eInputKeyboardKeysOther::kKEY_BACKSPACE;
	case eInputAllKeys::kCK_KEY_ENTER:
		return eInputKeyboardKeysEnter::kKEY_ENTER;
	case eInputAllKeys::kCK_KEY_ENTER_NUMPAD:
		return eInputKeyboardKeysEnter::kKEY_ENTER_NUMPAD;
	case eInputAllKeys::kCK_KEY_NUMPAD_NUMLOCK:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_NUMLOCK;
	case eInputAllKeys::kCK_KEY_NUMPAD_ENTER:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_ENTER;
	case eInputAllKeys::kCK_KEY_NUMPAD_SLASH:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_SLASH;
	case eInputAllKeys::kCK_KEY_NUMPAD_ASTERISK:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_ASTERISK;
	case eInputAllKeys::kCK_KEY_NUMPAD_1:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_1;
	case eInputAllKeys::kCK_KEY_NUMPAD_2:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_2;
	case eInputAllKeys::kCK_KEY_NUMPAD_3:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_3;
	case eInputAllKeys::kCK_KEY_NUMPAD_4:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_4;
	case eInputAllKeys::kCK_KEY_NUMPAD_5:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_5;
	case eInputAllKeys::kCK_KEY_NUMPAD_6:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_6;
	case eInputAllKeys::kCK_KEY_NUMPAD_7:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_7;
	case eInputAllKeys::kCK_KEY_NUMPAD_8:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_8;
	case eInputAllKeys::kCK_KEY_NUMPAD_9:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_9;
	case eInputAllKeys::kCK_KEY_NUMPAD_0:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_0;
	case eInputAllKeys::kCK_KEY_NUMPAD_MINUS:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_MINUS;
	case eInputAllKeys::kCK_KEY_NUMPAD_PLUS:
		return eInputKeyboardKeysNumpad::kKEY_NUMPAD_PLUS;
	case eInputAllKeys::kCK_KEY_MENU:
		return eInputKeyboardKeysApplication::kKEY_MENU;
	case eInputAllKeys::kCK_KEY_LEFT_ALT:
		return eInputKeyboardKeysApplication::kKEY_LEFT_ALT;
	case eInputAllKeys::kCK_KEY_RIGHT_ALT:
		return eInputKeyboardKeysApplication::kKEY_RIGHT_ALT;
	case eInputAllKeys::kCK_KEY_LEFT_SUPER:
		return eInputKeyboardKeysApplication::kKEY_LEFT_SUPER;
	case eInputAllKeys::kCK_KEY_RIGHT_SUPER:
		return eInputKeyboardKeysApplication::kKEY_RIGHT_SUPER;
	case eInputAllKeys::kCK_KEY_WINDOWS:
		return eInputKeyboardKeysSystem::kKEY_WINDOWS;
	case eInputAllKeys::kCK_KEY_ARROW_LEFT:
		return eInputKeyboardCursorControlKeys::kKEY_ARROW_LEFT;
	case eInputAllKeys::kCK_KEY_ARROW_UP:
		return eInputKeyboardCursorControlKeys::kKEY_ARROW_UP;
	case eInputAllKeys::kCK_KEY_ARROW_RIGHT:
		return eInputKeyboardCursorControlKeys::kKEY_ARROW_RIGHT;
	case eInputAllKeys::kCK_KEY_ARROW_DOWN:
		return eInputKeyboardCursorControlKeys::kKEY_ARROW_DOWN;
	case eInputAllKeys::kCM_KEY_LEFT:
		return eInputMouseKeys::kKEY_LeftButton;
	case eInputAllKeys::kCM_KEY_RIGHT:
		return eInputMouseKeys::kKEY_RightButton;
	case eInputAllKeys::kCM_KEY_MIDDLE:
		return eInputMouseKeys::kKEY_MiddleButton;
	default:
	{
		KOTEK_ASSERT(
			false, "you forgot to register something new! add case handling");
		return -1;
	}
	}
}

int ktkInput::Convert_AllKeysToCategory(eInputAllKeys field)
{
	switch (field)
	{
	case eInputAllKeys::kCK_KEY_A:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_B:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_C:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_D:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_E:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_F:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_G:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_H:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_I:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_J:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_K:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_L:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_M:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_N:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_O:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_P:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_Q:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_R:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_S:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_T:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_U:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_V:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_W:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_X:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_Y:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_Z:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_CAPS_LOCK:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_SCROLL_LOCK:
		return eInputControllerKeyboardCategory::kKeyboardKeysTypeWriter;
	case eInputAllKeys::kCK_KEY_1:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_2:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_3:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_4:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_5:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_6:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_7:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_8:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_9:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_0:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_MINUS:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_PLUS:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumbers;
	case eInputAllKeys::kCK_KEY_F1:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F2:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F3:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F4:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F5:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F6:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F7:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F8:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F9:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F10:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F11:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_F12:
		return eInputControllerKeyboardCategory::kKeyboardKeysFunctionKeysState;
	case eInputAllKeys::kCK_KEY_PRTSC:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_PAUSE:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_DEL:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_END:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_INSERT:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_HOME:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_PAGEUP:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_PAGEDOWN:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_SCROLLLOCK:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_ESC:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_SPACE:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_LEFT_SHIFT:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_RIGHT_SHIFT:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_LEFT_CONTROL:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_RIGHT_CONTROL:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_APOSTROPHE:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_COMMA:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_PERIOD:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_SLASH:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_BACKSLASH:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_SEMICOLON:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_EQUAL:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_LEFT_BRACKET:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_RIGHT_BRACKET:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_GRAVE_ACCENT:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_ESCAPE:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_TAB:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_BACKSPACE:
		return eInputControllerKeyboardCategory::kKeyboardKeysOtherState;
	case eInputAllKeys::kCK_KEY_ENTER:
		return eInputControllerKeyboardCategory::kKeyboardKeysEnter;
	case eInputAllKeys::kCK_KEY_ENTER_NUMPAD:
		return eInputControllerKeyboardCategory::kKeyboardKeysEnter;
	case eInputAllKeys::kCK_KEY_NUMPAD_NUMLOCK:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_ENTER:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_SLASH:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_ASTERISK:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_1:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_2:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_3:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_4:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_5:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_6:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_7:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_8:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_9:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_0:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_MINUS:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_NUMPAD_PLUS:
		return eInputControllerKeyboardCategory::kKeyboardKeysNumpad;
	case eInputAllKeys::kCK_KEY_MENU:
		eInputControllerKeyboardCategory::kKeyboardKeysSystem;
	case eInputAllKeys::kCK_KEY_LEFT_ALT:
		eInputControllerKeyboardCategory::kKeyboardKeysSystem;
	case eInputAllKeys::kCK_KEY_RIGHT_ALT:
		eInputControllerKeyboardCategory::kKeyboardKeysSystem;
	case eInputAllKeys::kCK_KEY_LEFT_SUPER:
		eInputControllerKeyboardCategory::kKeyboardKeysSystem;
	case eInputAllKeys::kCK_KEY_RIGHT_SUPER:
		eInputControllerKeyboardCategory::kKeyboardKeysSystem;
	case eInputAllKeys::kCK_KEY_WINDOWS:
		return eInputControllerKeyboardCategory::kKeyboardKeysApplication;
	case eInputAllKeys::kCK_KEY_ARROW_LEFT:
		return eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys;
	case eInputAllKeys::kCK_KEY_ARROW_UP:
		return eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys;
	case eInputAllKeys::kCK_KEY_ARROW_RIGHT:
		return eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys;
	case eInputAllKeys::kCK_KEY_ARROW_DOWN:
		return eInputControllerKeyboardCategory::kKeyboardKeysCursorControlKeys;
	case eInputAllKeys::kCM_KEY_LEFT:
		return -1;
	case eInputAllKeys::kCM_KEY_RIGHT:
		return -1;
	case eInputAllKeys::kCM_KEY_MIDDLE:
		return -1;
	case eInputAllKeys::kCA_KEY_END_ENUM:
		return -1;
	default:
	{
		KOTEK_ASSERT(false, "you forgot to register new case!");
		return -2;
	}
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK