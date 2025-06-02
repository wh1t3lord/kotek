#pragma once

#include <kotek.core.enum/include/kotek_core_enum.h>
#include <kotek.core.defines/include/kotek_core_defines.h>
#include <kotek.core.math/include/kotek_core_math.h>
#include <kotek.core.memory/include/kotek_core_memory.h>
#include <kotek.core.casting/include/kotek_core_casting.h>
#include <kotek.core.console/include/kotek_core_console.h>
#include <kotek.core.constants/include/kotek_core_constants.h>
#include <kotek.core.containers/include/kotek_core_containers.h>
#include <kotek.core.filesystem/include/kotek_core_filesystem.h>
#include <kotek.core.format/include/kotek_core_format.h>
#include <kotek.core.profilers/include/kotek_core_profilers.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.window_manager/include/kotek_core_window_manager.h>
#include <kotek.core.log/include/kotek_core_log.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.resource_manager/include/kotek_core_resource_manager.h>
#include <kotek.core.input/include/kotek_core_input.h>
#include <kotek.core.utility/include/kotek_core_utility.h>
#include <kotek.core.ecs/include/kotek_core_ecs.h>
#include <kotek.core.engine_config/include/kotek_core_engine_config.h>

#include "kotek_json_casting_math_matrix.h"
#include "kotek_json_casting_math_vector.h"
#include "kotek_json_casting_std_vector.h"
#include "kotek_json_casting_string.h"
#include "kotek_json_casting_other.h"

#ifdef KOTEK_NAMESPACE_KOTEK
namespace KOTEK_NAMESPACE_NAME_LOWERED = KN_KOTEK;
#endif

#ifdef KOTEK_NAMESPACE_CORE
KOTEK_BEGIN_NAMESPACE_KOTEK
namespace KOTEK_NAMESPACE_NAME_CORE_LOWERED = KUN_KOTEK KN_CORE;
KOTEK_END_NAMESPACE_KOTEK
#endif

#ifdef KOTEK_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_KOTEK
namespace KOTEK_NAMESPACE_NAME_RENDER_LOWERED = KUN_KOTEK KN_RENDER;
KOTEK_END_NAMESPACE_KOTEK
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core(ktkMainManager* p_manager);
bool SerializeModule_Core(ktkMainManager* p_manager);
bool DeserializeModule_Core(ktkMainManager* p_manager);
bool ShutdownModule_Core(ktkMainManager* p_manager);

void RegisterTests_String_ForModule_Containers_String(void);
void RegisterTests_Filesystem_ForModule_Core(void);
void RegisterTests_Math_ForModule_Core(void);
void RegisterTests_Translation_ForModule_Enum_Core(void);
void RegisterTests_Json_ForModule_Core(void);
void RegisterTests_String_ForModule_Core(void);
void RegisterTests_Input_ForModule_Core(void);
void RegisterTests_Utility_ForModule_Core(void);
void RegisterAllTests(void);

KOTEK_END_NAMESPACE_CORE

KOTEK_END_NAMESPACE_KOTEK