#pragma once

#include "HelloEngine/Events/Event.h"

namespace HelloEngine
{
	class HelloEngine_API MouseMovedEvent :public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			:m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class HelloEngine_API MouseScrolledEvent :public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class HelloEngine_API MouseButtonEvent :public Event
	{
	public:
		int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			:m_Button(button) {}

		int m_Button;
	};

	class HelloEngine_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HelloEngine_API MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}