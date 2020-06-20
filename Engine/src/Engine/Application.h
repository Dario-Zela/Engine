#pragma once

#include "Core.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/EventController.h"
#include "Engine/LayerStack.h"
#include "Window.h"

#include "Engine/ImGUI/ImGUILayer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"

namespace Engine 
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void OnEvent(Event& e);
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *sInstance; }
		inline Window& GetWindow() { return *mWindow; }

	private:
		static Application* sInstance;
		bool OnWindowClosed(WindowClosedEvent& e);
		std::unique_ptr<Window> mWindow;
		ImGUILayer* mImGUILayer;
		bool mRunning = true;
		LayerStack mLayerStack;

		std::shared_ptr<Shader> mShader;
		std::shared_ptr<VertexArray> mVertexArray;
	};

	// This linkes the game code to the engine and should be defined where it is used
	Application* CreateApplication();
}
