#pragma once

namespace HelloEngine
{
	enum class ShaderDataType
	{
		None = 0, 
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case HelloEngine::ShaderDataType::Float:    return 4;
			case HelloEngine::ShaderDataType::Float2:   return 4 * 2;
			case HelloEngine::ShaderDataType::Float3:   return 4 * 3;
			case HelloEngine::ShaderDataType::Float4:   return 4 * 4;
			case HelloEngine::ShaderDataType::Int:      return 4;
			case HelloEngine::ShaderDataType::Int2:     return 4 * 2;
			case HelloEngine::ShaderDataType::Int3:     return 4 * 3;
			case HelloEngine::ShaderDataType::Int4:     return 4 * 4;
			case HelloEngine::ShaderDataType::Mat3:     return 4 * 3 * 3;
			case HelloEngine::ShaderDataType::Mat4:     return 4 * 4 * 4;
			case HelloEngine::ShaderDataType::Bool:     return 1;
		}

		HE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	//buffer的必要属性
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case HelloEngine::ShaderDataType::Float:    return 1;
				case HelloEngine::ShaderDataType::Float2:   return 2;
				case HelloEngine::ShaderDataType::Float3:   return 3;
				case HelloEngine::ShaderDataType::Float4:   return 4;
				case HelloEngine::ShaderDataType::Int:      return 1;
				case HelloEngine::ShaderDataType::Int2:     return 2;
				case HelloEngine::ShaderDataType::Int3:     return 3;
				case HelloEngine::ShaderDataType::Int4:     return 4;
				case HelloEngine::ShaderDataType::Mat3:     return 3 * 3;
				case HelloEngine::ShaderDataType::Mat4:     return 4 * 4;
				case HelloEngine::ShaderDataType::Bool:     return 1;
			}

			HE_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& elememt : m_Elements)
			{
				elememt.Offset = offset;
				offset += elememt.Size;
				m_Stride += elememt.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}

