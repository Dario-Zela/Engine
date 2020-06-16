#include <Engine.h>

class Tester : public Engine::Application
{
public:
	Tester() 
	{

	}
	~Tester() 
	{

	}
};


Engine::Application* Engine::CreateApplication() 
{
	return new Tester();
}