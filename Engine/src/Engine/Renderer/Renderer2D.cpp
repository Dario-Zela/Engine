#include "ENPH.h"
#include "Renderer2D.h"

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	struct QuadVertex
	{
		glm::vec4 position;
		glm::vec2 texCoord;
		glm::vec4 color;
	};

	struct Renderer2DStorage
	{
		const unsigned int MaxQuads = 10000;
		const unsigned int MaxVerteces = MaxQuads * 4;
		const unsigned int MaxIndeces= MaxQuads * 6;

		Ref<VertexArray> QuadVA;
		Ref<VertexBuffer> QuadVB;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;

		unsigned int QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DStorage sStorage;

	void Renderer2D::Init()
	{
		sStorage.QuadVA = VertexArray::Create();
		sStorage.QuadVB = VertexBuffer::Create(sStorage.MaxVerteces * sizeof(QuadVertex));
		{
			BufferLayout layout =
			{
				{ "aPosition", ShaderDataType::VecF4},
				{ "aTexCoord", ShaderDataType::VecF2},
				{ "aColor", ShaderDataType::VecF4}
			};

			sStorage.QuadVB->SetLayout(layout);
		}

		sStorage.QuadVA->AddVertexBuffer(sStorage.QuadVB);

		sStorage.QuadVertexBufferBase = new QuadVertex[sStorage.MaxVerteces];

		unsigned int* quadIndeces = new uint32_t[sStorage.MaxIndeces];

		unsigned int offset = 0;
		for (unsigned int i = 0; i < sStorage.MaxIndeces;)
		{
			quadIndeces[i++] = offset + 0;
			quadIndeces[i++] = offset + 1;
			quadIndeces[i++] = offset + 2;

			quadIndeces[i++] = offset + 2;
			quadIndeces[i++] = offset + 3;
			quadIndeces[i++] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> QuadIndexBuffer = IndexBuffer::Create(sStorage.MaxIndeces, quadIndeces);
		sStorage.QuadVA->SetIndexBuffer(QuadIndexBuffer);
		delete[] quadIndeces;

		sStorage.Shader = Shader::Create("assets/Shaders/Texture.glsl");
		sStorage.Shader->Bind();
		//sStorage.Shader->SetInt("uTexture", 0);

		//sStorage.WhiteTexture = Texture2D::Create(1, 1);
		//unsigned int data = 0xffffffff;
		//sStorage.WhiteTexture->SetData(&data);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sStorage.Shader->Bind();
		sStorage.Shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

		sStorage.QuadIndexCount = 0;
		sStorage.QuadVertexBufferPtr = sStorage.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		unsigned int data = (unsigned char*)sStorage.QuadVertexBufferPtr - (unsigned char*)sStorage.QuadVertexBufferBase;
		sStorage.QuadVB->SetData(sStorage.QuadVertexBufferBase, data);
		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(sStorage.QuadVA, sStorage.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		//You can make it all into 1 to two multiplictions.
		glm::mat4 tranform = glm::mat4(1.0f);
		if (rotation != 0.0f)
			tranform = glm::rotate(tranform, glm::radians(rotation), glm::vec3(0, 0, 1));

		sStorage.QuadVertexBufferPtr->position = tranform * glm::vec4(position, 1.0f);
		sStorage.QuadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		sStorage.QuadVertexBufferPtr->color = color;
		sStorage.QuadVertexBufferPtr++;

		sStorage.QuadVertexBufferPtr->position = tranform * glm::vec4(position.x + size.x, position.y, position.z, 1.0f );
		sStorage.QuadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		sStorage.QuadVertexBufferPtr->color = color;
		sStorage.QuadVertexBufferPtr++;

		sStorage.QuadVertexBufferPtr->position = tranform * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f );
		sStorage.QuadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		sStorage.QuadVertexBufferPtr->color = color;
		sStorage.QuadVertexBufferPtr++;

		sStorage.QuadVertexBufferPtr->position = tranform * glm::vec4(position.x, position.y + size.y, position.z, 1.0f );
		sStorage.QuadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		sStorage.QuadVertexBufferPtr->color = color;
		sStorage.QuadVertexBufferPtr++;

		sStorage.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& shade, float textureScale, float rotation)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, shade, textureScale, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& shade, float textureScale, float rotation)
	{
		sStorage.Shader->Bind();
		sStorage.Shader->SetVecF4("uColor", shade);
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), position);
		if (rotation != 0.0f)
			tranform = glm::rotate(tranform, glm::radians(rotation), glm::vec3(0, 0, 1));
		tranform = glm::scale(tranform, { size.x, size.y, 1.0f });
		sStorage.Shader->SetMat4("uTransform", tranform);
		sStorage.Shader->SetFloat("uTexScale", textureScale);
		texture->Bind(0);

		sStorage.QuadVA->Bind();
		RenderCommand::DrawIndexed(sStorage.QuadVA);
	}

}