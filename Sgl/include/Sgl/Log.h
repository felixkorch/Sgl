#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace sgl
{
	class Log {
	private:
		static std::shared_ptr<spdlog::logger> mainLogger;
	public:
		static std::shared_ptr<spdlog::logger>& GetMainLogger()
		{
			return mainLogger;
		}

		static void Init()
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");
			mainLogger = spdlog::stdout_color_mt("SGL");
			mainLogger->set_level(spdlog::level::trace);
		}
	};
}