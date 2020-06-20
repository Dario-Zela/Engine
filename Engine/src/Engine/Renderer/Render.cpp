#include "ENPH.h"
#include "Render.h"

namespace Engine 
{
	Renderer::SceneData* Renderer::sSceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("uViewProjection", sSceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("uTransform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	void Renderer::EndScene()
	{
	}
}