#include "hepch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace HelloEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case HelloEngine::ShaderDataType::Float:    return GL_FLOAT;
			case HelloEngine::ShaderDataType::Float2:   return GL_FLOAT;
			case HelloEngine::ShaderDataType::Float3:   return GL_FLOAT;
			case HelloEngine::ShaderDataType::Float4:   return GL_FLOAT;
			case HelloEngine::ShaderDataType::Int:      return GL_INT;
			case HelloEngine::ShaderDataType::Int2:	    return GL_INT;
			case HelloEngine::ShaderDataType::Int3:	    return GL_INT;
			case HelloEngine::ShaderDataType::Int4:	    return GL_INT;
			case HelloEngine::ShaderDataType::Mat3:     return GL_FLOAT;
			case HelloEngine::ShaderDataType::Mat4:     return GL_FLOAT;
			case HelloEngine::ShaderDataType::Bool:     return GL_BOOL;
		}

		HE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_VertexArrayID);
		vertexBuffer->Bind();

		uint32_t stride = vertexBuffer->GetLayout().GetStride();
		const auto& bufferElements = vertexBuffer->GetLayout().GetElements();
		for (const auto& element : bufferElements)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				(const void*)(intptr_t)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_VertexArrayID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}