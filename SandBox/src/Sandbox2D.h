#pragma once
#include "HelloEngine.h"

#include <glm/glm.hpp>

class Sandbox2D :public HelloEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(const HelloEngine::Timestep& ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(HelloEngine::Event& e) override;
private:
	HelloEngine::OrthographicCameraController m_CameraController;

	//Temp
	HelloEngine::Ref<HelloEngine::VertexArray> m_SquareVA;
	HelloEngine::Ref<HelloEngine::Shader> m_FlatColorShader;

	HelloEngine::Ref<HelloEngine::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};