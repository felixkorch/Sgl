#include "Sgl/Events/EventQueue.h"

namespace sgl
{

	EventQueue::EventQueue() {}

	EventQueue::~EventQueue()
	{
		for (Event* e : events)
			delete e;
	}

	void EventQueue::PushEvent(Event* e)
	{
		events.push_back(e);
	}

	void EventQueue::Pop()
	{
		if (!events.empty()) {
			delete events.front();
			events.pop_front();
		}
	}

	Event* EventQueue::GetNext()
	{
		if(!events.empty())
			return events.front();
		return nullptr;
	}
}