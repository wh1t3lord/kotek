#include <cstdio>
#pragma once

#include <cstdio>
#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>
#include <kotek.core.containers.pair/include/kotek_core_containers_pair.h>
#include <kotek.core.containers.function/include/kotek_core_containers_function.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.utility\include\kotek_core_utility.h>
#include <kotek.core.ecs/include/kotek_core_ecs.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

static_assert(
	is_in_variant_v<
		kun_ktk enum_base_t,
		console_command_variant_t>,
	"you didn't register this type in variant"
);

static_assert(
	is_in_variant_v<
		kun_ktk entity_t,
		console_command_variant_t>,
	"you didn't register this type in variant"
);

using console_command_t =
	kun_ktk ivfunction<console_command_variant_t, bool>*;

KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_CORE
class ktkConsole : public ktkIConsole
{
	struct ParsingData
	{
		// TODO: make preprocessor for that please
		// KOTEK_DEF_CONSOLE_FUNCTION_MAX_LENGTH_NAME
		char function_name[32]{};
		ktk_vector<
			std::string_view,
			KOTEK_DEF_CONSOLE_FUNCTION_MAX_ARGUMENT_COUNT>
			args;
	};

public:
	ktkConsole(void);
	~ktkConsole(void);

	void
	Initialize(const console_user_callback_enum_translation_t&
	               translating_callback) override;
	void Shutdown(void) override;

	template <typename Func>
	void Register_Command(
		Func p_function, kun_ktk enum_base_t id
	) noexcept
	{
		if (this->m_storage.find(id) != this->m_storage.end())
		{
			KOTEK_MESSAGE(
				"you can't add command[{}] which is existed in "
				"storage",
				static_cast<ktk::enum_base_t>(id)
			);
			return;
		}

		this->m_storage[id] = kun_ktk make_vfunction_ptr<
			kun_ktk console_command_variant_t>(p_function);

#ifdef KOTEK_DEBUG
		if (this->m_storage.at(id))
			this->m_storage[id]->Set_Data(id);
#endif
	}

	void Push_Command(
		ktk::enum_base_t id,
		ktk::console_command_args_t data = {}
	) noexcept override;
	void Execute_Command(
		ktk::enum_base_t id,
		ktk::console_command_args_t data = {}
	) noexcept override;

	bool Push_Command(const char* p_text) override;
	bool Execute_Command(const char* p_text) override;

	void Flush(void) override;

private:
	bool Parse_ConsoleCommandAsString(
		ParsingData& data, const char* p_text
	);

private:
	console_user_callback_enum_translation_t
		m_user_callback_enum_translation;
	// TODO: make thread safe queue
	ktk_queue<
		ktk::pair<
			ktk::console_command_base_t,
			ktk::console_command_t>,
		KOTEK_DEF_CONSOLE_MAX_QUEUE_SIZE>
		m_buffer;
	ktk_unordered_map<
		ktk::enum_base_t,
		ktk::console_command_t,
		KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT>
		m_storage;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
