#include "Sgl/BaseInput.h"
#include "Sgl/BaseWindow.h"
#include "Sgl/Application.h"
#include "Sgl/Log.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	std::shared_ptr<Input> Input::sInstance = std::make_shared<BaseInput>();

	bool BaseInput::IsKeyPressedImpl(int keycode)
	{
		auto win = (GLFWwindow*)Application::Get().GetWindow()->GetNativeWindow();
		auto state = glfwGetKey(win, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool BaseInput::IsJoystickButtonPressedImpl(int code, int joystick)
	{
		if (!IsJoystickPresent(joystick))
			return false;

		int count;
		const unsigned char* button = glfwGetJoystickButtons(joystick, &count);
		if (code - 1 > count || code < 0) {
			SGL_CORE_WARN("Joystick({}) Button doesn't exist!", joystick);
			return false;
		}
		return button[code] == GLFW_PRESS || button[code] == GLFW_REPEAT;
	}

	bool BaseInput::IsJoystickPresentImpl(int number)
	{
		int present = glfwJoystickPresent(number);
		return present;
	}

	std::vector<float> BaseInput::GetJoystickAxisImpl(int joystick) // TODO: y-axis is inversed
	{
		if (!IsJoystickPresent(joystick))
			return std::vector<float>();

		int count;
		const float* axis = glfwGetJoystickAxes(joystick, &count);
		return std::vector<float>(axis, axis + count);
	}

	bool BaseInput::IsMouseButtonPressedImpl(int code)
	{
		auto win = (GLFWwindow*)Application::Get().GetWindow()->GetNativeWindow();
		return glfwGetMouseButton(win, code) == GLFW_PRESS;
	}

	double BaseInput::GetMousePositionXImpl()
	{
		return GetMousePositionImpl().first;
	}

	double BaseInput::GetMousePositionYImpl()
	{
		return GetMousePositionImpl().second;
	}

	std::pair<double, double> BaseInput::GetMousePositionImpl()
	{
		auto win = (BaseWindow*)Application::Get().GetWindow();
		auto glfwWindow = (GLFWwindow*)win->GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(glfwWindow, &xpos, &ypos);

		//SglTrace("Current Mousepos: {}, {}", xpos, win->GetWindowHeight() - ypos);

		return std::make_pair(xpos, win->GetHeight() - ypos);
	}
}