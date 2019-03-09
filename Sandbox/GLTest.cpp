#include "Sgl/Entrypoint.h"
#include "Sgl/Sgl2D.h"

#ifdef USE_EMSCRIPTEN
#define SHADER(x) x ".gles.shader"
#else
#define SHADER(x) x ".shader"
#endif

using namespace sgl;

class TestLayer : public Layer {
private:
	Shader* shader;
	IndexBuffer* iBuffer;
	VertexBuffer vBuffer;
	VertexBufferLayout layout;
public:
	TestLayer()
		: Layer("GameLayer")
	{
		shader = new Shader("res/shaders/" SHADER("GLTest"));
		shader->Bind();

		const static float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		const static unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		iBuffer = new IndexBuffer(indices, 6);

		//vBuffer.InitStaticDraw(vertices, 12 * sizeof(float));
		vBuffer.InitDynamicDraw(12 * sizeof(float));
		glBufferSubData(GL_ARRAY_BUFFER, 0, 12 * sizeof(float), vertices);

		layout.Push<float>(3);
		vBuffer.BindLayout(layout);
		vBuffer.Unbind();

	}

	void OnUpdate() override
	{
		shader->Bind();
		vBuffer.Bind();
		iBuffer->Bind();
		vBuffer.BindLayout(layout);
		std::cout << "Before draw" << std::endl;
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		std::cout << "After draw" << std::endl;

		vBuffer.Unbind();
		iBuffer->Unbind();

	}

	void OnEvent(Event& event) override
	{
		
	}
};

class GLTest : public Application {
public:

	GLTest()
		: Application(1280, 720, "Sandbox")
	{
		PushLayer(new TestLayer());
	}

	~GLTest() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new GLTest;
}
