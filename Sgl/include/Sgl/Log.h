#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace sgl
{
	class Log {
	private:
		static std::shared_ptr<spdlog::logger> mainLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	public:
		static std::shared_ptr<spdlog::logger>& GetMainLogger()
		{
			return mainLogger;
		}

		static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return clientLogger;
		}

		static void Init();
	};
}