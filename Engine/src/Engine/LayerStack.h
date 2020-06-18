#pragma once

#include "Engine/Core.h"
#include "Layer.h"

namespace Engine 
{
	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return lLayers.begin(); }
		std::vector<Layer*>::iterator end() { return lLayers.end(); }

	private:
		std::vector<Layer*> lLayers;
		std::vector<Layer*>::iterator lLayerInsert;
	};
}