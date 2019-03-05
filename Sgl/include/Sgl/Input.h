#pragma once
namespace sgl
{
	namespace input {
		static constexpr auto MaxKeys = 350;
		static bool keys[350]{};

		static bool IsKeyPressed(unsigned int keycode)
		{
			return keys[keycode];
		}
	}
}