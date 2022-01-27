#include "HelloEngine.h"
#include "HelloEngine/Core/EntryPoint.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox: public HelloEngine::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
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
