#include "ENPH.h"
#include "glad/glad.h"
#include "Application.h"
#include "Input.h"

namespace Engine
{ 
	Application* Application::sInstance = nullptr;

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		aRunning = false;
		return true;
	}

	Application::Application() 
	{
		EN_CORE_ASSERT(!sInstance, "Application already exists");
		sInstance = this;
		aWindow = std::unique_ptr<Window>(Window::Create());
		aWindow->SetEventCallback(EN_BIND_EVENT_FN(Application::OnEvent));

		aImGUILayer = new ImGUILayer();
		aLayerStack.PushOverlay(aImGUILayer);
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(EN_BIND_EVENT_FN(Application::OnWindowClosed));

		EN_CORE_TRACE("{0}", e);

		for (auto it = aLayerStack.end(); it != aLayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (aRunning)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : aLayerStack)
			{
				layer->OnUpdate();
			}
			aWindow->OnUpdate();

			aImGUILayer->Begin();
			for (Layer* layer : aLayerStack)
			{
				layer->OnImGUIRender();
			}
			aImGUILayer->End();

			auto [x, y] = Input::GetMousePosition();
			EN_CORE_TRACE("{0}, {1}", x, y);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		aLayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		aLayerStack.PushOverlay(overlay);
	}
}