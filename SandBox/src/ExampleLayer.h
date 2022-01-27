#pragma once
#include "HelloEngine.h"

class ExampleLayer : public HelloEngine::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(const HelloEngine::Timestep& ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(HelloEngine::Event& e) override;
private:
	HelloEngine::ShaderLibrary m_ShaderLibrary;

	HelloEngine::Ref<HelloEngine::Shader> m_Shader;
	HelloEngine::Ref<HelloEngine::VertexArray> m_VertexArray;

	HelloEngine::Ref<HelloEngine::Shader> m_FlatColorShader;
	HelloEngine::Ref<HelloEngine::VertexArray> m_FlatColorVertexArray;

	HelloEngine::Ref<HelloEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	HelloEngine::OrthographicCameraController m_CameraController;

	glm::vec3 m_FlatColor = { 0.2f, 0.3f, 0.8f };
};