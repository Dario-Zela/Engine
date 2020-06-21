#include <Engine.h>
#include <glm/gtc/matrix_transform.hpp>

#include <OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPosition(0.0f)
	{
		mVertexArray.reset(Engine::VertexArray::Create());

		float vertecies[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(sizeof(vertecies), vertecies));
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
		indexBuffer.reset(Engine::IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies));

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

		mShader.reset(Engine::Shader::Create(vertexSrc, fragmentSrc));

		mTexShader.reset(Engine::Shader::Create("assets/Shaders/Texture.glsl"));

		mTexture = Engine::Texture2D::Create("assets/Textures/Test.bmp");
		mTexture2 = Engine::Texture2D::Create("assets/Textures/Test2.png");

		std::dynamic_pointer_cast<Engine::OpenGLShader>(mTexShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(mTexShader)->UploadUniformInt("uTexture", 0);
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

		std::dynamic_pointer_cast<Engine::OpenGLShader>(mShader)->Bind();
		std::dynamic_pointer_cast<Engine::OpenGLShader>(mShader)->UploadUniformVecF3("uColor", mColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 Position(x * 0.11f, y * 0.11f, 0.0f);
				auto transform = glm::translate(glm::mat4(1.0f), Position) * scale;
				Engine::Renderer::Submit(mVertexArray, mShader, transform);
			}
		}

		mTexture->Bind(0);
		Engine::Renderer::Submit(mVertexArray, mTexShader, glm::scale(glm::mat4(0.1f), glm::vec3(1.5f)));
		mTexture2->Bind(0);
		Engine::Renderer::Submit(mVertexArray, mTexShader, glm::scale(glm::mat4(0.1f), glm::vec3(1.5f)));
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

	}

private:
		Engine::Ref<Engine::Shader> mShader;
		Engine::Ref<Engine::Shader> mTexShader;
		Engine::Ref<Engine::VertexArray> mVertexArray;
		Engine::OrthographicCamera mCamera;
		glm::vec3 mCameraPosition;
		float mCameraSpeed = 5.0f;

		float mCameraRotation = 0.0f;
		float mCameraRotationSpeed = 180.0f;

		Engine::Ref<Engine::Texture2D> mTexture, mTexture2;
		glm::vec3 mColor { 0.8f, 0.2f, 0.3f};
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