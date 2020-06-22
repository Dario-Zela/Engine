#include "ENPH.h"
#include "Renderer2D.h"

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"
#include <OpenGL/OpenGLShader.h>
#include "Engine/Renderer/RenderCommand.h"

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
	};

	static Renderer2DStorage* sStorage;

	void Renderer2D::Init()
	{
		sStorage = new Renderer2DStorage();
		sStorage->VertexArray = VertexArray::Create();

		float vertecies[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(sizeof(vertecies), vertecies);
		{
			BufferLayout layout =
			{
				{ "aPosition", ShaderDataType::VecF3},
				{ "aTexCoord", ShaderDataType::VecF2}
			};

			vertexBuffer->SetLayout(layout);
		}

		sStorage->VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indecies[] = { 0,1,2, 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies);

		sStorage->VertexArray->SetIndexBuffer(indexBuffer);

		sStorage->Shader = Shader::Create("assets/Shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete sStorage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(sStorage->Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(sStorage->Shader)->UploadUniformMat4("uViewProjection", camera.GetProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(sStorage->Shader)->UploadUniformMat4("uTransform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(sStorage->Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(sStorage->Shader)->UploadUniformVecF4("uColor", color);
		sStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(sStorage->VertexArray);
	}

}