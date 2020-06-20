#include <Engine.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPosition(0.0f)
	{
		mVertexArray.reset(Engine::VertexArray::Create());

		float vertecies[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0,
			0.5f, -0.5f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0
		};
		std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(sizeof(vertecies), vertecies));
		{
			Engine::BufferLayout layout =
			{
				{ "aPosition", Engine::ShaderDataType::VecF3},
				{ "aColor", Engine::ShaderDataType::VecF4 }
			};

			vertexBuffer->SetLayout(layout);
		}

		mVertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indecies[3] = { 0,1,2 };
		std::shared_ptr<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies));

		mVertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPosition;
		layout(location = 1) in vec4 aColor;
		
		uniform mat4 uTransform;
		uniform mat4 uViewProjection;
	
		out vec4 vCombined;

		void main()
		{
			vCombined = (vec4(aPosition  * 0.5 + 0.5, 1.0) + aColor) / 2.0;
			gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
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

		mShader.reset(new Engine::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Engine::TimeStep timeStep) override
	{
		float ts = timeStep;

		if (Engine::Input::IsKeyPressed(EN_KEY_LEFT))
			mCameraPosition.x -= mCameraSpeed * ts;

		if (Engine::Input::IsKeyPressed(EN_KEY_UP))
			mCameraPosition.y += mCameraSpeed * ts;

		if (Engine::Input::IsKeyPressed(EN_KEY_RIGHT))
			mCameraPosition.x += mCameraSpeed * ts;

		if (Engine::Input::IsKeyPressed(EN_KEY_DOWN))
			mCameraPosition.y -= mCameraSpeed * ts;

		if (Engine::Input::IsKeyPressed(EN_KEY_A))
			mCameraRotation -= mCameraRotationSpeed * ts;

		if (Engine::Input::IsKeyPressed(EN_KEY_D))
			mCameraRotation += mCameraRotationSpeed * ts;

		Engine::RenderCommand::Clear();

		mCamera.SetRotation(mCameraRotation);
		mCamera.SetPosition(mCameraPosition);

		Engine::Renderer::BeginScene(mCamera);

		glm::mat4 scale = glm::scale(glm::mat4(0.1f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 Position(x * 0.11f, y * 0.11f, 0.0f);
				auto transform = glm::translate(glm::mat4(1.0f), Position) * scale;
				Engine::Renderer::Submit(mVertexArray, mShader, transform);
			}
		}

		Engine::Renderer::EndScene();
	}

	void OnEvent(Engine::Event& e)
	{

	}

private:
		std::shared_ptr<Engine::Shader> mShader;
		std::shared_ptr<Engine::VertexArray> mVertexArray;
		Engine::OrthographicCamera mCamera;
		glm::vec3 mCameraPosition;
		float mCameraSpeed = 5.0f;

		float mCameraRotation = 0.0f;
		float mCameraRotationSpeed = 180.0f;
};

class Tester : public Engine::Application
{
public:
	Tester() 
	{
		PushLayer(new ExampleLayer());
	}
	~Tester() 
	{

	}
};


Engine::Application* Engine::CreateApplication() 
{
	return new Tester();
}