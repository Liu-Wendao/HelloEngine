
#include "HelloEngine.h"

class Sandbox: public HelloEngine::Application
{
public:
	Sandbox()
	{

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