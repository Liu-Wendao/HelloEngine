#pragma once

#include "HelloEngine/Core.h"
#include "HelloEngine/Window.h"
#include "HelloEngine/LayerStack.h"
#include "HelloEngine/Events/Event.h"
#include "HelloEngine/Events/ApplicationEvent.h"

#include "HelloEngine/ImGui/ImGuiLayer.h"

#include "HelloEngine/Renderer/Shader.h"
#include "HelloEngine/Renderer/Buffer.h"

namespace HelloEngine
{ 
	class HelloEngine_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	//在客户端定义该函数 
	Application* CreateApplication();
}

