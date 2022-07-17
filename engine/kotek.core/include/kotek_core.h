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
#include <kotek.core.window/include/kotek_core_window.h>
#include <kotek.core.log/include/kotek_core_log.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.resource_manager/include/kotek_core_resource_manager.h>
#include <kotek.core.input/include/kotek_core_input.h>
#include <kotek.core.utility/include/kotek_core_utility.h>
#include <kotek.core.ecs/include/kotek_core_ecs.h>
#include <kotek.core.engine_config/include/kotek_core_engine_config.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core(ktkMainManager* p_manager);
		bool SerializeModule_Core(ktkMainManager* p_manager);
		bool DeserializeModule_Core(ktkMainManager* p_manager);
		bool ShutdownModule_Core(ktkMainManager* p_manager);

		void RegisterTests_String_ForModule_Core(void);
		void RegisterTests_Filesystem_ForModule_Core(void);
		void RegisterTests_Math_ForModule_Core(void);
	} // namespace Core
} // namespace Kotek
