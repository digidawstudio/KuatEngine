#pragma once

#ifdef KE_PLATFORM_WINDOWS
#ifdef KE_BUILD_DLL
#define KUATENGINE_API __declspec(dllexport)
#else
#define KUATENGINE_API __declspec(dllimport)
#endif
#else
#error KuatEngine only support windows
#endif // KE_PLATFORM_WINDOWS
