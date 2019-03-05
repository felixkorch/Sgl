#pragma once
#include "Sgl/Events/Event.h"

#include <string>

namespace sgl
{
	class Layer {
	protected:
		std::string debugName;
	public:
		Layer(const std::string& name)
			: debugName(name) {}
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& e) {};

		const std::string& GetName()
		{
			return debugName;
		}
	};
}