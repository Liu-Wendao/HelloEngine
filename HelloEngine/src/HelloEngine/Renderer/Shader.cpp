#include "hepch.h"
#include "HelloEngine/Renderer/Shader.h"

#include "HelloEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace HelloEngine
{
	//---------------------------------------------------
	//--------------- Shader ----------------------------
	//---------------------------------------------------
	Ref<Shader> Shader::Create(const std::string& filepath)
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
				return CreateRef<OpenGLShader>(filepath);
			}
		}

		HE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
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
				return CreateRef<OpenGLShader>(name, vertexShaderSrc, fragmentShaderSrc);
			}
		}

		HE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	//---------------------------------------------------
	//--------------- ShaderLibrary ---------------------
	//---------------------------------------------------
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		HE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}