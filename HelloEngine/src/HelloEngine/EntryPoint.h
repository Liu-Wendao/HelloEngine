#pragma once

#ifdef HE_PLATFORM_WINDOWS

extern HelloEngine::Application* HelloEngine::CreateApplication();

int main()
{
	auto app = HelloEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
