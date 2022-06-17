#pragma once

#include <kotek.core.api/include/kotek_api.h>

namespace Kotek
{
	namespace Core
	{
		class ktkResourceLoaderManager : public ktkIResourceLoader
		{
		public:
			ktkResourceLoaderManager(void);
			~ktkResourceLoaderManager(void);

			void Initialize(void) override;
			void Shutdown(void) override;

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

			ktk::any Load_Text(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			ktk::any Load_Texture(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			ktk::any Load_Model(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			ktk::any Load_Sound(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;
			ktk::any Load_Video(const ktk::filesystem::path& path,
				ktk::any object_from_construct) noexcept override;

		protected:
			eResourceLoadingType DetectResourceTypeByFileFormat(
				const ktk::filesystem::path& path) noexcept override;
		};
	} // namespace Core
} // namespace Kotek