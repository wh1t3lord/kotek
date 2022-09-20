#include "../include/kotek_loader.h"

namespace Kotek
{
	namespace Render
	{
		ktkLoaderModel_CGLTF::ktkLoaderModel_CGLTF(
			Core::ktkIFileSystem* p_filesystem) :
			m_p_filesystem{p_filesystem},
			m_p_format_analyzer{}
		{
		}

		ktkLoaderModel_CGLTF::ktkLoaderModel_CGLTF(void) :
			m_p_filesystem{}, m_p_format_analyzer{}
		{
		}

		ktkLoaderModel_CGLTF::~ktkLoaderModel_CGLTF(void)
		{
			if (this->m_p_format_analyzer)
			{
				delete this->m_p_format_analyzer;
				this->m_p_format_analyzer = nullptr;
			}
		}

		ktk::any ktkLoaderModel_CGLTF::Load(
			const ktk::filesystem::path& path) noexcept
		{
			KOTEK_ASSERT(this->m_p_filesystem,
				"you must initialize file system for this loader");

			return ktk::any();
		}

		bool ktkLoaderModel_CGLTF::Load(const ktk::filesystem::path& path,
			ktk::any object_from_construct) noexcept
		{
			KOTEK_ASSERT(this->m_p_filesystem,
				"you must initialize file system for this loader");

			return true;
		}

		const ktk::string& ktkLoaderModel_CGLTF::Get_UserDescription(
			void) const noexcept
		{
			return KOTEK_TEXT("this is loader based on cgltf library for "
							  "loading glTF 2.0 models");
		}

		Core::eResourceLoadingType ktkLoaderModel_CGLTF::Get_Type(
			void) const noexcept
		{
			return Core::eResourceLoadingType::kModel;
		}

		bool ktkLoaderModel_CGLTF::DetectTypeByFullPath(
			const ktk::filesystem::path& path) noexcept
		{
			return this->m_p_format_analyzer->Analyze(path);
		}

		Core::ktkIResourceFormatAnalyzer*
		ktkLoaderModel_CGLTF::Get_FormatAnalyzer() const noexcept
		{
			return this->m_p_format_analyzer;
		}

		void ktkLoaderModel_CGLTF::Set_FormatAnalyzer(
			Core::ktkIResourceFormatAnalyzer* p_format_analyzer) noexcept
		{
			this->m_p_format_analyzer = p_format_analyzer;
		}
	} // namespace Render
} // namespace Kotek
