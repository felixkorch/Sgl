#pragma once
#include "Sgl/Events/Event.h"
#include <deque>

namespace sgl
{
	/// EventQueue is a temporary container for Events which gets distributed by the application.
	/// It is using a FIFO based data structure.

	class EventQueue {
	private:
		std::deque<Event*> events;
	public:
		EventQueue();
		~EventQueue();
		EventQueue(const EventQueue&) = delete;
		void operator=(const EventQueue&) = delete;

		void PushEvent(Event* e);
		void Pop();
		Event* GetNext();
	};
}