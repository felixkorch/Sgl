#pragma once
#include "Sgl/GenericInput.h"
#include "Sgl/GenericWindow.h"
#include "Sgl/Application.h"
#include "Sgl/Common.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	Input* Input::sInstance = new GenericInput;

	bool GenericInput::IsKeyPressedImpl(int keycode)
	{
		auto win = (GLFWwindow*)Application::Get().GetWindow()->GetNativeWindow();
		auto state = glfwGetKey(win, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GenericInput::IsJoystickButtonPressedImpl(int code, int joystick)
	{
		if (!IsJoystickPresent(joystick))
			return false;

		int count;
		const unsigned char* button = glfwGetJoystickButtons(joystick, &count);
		if (code - 1 > count || code < 0) {
			SglWarn("Joystick({}) Button doesn't exist!", joystick);
			return false;
		}
		return button[code] == GLFW_PRESS || button[code] == GLFW_REPEAT;
	}

	bool GenericInput::IsJoystickPresentImpl(int number)
	{
		int present = glfwJoystickPresent(number);
		return present;
	}

	std::vector<float> GenericInput::GetJoystickAxisImpl(int joystick) // TODO: y-axis is inversed
	{
		if (!IsJoystickPresent(joystick))
			return std::vector<float>();

		int count;
		const float* axis = glfwGetJoystickAxes(joystick, &count);
		std::vector<float> temp(count);
		std::copy(axis, axis + count, temp.begin());
		return temp;
	}

	bool GenericInput::IsMouseButtonPressedImpl(int code)
	{
		auto win = (GLFWwindow*)Application::Get().GetWindow()->GetNativeWindow();
		return glfwGetMouseButton(win, code) == GLFW_PRESS;
	}

	double GenericInput::GetMousePositionXImpl()
	{
		return GetMousePositionImpl().first;
	}

	double GenericInput::GetMousePositionYImpl()
	{
		return GetMousePositionImpl().second;
	}

	std::pair<double, double> GenericInput::GetMousePositionImpl()
	{
		auto win = (GenericWindow*)Application::Get().GetWindow();
		auto glfwWindow = (GLFWwindow*)win->GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(glfwWindow, &xpos, &ypos);

		//SglTrace("Current Mousepos: {}, {}", xpos, win->GetWindowHeight() - ypos);

		return std::make_pair(xpos, win->GetWindowHeight() - ypos);
	}
}