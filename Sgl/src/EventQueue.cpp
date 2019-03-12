#include "Sgl/Events/EventQueue.h"

namespace sgl
{
	void EventQueue::PushEvent(Event* e)
	{
		events.push_back(e);
	}

	void EventQueue::Pop()
	{
		delete events.front();
		events.pop_front();
	}

	Event* EventQueue::GetNext()
	{
		if(!events.empty())
			return events.front();
		return nullptr;
	}
}