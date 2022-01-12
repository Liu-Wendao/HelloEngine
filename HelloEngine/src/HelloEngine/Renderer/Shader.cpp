#include "hepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace HelloEngine
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLShader(filepath);
			}
		}

		HE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLShader(vertexShaderSrc, fragmentShaderSrc);
			}
		}

		HE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}