#pragma once
#include "Sgl/Input.h"

namespace sgl
{
	class BaseInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsJoystickButtonPressedImpl(int code, int joystick) override;
		virtual bool IsJoystickPresentImpl(int number) override;
		virtual std::vector<float> GetJoystickAxisImpl(int joystick) override;
		virtual bool IsMouseButtonPressedImpl(int code) override;
		virtual double GetMousePositionXImpl() override;
		virtual double GetMousePositionYImpl() override;
		virtual std::pair<double, double> GetMousePositionImpl() override;
	};
}