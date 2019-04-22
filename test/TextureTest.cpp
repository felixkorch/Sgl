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

	Texture2D tex0, tex1;
	Sprite sprite0, sprite1;

	const float aspectRatio = (float)TexWidth / (float)TexHeight;

    bool showSettings;

public:
	MainLayer() :
		Layer("GameLayer"),
		tex0(TexWidth, TexHeight),
		tex1(100, 100),
        showSettings(false)

	{
        renderer = std::unique_ptr<Renderer2D>(Renderer2D::Create(Width, Height));

		const float scaledWidth = (float)Height * aspectRatio;
		const float xPosition = Width / 2 - scaledWidth / 2;

        tex0.SetColor(120, 120, 160, 255);
		tex1.SetColor(255, 150, 150, 255);

		sprite0 = Sprite(0, 0, &tex0);
		sprite1 = Sprite(0, 0, &tex1);
        sprite1.SetPos(Width - 100, Height - 100);
	}

    ~MainLayer() override
	{
	}

	void OnUpdate() override
	{
		renderer->Begin();
        sprite0.Submit(renderer.get());
        sprite1.Submit(renderer.get());
		renderer->End();
		renderer->Flush();
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
                ImGui::SliderInt("FPS", &app.GetWindow()->GetFPS(), 30, 144);
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
			// Update the renderable
            sprite0.SetSize(scaledWidth, e.GetHeight());
            sprite0.SetPos(xPosition, 0);
			// Set new camera
			renderer->SetCamera(Camera2D::Create(e.GetWidth(), e.GetHeight()));
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

	~NESApp() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new NESApp;
}
