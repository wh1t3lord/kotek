#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			// TODO: move to one project that will be shared to other gl
			// versions and do it for other GAPIs
			enum class eRenderGraphBuilderType : ktk::enum_base_t
			{
				/// <summary>
				/// Uses backbuffer only, so you have only one render target for
				/// all passes
				/// </summary>
				kRenderBuilderFor_Forward_Only,
				// TODO: implement for outputs but we need to merge into back
				// buffer?
				kRenderBuilderFor_Forward_With_Outputs,
				// TODO: implement for deferred sometime...
				kRenderBuilderFor_Deferred,
				kRenderBuilderFor_Undefined
			};

			enum class eRenderGraphBuilderPipelineRenderingType : ktk::
				enum_base_t
			{
				kRenderBuilderBasedOnPipeline_Orthodox,

				// TODO: add support for RTX in new version
				kRenderBuilderBasedOnPipeline_RTX
			};

			enum class eResourceSynchronizationStatus : ktk::enum_base_t
			{
				kEmpty,
				kFromOutputToInput,
				kToInputOnly
			};

			class ktkRenderTextureInfo
			{
			public:
				ktkRenderTextureInfo(void) :
					m_target{}, m_level{}, m_internalformat{}, m_width{},
					m_height{}, m_depth{}, m_border{}, m_format{}
				{
				}

				~ktkRenderTextureInfo(void) {}

				GLenum Get_Target(void) const noexcept
				{
					return this->m_target;
				}

				void Set_Target(GLenum value) noexcept
				{
					this->m_target = value;
				}

				GLint Get_Level(void) const noexcept { return this->m_level; }

				void Set_Level(GLint value) noexcept { this->m_level = value; }

				GLint Get_InternalFormat(void) const noexcept
				{
					return this->m_internalformat;
				}

				GLsizei Get_Width(void) const noexcept { return this->m_width; }

				void Set_Width(GLsizei value) noexcept
				{
					this->m_width = value;
				}

				GLsizei Get_Height(void) const noexcept
				{
					return this->m_height;
				}

				void Set_Height(GLsizei value) noexcept
				{
					this->m_height = value;
				}

				GLsizei Get_Depth(void) const noexcept { return this->m_depth; }

				void Set_Depth(GLsizei value) noexcept
				{
					this->m_depth = value;
				}

				GLint Get_Border(void) const noexcept { return this->m_border; }

				void Set_Border(GLint value) noexcept
				{
					this->m_border = value;
				}

				GLenum Get_Format(void) const noexcept
				{
					return this->m_format;
				}

				void Set_Format(GLenum value) noexcept
				{
					this->m_format = value;
				}

			private:
				GLenum m_target;
				GLint m_level;
				GLint m_internalformat;
				GLsizei m_width;
				GLsizei m_height;
				GLsizei m_depth;
				GLint m_border;
				GLenum m_format;
			};

			class ktkRenderBufferInfo
			{
			public:
				ktkRenderBufferInfo(void) {}
				~ktkRenderBufferInfo(void) {}

			private:
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek