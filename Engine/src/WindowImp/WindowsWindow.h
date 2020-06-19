#pragma once
#include "Engine/Window.h"
#include "Engine/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Engine 
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return wData.Width; }
		inline unsigned int GetHeight() const override { return wData.Height; }

		//Window Atributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { wData.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const { return (void*)wWindow; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
		
		GLFWwindow* wWindow;
		GraphicsContext* wContext;

		struct WindowData
		{
			std::string  Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData wData;
	};

}