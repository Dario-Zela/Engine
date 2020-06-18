#include "ENPH.h"
#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
		lLayerInsert = lLayers.begin();
	}

	LayerStack::~LayerStack() 
	{
		for (Layer* layer : lLayers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		lLayerInsert = lLayers.emplace(lLayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		lLayers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(lLayers.begin(), lLayers.end(), layer);
		if (it != lLayers.end())
		{
			lLayers.erase(it);
			lLayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(lLayers.begin(), lLayers.end(), overlay);
		if (it != lLayers.end())
		{
			lLayers.erase(it);
		}
	}
}