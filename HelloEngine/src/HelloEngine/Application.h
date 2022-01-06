#pragma once

#include "HelloEngine/Core.h"
#include "HelloEngine/Window.h"
#include "HelloEngine/LayerStack.h"
#include "HelloEngine/Events/Event.h"
#include "HelloEngine/Events/ApplicationEvent.h"

#include "HelloEngine/ImGui/ImGuiLayer.h"

namespace HelloEngine
{ 
	class HelloEngine_API Application
	{
	public:
		Application();
		virtual ~Application() = default;
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		bool m_Running = true;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//在客户端定义该函数 
	Application* CreateApplication();
}

