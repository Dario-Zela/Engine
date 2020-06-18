#pragma once

#include "Engine/Core.h"
#include "Engine/Events/EventController.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return lDebugName; }

	private:
		std::string lDebugName;
	};
}