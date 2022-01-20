#pragma once
#include "HelloEngine/Core/Layer.h"

#include "HelloEngine/Events/ApplicationEvent.h"
#include "HelloEngine/Events/KeyEvent.h"
#include "HelloEngine/Events/MouseEvent.h"


namespace HelloEngine
{
	class ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		
	};
}