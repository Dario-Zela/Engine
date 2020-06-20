#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Engine
{
	class Renderer 
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);
		static void EndScene();

		inline static RendererAPI::API GetCurrenAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* sSceneData;
	};
}