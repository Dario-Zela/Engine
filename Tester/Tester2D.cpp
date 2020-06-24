#include "Tester2D.h"

Tester2D::Tester2D()
	:Layer("Tester2D"), mCameraController(1280.0f / 720.0f, true)
{
}

void Tester2D::OnUpdate(Engine::TimeStep timeStep)
{
	mCameraController.OnUpdate(timeStep);
	Engine::RenderCommand::Clear();
	Engine::Renderer2D::BeginScene(mCameraController.GetCamera());
	for(float i = 0; i < num; i += 0.5f)
		Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f }, i);
	//Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.8f,0.2f,0.8f, 1.0f }, 0.0f);
	//Engine::Renderer2D::DrawQuad({ 0.0f , 0.0f , -0.1f }, { 10.0f, 10.0f }, mTexture, { 1.0f, 0.8f, 0.2f, 1.0f}, 100.0f, 10.0f);
	Engine::Renderer2D::EndScene();
}



void Tester2D::OnImGUIRender()
{
	Engine::ImGUI::Begin("Settings");
	Engine::ImGUI::ColorEdit3("Color", glm::value_ptr(mColor));
	Engine::ImGUI::DragFloat("Number", &num, 0.1f, 1.0f, 360.0f);
	Engine::ImGUI::End();
}

void Tester2D::OnEvent(Engine::Event& e)
{
	mCameraController.OnEvent(e);
}

void Tester2D::OnAttach()
{
	mTexture = Engine::Texture2D::Create("assets/Textures/Test.bmp");
}

void Tester2D::OnDetach()
{

}
