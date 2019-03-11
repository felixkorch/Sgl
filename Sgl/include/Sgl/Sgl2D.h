#pragma once
#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Renderer2D.h"
#include "Sgl/Shader.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Events/KeyCodes.h"
#include "Sgl/Events/MouseCodes.h"
#include "Sgl/Events/JoystickCodes.h"
#include "Sgl/Log.h"
#include "Sgl/Input.h"

#define ClientWarn(...)  Log::GetClientLogger()->warn(__VA_ARGS__)
#define ClientError(...) Log::GetClientLogger()->error(__VA_ARGS__)
#define ClientTrace(...) Log::GetClientLogger()->trace(__VA_ARGS__)
#define ClientInfo(...)  Log::GetClientLogger()->info(__VA_ARGS__)
#define ClientFatal(...) Log::GetClientLogger()->fatal(__VA_ARGS__)