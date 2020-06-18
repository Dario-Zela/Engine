#include <Engine.h>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example") { }

	void OnUpdate() override
	{
		EN_INFO("Example Layer Update");
	}

	void OnEvent(Engine::Event& e) 
	{
		EN_TRACE("{0}", e);
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