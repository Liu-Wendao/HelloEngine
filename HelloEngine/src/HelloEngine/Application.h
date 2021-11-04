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

	//在客户端定义该函数 
	Application* CreateApplication();
}

