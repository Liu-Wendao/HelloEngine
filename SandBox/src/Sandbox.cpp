#include "hepch.h"
#include "HelloEngine.h"

#include "imgui/imgui.h"
class ExampleLayer : public HelloEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	virtual void OnUpdate() override
	{
		if (HelloEngine::Input::IsKeyPressed(HE_KEY_TAB))
			HE_CLIENT_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello Engine!");
		ImGui::End();
	}

	virtual void OnEvent(HelloEngine::Event& event) override
	{
		if (event.GetEventType() == HelloEngine::EventType::KeyPressed)
		{
			HelloEngine::KeyPressedEvent& e = (HelloEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HE_KEY_TAB)
				HE_CLIENT_TRACE("Tab key is pressed (event)!");
			HE_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};


class Sandbox: public HelloEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

private:

};


HelloEngine::Application* HelloEngine::CreateApplication()
{
	return new Sandbox;
}
