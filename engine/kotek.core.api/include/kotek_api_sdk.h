#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkISDKRedoUndo
{
public:
	virtual ~ktkISDKRedoUndo(void) {}

	virtual void Execute() = 0;
	virtual void Undo() = 0;
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