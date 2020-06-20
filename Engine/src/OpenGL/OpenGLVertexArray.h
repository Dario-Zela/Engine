#pragma once
#include "Engine/Renderer/VertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) override;

		virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override {return mVertexBuffers;}
		virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return mIndexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffer;

		unsigned int mRendererID;
	};
}