#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

namespace Kotek
{
	namespace Core
	{
		class ktkEngineConfig : public ktkIEngineConfig
		{
		public:
			ktkEngineConfig(void);
			~ktkEngineConfig(void);

			void Initialize(void) override;
			void Shutdown(void) override;

			bool IsFeatureEnabled(eEngineFeature id) const noexcept override;
			void SetFeatureStatus(
				eEngineFeature id, bool status) noexcept override;
			ktk::string GetRenderName(void) const noexcept override;
			eEngineFeature GetRenderFeature(void) const noexcept override;
			bool IsCurrentRenderLegacy(void) const noexcept override;
			bool IsCurrentRenderModern(void) const noexcept override;
			int GetARGC(void) const noexcept override;
			char** GetARGV(void) const noexcept override;
			bool IsContainsConsoleCommandLineArgument(
				const ktk::string& your_argument) const noexcept override;
			bool IsApplicationWorking(void) const noexcept override;
			void SetApplicationWorking(bool status) noexcept override;

		private:
			bool IsFeatureRender(eEngineFeature feature) const noexcept;

		private:
			int m_argc;
			char** m_argv;
			ktk::vector<ktk::string> m_parsed_command_line_arguments;
			ktk::unordered_map<eEngineFeature, bool> m_engine_flags;
			ktk::mt::atomic<bool> m_is_running;
		};
	} // namespace Core
} // namespace Kotek