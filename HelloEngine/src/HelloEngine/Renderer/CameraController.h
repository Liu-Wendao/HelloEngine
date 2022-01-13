#pragma once

#include <glm/glm.hpp>

#include "HelloEngine/Renderer/Camera.h"
#include "HelloEngine/Core/Timestep.h"

#include "HelloEngine/Events/MouseEvent.h"
#include "HelloEngine/Events/ApplicationEvent.h"

namespace HelloEngine
{
	//-------------------------------------------------
	//正交相机-----------------------------------------
	//-------------------------------------------------
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio = 1.6f, bool isRotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio; //宽高比
		float m_ZoomLevel = 1.0f; //屏幕高的一半
		OrthographicCamera m_Camera;

		bool m_IsRotation;
		float m_CameraRotation = 0.0f;
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };

		float m_CameraTranslationSpeed = 2.0f;
		float m_CameraRotationSpeed = 90.0f;
	};


	//-------------------------------------------------
	//透视相机-----------------------------------------
	//-------------------------------------------------
}