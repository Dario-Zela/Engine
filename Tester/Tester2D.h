#pragma once
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Tester2D : public Engine::Layer
{
public:
	Tester2D();
	~Tester2D() = default;
	void OnUpdate(Engine::TimeStep timeStep) override;
	virtual void OnImGUIRender() override;
	void OnEvent(Engine::Event& e);
	virtual void OnAttach() override;
	virtual void OnDetach() override;
private:
	Engine::OrthographicCameraController mCameraController;
	int num = 360;
	Engine::Ref<Engine::VertexArray> mVertexArray;
	Engine::Ref<Engine::Shader> mShader;
	Engine::Ref<Engine::Texture2D> mTexture;
	glm::vec3 mColor{ 0.8f, 0.2f, 0.3f };
};