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

	#define SglCoreWarn(...)  Log::GetMainLogger()->warn(__VA_ARGS__)
	#define SglCoreError(...) Log::GetMainLogger()->error(__VA_ARGS__)
	#define SglCoreTrace(...) Log::GetMainLogger()->trace(__VA_ARGS__)
	#define SglCoreInfo(...)  Log::GetMainLogger()->info(__VA_ARGS__)
	#define SglCoreFatal(...) Log::GetMainLogger()->fatal(__VA_ARGS__)

	#define SglWarn(...)  Log::GetMainLogger()->warn(__VA_ARGS__)
	#define SglError(...) Log::GetMainLogger()->error(__VA_ARGS__)
	#define SglTrace(...) Log::GetMainLogger()->trace(__VA_ARGS__)
	#define SglInfo(...)  Log::GetMainLogger()->info(__VA_ARGS__)
	#define SglFatal(...) Log::GetMainLogger()->fatal(__VA_ARGS__)
}
