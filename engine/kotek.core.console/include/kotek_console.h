#pragma once

#include "kotek_std.h"

namespace Kotek
{
	namespace ktk
	{
		using console_command_args_t = const ktk::vector<ktk::string>&;
		using console_command_signature_function_t = bool(
			console_command_args_t);
		using console_command_t =
			ktk::function<console_command_signature_function_t>;
	} // namespace ktk

	namespace Core
	{
		constexpr const ktk::tchar* kConsoleCommandArg_Editor =
			KOTEK_TEXT("--editor");
		constexpr const ktk::tchar* kConsoleCommandArg_Width =
			KOTEK_TEXT("--width");
		constexpr const ktk::tchar* kConsoleCommandArg_Height =
			KOTEK_TEXT("--height");

		constexpr const ktk::tchar* kConsoleCommandArg_Render_OpenGL =
			KOTEK_TEXT("--render_gl");
		constexpr const ktk::tchar* kConsoleCommandArg_Render_Vulkan =
			KOTEK_TEXT("--render_vk");

		constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX9 =
			KOTEK_TEXT("--render_dx_9");
		constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX11 =
			KOTEK_TEXT("--render_dx_11");
		constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX12 =
			KOTEK_TEXT("--render_dx_12");

		enum class ktkConsoleCommandIndex : ktk::enum_base_t
		{
			// (int width, int height)
			kConsoleCommand_Resize,

			kConsoleCommand_App_Close,
			kConsoleCommand_App_Hide,
			kConsoleCommand_App_Show,
			kConsoleCommand_Render_UploadAllResourcesToGPU
		};

		class ktkConsole : public ktkIConsole
		{
		public:
			ktkConsole(void);
			~ktkConsole(void);

			void Initialize(void) override;
			void Shutdown(void) override;

			void RegisterCommand(ktkConsoleCommandIndex id,
				const ktk::console_command_t& p_function) noexcept;
			void PushCommand(ktkConsoleCommandIndex id,
				ktk::console_command_args_t data = {}) noexcept;
			void Flush(void);

			void Execute(ktkConsoleCommandIndex id,
				ktk::console_command_args_t data = {}) noexcept;

		private:
			// TODO: make thread safe queue
			ktk::queue<
				ktk::pair<ktk::vector<ktk::string>, ktk::console_command_t>>
				m_buffer;
			ktk::unordered_map<ktkConsoleCommandIndex, ktk::console_command_t>
				m_storage;
		};
	} // namespace Core
} // namespace Kotek