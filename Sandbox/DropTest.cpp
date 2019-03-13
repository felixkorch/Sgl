#include "Sgl/Sgl2D.h"

#ifdef USE_EMSCRIPTEN
#define SHADER(x) x ".gles.shader"
#else
#define SHADER(x) x ".shader"
#endif

#define Width 512
#define Height 480

#define TexWidth 32
#define TexHeight 30

using namespace sgl;

class MainLayer : public Layer {
private:
	Renderer2D* renderer;
	Shader shader;
	Texture2D *tex0;
	Renderable2D renderable0;

public:
	MainLayer()
		: Layer("Main Layer"), shader("res/shaders/" SHADER("2D"))
	{
		renderer = Renderer2D::Create(Width, Height, shader);
		renderable0 = Renderable2D(glm::vec2(Width, Height), glm::vec2(0, 0));

		tex0 = new Texture2D(Width, Height);
	}


	~MainLayer()
	{
		delete tex0;
		delete renderer;
	}

	void OnUpdate() override
	{
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
			
			auto file = c.GetPaths()[0];
			tex0 = new Texture2D(file);

		}
	}
};


class DropTest : public Application {
public:

	DropTest()
		: Application(Width, Height, "DropTest")
	{
		PushLayer(new MainLayer());
	}

	~DropTest() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new DropTest;
}