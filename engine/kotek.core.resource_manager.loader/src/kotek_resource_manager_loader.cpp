#include "../include/kotek_resource_manager_loader.h"

namespace Kotek
{
	namespace Core
	{
		ktkResourceLoaderManager::ktkResourceLoaderManager(void) {}

		ktkResourceLoaderManager::~ktkResourceLoaderManager(void) {}

		void ktkResourceLoaderManager::Initialize(void) {}

		void ktkResourceLoaderManager::Shutdown(void) {}

		eResourceLoadingType
		ktkResourceLoaderManager::DetectResourceTypeByFileFormat(
			const ktk::filesystem::path& path) noexcept
		{
			return eResourceLoadingType();
		}

		ktk::any ktkResourceLoaderManager::Load_Text(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Texture(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Model(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Sound(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Video(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_CPlusPlusLibrary(
			const ktk::filesystem::path& path) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Text(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Texture(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Model(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Sound(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return ktk::any();
		}

		ktk::any ktkResourceLoaderManager::Load_Video(
			const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			return ktk::any();
		}
	} // namespace Core
} // namespace Kotek