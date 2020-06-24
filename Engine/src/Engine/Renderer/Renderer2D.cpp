#include "ENPH.h"
#include "Renderer2D.h"

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;
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

		sStorage->VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indecies[] = { 0,1,2, 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(sizeof(indecies) / sizeof(unsigned int), indecies);

		sStorage->VertexArray->SetIndexBuffer(indexBuffer);

		sStorage->Shader = Shader::Create("assets/Shaders/Texture.glsl");
		sStorage->Shader->Bind();
		sStorage->Shader->SetInt("uTexture", 0);

		sStorage->WhiteTexture = Texture2D::Create(1, 1);
		unsigned int data = 0xffffffff;
		sStorage->WhiteTexture->SetData(&data);
	}

	void Renderer2D::Shutdown()
	{
		delete sStorage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sStorage->Shader->Bind();
		sStorage->Shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		sStorage->Shader->Bind();
		sStorage->Shader->SetVecF4("uColor", color);
		sStorage->WhiteTexture->Bind();
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position);
		if (rotation != 0.0f)
			tranform = glm::rotate(tranform, glm::radians(rotation), glm::vec3(0, 0, 1));
		tranform = glm::scale(tranform, { size.x, size.y, 1.0f });
		sStorage->Shader->SetMat4("uTransform", tranform);
		sStorage->Shader->SetFloat("uTexScale", 1.0f);
		sStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(sStorage->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& shade, float textureScale, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, shade, textureScale, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& shade, float textureScale, float rotation)
	{
		sStorage->Shader->Bind();
		sStorage->Shader->SetVecF4("uColor", shade);
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position);
		if (rotation != 0.0f)
			tranform = glm::rotate(tranform, glm::radians(rotation), glm::vec3(0, 0, 1));
		tranform = glm::scale(tranform, { size.x, size.y, 1.0f });
		sStorage->Shader->SetMat4("uTransform", tranform);
		sStorage->Shader->SetFloat("uTexScale", textureScale);
		texture->Bind(0);

		sStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(sStorage->VertexArray);
	}

}