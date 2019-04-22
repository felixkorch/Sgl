#include "Sgl/ImGuiLayer.h"
#include "Sgl/Events/KeyCodes.h"
#include "Sgl/ImGuiRenderer.h"
#include "Sgl/Application.h"
#include "Sgl/OpenGL.h"
#include "Sgl/Log.h"
#include "GLFW/glfw3.h"

namespace sgl {

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{

}

ImGuiLayer::~ImGuiLayer()
{

}

void ImGuiLayer::OnEvent(Event& event)
{
    EventDispatcher dispatcher(&event);
    dispatcher.Dispatch<MouseButtonPressed>(SGL_BIND_EVENT(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleased>(SGL_BIND_EVENT(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(SGL_BIND_EVENT(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(SGL_BIND_EVENT(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(SGL_BIND_EVENT(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyTypedEvent>(SGL_BIND_EVENT(ImGuiLayer::OnKeyTypedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(SGL_BIND_EVENT(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<WindowResizedEvent>(SGL_BIND_EVENT(ImGuiLayer::OnWindowResizeEvent));
}

void ImGuiLayer::OnUpdate()
{
}

void ImGuiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.KeyMap[ImGuiKey_Tab]        = SGL_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]  = SGL_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SGL_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]    = SGL_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow]  = SGL_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp]     = SGL_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown]   = SGL_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home]       = SGL_KEY_HOME;
    io.KeyMap[ImGuiKey_End]        = SGL_KEY_END;
    io.KeyMap[ImGuiKey_Insert]     = SGL_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete]     = SGL_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace]  = SGL_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space]      = SGL_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter]      = SGL_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape]     = SGL_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A]          = SGL_KEY_A;
    io.KeyMap[ImGuiKey_C]          = SGL_KEY_C;
    io.KeyMap[ImGuiKey_V]          = SGL_KEY_V;
    io.KeyMap[ImGuiKey_X]          = SGL_KEY_X;
    io.KeyMap[ImGuiKey_Y]          = SGL_KEY_Y;
    io.KeyMap[ImGuiKey_Z]          = SGL_KEY_Z;

    #ifndef PLATFORM_WEB
    ImGui_ImplOpenGL3_Init("#version 330");
    #else
    ImGui_ImplOpenGL3_Init("#version 300 es");
    #endif
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressed* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e->GetButton()] = true;

    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleased* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e->GetButton()] = false;

    return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e->GetXPos(), e->GetYPos());

    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e->GetXOffset();
    io.MouseWheel += e->GetYOffset();

    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e->GetKeyCode()] = true;

    io.KeyCtrl = io.KeysDown[SGL_KEY_LEFT_CONTROL] || io.KeysDown[SGL_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[SGL_KEY_LEFT_SHIFT] || io.KeysDown[SGL_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[SGL_KEY_LEFT_ALT] || io.KeysDown[SGL_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[SGL_KEY_LEFT_SUPER] || io.KeysDown[SGL_KEY_RIGHT_SUPER];
    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e->GetKeyCode()] = false;

    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent* e)
{
    ImGuiIO& io = ImGui::GetIO();
    int keycode = e->GetKeyCode();
    if (keycode > 0 && keycode < 0x10000)
        io.AddInputCharacter((unsigned short)keycode);

    return false;
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizedEvent* e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e->GetWidth(), e->GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e->GetWidth(), e->GetHeight());

    return false;
}

void ImGuiLayer::OnDetach()
{

}

void ImGuiLayer::Begin()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    float currentTime = (float)glfwGetTime();
    io.DeltaTime = time > 0.0f ? (currentTime - time) : (1.0f / 60.0f);
    time = currentTime;
}

void ImGuiLayer::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}


