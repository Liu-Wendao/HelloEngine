#pragma once

#include "HelloEngine/Core.h"
#include "HelloEngine/Window.h"
#include "HelloEngine/LayerStack.h"
#include "HelloEngine/Events/Event.h"
#include "HelloEngine/Events/ApplicationEvent.h"

#include "HelloEngine/ImGui/ImGuiLayer.h"

#include "HelloEngine/Renderer/Shader.h"
#include "HelloEngine/Renderer/Buffer.h"
#include "HelloEngine/Renderer/VertexArray.h"
#include "HelloEngine/Renderer/Camera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_BlueVertexArray;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//在客户端定义该函数 
	Application* CreateApplication();
}

