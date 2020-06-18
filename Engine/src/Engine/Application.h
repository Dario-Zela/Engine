#pragma once

#include "Core.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/EventController.h"
#include "Engine/LayerStack.h"
#include "Window.h"

namespace Engine 
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *sInstance; }
		inline Window& GetWindow() { return *aWindow; }
	private:

		static Application* sInstance;
		bool OnWindowClosed(WindowClosedEvent& e);
		std::unique_ptr<Window> aWindow;
		bool aRunning = true;
		LayerStack aLayerStack;
	};

	// This linkes the game code to the engine and should be defined where it is used
	Application* CreateApplication();
}
