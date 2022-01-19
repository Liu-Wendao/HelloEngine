#include "hepch.h"
#include "VertexArray.h"

#include "HelloEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace HelloEngine
{
	Ref<VertexArray> VertexArray::Create()
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
				return CreateRef<OpenGLVertexArray>();
			}			
		}

		HE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}