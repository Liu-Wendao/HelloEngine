#pragma once

#ifdef HE_PLATFORM_WINDOWS

extern HelloEngine::Application* HelloEngine::CreateApplication();

int main(int argc, char** argv)
{
	HelloEngine::Log::Init();

	HE_PROFILE_BEGIN_SESSION("Startup", "HelloEngineProfile-Startup.json");
	auto app = HelloEngine::CreateApplication();
	HE_PROFILE_END_SESSION();

	HE_PROFILE_BEGIN_SESSION("Runtime", "HelloEngineProfile-Runtime.json");
	app->Run();
	HE_PROFILE_END_SESSION();

	HE_PROFILE_BEGIN_SESSION("Shutdown", "HelloEngineProfile-Shutdown.json");
	delete app;
	HE_PROFILE_END_SESSION();

	return 0;
}

#endif
