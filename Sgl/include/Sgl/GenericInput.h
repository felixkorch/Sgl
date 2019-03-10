#pragma once
#include "Sgl/Input.h"

namespace sgl
{
	class GenericInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int code) override;
		virtual double GetMousePositionXImpl() override;
		virtual double GetMousePositionYImpl() override;
		virtual std::pair<double, double> GetMousePositionImpl() override;
	};
}