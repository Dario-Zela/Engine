#pragma once

#include "Core.h"

namespace Engine 
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// This linkes the game code to the engine and should be defined where it is used
	Application* CreateApplication();
}
