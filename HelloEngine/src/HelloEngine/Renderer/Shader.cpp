#include "hepch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace HelloEngine
{
	Shader::Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		//����������ɫ��
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//��������ɫ�����뷢�͸�OPENGL
		const char* source = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		//���붥����ɫ��
		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			
			//����������ɾ�����������ɫ��
			glDeleteShader(vertexShader);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		//����Ƭ����ɫ��
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//��Ƭ����ɫ�����뷢�͸�OPENGL
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

			//����������ɾ�����������ɫ��
			glDeleteShader(fragmentShader);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		//������õĶ�����ɫ����Ƭ����ɫ�����ӵ�һ����ɫ��������
		//������ɫ������
		m_RendererID = glCreateProgram();

		//������õ���ɫ�����븽�ӵ���ɫ��������
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		//����
		glLinkProgram(m_RendererID);

		int isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			//������ӳ���ɾ�������ɫ������
			glDeleteProgram(m_RendererID);
			//Ҳɾ����Ӧ�Ķ�����ɫ����Ƭ����ɫ��
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Shader links failure!");
			return;
		}

		//�ɹ�����֮�󣬷���������ɫ��
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