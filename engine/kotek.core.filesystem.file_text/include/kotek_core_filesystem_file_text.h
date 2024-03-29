#pragma once

#include "kotek_file_text.h"
#include "kotek_loader_file_text.h"
#include "kotek_saver_file_text.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_FileSystem_File_Text(ktkMainManager* p_manager);
bool SerializeModule_Core_FileSystem_File_Text(ktkMainManager* p_manager);
bool DeserializeModule_Core_FileSystem_File_Text(ktkMainManager* p_manager);
bool ShutdownModule_Core_FileSystem_File_Text(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK