#include "ENPH.h"
#include "glad/glad.h"
#include "Application.h"
#include "Input.h"

namespace Engine
{ 
	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None: EN_CORE_ASSERT(false, "Invalid ShaderDataType"); return GL_NONE;
		case ShaderDataType::VecF2: return GL_FLOAT;
		case ShaderDataType::VecF3: return GL_FLOAT;
		case ShaderDataType::VecF4: return GL_FLOAT;
		case ShaderDataType::VecI2: return GL_INT;
		case ShaderDataType::VecI3: return GL_INT;
		case ShaderDataType::VecI4: return GL_INT;
		case ShaderDataType::MatF2: return GL_FLOAT;
		case ShaderDataType::MatF3: return GL_FLOAT;
		case ShaderDataType::MatF4: return GL_FLOAT;
		case ShaderDataType::MatI2: return GL_INT;
		case ShaderDataType::MatI3: return GL_INT;
		case ShaderDataType::MatI4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}

		EN_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

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
		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(EN_BIND_EVENT_FN(Application::OnEvent));

		mImGUILayer = new ImGUILayer();
		mLayerStack.PushOverlay(mImGUILayer);

		glGenVertexArrays(1, &aVertexArray);
		glBindVertexArray(aVertexArray);

		float vertecies[] = 
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0,
			0.5f, -0.5f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0
		};

		mVertexBuffer.reset(VertexBuffer::Create(sizeof(vertecies), vertecies));
		{
			BufferLayout layout =
			{
				{ "aPosition", ShaderDataType::VecF3},
				{ "aColor", ShaderDataType::VecF4 }
			};

			mVertexBuffer->SetLayout(layout);
		}
		unsigned int index = 0;
		const auto& layout = mVertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetElementCount(), ShaderDataTypeToGLBaseType(element.Type),
				element.Normalised ? GL_TRUE : GL_FALSE, layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		unsigned int indecies[3] = { 0,1,2 };
		mIndexBuffer.reset(IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies));
		mIndexBuffer->Bind();

		std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPosition;
		layout(location = 1) in vec4 aColor;
		out vec4 vCombined;

		void main()
		{
			vCombined = (vec4(aPosition  * 0.5 + 0.5, 1.0) + aColor) / 2.0;
			gl_Position = vec4(aPosition,1.0);
		}
		)";

		std::string fragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;
		in vec4 vCombined;		

		void main()
		{
			color = vec4(vCombined);
		}
		)";

		mShader.reset(new Shader(vertexSrc, fragmentSrc));
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
			glClear(GL_COLOR_BUFFER_BIT);

			mShader->Bind();
			glBindVertexArray(aVertexArray);
			glDrawElements(GL_TRIANGLES, mIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : mLayerStack)
			{
				layer->OnUpdate();
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