#pragma once

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

		protected:
			ktk::any Load_Resource(const ktkLoadingRequest& request) override;

		private:
			ktkIResourceLoader* m_p_manager_resource_loader;
		};
	} // namespace Core
} // namespace Kotek