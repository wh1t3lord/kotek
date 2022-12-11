#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkIRenderDevice;
class ktkIRenderResourceManager;
class ktkFileSystem;
class ktkIRenderGraphResourceManager;
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphStorageOutput;
	class ktkRenderGraphStorageInput;
} // namespace gl

namespace gl
{
	class ktkRenderGraphSimplifiedBuilder;
	class ktkRenderGraphSimplifiedNode;
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphSimplifiedRenderPass
	{
		friend class ktkRenderGraphSimplifiedBuilder;

	public:
		ktkRenderGraphSimplifiedRenderPass(void);
		virtual ~ktkRenderGraphSimplifiedRenderPass(void) = default;

		virtual void OnSetupInput(
			gl::ktkRenderGraphSimplifiedStorageInput& storage,
			Core::ktkIRenderDevice* p_device,
			Core::ktkFileSystem* p_file_system);

		virtual void OnSetupOutput(
			gl::ktkRenderGraphSimplifiedStorageOutput& storage,
			Core::ktkIRenderDevice* p_device);

		virtual void OnCreatedResources(void);
		virtual void OnUpdate();
		virtual void OnRender(const ktkRenderGraphSimplifiedNode& node);

		/// <summary>
		/// Don't set it by your own hands, because this method is
		/// called by render_graph_builder manager
		/// </summary>
		/// <param name="name">that's parameter specifies your name for
		/// describing pass, because all passes referencing by hashed
		/// value and that means for human being it's hard to understand
		/// what is written in hash instead of reading rational
		/// string</param> <returns>nothing</returns>
		void Set_Name(const ktk::string& name) noexcept;

		const ktk::string& Get_Name(void) const noexcept;

	private:
		void Initialize(Core::ktkIRenderResourceManager* p_manager_resource,
			Core::ktkIRenderGraphResourceManager*
				p_manager_resource_graph) noexcept;

	protected:
		Core::ktkIRenderResourceManager* m_p_manager_resource;
		Core::ktkIRenderGraphResourceManager* m_p_manager_resource_graph;

	private:
		ktk::string m_name;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK