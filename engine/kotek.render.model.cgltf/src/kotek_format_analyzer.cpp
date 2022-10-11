#include "../include/kotek_format_analyzer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

ktkFormatAnalyzer_CGLTF::ktkFormatAnalyzer_CGLTF(void)
{
	this->m_formats.insert(".gltf");

	// binary format
	// see
	// https://docs.blender.org/manual/en/2.80/addons/io_scene_gltf2.html#gltf-binary-glb
	this->m_formats.insert(".glb");
}

ktkFormatAnalyzer_CGLTF::~ktkFormatAnalyzer_CGLTF(void) {}

bool ktkFormatAnalyzer_CGLTF::Analyze(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(path.empty() == false, "you can't pass an empty path");

	KOTEK_ASSERT(path.has_extension(),
		"you must have extension for your file, supported extensions "
		"for analyze: [{}]",
		this->Get_AllFormats());

	return this->m_formats.find(path.extension().c_str()) !=
		this->m_formats.end();
}

ktk::string ktkFormatAnalyzer_CGLTF::Get_AllFormats(void) const noexcept
{
	KOTEK_ASSERT(
		this->m_formats.empty() == false, "you must initialize formats");

	ktk::string result;
	for (const auto& format_name : this->m_formats)
	{
		result += format_name;
		result += " ";
	}

	result.get_as_is().pop_back();

	return result;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
