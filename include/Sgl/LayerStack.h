#pragma once
#include "Sgl/Layer.h"
#include <deque>

namespace sgl
{
	class LayerStack {
	private:
		std::deque<Layer*> layers;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		std::deque<Layer*>::iterator begin();
		std::deque<Layer*>::iterator end();
	};
}