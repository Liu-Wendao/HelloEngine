#pragma once

#include "Core.h"

namespace HelloEngine
{ 
	class HelloEngine_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//�ڿͻ��˶���ú��� 
	Application* CreateApplication();
}

