#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include "Tester2D.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), mCameraController(1.6f/0.9f, true)
	{
		mVertexArray = Engine::VertexArray::Create();

		float vertecies[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer = Engine::VertexBuffer::Create(sizeof(vertecies), vertecies);
		{
			Engine::BufferLayout layout =
			{
				{ "aPosition", Engine::ShaderDataType::VecF3},
				{ "aTexCoord", Engine::ShaderDataType::VecF2}
			};

			vertexBuffer->SetLayout(layout);
		}

		mVertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indecies[] = { 0,1,2, 2, 3, 0 };
		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer = Engine::IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies);

		mVertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPosition;
		
		uniform mat4 uTransform;
		uniform mat4 uViewProjection;

		void main()
		{
			gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
		}
		)";

		std::string fragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;

		uniform vec3 uColor;

		void main()
		{
			color = vec4(uColor, 1.0);
		}
		)";

		mShaderLibrary.Add("FlatColor", Engine::Shader::Create(vertexSrc, fragmentSrc));

		auto textureShader = mShaderLibrary.Load("assets/Shaders/Texture.glsl");

		mTexture = Engine::Texture2D::Create("assets/Textures/Test.bmp");
		mTexture2 = Engine::Texture2D::Create("assets/Textures/Test2.png");
	}

	void OnUpdate(Engine::TimeStep timeStep) override
	{
		mCameraController.OnUpdate(timeStep);

		EN_TRACE("Time: {0}ms, or {1} fps", timeStep.GetMilliseconds(), 1.0f / timeStep.GetSeconds());
		float ts = timeStep;

		Engine::RenderCommand::Clear();
		Engine::Renderer::BeginScene(mCameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(0.1f), glm::vec3(0.1f));
		auto flatShader = mShaderLibrary.Get("FlatColor");

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 Position(x * 0.11f, y * 0.11f, 0.0f);
				auto transform = glm::translate(glm::mat4(1.0f), Position) * scale;
				Engine::Renderer::Submit(mVertexArray, mShaderLibrary.Get("FlatColor"), transform);
			}
		}

		auto textureShader =  mShaderLibrary.Get("Texture");

		mTexture->Bind(0);
		Engine::Renderer::Submit(mVertexArray, textureShader, glm::scale(glm::mat4(0.1f), glm::vec3(1.5f)));
		mTexture2->Bind(0);
		Engine::Renderer::Submit(mVertexArray, textureShader, glm::scale(glm::mat4(0.1f), glm::vec3(1.5f)));
		Engine::Renderer::EndScene();
	}

	virtual void OnImGUIRender() override
	{
		Engine::ImGUI::Begin("Settings");
		Engine::ImGUI::ColorEdit3("Color", glm::value_ptr(mColor));
		Engine::ImGUI::End();
	}

	void OnEvent(Engine::Event& e)
	{
		mCameraController.OnEvent(e);
	}

private:
		Engine::ShaderLibrary mShaderLibrary;
		Engine::Ref<Engine::VertexArray> mVertexArray;
		Engine::OrthographicCameraController mCameraController;

		Engine::Ref<Engine::Texture2D> mTexture, mTexture2;
		glm::vec3 mColor { 0.8f, 0.2f, 0.3f};
};

class Tester : public Engine::Application
{
public:
	Tester() 
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Tester2D());
	}
	~Tester() 
	{

	}
};


Engine::Application* Engine::CreateApplication() 
{
	return new Tester();
}