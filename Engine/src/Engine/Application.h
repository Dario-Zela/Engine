#pragma once

#include "Core.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/EventController.h"
#include "Engine/LayerStack.h"
#include "Window.h"

#include "Engine/ImGUI/ImGUILayer.h"

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
		ImGUILayer* aImGUILayer;
		bool aRunning = true;
		LayerStack aLayerStack;

		unsigned int aVertexArray, aVertexBuffer, aIndexBuffer;
	};

	// This linkes the game code to the engine and should be defined where it is used
	Application* CreateApplication();
}
