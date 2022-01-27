#include "hepch.h"
#include "HelloEngine/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace HelloEngine
{
	//-------------------------------------------------
	//正交相机-----------------------------------------
	//-------------------------------------------------
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, znear, zfar)), m_ViewMatrix(1.0f)
	{
		HE_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float znear, float zfar)
	{
		HE_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, znear, zfar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		HE_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	//-------------------------------------------------
	//透视相机-----------------------------------------
	//-------------------------------------------------

}