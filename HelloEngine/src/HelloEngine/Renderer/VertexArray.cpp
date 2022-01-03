#include "hepch.h"
#include "VertexArray.h"

#include "HelloEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace HelloEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: 
			{
				HE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
				return nullptr;
			}
			case RendererAPI::OpenGL:
			{
				return new OpenGLVertexArray();
			}			
		}

		HE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}