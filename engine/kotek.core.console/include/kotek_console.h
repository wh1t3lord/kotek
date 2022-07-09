#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>
#include <kotek.core.containers.pair/include/kotek_core_containers_pair.h>
#include <kotek.core.containers.function/include/kotek_core_containers_function.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

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
