#pragma once
#include "Engine/Layer.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine
{
	class ENGINE_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();

		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnImGUIRender() override;

		void Begin();
		void End();
	private:
		float iTime;
	};
}