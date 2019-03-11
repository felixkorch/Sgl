#include "Sgl/Entrypoint.h"
#include "Sgl/Sgl2D.h"
#include "Sgl/Graphics/Texture.h"

#ifdef USE_EMSCRIPTEN
#define SHADER(x) x ".gles.shader"
#else
#define SHADER(x) x ".shader"
#endif

#define Width 512
#define Height 480

using namespace sgl;

class MainLayer : public Layer {
private:
	Renderer2D* renderer;
	Shader shader;
	Texture *tex0, *tex1;

	float* pixels;

	Renderable2D renderable0, renderable1;

	static constexpr unsigned int nesRGB[] =
	{ 0x7C7C7C, 0x0000FC, 0x0000BC, 0x4428BC, 0x940084, 0xA80020, 0xA81000, 0x881400,
	  0x503000, 0x007800, 0x006800, 0x005800, 0x004058, 0x000000, 0x000000, 0x000000,
	  0xBCBCBC, 0x0078F8, 0x0058F8, 0x6844FC, 0xD800CC, 0xE40058, 0xF83800, 0xE45C10,
	  0xAC7C00, 0x00B800, 0x00A800, 0x00A844, 0x008888, 0x000000, 0x000000, 0x000000,
	  0xF8F8F8, 0x3CBCFC, 0x6888FC, 0x9878F8, 0xF878F8, 0xF85898, 0xF87858, 0xFCA044,
	  0xF8B800, 0xB8F818, 0x58D854, 0x58F898, 0x00E8D8, 0x787878, 0x000000, 0x000000,
	  0xFCFCFC, 0xA4E4FC, 0xB8B8F8, 0xD8B8F8, 0xF8B8F8, 0xF8A4C0, 0xF0D0B0, 0xFCE0A8,
	  0xF8D878, 0xD8F878, 0xB8F8B8, 0xB8F8D8, 0x00FCFC, 0xF8D8F8, 0x000000, 0x000000 };

public:
	MainLayer()
		: Layer("GameLayer"), shader("res/shaders/" SHADER("2D"))
	{
		renderer = Renderer2D::Create(Width, Height, shader);
		renderable0 = Renderable2D(glm::vec2(Width, Height), glm::vec2(0, 0));
		renderable1 = Renderable2D(glm::vec2(100, 100), glm::vec2(0,0));
		renderable1.tid = 1;


		TextureParameters params{ TextureWrap::REPEAT, TextureFormat::RGBA, TextureFilter::NEAREST };
		tex0 = new Texture(256, 240, params);
		tex1 = new Texture("res/tile.png", params);


		srand(time(nullptr));

		pixels = new float[256 * 240 * sizeof(float)];

		for (int i = 0; i < (256 * 240 * sizeof(float)); i += (4 * 8)) {
			auto rgba = HexToRgb(nesRGB[rand() % 64]);
			for (int j = 0; j < 32; j += 4) {
				pixels[i + j + 0] = rgba.x;
				pixels[i + j + 1] = rgba.y;
				pixels[i + j + 2] = rgba.z;
				pixels[i + j + 3] = rgba.w;
			}
		}

		tex0->SetData(pixels, GL_FLOAT);
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

	~MainLayer()
	{
		delete pixels;
		delete tex0;
		delete tex1;
		delete renderer;
	}

	void OnUpdate() override
	{
		renderer->Begin();
		renderer->Submit(renderable0);
		renderer->Submit(renderable1);
		renderer->SubmitTexture(tex0);
		renderer->SubmitTexture(tex1);
		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		
	}
};

class Sandbox : public Application {
public:

	Sandbox()
		: Application(Width, Height, "Sandbox")
	{
		PushLayer(new MainLayer());
	}

	~Sandbox() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new Sandbox;
}