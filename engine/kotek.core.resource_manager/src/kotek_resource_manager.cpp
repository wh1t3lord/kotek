#include "../include/kotek_resource_manager.h"
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

namespace Kotek
{
	namespace Core
	{
		ktkResourceManager::ktkResourceManager(void) :
			m_p_manager_resource_loader{}, m_p_manager_render_resource{},
			m_p_manager_main{}
		{
		}

		ktkResourceManager::~ktkResourceManager(void) {}

		void ktkResourceManager::Initialize(void) {}

		void ktkResourceManager::Shutdown(void) {}

		void ktkResourceManager::Set_ResourceLoader(
			ktkIResourceLoader* p_instance) noexcept
		{
			this->m_p_manager_resource_loader = p_instance;
		}

		void ktkResourceManager::Set_RenderResourceManager(
			ktkIRenderResourceManager* p_instance) noexcept
		{
			KOTEK_ASSERT(!this->m_p_manager_render_resource,
				"you can't initialize this twice! Some Renderer didn't set "
				"this to nullptr");

			this->m_p_manager_render_resource = p_instance;
		}

		ktkIResourceLoader* ktkResourceManager::Get_ResourceLoader(
			void) const noexcept
		{
			return this->m_p_manager_resource_loader;
		}

		ktkIRenderResourceManager*
		ktkResourceManager::Get_RenderResourceManager(void) const noexcept
		{
			return nullptr;
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

		void ktkResourceManager::Update_WorkerQueue(void) noexcept {}

		ktk::any ktkResourceManager::Load_Resource(
			const ktkLoadingRequest& request)
		{
			return ktk::any();
		}
	} // namespace Core
} // namespace Kotek