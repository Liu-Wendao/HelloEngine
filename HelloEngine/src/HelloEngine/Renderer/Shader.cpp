#include "hepch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace HelloEngine
{
	Shader::Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		//创建顶点着色器
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//将顶点着色器代码发送给OPENGL
		const char* source = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		//编译顶点着色器
		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			
			//如果编译出错，删掉这个顶点着色器
			glDeleteShader(vertexShader);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		//创建片段着色器
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//将片段着色器代码发送给OPENGL
		source = fragmentShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			//如果编译出错，删掉这个顶点着色器
			glDeleteShader(fragmentShader);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		//将编译好的顶点着色器和片段着色器链接到一个着色器程序里
		//创建着色器程序
		m_RendererID = glCreateProgram();

		//将编译好的着色器代码附加到着色器程序里
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		//链接
		glLinkProgram(m_RendererID);

		int isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			//如果链接出错，删掉这个着色器程序
			glDeleteProgram(m_RendererID);
			//也删掉对应的顶点着色器和片段着色器
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Shader links failure!");
			return;
		}

		//成功链接之后，分离两个着色器
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}