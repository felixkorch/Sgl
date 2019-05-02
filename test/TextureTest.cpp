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
    Renderer2D renderer;
	std::unique_ptr<Texture2D> tex0, tex1;
    Group group0;
	Renderable2D sprite0, sprite1, sprite2;
	const float aspectRatio = (float)TexWidth / (float)TexHeight;

    bool showSettings;

public:
	MainLayer()
        : Layer("GameLayer")
        , tex0(Texture2D::Create(TexWidth, TexHeight))
        , tex1(Texture2D::Create(100, 100))
        , group0(glm::translate(glm::mat4(1), glm::vec3(300, 0, 0)))
        , showSettings(false)
        , renderer(Width, Height)

	{
		renderer.SetPostEffectsShader(Shader::CreateFromString(Shader::GreyScaleShader));
		tex1->SetColor(120, 120, 160, 255);
		tex1->SetColor(255, 150, 150, 255);

		const float scaledWidth = (float)Height * aspectRatio;
		const float xPosition = Width / 2 - scaledWidth / 2;

        sprite0 = Renderable2D(glm::vec2(100, 100), glm::vec2(0, 0), glm::vec4(0.5, 0.5, 0.5, 0.5));
        sprite1 = Renderable2D(0, 0, tex1.get());
        sprite1.SetPos(200, 0);
        sprite2 = Renderable2D(0, 0, tex1.get());

        group0.Add(&sprite0);
        group0.Add(&sprite1);
	}

    ~MainLayer() override
	{
	}

	void OnUpdate() override
	{
		renderer.Begin();
        group0.Submit(&renderer);
        sprite2.Submit(&renderer);
		renderer.End();
		renderer.Flush();
	}

    void OnImGuiRender() override
    {
        auto& app = Application::Get();
        static int counter = 0;

        //ImGui::ShowDemoWindow();

        if (showSettings) {
            bool show = ImGui::Begin("Settings", &showSettings, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
            if (!show) {
                ImGui::End();
            }
            else {
                ImGui::SetWindowSize(ImVec2((float)app.GetWindow()->GetWidth() * 0.75, (float)app.GetWindow()->GetHeight() * 0.75));
                ImGui::SetWindowPos(ImVec2((float)app.GetWindow()->GetWidth() * 0.125, (float)app.GetWindow()->GetHeight() * 0.125));

                ImGui::Columns(2, "Columns", false);
                ImGui::Separator();

                ImGui::Text("Set Frames per second.");
                ImGui::SameLine();
                //ImGui::SliderInt("FPS", &app.GetWindow()->GetFPS(), 30, 144);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                ImGui::NextColumn();

                if (ImGui::Button("Save State"))
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::End();
            }
        }
    }

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::DropEvent) {
			auto& e = (DropEvent&)event;
			SGL_TRACE(e.ToString());
		}

		else if (event.GetEventType() == EventType::KeyPressed) {
            KeyPressedEvent& e = (KeyPressedEvent&)event;
            if (e.GetKeyCode() == SGL_KEY_ESCAPE) {
                showSettings = !showSettings;
            }
		}

		else if (event.GetEventType() == EventType::WindowResized) {
			auto& e = (WindowResizedEvent&)event;

			// Width according to aspect ratio
			const float scaledWidth = (float)e.GetHeight() * aspectRatio;
			// Centralize the frame
			const float xPosition = e.GetWidth() / 2 - scaledWidth / 2;
			// Set new camera
			renderer.SetCamera(Camera2D::Create(e.GetWidth(), e.GetHeight()));
		}
	}
};

const WindowProperties props {
		Width,         // WindowWidth
		Height,        // WindowHeight
		true,         // Resizable
		"TextureTest", // Title
};

class NESApp : public Application {
private:

public:

	NESApp()
		: Application(props)
	{
		PushLayer(new MainLayer);
	}

	~NESApp()
    {
    }

};

sgl::Application* sgl::CreateApplication()
{
	return new NESApp;
}
