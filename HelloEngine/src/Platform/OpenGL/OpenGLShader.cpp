#include "hepch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace HelloEngine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		HE_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		HE_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		//使用着色器文件名作为着色器名字
		//assets/shaders/Texture.glsl
		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.');
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
		:m_Name(name)
	{
		HE_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexShaderSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentShaderSrc;
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		HE_PROFILE_FUNCTION();

		glDeleteProgram(m_ShaderID);
	}

	void OpenGLShader::Bind() const
	{
		HE_PROFILE_FUNCTION();

		glUseProgram(m_ShaderID);
	}

	void OpenGLShader::Unbind() const
	{
		HE_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		HE_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		HE_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		HE_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		HE_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
		
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		HE_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], result.size());
				in.close();
			}
			else
			{
				HE_CORE_ERROR("Could not read from file '{0}'", filepath);
			}	
		}
		else
		{
			HE_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		HE_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		//#type vertex
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //shader类型声明行的开始
		while (pos != std::string::npos)
		{
			//查找#type vertex的换行符
			size_t eol = source.find_first_of("\r\n", pos); //shader类型声明行的结束
			HE_CORE_ASSERT(eol != std::string::npos, "Syntax error in shader declaration line!");
			size_t begin = pos + typeTokenLength + 1; //"#type"之后的shader类型的开始
			std::string type = source.substr(begin, eol - begin); //取出shader类型
			HE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //shader类型声明行之后shader代码的开始
			HE_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error after shader declaration line!")
			pos = source.find(typeToken, nextLinePos); //下一个shader声明行的开始

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		HE_PROFILE_FUNCTION();

		std::array<GLenum, 2> glShaderIDs;
		HE_CORE_ASSERT(shaderSources.size() <= 2, "Only support vertexshader and fragmentshader!");
		GLint program = glCreateProgram();
		int shaderID = 0;
		for (auto kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			//创建xx着色器
			GLuint shader = glCreateShader(type);
			//将xx着色器代码发送给OPENGL
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			//编译xx着色器
			glCompileShader(shader);

			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				//如果编译出错，删掉这个着色器
				glDeleteShader(shader);

				HE_CORE_ERROR("{0}", infoLog.data());
				HE_CORE_ASSERT(false, "Shader compilation failure!");
				return;
			}

			glAttachShader(program, shader);
			glShaderIDs[shaderID++] = shader;
		}

		//链接
		glLinkProgram(program);

		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			//如果链接出错，删掉这个着色器程序
			glDeleteProgram(program);
			//也删掉对应的顶点着色器和片段着色器
			for(auto id :glShaderIDs)
				glDeleteShader(id);

			HE_CORE_ERROR("{0}", infoLog.data());
			HE_CORE_ASSERT(false, "Shader links failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		//当一切都没有错误，再将创建的着色程序ID赋给m_ShaderID
		m_ShaderID = program;
	}

}