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

			enum class eShaderLoadingDataType : ktk::enum_base_t
			{
				kShaderLoadingDataType_FilePathString,
				kShaderLoadingDataType_SourceCode_TextString,
				kShaderLoadingDataType_ByteArrayFile,
				kShaderLoadingDataType_ByteArrayCompiledSPIRV,
				kShaderLoadingDataType_NotInitialized = -1
			};

			enum class eShaderType : ktk::enum_base_t
			{
				kShaderType_Vertex,
				// @ fragment
				kShaderType_Pixel,
				kShaderType_Geometry,
				kShaderType_Compute,
				kShaderType_Mesh,
				kShaderType_Task,
				kShaderType_TessellationControl,
				kShaderType_TessellationEvaluation,
				kShaderType_RTX_Generation,
				kShaderType_RTX_Intersection,
				kShaderType_RTX_AnyHit,
				kShaderType_RTX_ClosesHit,
				kShaderType_RTX_Miss,
				kShaderType_RTX_Callable,

				kShaderType_Unknown = -1
			};

			class ktkRenderGraphTextureInfo
			{
			public:
				ktkRenderGraphTextureInfo(void);
				~ktkRenderGraphTextureInfo(void);

				GLenum Get_Target(void) const noexcept;
				void Set_Target(GLenum value) noexcept;

				GLint Get_Level(void) const noexcept;
				void Set_Level(GLint value) noexcept;

				GLint Get_InternalFormat(void) const noexcept;

				GLsizei Get_Width(void) const noexcept;
				void Set_Width(GLsizei value) noexcept;

				GLsizei Get_Height(void) const noexcept;
				void Set_Height(GLsizei value) noexcept;

				GLsizei Get_Depth(void) const noexcept;
				void Set_Depth(GLsizei value) noexcept;

				GLint Get_Border(void) const noexcept;
				void Set_Border(GLint value) noexcept;

				GLenum Get_Format(void) const noexcept;
				void Set_Format(GLenum value) noexcept;

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

			class ktkRenderGraphBufferInfo
			{
			public:
				ktkRenderGraphBufferInfo(void);
				~ktkRenderGraphBufferInfo(void);

			private:
			};

			class ktkRenderGraphShaderTextInfo
			{
			public:
				explicit ktkRenderGraphShaderTextInfo(
					eShaderLoadingDataType type_loading_data,
					const ktk::string& path_to_file_or_source_code_string);

				explicit ktkRenderGraphShaderTextInfo(
					eShaderLoadingDataType type_loading_data, void* p_data);

				ktkRenderGraphShaderTextInfo(void);

				~ktkRenderGraphShaderTextInfo(void);

				eShaderLoadingDataType Get_Type(void) const noexcept;
				void Set_Type(eShaderLoadingDataType type) noexcept;

				const ktk::variant<void*, ktk::string>& Get_Data(
					void) const noexcept;
				void Set_Data(
					const ktk::variant<void*, ktk::string>& data) noexcept;

			private:
				eShaderLoadingDataType m_type;
				ktk::variant<void*, ktk::string> m_data;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek