#include "ENPH.h"
#include "Application.h"
#include "Input.h"
#include "Engine/Renderer/Render.h"

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
		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(EN_BIND_EVENT_FN(Application::OnEvent));

		mImGUILayer = new ImGUILayer();
		mLayerStack.PushOverlay(mImGUILayer);

		mVertexArray.reset(VertexArray::Create());

		float vertecies[] = 
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0,
			0.5f, -0.5f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(sizeof(vertecies), vertecies));
		{
			BufferLayout layout =
			{
				{ "aPosition", ShaderDataType::VecF3},
				{ "aColor", ShaderDataType::VecF4 }
			};

			vertexBuffer->SetLayout(layout);
		}
		
		mVertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indecies[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies));
		
		mVertexArray->SetIndexBuffer(indexBuffer);

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
			RenderCommand::Clear();

			Renderer::BeginScene();
			mShader->Bind();
			Renderer::Submit(mVertexArray);
			Renderer::EndScene();

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