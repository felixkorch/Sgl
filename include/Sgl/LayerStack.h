#pragma once
#include "Sgl/Layer.h"
#include <vector>

namespace sgl
{
	class LayerStack {
		std::vector<Layer*> layers;
        unsigned int layerInsertIndex = 0;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
        std::vector<Layer*>& GetLayers()
        {
            return layers;
        }
	};
}