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

		glGenVertexArrays(1, &aVertexArray);
		glBindVertexArray(aVertexArray);

		glGenBuffers(1, &aVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, aVertexBuffer);

		float vertecies[9] = 
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &aIndexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, aIndexBuffer);

		unsigned int indecies[3] = { 0,1,2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(EN_BIND_EVENT_FN(Application::OnWindowClosed));

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
			glBindVertexArray(aVertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


			for (Layer* layer : aLayerStack)
			{
				layer->OnUpdate();
			}

			aImGUILayer->Begin();
			for (Layer* layer : aLayerStack)
			{
				layer->OnImGUIRender();
			}
			aImGUILayer->End();

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