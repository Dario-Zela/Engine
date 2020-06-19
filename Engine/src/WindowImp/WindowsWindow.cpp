#include "ENPH.h"
#include "WindowsWindow.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "OpenGL/OpenGLContext.h"

namespace Engine
{
	static bool sGLFWInitialised = false;

	static void GLFWErrorCallback(int error, const char* description ) 
	{
		EN_CORE_ERROR("GLFW Error [{0}]: {1} ", error, description);
	}

	Window* Window::Create(const WindowProps& props) 
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() 
	{
		ShutDown();
	};

	void WindowsWindow::Init(const WindowProps& props)
	{
		wData.Title = props.Title;
		wData.Height = props.Height;
		wData.Width = props.Width;

		EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!sGLFWInitialised)
		{
			int Success = glfwInit();
			EN_CORE_ASSERT(Success, "Could not initialise GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			sGLFWInitialised = true;
		}

		wWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		wContext = new OpenGLContext(wWindow);
		
		wContext->Init();
		
		glfwSetWindowUserPointer(wWindow, &wData);
		SetVSync(true);

		// Set GLFW Callback

		glfwSetWindowSizeCallback(wWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(wWindow, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowClosedEvent event;
				data.EventCallback(event);
			});
		glfwSetCharCallback(wWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});
		glfwSetKeyCallback(wWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetMouseButtonCallback(wWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetScrollCallback(wWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(wWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::ShutDown() 
	{
		glfwDestroyWindow(wWindow);
	};

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		wContext->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) 
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		wData.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return wData.VSync;
	}
}