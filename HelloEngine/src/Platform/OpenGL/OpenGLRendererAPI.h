#pragma once
#include "HelloEngine/Renderer/RendererAPI.h"

namespace HelloEngine
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() const override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
        virtual void SetClearColor(const glm::vec4& color) const override;
        virtual void Clear() const override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const override;
    };
}

