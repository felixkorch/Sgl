#include "Sgl/LayerStack.h"

namespace sgl
{
    /// The Layerstack stores all the layers and can push layers aswell as overlays.
    /// Overlays will always be placed at the back of the vector and the layers on the next available position.
    /// This class owns the memory of the layers and will free the memory when popped / destructor gets called.
    ///

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack()
	{
        for (Layer* layer : layers) {
            layer->OnDetach();
            delete layer;
        }
	}

	void LayerStack::PushLayer(Layer* layer)
	{
        layers.emplace(layers.begin() + layerInsertIndex, layer);
        layerInsertIndex++;
        layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
        layers.emplace_back(overlay);
        overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
        auto it = std::find(layers.begin(), layers.end(), layer);
        if (it != layers.end()) {
            layers.erase(it);
            layerInsertIndex--;
            layer->OnDetach();
            delete layer;
        }
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if (it != layers.end()) {
            layers.erase(it);
            overlay->OnDetach();
            delete overlay;
        }
	}

}