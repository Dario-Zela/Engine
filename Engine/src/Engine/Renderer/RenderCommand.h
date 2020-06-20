#pragma once

#include "RendererAPI.h"

namespace Engine
{
	class ENGINE_API RenderCommand
	{
	public:
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { sRendererAPI->DrawIndexed(vertexArray); }
		inline static void Clear(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) { sRendererAPI->Clear(color); }
	private:
		static RendererAPI* sRendererAPI;
	};
}