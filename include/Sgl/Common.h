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

#endif

#define GLM_ENABLE_EXPERIMENTAL