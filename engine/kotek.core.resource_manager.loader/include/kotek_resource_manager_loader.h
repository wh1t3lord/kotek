#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>

namespace Kotek
{
	namespace Core
	{
		class ktkResourceLoaderManager : public ktkIResourceLoaderManager
		{
		public:
			ktkResourceLoaderManager(void);
			~ktkResourceLoaderManager(void);

			void Initialize(ktkIFileSystem* p_manager_filesystem) override;
			void Shutdown(void) override;

			void Set_Loader(eResourceLoadingType resource_type,
				ktkIResourceLoader* p_loader) override;

			ktkIResourceLoader* Get_Loader(
				eResourceLoadingType resource_type) const noexcept override;

			ktk::any Load_Text(
				const ktk::filesystem::path& path) noexcept override;
			ktk::any Load_Texture(
				const ktk::filesystem::path& path) noexcept override;
			ktk::any Load_Model(
				const ktk::filesystem::path& path) noexcept override;
			ktk::any Load_Sound(
				const ktk::filesystem::path& path) noexcept override;
			ktk::any Load_Video(
				const ktk::filesystem::path& path) noexcept override;
			ktk::any Load_CPlusPlusLibrary(
				const ktk::filesystem::path& path) noexcept override;

			bool Load_Text(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			bool Load_Texture(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			bool Load_Model(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			bool Load_Sound(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			bool Load_Video(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;

		protected:
			eResourceLoadingType DetectResourceTypeByFileFormat(
				const ktk::filesystem::path& path) noexcept override;

			ktk::unordered_map<eResourceLoadingType, ktkIResourceLoader*>
				m_loaders;
		};
	} // namespace Core
} // namespace Kotek