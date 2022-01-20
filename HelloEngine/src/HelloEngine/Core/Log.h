#pragma once

#include "HelloEngine/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>  //���ͷ�ļ���spdlog��ֱ�����������<<����

namespace HelloEngine {
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
		
	};
}


//�������־��
#define HE_CORE_TRACE(...)			::HelloEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HE_CORE_INFO(...)			::HelloEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HE_CORE_WARN(...)			::HelloEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HE_CORE_ERROR(...)			::HelloEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HE_CORE_CRITICAL(...)		::HelloEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

//�ͻ��˵���־��
#define HE_CLIENT_TRACE(...)		::HelloEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HE_CLIENT_INFO(...)			::HelloEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define HE_CLIENT_WARN(...)			::HelloEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HE_CLIENT_ERROR(...)		::HelloEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define HE_CLIENT_CRITICAL(...)		::HelloEngine::Log::GetClientLogger()->critical(__VA_ARGS__)