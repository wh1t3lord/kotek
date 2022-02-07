#pragma once

#include "kotek_std.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Kotek
{
	namespace Core
	{
		enum class eResourceLoadingType : ktk::enum_base_t
		{
			kText,
			kTexture,
			kModel,
			kSound,
			kVideo,
			kAutoDetect,
			kUnknown = kAutoDetect
		};

		class ktkIResourceLoader
		{
		public:
			virtual ~ktkIResourceLoader(void) {}


			virtual ktk::any LoadText(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadTexture(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadModel(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadSound(const ktk::string& path) noexcept = 0;
			virtual ktk::any LoadVideo(const ktk::string& path) noexcept = 0;
			
			virtual ktk::any LoadText(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadTexture(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadModel(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadSound(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;
			virtual ktk::any LoadVideo(const ktk::string& path,
				ktk::any object_from_construct) noexcept = 0;

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

		protected:
			virtual eResourceLoadingType DetectResourceTypeByFileFormat(
				const ktk::string& path) noexcept = 0;
		};
	} // namespace Core
} // namespace Kotek