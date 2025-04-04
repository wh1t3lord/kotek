#include "../include/kotek_core_containers.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_Containers(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [containers]");
		p_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_Core_Containers_Any(p_manager);
	InitializeModule_Core_Containers_Array(p_manager);
	InitializeModule_Core_Containers_Deque(p_manager);
	InitializeModule_Core_Containers_DLL(p_manager);
	InitializeModule_Core_Containers_FileSystem(p_manager);
	InitializeModule_Core_Containers_Function(p_manager);
	InitializeModule_Core_Containers_Hash(p_manager);
	InitializeModule_Core_Containers_IO(p_manager);
	InitializeModule_Core_Containers_JSON(p_manager);
	InitializeModule_Core_Containers_Map(p_manager);
	InitializeModule_Core_Containers_Microsoft(p_manager);
	InitializeModule_Core_Containers_MultiThreading(p_manager);
	InitializeModule_Core_Containers_Pair(p_manager);
	InitializeModule_Core_Containers_Queue(p_manager);
	InitializeModule_Core_Containers_Shared_Ptr(p_manager);
	InitializeModule_Core_Containers_String(p_manager);
	InitializeModule_Core_Containers_Unique_Ptr(p_manager);
	InitializeModule_Core_Containers_Unordered_Map(p_manager);
	InitializeModule_Core_Containers_Unordered_Set(p_manager);
	InitializeModule_Core_Containers_Variant(p_manager);
	InitializeModule_Core_Containers_Vector(p_manager);
	InitializeModule_Core_Containers_List(p_manager);

	return true;
}

bool SerializeModule_Core_Containers(ktkMainManager* p_manager)
{
	SerializeModule_Core_Containers_Any(p_manager);
	SerializeModule_Core_Containers_Array(p_manager);
	SerializeModule_Core_Containers_Deque(p_manager);
	SerializeModule_Core_Containers_DLL(p_manager);
	SerializeModule_Core_Containers_FileSystem_Path(p_manager);
	SerializeModule_Core_Containers_Function(p_manager);
	SerializeModule_Core_Containers_Hash(p_manager);
	SerializeModule_Core_Containers_IO(p_manager);
	SerializeModule_Core_Containers_JSON(p_manager);
	SerializeModule_Core_Containers_Map(p_manager);
	SerializeModule_Core_Containers_Microsoft(p_manager);
	SerializeModule_Core_Containers_MultiThreading(p_manager);
	SerializeModule_Core_Containers_Pair(p_manager);
	SerializeModule_Core_Containers_Queue(p_manager);
	SerializeModule_Core_Containers_Shared_Ptr(p_manager);
	SerializeModule_Core_Containers_String(p_manager);
	SerializeModule_Core_Containers_Unique_Ptr(p_manager);
	SerializeModule_Core_Containers_Unordered_Map(p_manager);
	SerializeModule_Core_Containers_Unordered_Set(p_manager);
	SerializeModule_Core_Containers_Variant(p_manager);
	SerializeModule_Core_Containers_Vector(p_manager);
	SerializeModule_Core_Containers_List(p_manager);

	return true;
}

bool DeserializeModule_Core_Containers(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Containers_Any(p_manager);
	DeserializeModule_Core_Containers_Array(p_manager);
	DeserializeModule_Core_Containers_Deque(p_manager);
	DeserializeModule_Core_Containers_DLL(p_manager);
	DeserializeModule_Core_Containers_FileSystem_Path(p_manager);
	DeserializeModule_Core_Containers_Function(p_manager);
	DeserializeModule_Core_Containers_Hash(p_manager);
	DeserializeModule_Core_Containers_IO(p_manager);
	DeserializeModule_Core_Containers_JSON(p_manager);
	DeserializeModule_Core_Containers_Map(p_manager);
	DeserializeModule_Core_Containers_Microsoft(p_manager);
	DeserializeModule_Core_Containers_MultiThreading(p_manager);
	DeserializeModule_Core_Containers_Pair(p_manager);
	DeserializeModule_Core_Containers_Queue(p_manager);
	DeserializeModule_Core_Containers_Shared_Ptr(p_manager);
	DeserializeModule_Core_Containers_String(p_manager);
	DeserializeModule_Core_Containers_Unique_Ptr(p_manager);
	DeserializeModule_Core_Containers_Unordered_Map(p_manager);
	DeserializeModule_Core_Containers_Unordered_Set(p_manager);
	DeserializeModule_Core_Containers_Variant(p_manager);
	DeserializeModule_Core_Containers_Vector(p_manager);
	DeserializeModule_Core_Containers_List(p_manager);

	return true;
}

bool ShutdownModule_Core_Containers(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Containers_Any(p_manager);
	ShutdownModule_Core_Containers_Array(p_manager);
	ShutdownModule_Core_Containers_Deque(p_manager);
	ShutdownModule_Core_Containers_DLL(p_manager);
	ShutdownModule_Core_Containers_FileSystem_Path(p_manager);
	ShutdownModule_Core_Containers_Function(p_manager);
	ShutdownModule_Core_Containers_Hash(p_manager);
	ShutdownModule_Core_Containers_IO(p_manager);
	ShutdownModule_Core_Containers_JSON(p_manager);
	ShutdownModule_Core_Containers_Map(p_manager);
	ShutdownModule_Core_Containers_Microsoft(p_manager);
	ShutdownModule_Core_Containers_MultiThreading(p_manager);
	ShutdownModule_Core_Containers_Pair(p_manager);
	ShutdownModule_Core_Containers_Queue(p_manager);
	ShutdownModule_Core_Containers_Shared_Ptr(p_manager);
	ShutdownModule_Core_Containers_String(p_manager);
	ShutdownModule_Core_Containers_Unique_Ptr(p_manager);
	ShutdownModule_Core_Containers_Unordered_Map(p_manager);
	ShutdownModule_Core_Containers_Unordered_Set(p_manager);
	ShutdownModule_Core_Containers_Variant(p_manager);
	ShutdownModule_Core_Containers_Vector(p_manager);
	ShutdownModule_Core_Containers_List(p_manager);

	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK