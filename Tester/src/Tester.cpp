#include <Engine.h>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	void OnUpdate() override
	{
	}

	void OnEvent(Engine::Event& e) 
	{
	}
};

class Tester : public Engine::Application
{
public:
	Tester() 
	{
		PushLayer(new ExampleLayer());
	}
	~Tester() 
	{

	}
};


Engine::Application* Engine::CreateApplication() 
{
	return new Tester();
}