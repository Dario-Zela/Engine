#include "ENPH.h"
#include "Application.h"
#include "Input.h"
#include "Engine/Renderer/Render.h"
#include "GLFW/glfw3.h"

namespace Engine
{ 
	Application* Application::sInstance = nullptr;

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		mRunning = false;
		return true;
	}

	Application::Application()
	{
		EN_CORE_ASSERT(!sInstance, "Application already exists");
		sInstance = this;
		mWindow = Scope<Window>(Window::Create());
		mWindow->SetEventCallback(EN_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		mImGUILayer = new ImGUILayer();
		PushOverlay(mImGUILayer);
	}

	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(EN_BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (mRunning)
		{
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - mLastFrameTime ;
			mLastFrameTime = time;

			for (Layer* layer : mLayerStack)
			{
				layer->OnUpdate(timeStep);
			}

			mImGUILayer->Begin();
			for (Layer* layer : mLayerStack)
			{
				layer->OnImGUIRender();
			}
			mImGUILayer->End();

			mWindow->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		mLayerStack.PushOverlay(overlay);
	}


}