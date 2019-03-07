#pragma once
namespace sgl
{
	class Input {
	private:
		constexpr static auto MaxKeys = 350;
		static bool keys[MaxKeys];
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