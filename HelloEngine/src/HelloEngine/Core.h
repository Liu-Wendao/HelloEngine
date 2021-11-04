#pragma once

#ifdef HE_PLATFORM_WINDOWS
	#ifdef HE_BUILD_DLL
		#define HelloEngine_API __declspec(dllexport)
	#else
		#define HelloEngine_API __declspec(dllimport)
	#endif 
#else
	#error HelloEngine only support windows!
#endif