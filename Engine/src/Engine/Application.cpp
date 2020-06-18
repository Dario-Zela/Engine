#include "ENPH.h"
#include "Application.h"

namespace Engine
{ 
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		aRunning = false;
		return true;
	}

	Application::Application() 
	{
		aWindow = std::unique_ptr<Window>(Window::Create());
		aWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClosed));

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
			for (Layer* layer : aLayerStack)
			{
				layer->OnUpdate();
			}
			aWindow->OnUpdate();
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