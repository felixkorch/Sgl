/*
#include "Sgl/Sgl2D.h"

#ifdef USE_EMSCRIPTEN
#define Shader(x) x ".gles3.shader"
#else
#define Shader(x) x ".shader"
#endif

using namespace sgl;

class MainLayer : public Layer {
private:
	BatchRenderer* renderer;
public:
	MainLayer()
		: Layer("GameLayer")
	{
		Shader shader("res/shaders/" Shader("2D"));
		renderer = new BatchRenderer(512, 480, shader);
	}

	glm::vec4 HexToRgb(unsigned int hexValue)
	{
		glm::vec4 rgbColor;

		rgbColor.x = ((hexValue >> 16) & 0xFF) / 255.0;
		rgbColor.y = ((hexValue >> 8) & 0xFF) / 255.0;
		rgbColor.z = ((hexValue) & 0xFF) / 255.0;
		rgbColor.w = 1;

		return rgbColor;
	}

	void OnUpdate() override
	{
		ClientTrace("Main loop");

		srand(time(nullptr));

		glm::vec2 nesRes(512, 480);

		const std::array<unsigned int, 64> nesRGB =
		{ 0x7C7C7C, 0x0000FC, 0x0000BC, 0x4428BC, 0x940084, 0xA80020, 0xA81000, 0x881400,
		  0x503000, 0x007800, 0x006800, 0x005800, 0x004058, 0x000000, 0x000000, 0x000000,
		  0xBCBCBC, 0x0078F8, 0x0058F8, 0x6844FC, 0xD800CC, 0xE40058, 0xF83800, 0xE45C10,
		  0xAC7C00, 0x00B800, 0x00A800, 0x00A844, 0x008888, 0x000000, 0x000000, 0x000000,
		  0xF8F8F8, 0x3CBCFC, 0x6888FC, 0x9878F8, 0xF878F8, 0xF85898, 0xF87858, 0xFCA044,
		  0xF8B800, 0xB8F818, 0x58D854, 0x58F898, 0x00E8D8, 0x787878, 0x000000, 0x000000,
		  0xFCFCFC, 0xA4E4FC, 0xB8B8F8, 0xD8B8F8, 0xF8B8F8, 0xF8A4C0, 0xF0D0B0, 0xFCE0A8,
		  0xF8D878, 0xD8F878, 0xB8F8B8, 0xB8F8D8, 0x00FCFC, 0xF8D8F8, 0x000000, 0x000000 };

		renderer->Begin();

		for (int i = 0; i < nesRes.x; i += 16) {
			for (int j = 0; j < nesRes.y; j += 16) {
				renderer->DrawRectangle(glm::vec2(16, 16), glm::vec2(i, j), HexToRgb(nesRGB[rand() % 64]));
			}
		}

		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent k = (KeyPressedEvent&)event;

			switch (k.GetKeyCode()) {
			case SGL_KEY_RIGHT: {
				ClientTrace("Right key pressed!");
				break;
			}
			case SGL_KEY_LEFT: {
				ClientTrace("Left key pressed!");
				break;
			}
			}
		}
		if (event.GetEventType() == EventType::MouseButtonPressed) {
			MouseButtonPressed c = (MouseButtonPressed&)event;
			ClientTrace(c.ToString());
		}
	}
};

class Sandbox : public Application {
public:

	Sandbox()
		: Application(512, 480, "Sandbox")
	{
		PushLayer(new MainLayer());
	}

	~Sandbox() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new Sandbox;
}*/