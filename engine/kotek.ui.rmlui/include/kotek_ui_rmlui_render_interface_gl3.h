#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.os/include/kotek_core_os.h>

#ifdef KOTEK_USE_RMLUI_LIBRARY
	#include <RmlUi/Core/RenderInterface.h>
	#include <RmlUi/Core/Types.h>
#endif

namespace Gfx
{
	struct ShadersData;
}

#ifdef KOTEK_PLATFORM_LINUX
    #undef None
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

class ktkRenderInterface_GL3 : public Rml::RenderInterface
{
public:
	ktkRenderInterface_GL3();
	~ktkRenderInterface_GL3();

	// Returns true if the renderer was successfully constructed.
	explicit operator bool() const { return static_cast<bool>(shaders); }

	// The viewport should be updated whenever the window size changes.
	void SetViewport(int viewport_width, int viewport_height);

	// Sets up OpenGL states for taking rendering commands from RmlUi.
	void BeginFrame();
	void EndFrame();

	// Optional, can be used to clear the framebuffer.
	void Clear();

	// -- Inherited from Rml::RenderInterface --

	void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices,
		int num_indices, Rml::TextureHandle texture,
		const Rml::Vector2f& translation) override;

	Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices,
		int num_vertices, int* indices, int num_indices,
		Rml::TextureHandle texture) override;
	void RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry,
		const Rml::Vector2f& translation) override;
	void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry) override;

	void EnableScissorRegion(bool enable) override;
	void SetScissorRegion(int x, int y, int width, int height) override;

	// TODO: replace tga, implement for ktx
	bool LoadTexture(Rml::TextureHandle& texture_handle,
		Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
	bool GenerateTexture(Rml::TextureHandle& texture_handle,
		const Rml::byte* source,
		const Rml::Vector2i& source_dimensions) override;
	void ReleaseTexture(Rml::TextureHandle texture_handle) override;

	void SetTransform(const Rml::Matrix4f* transform) override;

	// Can be passed to RenderGeometry() to enable texture rendering without
	// changing the bound texture.
	static const Rml::TextureHandle TextureEnableWithoutBinding =
		Rml::TextureHandle(-1);

private:
	enum class ProgramId
	{
		None,
		Texture = 1,
		Color = 2,
		All = (Texture | Color)
	};
	void SubmitTransformUniform(ProgramId program_id, int uniform_location);

	Rml::Matrix4f transform, projection;
	ProgramId transform_dirty_state = ProgramId::All;
	bool transform_active = false;

	enum class ScissoringState
	{
		Disable,
		Scissor,
		Stencil
	};
	ScissoringState scissoring_state = ScissoringState::Disable;

	int viewport_width = 0;
	int viewport_height = 0;

	Rml::UniquePtr<Gfx::ShadersData> shaders;
};

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
