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