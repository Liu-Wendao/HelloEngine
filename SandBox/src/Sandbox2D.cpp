#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	HE_PROFILE_FUNCTION();

	m_CheckerboardTexture = HelloEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	HE_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(const HelloEngine::Timestep& ts)
{
	HE_PROFILE_FUNCTION();

	//Update
	m_CameraController.OnUpdate(ts);
	//Render
	{
		HE_PROFILE_SCOPE("Renderer Prep");
		HelloEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		HelloEngine::RenderCommand::Clear();
	}
	{
		HE_PROFILE_SCOPE("Renderer Draw");
		HelloEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		HelloEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		HelloEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		HelloEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		HelloEngine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HE_PROFILE_FUNCTION();

	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Flat Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(HelloEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
