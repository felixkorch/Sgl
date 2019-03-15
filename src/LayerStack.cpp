#include "Sgl/LayerStack.h"

namespace sgl
{
	LayerStack::LayerStack() {}

	LayerStack::~LayerStack()
	{
		for (Layer* l : layers)
			delete l;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.push_front(layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.push_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			delete *it;
			layers.erase(it);
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if (it != layers.end()) {
			delete *it;
			layers.erase(it);
		}
	}

	std::deque<Layer*>::iterator LayerStack::begin()
	{
		return layers.begin();
	}

	std::deque<Layer*>::iterator LayerStack::end()
	{
		return layers.end();
	}
}