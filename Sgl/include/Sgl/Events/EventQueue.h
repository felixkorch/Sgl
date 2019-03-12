#pragma once
#include "Sgl/Events/Event.h"
#include <deque>

namespace sgl
{
	class EventQueue {
	private:
		std::deque<Event*> events;
	public:
		void PushEvent(Event* e);
		void Pop();
		Event* GetNext();

	};
}