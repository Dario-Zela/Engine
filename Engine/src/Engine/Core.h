#pragma once

#ifdef EN_BUILD_DLL
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

#define BIT(x) (1 << x)

#ifdef EN_DEBUG
	#define EN_ENABLE_ASSERTS
#endif

#ifdef EN_ENABLE_ASSERTS
	#define EN_ASSERT(x,...) {if(!(x)) {EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define	EN_CORE_ASSERT(x,...) {if(!(x)) {EN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EN_ASSERT(x,...)
	#define	EN_CORE_ASSERT(x,...)
#endif // EN_ENABLE_ASSERTS

#define EN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)