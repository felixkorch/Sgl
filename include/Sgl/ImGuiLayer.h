#include "Sgl/Layer.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/ApplicationEvent.h"

namespace sgl {
    class ImGuiLayer : public Layer {
        float time = 0.0f;
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate() override;
        void OnEvent(Event& event) override;
        void OnAttach() override;
        void OnDetach() override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressed* e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleased* e);
        bool OnMouseMovedEvent(MouseMovedEvent* e);
        //bool OnMouseScrolledEvent(MouseScrolledEvent* e);
        bool OnKeyPressedEvent(KeyPressedEvent* e);
        bool OnKeyReleasedEvent(KeyReleasedEvent* e);
        //bool OnKeyTypedEvent(KeyTypedEvent* e);
        bool OnWindowResizeEvent(WindowResizedEvent* e);
    };
}