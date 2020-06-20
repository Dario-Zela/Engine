#pragma once
#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Clear(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}