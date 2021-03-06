#include "hepch.h"
#include "HelloEngine/Renderer/CameraController.h"

#include "HelloEngine/Core/Input.h"
#include "HelloEngine/Core/KeyCodes.h"

namespace HelloEngine
{
	//-------------------------------------------------
	//????????-----------------------------------------
	//-------------------------------------------------

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool isRotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_IsRotation(isRotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HE_PROFILE_FUNCTION();

		if (HelloEngine::Input::IsKeyPressed(HE_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation))* m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation))* m_CameraTranslationSpeed * ts;
		}
		else if (HelloEngine::Input::IsKeyPressed(HE_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (HelloEngine::Input::IsKeyPressed(HE_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}	
		else if (HelloEngine::Input::IsKeyPressed(HE_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_IsRotation)
		{
			if (HelloEngine::Input::IsKeyPressed(HE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (HelloEngine::Input::IsKeyPressed(HE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HE_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	//-------------------------------------------------
	//͸??????-----------------------------------------
	//-------------------------------------------------
}