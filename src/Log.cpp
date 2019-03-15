#include "Sgl/Log.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace sgl
{
	std::shared_ptr<spdlog::logger> Log::mainLogger;   // Definition of the global logger
	std::shared_ptr<spdlog::logger> Log::clientLogger; // Definition of the global client-logger

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		mainLogger = spdlog::stdout_color_mt("SGL");
		mainLogger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] %n: %v%$");
		clientLogger = spdlog::stdout_color_mt("CLIENT");
		clientLogger->set_level(spdlog::level::trace);
	}
}