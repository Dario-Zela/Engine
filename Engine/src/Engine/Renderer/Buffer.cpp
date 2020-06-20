#include "ENPH.h"
#include "Buffer.h"

#include "OpenGL/OpenGLBuffer.h"
#include "Engine/Renderer/Render.h"

namespace Engine
{
	VertexBuffer* VertexBuffer::Create(unsigned int size, float* vertecies)
	{
		switch (Renderer::GetCurrenAPI())
		{
		case RendererAPI::API::None: EN_CORE_ASSERT(false, "No Renderer API has been selected"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(size, vertecies);
		default:
			break;
		}
		EN_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int count, unsigned int* indices)
	{
		switch (Renderer::GetCurrenAPI())
		{
		case RendererAPI::API::None: EN_CORE_ASSERT(false, "No Renderer API has been selected"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(count, indices);
		default:
			break;
	}
		EN_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

}