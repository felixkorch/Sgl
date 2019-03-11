#pragma once
#ifdef USE_EMSCRIPTEN
#include "emscripten/emscripten.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GLES2/gl2.h"
#else
#include "glad/glad.h"
#endif