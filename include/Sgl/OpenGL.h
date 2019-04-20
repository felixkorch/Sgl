#pragma once
#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#include "emscripten/html5.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GLES2/gl2.h"
#else
#include "glad/glad.h"
#endif