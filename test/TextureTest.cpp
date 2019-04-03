#include <Sgl.h>
#include <ctime>
#include <functional>

#define Width 1280
#define Height 720

#define TexWidth 512
#define TexHeight 480

using namespace sgl;

class MainLayer : public Layer {
private:
	std::unique_ptr<Renderer2D> renderer;
	std::unique_ptr<std::uint8_t[]> pixels; // pixels[ x * height * depth + y * depth + z ] = elements[x][y][z] 

	Texture2D tex0, tex1;
	Renderable2D renderable0, renderable1;

	static unsigned int nesRGB[64];
	const float aspectRatio = (float)TexWidth / (float)TexHeight;

public:
	MainLayer() :
		Layer("GameLayer"),
		renderer(Renderer2D::Create(Width, Height)),
		pixels(new std::uint8_t[TexWidth * TexHeight * 4]),
		tex0(TexWidth, TexHeight),
		tex1(100, 100)

	{
		const float scaledWidth = (float)Height * aspectRatio;
		const float xPosition = Width / 2 - scaledWidth / 2;

		renderable0 = Renderable2D(glm::vec2(scaledWidth, Height), glm::vec2(xPosition, 0));
		renderable1 = Renderable2D(glm::vec2(100, 100), glm::vec2(0, 0));
		renderable1.tid = 1;

		tex1.SetColor(255, 150, 150, 255);


		srand(time(nullptr));

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

		tex0.SetData(pixels.get());
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

    ~MainLayer() override
	{
	}

	void OnUpdate() override
	{
		renderer->Begin();
		renderer->Submit(renderable0);
		//renderer->Submit(renderable1);
		renderer->SubmitTexture(&tex0);
		renderer->SubmitTexture(&tex1);
		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::DropEvent) {
			auto& e = (DropEvent&)event;
			SglTrace(e.ToString());
		}

		else if (event.GetEventType() == EventType::KeyPressed) {
			auto& e = (KeyPressedEvent&)event;
		}

		else if (event.GetEventType() == EventType::WindowResizedEvent) {
			auto& e = (WindowResizedEvent&)event;

			// Width according to aspect ratio
			const float scaledWidth = (float)e.GetHeight() * aspectRatio;
			// Centralize the frame
			const float xPosition = e.GetWidth() / 2 - scaledWidth / 2;
			// Update the renderable
			renderable0 = Renderable2D(glm::vec2(scaledWidth, e.GetHeight()), glm::vec2(xPosition, 0));
			// Set size of camera
			renderer->SetScreenSize(e.GetWidth(), e.GetHeight());
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


class OverLayTest : public Layer {
public:
	OverLayTest()
		: Layer("TestOverlay") {}

    ~OverLayTest() override
	{
	}

	void OnAttach() override
	{

	}

	void OnDetach() override
	{
		SglTrace("Terminating overlay");
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed) {
			SglTrace("Key pressed from Overlay");
		}
	}

	void OnUpdate() override
	{

	}
};

const WindowProperties props {
		Width,         // WindowWidth
		Height,        // WindowHeight
		false,         // Resizable
		"TextureTest", // Title
};

class NESApp : public Application {
private:

public:

	NESApp()
		: Application(props)
	{
		window->SetFPS(60);
		PushLayer(new MainLayer);
	}

	~NESApp() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new NESApp;
}
