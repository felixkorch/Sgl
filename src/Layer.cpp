#include "Sgl/Layer.h"

namespace sgl
{
	Layer::Layer(const std::string& name)
        : debugName(name)
	{
	}

	Layer::~Layer()
	{
		OnDetach();
	}
}
