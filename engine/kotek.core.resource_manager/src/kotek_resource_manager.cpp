#include "../include/kotek_resource_manager.h"

namespace Kotek
{
	namespace Core
	{
		ktkResourceManager::ktkResourceManager(void) :
			m_p_manager_resource_loader{}
		{
		}

		ktkResourceManager::~ktkResourceManager(void) 
		{
		}

		void ktkResourceManager::Initialize(void) {}

		void ktkResourceManager::Shutdown(void) {}

		void ktkResourceManager::Set_ResourceLoader(
			ktkIResourceLoader* p_instance) noexcept
		{
			this->m_p_manager_resource_loader = p_instance;
		}

		ktkIResourceLoader* ktkResourceManager::Get_ResourceLoader(
			void) const noexcept
		{
			return this->m_p_manager_resource_loader;
		}

		void ktkResourceManager::Set_MainManager(
			ktkMainManager* p_instance) noexcept
		{
			this->m_p_manager_main = p_instance;
		}

		ktkMainManager* ktkResourceManager::Get_MainManager(void) const noexcept
		{
			return this->m_p_manager_main;
		}

		ktk::any ktkResourceManager::Load_Resource(
			const ktkLoadingRequest& request)
		{
			return ktk::any();
		}
	} // namespace Core
} // namespace Kotek