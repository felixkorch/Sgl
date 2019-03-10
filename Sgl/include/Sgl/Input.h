#pragma once
#include <utility>

namespace sgl
{
	class Input {
	public:
		static bool IsKeyPressed(int keycode)
		{
			return sInstance->IsKeyPressedImpl(keycode);
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
		virtual bool IsMouseButtonPressedImpl(int code) = 0;
		virtual double GetMousePositionXImpl() = 0;
		virtual double GetMousePositionYImpl() = 0;
		virtual std::pair<double, double> GetMousePositionImpl() = 0;
	private:
		static Input* sInstance;
	};
}