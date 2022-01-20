#pragma once
#include "HelloEngine/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace HelloEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() const = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;
		virtual void SetClearColor(const glm::vec4& color) const = 0;
		virtual void Clear() const = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const = 0;

		inline static API GetAPI() { return s_API; }
		
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}

