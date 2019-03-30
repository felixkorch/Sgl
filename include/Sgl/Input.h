#pragma once
#include <utility>
#include <vector>
#include <memory>

namespace sgl
{
	class Input {
	public:
		static bool IsKeyPressed(int keycode)
		{
			return sInstance->IsKeyPressedImpl(keycode);
		}

		static bool IsJoystickButtonPressed(int code, int joystick)
		{
			return sInstance->IsJoystickButtonPressedImpl(code, joystick);
		}

		static bool IsJoystickPresent(int number)
		{
			return sInstance->IsJoystickPresentImpl(number);
		}

		static std::vector<float> GetJoystickAxis(int joystick)
		{
			return sInstance->GetJoystickAxisImpl(joystick);
		}

		static bool IsMouseButtonPressed(int code)
		{
			return sInstance->IsMouseButtonPressedImpl(code);
		}

		static double GetMousePositionX()
		{
			return sInstance->GetMousePositionXImpl();
		}

		static double GetMousePositionY()
		{
			return sInstance->GetMousePositionYImpl();
		}

		static std::pair<double, double> GetMousePosition()
		{
			return sInstance->GetMousePositionImpl();
		}

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsJoystickPresentImpl(int number) = 0;
		virtual bool IsJoystickButtonPressedImpl(int code, int joystick) = 0;
		virtual std::vector<float> GetJoystickAxisImpl(int joystick) = 0;
		virtual bool IsMouseButtonPressedImpl(int code) = 0;
		virtual double GetMousePositionXImpl() = 0;
		virtual double GetMousePositionYImpl() = 0;
		virtual std::pair<double, double> GetMousePositionImpl() = 0;
	private:
		static std::shared_ptr<Input> sInstance;
	};
}
