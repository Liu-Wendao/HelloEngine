#pragma once

#ifdef HE_PLATFORM_WINDOWS
	#ifdef HE_DYNAMIC_LINK
		#ifdef HE_BUILD_DLL
			#define HelloEngine_API __declspec(dllexport)
		#else
			#define HelloEngine_API __declspec(dllimport)
		#endif
	#else
		#define HelloEngine_API
	#endif
#else
	#error HelloEngine only support windows!
#endif

#ifdef HE_DEBUG
	#define HE_ENABLE_ASSERTS
#endif

#ifdef HE_ENABLE_ASSERTS
	#define HE_CLIENT_ASSERT(x, ...) { if(!(x)) { HE_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define HE_CORE_ASSERT(x, ...) { if(!(x)) { HE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define HE_CLIENT_ASSERT(x, ...)
	#define HE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HE_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)

namespace HelloEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}