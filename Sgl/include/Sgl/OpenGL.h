#pragma once
#ifdef USE_EMSCRIPTEN
#include "emscripten/emscripten.h"
#define GLFW_INCLUDE_ES2
#include "GLFW/glfw3.h"
#else
#include "glad/glad.h"
#endif