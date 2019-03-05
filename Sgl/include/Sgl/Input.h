#pragma once
namespace sgl
{
	class Input {
	private:
		static constexpr auto MaxKeys = 350;
		static bool keys[350];
	public:
		static bool IsKeyPressed(unsigned int keycode)
		{
			return keys[keycode];
		}

		static bool* GetKeys()
		{
			return keys;
		}
	};
}