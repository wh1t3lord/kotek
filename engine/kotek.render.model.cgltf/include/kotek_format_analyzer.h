#pragma once

namespace Kotek
{
	namespace Render
	{
		class ktkFormatAnalyzer_CGLTF : public Core::ktkIResourceFormatAnalyzer
		{
		public:
			ktkFormatAnalyzer_CGLTF(void);
			~ktkFormatAnalyzer_CGLTF(void);

			bool Analyze(const ktk::filesystem::path& path) noexcept override;

			/// \~english @brief All formats go in this string in view
			/// "format_name format_name2 ..."
			/// @param nothing as input for passing
			/// @return string that contains all formats written in format like
			/// "format1 format2 format3 ..."
			ktk::string Get_AllFormats(void) const noexcept override;

		private:
			ktk::unordered_set<ktk::string> m_formats;
		};
	} // namespace Render
} // namespace Kotek