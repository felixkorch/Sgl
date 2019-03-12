#pragma once
#include "Sgl/Events/Event.h"
#include <vector>

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

	class DropCallbackEvent : public Event {
	private:
		std::vector<std::string> paths;
	public:
		DropCallbackEvent(int count, const char** _paths)
		{
			for (int i = 0; i < count; i++) {
				const char* temp = _paths[i];
				paths.emplace_back(std::string(temp));
			}
		}

		const EventType GetEventType() const override
		{
			return EventType::DropCallbackEvent;
		}

		std::vector<std::string> GetPaths()
		{
			return paths;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Files Dropped:" << std::endl;
			for (const auto& p : paths)
				ss << p << std::endl;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::DropCallbackEvent; }
	};
}