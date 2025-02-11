#include "../include/kotek_console.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkConsole::ktkConsole(void) {}

ktkConsole::~ktkConsole(void)
{
	KOTEK_ASSERT(
		this->m_storage.empty(), "you forgot to deallocate the storage!");
}

void ktkConsole::Initialize(
	const console_user_callback_enum_translation_t& translating_callback)
{
	KOTEK_MESSAGE("console is initialized!");

	if (!translating_callback)
	{
		KOTEK_MESSAGE_WARNING(
			"you didn't pass or passed invalid callback for translating enums. "
			"Calling functions from console is not accessible!");
	}

	this->m_user_callback_enum_translation = translating_callback;
}

void ktkConsole::Flush(void)
{
	while (this->m_buffer.empty() == false)
	{
		auto& pair = this->m_buffer.front();
		auto& argument = pair.first;
		auto& p_callback = pair.second;

		KOTEK_ASSERT(p_callback, "must be valid allocated pointer!");

		bool status = (*p_callback)(argument);

		KOTEK_ASSERT(status, "invalid calling for console command");

		this->m_buffer.pop();
	}
}

bool ktkConsole::Parse_ConsoleCommandAsString(
	ParsingData& result, const char* p_text)
{
	KOTEK_ASSERT(p_text, "must be valid string!");

	bool status = true;

	if (p_text)
	{
		ktk_cstring_view input(p_text);

		auto is_ws = [](char c) { return c == ' ' || c == '\t' || c == '\n'; };

		if (input.empty() == false)
		{
			// Find the opening parenthesis.
			auto openParen = input.find('(');
			if (openParen == std::string_view::npos)
			{
				KOTEK_MESSAGE_WARNING(
					"failed to parse function calling: Missing '(' in function "
					"call. Your input string: [{}]",
					p_text);
				status = false;
				return status;
			}

			// Extract and trim the function name.
			auto funcName = input.substr(0, openParen);
			while (!funcName.empty() && is_ws(funcName.front()))
				funcName.remove_prefix(1);
			while (!funcName.empty() && is_ws(funcName.back()))
				funcName.remove_suffix(1);
			result.function_name = funcName;

			// Find the closing parenthesis.
			auto closeParen = input.rfind(')');
			if (closeParen == std::string_view::npos || closeParen < openParen)
			{
				KOTEK_MESSAGE_WARNING(
					"failed to parse function calling: Missing ')' in function "
					"call. Your input string: [{}]",
					p_text);

				status = false;
				return status;
			}
			// Get the arguments string.
			auto argsStr =
				input.substr(openParen + 1, closeParen - openParen - 1);

			// Parse the arguments.
			std::size_t start = 0;
			while (start < argsStr.size())
			{
				while (start < argsStr.size() && is_ws(argsStr[start]))
					++start;
				if (start >= argsStr.size())
					break;

				std::size_t end = start;
				bool inQuotes = false;
				while (end < argsStr.size())
				{
					char c = argsStr[end];
					if (c == '"')
						inQuotes = !inQuotes;
					else if (c == ',' && !inQuotes)
						break;
					++end;
				}
				auto token = argsStr.substr(start, end - start);
				while (!token.empty() && is_ws(token.front()))
					token.remove_prefix(1);
				while (!token.empty() && is_ws(token.back()))
					token.remove_suffix(1);

				result.args.push_back(token);
				start = end + 1;
			}
		}
		else
		{
			status = false;
		}
	}
	else
	{
		status = false;
	}

	return status;
}

void ktkConsole::Shutdown(void)
{
	for (auto& pair : this->m_storage)
	{
		if (pair.second)
		{
			delete pair.second;
		}
	}

	this->m_storage.clear();
}

void ktkConsole::Push_Command(
	ktk::enum_base_t id, ktk::console_command_args_t data) noexcept
{
	if (this->m_storage.find(id) == this->m_storage.end())
	{
		KOTEK_MESSAGE("can't find command by id: [{}]",
			static_cast<ktk::enum_base_t>(id));
		return;
	}

	this->m_buffer.push({data, this->m_storage.at(id)});

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("command pushed: {}", id);
#endif
}

void ktkConsole::Execute_Command(
	ktk::enum_base_t id, ktk::console_command_args_t data) noexcept
{
	if (this->m_storage.find(id) == this->m_storage.end())
	{
		KOTEK_MESSAGE(
			"can't find command by id [{}]", static_cast<ktk::enum_base_t>(id));
		return;
	}

	bool status = (*this->m_storage.at(id))(data);

	KOTEK_ASSERT(status, "command was issued not correctly");
}

bool ktkConsole::Push_Command(const char* p_text)
{
	bool successful{};
	if (!this->m_user_callback_enum_translation)
		return successful;

	ParsingData data;

	successful = this->Parse_ConsoleCommandAsString(data, p_text);

	if (successful)
	{
		eConsoleCommandIndex function_id = static_cast<eConsoleCommandIndex>(
			this->m_user_callback_enum_translation(data.function_name.data()));

		successful = static_cast<int>(function_id) != -1;

		if (successful)
		{
			KOTEK_ASSERT(this->m_storage.find(static_cast<kun_ktk enum_base_t>(
							 function_id)) != this->m_storage.end(),
				"can't be!");

			if (this->m_storage.find(static_cast<kun_ktk enum_base_t>(
					function_id)) != this->m_storage.end())
			{
				auto p_callback = this->m_storage.at(
					static_cast<kun_ktk enum_base_t>(function_id));

				KOTEK_ASSERT(
					p_callback, "invalid pointer can't be, memory corruption?");

				if (p_callback)
				{
					auto args_variant = p_callback->Parse(data.args);

					this->Push_Command(
						static_cast<kun_ktk enum_base_t>(function_id),
						args_variant);
				}
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"your translation function returned supposedly correct "
					"value but there's no a such function in storage so it "
					"means you didn't register or some internal error? Key: {} "
					"Function Name: {}",
					static_cast<kun_ktk enum_base_t>(function_id),
					data.function_name);
			}
		}
		else
		{
			KOTEK_MESSAGE_WARNING(
				"you didn't register function name for console translation: {}",
				data.function_name);
		}
	}

	return successful;
}

bool ktkConsole::Execute_Command(const char* p_text)
{
	bool successful{};
	if (!this->m_user_callback_enum_translation)
		return successful;

	ParsingData data;

	successful = this->Parse_ConsoleCommandAsString(data, p_text);

	if (successful)
	{
	}

	return successful;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK