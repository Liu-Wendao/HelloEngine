#pragma once

#include "glm/glm.hpp"
namespace HelloEngine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}

