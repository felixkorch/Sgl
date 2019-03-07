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
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();
	};
}