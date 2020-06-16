#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Log::lCoreLogger;
	std::shared_ptr<spdlog::logger> Log::lClientLogger;

	void Log::Init() 
	{
		spdlog::set_pattern("%^[%T][%n] %v%$");
		lCoreLogger = spdlog::stdout_color_mt("ENGINE");
		lCoreLogger->set_level(spdlog::level::trace);

		lClientLogger = spdlog::stdout_color_mt("APP");
		lClientLogger->set_level(spdlog::level::trace);
	}
}