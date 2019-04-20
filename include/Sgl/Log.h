#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

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

    #ifndef NDEBUG
    #define SGL_ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
    #else
    #define SGL_ASSERT(condition, message)
    #endif

    #define GLM_ENABLE_EXPERIMENTAL

	#define SGL_CORE_WARN(...)  Log::GetMainLogger()->warn(__VA_ARGS__)
	#define SGL_CORE_ERROR(...) Log::GetMainLogger()->error(__VA_ARGS__)
	#define SGL_CORE_TRACE(...) Log::GetMainLogger()->trace(__VA_ARGS__)
	#define SGL_CORE_INFO(...)  Log::GetMainLogger()->info(__VA_ARGS__)
	#define SGL_CORE_FATAL(...) Log::GetMainLogger()->fatal(__VA_ARGS__)

	#define SGL_WARN(...)  Log::GetMainLogger()->warn(__VA_ARGS__)
	#define SGL_ERROR(...) Log::GetMainLogger()->error(__VA_ARGS__)
	#define SGL_TRACE(...) Log::GetMainLogger()->trace(__VA_ARGS__)
	#define SGL_INFO(...)  Log::GetMainLogger()->info(__VA_ARGS__)
	#define SGL_FATAL(...) Log::GetMainLogger()->fatal(__VA_ARGS__)
}
