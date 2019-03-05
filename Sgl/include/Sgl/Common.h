#pragma once
#include "spdlog/spdlog.h"
#include "Sgl/Log.h"

#include <cassert>
#include <cstddef>
#include <iostream>

#ifndef NDEBUG
#define SglAssert(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)

#define SglWarn(...)  Log::GetMainLogger()->warn(__VA_ARGS__)
#define SglError(...) Log::GetMainLogger()->error(__VA_ARGS__)
#define SglTrace(...) Log::GetMainLogger()->trace(__VA_ARGS__)
#define SglInfo(...)  Log::GetMainLogger()->info(__VA_ARGS__)
#define SglFatal(...) Log::GetMainLogger()->fatal(__VA_ARGS__)

#endif

#define GLM_ENABLE_EXPERIMENTAL

#ifdef USE_EMSCRIPTEN
#include "emscripten/emscripten.h"
#include "GLES3/gl32.h"
#define GLFW_INCLUDE_ES3
#else
#include "glad/glad.h"
#endif

#include "GLFW/glfw3.h"