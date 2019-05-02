#include "Sgl/Events/EventQueue.h"

namespace sgl
{
    /// The EventQueue is a FIFO queue and stores all the events temporary.
    /// Each update loop the Application will run through it, handle the event and pop them.
    /// This class owns the memory of the events and will free the memory when popped / destructor gets called.
    ///

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
		if (!events.empty())
			return events.front();
		return nullptr;
	}
}