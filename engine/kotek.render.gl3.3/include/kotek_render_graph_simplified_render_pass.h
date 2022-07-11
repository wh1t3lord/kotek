#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderDevice;
			class ktkRenderResourceManager;
			class ktkRenderGraphResourceManager;
			class ktkRenderGraphStorageOutput;
			class ktkRenderGraphStorageInput;
			class ktkRenderGraphSimplifiedBuilder;
			class ktkRenderGraphSimplifiedNode;
		} // namespace gl3_3
	}     // namespace Render

	namespace Core
	{
		class ktkFileSystem;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraphSimplifiedRenderPass
			{
				friend class ktkRenderGraphSimplifiedBuilder;

			public:
				ktkRenderGraphSimplifiedRenderPass(void);
				virtual ~ktkRenderGraphSimplifiedRenderPass(void) = default;

				virtual void OnSetupInput(ktkRenderGraphStorageInput& storage,
					ktkRenderDevice* p_device,
					Core::ktkFileSystem* p_file_system);

				virtual void OnSetupOutput(ktkRenderGraphStorageOutput& storage,
					ktkRenderDevice* p_device);

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
				void SetName(const ktk::string& name) noexcept;

				const ktk::string& GetName(void) const noexcept;

			private:
				void Initialize(ktkRenderResourceManager* p_manager_resource,
					ktkRenderGraphResourceManager*
						p_manager_resource_graph) noexcept;

			protected:
				ktkRenderResourceManager* m_p_manager_resource;
				ktkRenderGraphResourceManager* m_p_manager_resource_graph;

			private:
				ktk::string m_name;
			};
		}
	} // namespace Render
} // namespace Kotek