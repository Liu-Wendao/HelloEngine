#pragma once
#include "HelloEngine/Layer.h"

#include "HelloEngine/Events/ApplicationEvent.h"
#include "HelloEngine/Events/KeyEvent.h"
#include "HelloEngine/Events/MouseEvent.h"


namespace HelloEngine
{
	class HelloEngine_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		
	};
}