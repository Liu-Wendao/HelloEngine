#pragma once

#ifdef HE_PLATFORM_WINDOWS

extern HelloEngine::Application* HelloEngine::CreateApplication();

int main(int argc, char** argv)
{
	HelloEngine::Log::Init();

	auto app = HelloEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
