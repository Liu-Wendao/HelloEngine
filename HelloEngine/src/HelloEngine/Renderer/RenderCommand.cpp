#include "hepch.h"
#include "HelloEngine/Renderer/RenderCommand.h"



namespace HelloEngine
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}