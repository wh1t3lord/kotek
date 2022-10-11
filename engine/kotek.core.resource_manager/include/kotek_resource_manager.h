#pragma once

#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkResourceManager : public ktkIResourceManager
{
public:
	ktkResourceManager(void);
	~ktkResourceManager(void);

	void Initialize(void);
	void Shutdown(void);

	// TODO: implement for saver too!
	void Set_ResourceLoader(
		ktkIResourceLoaderManager* p_instance) noexcept override;

	void Set_RenderResourceManager(
		ktkIRenderResourceManager* p_instance) noexcept override;

	ktkIResourceLoaderManager* Get_ResourceLoader(void) const noexcept override;

	ktkIRenderResourceManager* Get_RenderResourceManager(
		void) const noexcept override;

	// TODO: does we really need to have this method for storing main
	// manager? if so just delete todo otherwise delete methods and todo
	void Set_MainManager(ktkMainManager* p_instance) noexcept override;

	ktkMainManager* Get_MainManager(void) const noexcept override;

	void Update_WorkerQueue(void) noexcept override;

protected:
	ktk::any Load_Resource(const ktkLoadingRequest& request) override;

private:
	ktkIResourceLoaderManager* m_p_manager_resource_loader;
	ktkIRenderResourceManager* m_p_manager_render_resource;
	ktkMainManager* m_p_manager_main;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK