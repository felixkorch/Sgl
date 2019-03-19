#include <Sgl.h>
#include <ctime>

#ifdef USE_EMSCRIPTEN
#define VertexShader   Shader::GLES2_Vertex_Shader2D
#define FragmentShader Shader::GLES2_Fragment_Shader2D
#else
#define VertexShader   Shader::Core_Vertex_Shader2D
#define FragmentShader Shader::Core_Fragment_Shader2D
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
		: Layer("Main Layer"), shader(VertexShader, FragmentShader)
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
		if (Input::IsKeyPressed(SGL_KEY_RIGHT)) {
			renderable0.bounds.pos.x += 1;
		}
		else if (Input::IsKeyPressed(SGL_KEY_LEFT)) {
			renderable0.bounds.pos.x -= 1;
		}

		renderer->Begin();
		renderer->Submit(renderable0);
		renderer->SubmitTexture(tex0);
		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::DropEvent) {
			auto& c = (DropEvent&)event;
			
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