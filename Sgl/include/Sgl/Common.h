#pragma once
#include <cassert>
#include <cstddef>
#include <iostream>

#ifndef NDEBUG
#define SGLASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
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