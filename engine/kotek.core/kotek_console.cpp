#include "kotek_console.h"

namespace Kotek
{
	namespace Core
	{
		ktkConsole::ktkConsole(void) {}

		ktkConsole::~ktkConsole(void) {}

		void ktkConsole::Initialize(void)
		{
			KOTEK_MESSAGE("console is initialized!");
		}

		void ktkConsole::RegisterCommand(ktkConsoleCommandIndex id,
			const ktk::console_command_t& p_function) noexcept
		{
			if (this->m_storage.find(id) != this->m_storage.end())
			{
				KOTEK_MESSAGE(
					"you can't add command[{}] which is existed in storage",
					id);
				return;
			}

			if (p_function == nullptr)
			{
				KOTEK_MESSAGE("can't register and invalid command");
				return;
			}

			this->m_storage[id] = p_function;
		}

		void ktkConsole::PushCommand(ktkConsoleCommandIndex id,
			ktk::console_command_args_t data) noexcept
		{
			if (this->m_storage.find(id) == this->m_storage.end())
			{
				KOTEK_MESSAGE("can't find command by id: [{}]", id);
				return;
			}

			this->m_buffer.push({data, this->m_storage.at(id)});
		}

		void ktkConsole::Flush(void)
		{
			while (this->m_buffer.empty() == false)
			{
				auto& pair = this->m_buffer.front();
				auto& argument = pair.first;
				auto& callback = pair.second;

				bool status = callback(argument);

				KOTEK_ASSERT(status, "invalid calling for console command");

				this->m_buffer.pop();
			}
		}

		void ktkConsole::Shutdown(void) {}

		void ktkConsole::Execute(ktkConsoleCommandIndex id,
			ktk::console_command_args_t data) noexcept
		{
			if (this->m_storage.find(id) == this->m_storage.end())
			{
				KOTEK_MESSAGE("can't find command by id [{}]", id);
				return;
			}

			bool status = this->m_storage.at(id)(data);

			KOTEK_ASSERT(status, "command was issued not correctly");
		}
	} // namespace Core
} // namespace Kotek