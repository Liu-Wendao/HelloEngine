#pragma once
#include "HelloEngine/Renderer/RendererAPI.h"

namespace HelloEngine
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void SetClearColor(const glm::vec4& color) const override;
        virtual void Clear() const override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const override;
    };
}

