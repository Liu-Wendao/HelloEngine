#pragma once

#ifdef HE_PLATFORM_WINDOWS

extern HelloEngine::Application* HelloEngine::CreateApplication();

int main(int argc, char** argv)
{
	HelloEngine::Log::Init();
	
	HE_CORE_ERROR("ERROR!");
	HE_CLIENT_INFO("HELLO!");
	
	auto app = HelloEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
