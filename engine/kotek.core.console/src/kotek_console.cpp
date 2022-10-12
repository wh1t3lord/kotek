#include "../include/kotek_console.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkConsole::ktkConsole(void) {}

ktkConsole::~ktkConsole(void) {}

void ktkConsole::Initialize(void)
{
	KOTEK_MESSAGE("console is initialized!");
}

void ktkConsole::RegisterCommand(
	eConsoleCommandIndex id, const ktk::console_command_t& p_function) noexcept
{
	if (this->m_storage.find(id) != this->m_storage.end())
	{
		KOTEK_MESSAGE("you can't add command[{}] which is existed in storage",
			static_cast<ktk::enum_base_t>(id));
		return;
	}

	if (p_function == nullptr)
	{
		KOTEK_MESSAGE("can't register and invalid command");
		return;
	}

	this->m_storage[id] = p_function;
}

void ktkConsole::PushCommand(
	eConsoleCommandIndex id, ktk::console_command_args_t data) noexcept
{
	if (this->m_storage.find(id) == this->m_storage.end())
	{
		KOTEK_MESSAGE("can't find command by id: [{}]",
			static_cast<ktk::enum_base_t>(id));
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

void ktkConsole::Execute(
	eConsoleCommandIndex id, ktk::console_command_args_t data) noexcept
{
	if (this->m_storage.find(id) == this->m_storage.end())
	{
		KOTEK_MESSAGE(
			"can't find command by id [{}]", static_cast<ktk::enum_base_t>(id));
		return;
	}

	bool status = this->m_storage.at(id)(data);

	KOTEK_ASSERT(status, "command was issued not correctly");
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK