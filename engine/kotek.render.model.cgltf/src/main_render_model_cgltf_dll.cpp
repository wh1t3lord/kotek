#include "../include/kotek_render_model_cgltf.h"
#include "../include/kotek_format_analyzer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
bool InitializeModule_Render_Model_CGLTF(Core::ktkMainManager* p_main_manager)
{
	KOTEK_ASSERT(p_main_manager->GetResourceManager(),
		"you must initialize resource manager");

	KOTEK_ASSERT(p_main_manager->GetResourceManager()->Get_ResourceLoader(),
		"you must initialize resource loader");

	ktkFormatAnalyzer_CGLTF* p_format_analyzer = new ktkFormatAnalyzer_CGLTF();

	ktkLoaderModel_CGLTF* p_loader =
		new ktkLoaderModel_CGLTF(p_main_manager->GetFileSystem());

	p_loader->Set_FormatAnalyzer(p_format_analyzer);

	p_main_manager->GetResourceManager()->Get_ResourceLoader()->Set_Loader(
		Core::eResourceLoadingType::kModel, p_loader);

	return true;
}

bool ShutdownModule_Render_Model_CGLTF(Core::ktkMainManager* p_main_manager)
{
	KOTEK_ASSERT(p_main_manager->GetResourceManager(),
		"you must initialize resource manager");

	KOTEK_ASSERT(p_main_manager->GetResourceManager()->Get_ResourceLoader(),
		"you must initialize resource loader");

	auto* p_loader = dynamic_cast<ktkLoaderModel_CGLTF*>(
		p_main_manager->GetResourceManager()->Get_ResourceLoader()->Get_Loader(
			Core::eResourceLoadingType::kModel));

	KOTEK_ASSERT(p_loader != nullptr,
		"bad cast to ktkLoaderModel_CGLTF*, you have something "
		"different");

	auto* p_format_analyzer =
		dynamic_cast<ktkFormatAnalyzer_CGLTF*>(p_loader->Get_FormatAnalyzer());

	KOTEK_ASSERT(p_format_analyzer != nullptr,
		"bad cast to ktkFormatAnalyzer_CGLTF*, you have something "
		"different");

	delete p_format_analyzer;
	delete p_loader;

	return true;
}
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK