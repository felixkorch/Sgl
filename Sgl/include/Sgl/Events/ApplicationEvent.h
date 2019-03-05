#pragma once
#include "Sgl/Events/Event.h"

namespace sgl
{
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		const EventType GetEventType() const override
		{
			return EventType::WindowClose;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent occured!";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::WindowClose; }
	};
}