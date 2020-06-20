#pragma once

#include "RendererAPI.h"

namespace Engine
{
	class RenderCommand
	{
	public:
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { sRendererAPI->DrawIndexed(vertexArray); }
		inline static void Clear(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) { sRendererAPI->Clear(color); }
	private:
		static RendererAPI* sRendererAPI;
	};
}