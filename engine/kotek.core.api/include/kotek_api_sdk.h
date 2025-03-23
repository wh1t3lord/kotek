#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KTK

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkIResourceManager;

class ktkISDKRedoUndo
{
public:
	virtual ~ktkISDKRedoUndo(void) {}

	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual const char* GetName() = 0;
	virtual ktk::uint32_t GetEntityID(void) const noexcept { return -1; }
	virtual void SetEntityID(ktk::uint32_t id) noexcept {}
	virtual ktk::enum_base_t GetCommandType() noexcept = 0;

	virtual ktk::size_t Serialize(kun_ktk cfstream* p_file,
		Kotek::Core::ktkIResourceManager* p_resource_manager) noexcept = 0;
};

/// @brief manager stores registered command that will be accessed through
class ktkISDKCommandHistoryManager
{
public:
	virtual ~ktkISDKCommandHistoryManager(void) {}

	/// @brief adds and executes
	/// @param p_command
	virtual void ExecuteCommand(ktkISDKRedoUndo* p_command) = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK