#include "ENPH.h"
#include "Engine/Application.h"
#include "ImGUILayer.h"
#include "imgui.h"
#include "OpenGL/ImGUIOpengl3Renderer.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine 
{
	ImGUILayer::ImGUILayer()
		:Layer("ImGUILayer"), iTime(0.0f) {}

	ImGUILayer::~ImGUILayer()
	{

	}

	void ImGUILayer::OnUpdate()
	{

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = iTime > 0.0f ? (time - iTime) : (1.00f / 60);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGUILayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnWindowResizeEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(EN_BIND_EVENT_FN(ImGUILayer::OnKeyTypedEvent));
	}

	bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL || GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT || GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT || GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER || GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetMouseX(), e.GetMouseY());

		return false;
	}

	bool ImGUILayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetMouseYOffest();
		io.MouseWheelH += e.GetMouseXOffset();
		return false;
	}

	bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}
		return false;
	}

	bool ImGUILayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	void ImGUILayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsClassic();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGUILayer::OnDetach()
	{

	}
}