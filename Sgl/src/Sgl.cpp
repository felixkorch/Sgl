#include "Sgl/Log.h"
#include "Sgl/Input.h"

namespace sgl
{
	std::shared_ptr<spdlog::logger> Log::mainLogger;
	bool Input::keys[MaxKeys];
}