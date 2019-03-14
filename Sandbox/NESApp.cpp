#include <Sgl.h>
#include "NESKeys.h"

#ifdef USE_EMSCRIPTEN
#define SHADER(x) x ".gles.shader"
#else
#define SHADER(x) x ".shader"
#endif

#define Width 512
#define Height 480

#define TexWidth 256
#define TexHeight 240

using namespace sgl;

class MainLayer : public Layer {
private:
	Renderer2D* renderer;
	Shader shader;
	Texture2D *tex0;
	NESKeyMapper keyMapper;

	std::uint8_t* pixels; // pixels[ x * height * depth + y * depth + z ] = elements[x][y][z] 

	Renderable2D renderable0;

	static unsigned int nesRGB[64];

public:
	MainLayer()
		: Layer("MainLayer"), shader("res/shaders/" SHADER("2D"))
	{
		renderer = Renderer2D::Create(Width, Height, shader);
		renderable0 = Renderable2D(glm::vec2(Width, Height), glm::vec2(0, 0));

		tex0 = new Texture2D(TexWidth, TexHeight);

		srand(time(nullptr));

		pixels = new std::uint8_t[TexWidth * TexHeight * 4];

		int i, j;

		for (i = 0; i < TexWidth; i++) {
			for (j = 0; j < TexHeight; j++) {
				auto c = HexToRgb(nesRGB[rand() % 64]);
				pixels[i * TexHeight * 4 + j * 4 + 0] = (std::uint8_t)c.x;
				pixels[i * TexHeight * 4 + j * 4 + 1] = (std::uint8_t)c.y;
				pixels[i * TexHeight * 4 + j * 4 + 2] = (std::uint8_t)c.z;
				pixels[i * TexHeight * 4 + j * 4 + 3] = (std::uint8_t)255;
			}
		}

		tex0->SetData(pixels);

		/* Input */

		keyMapper.MapKey(NESKey::Start, SGL_KEY_ENTER);
		keyMapper.MapKey(NESKey::A, SGL_KEY_A);
		keyMapper.MapKey(NESKey::B, SGL_KEY_B);
	}

	glm::vec4 HexToRgb(unsigned int hexValue)
	{
		glm::vec4 rgbColor;

		rgbColor.x = ((hexValue >> 16) & 0xFF);
		rgbColor.y = ((hexValue >> 8) & 0xFF);
		rgbColor.z = ((hexValue) & 0xFF);
		rgbColor.w = 1;

		return rgbColor;
	}

	~MainLayer()
	{
		delete pixels;
		delete tex0;
		delete renderer;
	}

	void OnUpdate() override
	{
		/* Update */

		if (Input::IsKeyPressed(keyMapper.GetKey(NESKey::Start)))
			SglInfo("Start key is down!");
		else if (Input::IsKeyPressed(keyMapper.GetKey(NESKey::A)))
			SglInfo("A key is down!");
		else if (Input::IsKeyPressed(keyMapper.GetKey(NESKey::B)))
			SglInfo("B key is down!");

		/* Render */

		renderer->Begin();
		renderer->Submit(renderable0);
		renderer->SubmitTexture(tex0);
		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::DropEvent) {
			DropEvent c = (DropEvent&)event;
			SglTrace(c.ToString());
			/* Handle ROM loading */
		}
		else if (event.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent c = (KeyPressedEvent&)event;
			SglTrace(c.ToString());
		}
		else if (event.GetEventType() == EventType::KeyReleased) {
			KeyReleasedEvent c = (KeyReleasedEvent&)event;
			SglTrace(c.ToString());
		}
	}
};

unsigned int MainLayer::nesRGB[] =
{ 0x7C7C7C, 0x0000FC, 0x0000BC, 0x4428BC, 0x940084, 0xA80020, 0xA81000, 0x881400,
  0x503000, 0x007800, 0x006800, 0x005800, 0x004058, 0x000000, 0x000000, 0x000000,
  0xBCBCBC, 0x0078F8, 0x0058F8, 0x6844FC, 0xD800CC, 0xE40058, 0xF83800, 0xE45C10,
  0xAC7C00, 0x00B800, 0x00A800, 0x00A844, 0x008888, 0x000000, 0x000000, 0x000000,
  0xF8F8F8, 0x3CBCFC, 0x6888FC, 0x9878F8, 0xF878F8, 0xF85898, 0xF87858, 0xFCA044,
  0xF8B800, 0xB8F818, 0x58D854, 0x58F898, 0x00E8D8, 0x787878, 0x000000, 0x000000,
  0xFCFCFC, 0xA4E4FC, 0xB8B8F8, 0xD8B8F8, 0xF8B8F8, 0xF8A4C0, 0xF0D0B0, 0xFCE0A8,
  0xF8D878, 0xD8F878, 0xB8F8B8, 0xB8F8D8, 0x00FCFC, 0xF8D8F8, 0x000000, 0x000000 };

class NESApp : public Application {
public:

	NESApp()
		: Application(Width, Height, "Nemu - NES Emulator")
	{
		PushLayer(new MainLayer());
	}

	~NESApp() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new NESApp;
}