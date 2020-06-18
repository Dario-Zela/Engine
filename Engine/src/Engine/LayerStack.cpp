#include "ENPH.h"
#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack() 
	{
		for (Layer* layer : lLayers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		lLayers.emplace(lLayers.begin() + lLayerInsertIndex, layer);
		lLayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		lLayers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(lLayers.begin(), lLayers.end(), layer);
		if (it != lLayers.end())
		{
			lLayers.erase(it);
			lLayerInsertIndex--;
		}
		layer->OnDetach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(lLayers.begin(), lLayers.end(), overlay);
		if (it != lLayers.end())
		{
			lLayers.erase(it);
		}
		overlay->OnDetach();
	}
}