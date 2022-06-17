#pragma once

#include <kotek.core.api/include/kotek_api.h>

namespace Kotek
{
	namespace Core
	{
		class ktkResourceManager : public ktkIResourceManager
		{
		public:
			ktkResourceManager(void);
			~ktkResourceManager(void);

			void Initialize(void);
			void Shutdown(void);

			// TODO: implement for saver too!
			void Set_ResourceLoader(
				ktkIResourceLoader* p_instance) noexcept override;

			ktkIResourceLoader* Get_ResourceLoader(
				void) const noexcept override;

			// TODO: does we really need to have this method for storing main
			// manager? if so just delete todo otherwise delete methods and todo
			void Set_MainManager(ktkMainManager* p_instance) noexcept override;

			ktkMainManager* Get_MainManager(void) const noexcept override;

		protected:
			ktk::any Load_Resource(const ktkLoadingRequest& request) override;

		private:
			ktkIResourceLoader* m_p_manager_resource_loader;
			ktkMainManager* m_p_manager_main;
		};
	} // namespace Core
} // namespace Kotek