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

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK
using console_command_base_t = ktk::vector<
	std::variant<ktk::int64_t, ktk::int32_t, ktk::int16_t, ktk::int8_t,
		ktk::uint64_t, ktk::uint32_t, ktk::uint16_t, ktk::uint8_t, ktk::cstring,
		Kotek::Core::ktkLoadingRequest, ktk::shared_ptr<ktk::any>>>;
using console_command_args_t = const console_command_base_t&;
using console_command_signature_function_t = bool(console_command_args_t);
using console_command_t = ktk::function<console_command_signature_function_t>;
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_CORE
class ktkConsole : public ktkIConsole
{
public:
	ktkConsole(void);
	~ktkConsole(void);

	void Initialize(void) override;
	void Shutdown(void) override;

	void RegisterCommand(
		ktk::enum_base_t id, const ktk::console_command_t& p_function) noexcept;
	void PushCommand(
		ktk::enum_base_t id, ktk::console_command_args_t data = {}) noexcept;
	void Flush(void);

	void Execute(
		ktk::enum_base_t id, ktk::console_command_args_t data = {}) noexcept;

private:
	// TODO: make thread safe queue
	ktk::queue<ktk::pair<ktk::console_command_base_t, ktk::console_command_t>>
		m_buffer;
	ktk_unordered_map<ktk::enum_base_t, ktk::console_command_t,
		KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT>
		m_storage;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
