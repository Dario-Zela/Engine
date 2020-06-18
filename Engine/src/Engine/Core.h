#pragma once

#ifdef EN_BUILD_DLL
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

#define BIT(x) (1 << x)

#ifdef EN_ENABLE_ASSERTS
	#define HZ_ASSERT(x,...) {if(!(x)) {EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define	HZ_CORE_ASSERT(x,...) {if(!(x)) {EN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x,...)
	#define	HZ_CORE_ASSERT(x,...)
#endif // EN_ENABLE_ASSERTS
