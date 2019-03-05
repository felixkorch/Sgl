#pragma once
#include "Sgl/Layer.h"

#include <vector>

namespace sgl
{
	class LayerStack {
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;
	public:
		LayerStack()
		{
			layerInsert = layers.begin();
		}
		~LayerStack()
		{
			for (auto l : layers)
				delete l;
		}

		void PushLayer(Layer* layer)
		{
			layerInsert = layers.emplace(layerInsert, layer);
		}

		void PushOverlay(Layer* overlay)
		{
			layers.emplace_back(overlay);
		}

		void PopLayer(Layer* layer)
		{
			auto it = std::find(layers.begin(), layers.end(), layer);
			if (it != layers.end()) {
				layers.erase(it);
				--layerInsert;
			}
		}

		void PopOverlay(Layer* overlay)
		{
			auto it = std::find(layers.begin(), layers.end(), overlay);
			if (it != layers.end())
				layers.erase(it);
		}

		std::vector<Layer*>::iterator begin()
		{
			return layers.begin();
		}

		std::vector<Layer*>::iterator end()
		{
			return layers.end();
		}
	};
}